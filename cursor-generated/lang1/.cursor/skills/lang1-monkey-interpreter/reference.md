# lang1 — Extended reference

Use this file when implementing non-trivial features or debugging interpreter behavior. The main [SKILL.md](SKILL.md) holds workflows and conventions.

## Pipeline contract

1. **Lexer** produces a stream of `Token` with `type` and `literal` (string form as in source).
2. **Parser** consumes tokens and builds `ast_nodes` dataclass instances. Parser errors accumulate in `parser.errors` as human-readable strings.
3. **Evaluator** walks the AST with `monkey_eval(node, env)` and returns a `MonkeyObject` subclass (or propagates `ErrorObj` / `ReturnValue`).

`main.run()` wires: `Lexer` → `Parser.parse_program()` → abort on `parser.errors` → `monkey_eval(program, env)`.

## Statement vs expression (surface language)

- Top-level and block bodies use `_parse_statement()`, which dispatches on `let`, `return`, `class`, or falls through to **expression statement**.
- `if (...) { ... } else { ... }` is parsed as an **expression** (`IfExpression`), so it can appear where any expression is allowed (including as the last expression in a block, which acts like an implicit “return” value in many Monkey-style interpreters).
- **Member assignment** is special-cased: if the parsed expression is a `MemberExpression` and the next token is `=`, the parser builds `AssignStatement(MemberExpression, value)` instead of an expression statement.

## Parser precedence table (`PRECEDENCES`)

Higher number = binds tighter when the parser decides whether to consume an infix/postfix operator.

| Name       | Value | Tokens |
|-----------|-------|--------|
| LOWEST    | 1     | —      |
| EQUALS    | 2     | `==`, `!=` |
| LESSGREATER | 3   | `<`, `>`, `<=`, `>=` |
| SUM       | 4     | `+`, `-` |
| PRODUCT   | 5     | `/`, `*`, `%` |
| PREFIX    | 6     | (used for prefix binding in `_parse_prefix_expression`) |
| CALL      | 7     | `(` call |
| INDEX     | 8     | `[` index |
| MEMBER    | 9     | `.` member |

The loop in `_parse_expression` stops at `;` **or** when current precedence is not less than peek precedence. Adding a new binary operator requires updating this loop’s whitelist of `peek_token` types **and** `PRECEDENCES`.

## Runtime object model (`evaluator.py`)

| Class        | Role |
|-------------|------|
| `IntegerObj`, `StringObj`, `BooleanObj` | Values; booleans use singletons `TRUE`/`FALSE`. |
| `NullObj`   | Singleton `NULL`. |
| `ReturnValue` | Wraps return payload; unwound in `_eval_program` / `_apply_function`. |
| `ErrorObj`  | Carries `message`; short-circuits evaluation when returned. |
| `FunctionObj` | Closure: `parameters`, `body`, `env` (capturing env). |
| `ArrayObj`  | `elements: list[MonkeyObject]`. |
| `BuiltinObj`| Wraps a Python callable `fn(*args)`. |
| `ClassObj`  | `name`, `methods: dict[str, (parameters, body)]`, `env` (defining environment). |
| `InstanceObj` | `klass`, `properties` dict; `get`/`set` for fields. |

**Truthiness** (`_is_truthy`): `NULL` and `FALSE` are false; everything else is true (including `0`).

**Identifier resolution**: `Environment.get` walks `outer` chain; if missing, check `BUILTINS`.

## Classes and `this`

- `class Name { fn method(...) { ... } }` registers a `ClassObj` in the current env under `Name`.
- `new ClassName(args...)` builds an `InstanceObj`, then if `init` exists, runs it with a fresh env: `outer = cls.env`, `this` bound to the instance, parameters bound to evaluated arguments. **Return value of `init` is ignored**; the expression value is the instance.
- `instance.field` / `instance.method`: `_eval_member_expression` loads from instance `properties` first; otherwise, if a class method exists, it returns `FunctionObj(params, body, bound_env)` where `bound_env = Environment(outer=obj.klass.env)` and `bound_env.set("this", obj)`. `_apply_function` then extends that env for the call’s parameter bindings.
- Property assignment: `obj.prop = expr` → `AssignStatement` evaluates object, ensures `InstanceObj`, evaluates RHS, `obj.set(prop, val)`.

## Builtins

| Name   | Arity | Behavior |
|--------|-------|----------|
| `len`  | 1     | String length or array length. |
| `puts` | *     | Prints each arg; returns `NULL`. |
| `first`| 1     | First element of array or `NULL` if empty. |
| `last` | 1     | Last element or `NULL`. |
| `rest` | 1     | New array without first element, or `NULL` if empty. |
| `push` | 2     | New array with element appended (non-mutating). |

## Integer division

`/`` uses **floor division** (`//`) in Python when both operands are integers—document if you change to true float division.

## Common extension points (checklist)

1. **New keyword**  
   - Add `TokenType` and entry in `KEYWORDS`.  
   - Lexer: usually no change if it matches `[a-zA-Z_][...]`.  
   - Parser: dispatch in `_parse_statement` or `_parse_prefix` as appropriate.  
   - AST: new dataclass(es).  
   - Evaluator: branch in `monkey_eval`.

2. **New operator**  
   - Lexer: single or two-character token.  
   - `PRECEDENCES` + `_parse_expression` peek whitelist.  
   - `_eval_infix` / `_eval_prefix` as needed.

3. **New literal type**  
   - Token + lexer + AST literal + `monkey_eval` + possibly string representation in `__repr__` of runtime object.

## Files not to confuse

- `PROMPT.md` — original project notes; not executed.
- `examples.monkey` — sample program; run with `python main.py examples.monkey`.
- `test_results.md` — manual test log if present; not part of the interpreter.
