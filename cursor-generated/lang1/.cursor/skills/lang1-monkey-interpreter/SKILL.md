---
name: lang1-monkey-interpreter
description: >-
  Authors and extends the lang1 Monkey-style interpreter (Python lexer, Pratt
  parser, tree-walking evaluator with closures, arrays, builtins, and classes).
  Use when editing or adding features in cursor-generated/lang1, when the user
  mentions Monkey/REPL/tokens/parser/evaluator/AST for this project, or when
  implementing language semantics matching this codebase.
---

# lang1 Monkey-style interpreter

This project is a **small interpreter in Python** for a **Monkey-inspired** language: a REPL and file runner with integers, strings, booleans, `let`, `fn`, calls, `if`/`else`, `return`, arrays and indexing, comparison and arithmetic operators, **classes** with `new`, `this`, methods, and instance fields. The implementation follows the classic book-style split: **tokens → lexer → AST → parser → evaluator**, with **no bytecode VM**—execution is recursive AST interpretation.

Read [reference.md](reference.md) for precedence tables, object model details, class/`this` semantics, builtins, and extension checklists beyond the day-to-day workflow below.

---

## When this skill applies

- Any change under `lang1/` that touches **language behavior** or **interpreter internals**.
- Adding **syntax**, **operators**, **statements**, **runtime values**, or **builtins**.
- Debugging **parse errors** (`parser.errors`), **runtime errors** (`ErrorObj`), or **scoping** (closures, `this`, class envs).
- Keeping new code **consistent** with existing patterns (dataclass AST nodes, `MonkeyObject` subclasses, `Environment`).

---

## Project layout and responsibilities

| File | Responsibility |
|------|------------------|
| `tokens.py` | `TokenType` enum, `KEYWORDS` map, `Token` (type + literal string). |
| `lexer.py` | `Lexer`: single-pass character scanning, `next_token()`. |
| `ast_nodes.py` | AST as `@dataclass` types under `Expression` / `Statement` / `Node`. |
| `parser.py` | `Parser`: two-token lookahead, Pratt-style expression parsing, statement parsing. |
| `evaluator.py` | `monkey_eval`, runtime objects (`*Obj`), `Environment`, builtins. |
| `main.py` | `run()`, REPL, `run_file()`; glues lexer → parser → evaluator. |
| `examples.monkey` | Example programs (factorial, higher-order functions, classes). |

Run from the `lang1` directory:

```bash
python main.py                 # REPL
python main.py examples.monkey # execute file
```

There is **no** `requirements.txt`; the code uses the Python standard library only (`enum`, `dataclasses`, `typing`).

### Surface syntax (what programs look like)

Reserved words: `let`, `fn`, `true`, `false`, `if`, `else`, `return`, `class`, `new`, `this`.

- **Bindings**: `let name = expr;` (trailing semicolon often accepted when present).
- **Functions**: `fn(a, b) { stmts }` — body is a brace block; last expression value can propagate from blocks used as `if` branches.
- **Calls**: `f(arg1, arg2)`.
- **Conditionals**: `if (cond) { ... } else { ... }` — parentheses around condition are parsed as grouped expression.
- **Arrays**: `[1, 2, 3]`, index `arr[i]`.
- **Operators**: `+ - * / %`, comparisons `== != < > <= >=`, unary `!` and `-`, logical truthiness per evaluator (not short-circuit `&&`/`||` in the grammar—use `if`).
- **Classes**:

```text
class Dog {
    fn init(name, age) { this.name = name; this.age = age; }
    fn bark() { puts("woof"); }
}
let d = new Dog("Rex", 5);
d.bark();
d.name;
```

Instance construction runs `init` if defined; **fields** are dynamic properties on the instance (`this.x = ...` in `init`, or external assignment `obj.field = expr` via `AssignStatement`).

---

## Architectural rules (do not violate casually)

1. **Single source of truth for keywords**  
   Identifiers are classified in the lexer via `KEYWORDS` in `tokens.py`. Adding a reserved word means adding both a `TokenType` and a `KEYWORDS` entry.

2. **AST shape**  
   Nodes are plain dataclasses with optional fields defaulting to `None` or empty lists. Prefer **new node types** over overloading existing ones with sentinel meanings unless the language truly stays uniform.

3. **Parser errors are non-fatal lists**  
   `Parser.errors` collects strings; `parse_program` still returns a `Program` when possible. `main.run` prints errors and skips evaluation—mirror this if you add alternate entrypoints.

4. **Evaluation returns `MonkeyObject`**  
   `monkey_eval` always returns some `MonkeyObject` (often `NULL`). Use `ErrorObj` for user-visible failures; use `ReturnValue` only to implement `return` unwinding.

5. **Environment chain**  
   Lexical scoping: `Environment(outer=...)` for function bodies and method bodies. Builtins are **not** stored in every env—they are resolved in `_eval_identifier` after env lookup fails.

6. **Closures**  
   `FunctionObj` stores the **defining** `env`. Applying a function creates `extended_env = Environment(outer=fn.env)` and binds parameters there.

---

## Lexer conventions (`lexer.py`)

- **State**: `source`, `pos`, current char `ch`. `_read_char` advances; `_peek_char` does not consume.
- **Whitespace**: skipped between tokens via `_skip_whitespace` (space, tab, newlines).
- **Identifiers**: start with letter or `_`, continue with alphanumeric/`_`; look up `KEYWORDS` to distinguish keywords from `IDENT`.
- **Numbers**: contiguous digits only (no floats in this language).
- **Strings**: double quotes `"..."`; `_read_string` returns **unescaped** content between quotes (no escape sequences in the lexer as written—be explicit if you add them).
- **Two-char operators**: `==`, `!=`, `<=`, `>=` use `_peek_char` after the first character.
- **Unknown char**: emit `ILLEGAL` with that character as literal and advance.

When adding a token: implement the branch in `next_token`, add `TokenType`, and if it is alphabetic, add to `KEYWORDS` **only** if it should be reserved.

---

## AST conventions (`ast_nodes.py`)

- **Base types**: `Node` → `Expression` / `Statement`. Everything is a dataclass for straightforward inspection and debugging.
- **Naming**: AST types use suffixes `*Literal`, `*Expression`, `*Statement`, `BlockStatement`, `Program`.
- **Class-related nodes**: `ClassStatement`, `MethodDef`, `ThisExpression`, `MemberExpression`, `NewExpression`, `AssignStatement` (for `obj.prop = expr`).

Keep fields **typed** with `Optional[...]` where the parser may leave them unset on error paths.

---

## Parser conventions (`parser.py`)

- **Initialization**: Reads two tokens (`cur_token`, `peek_token`) so both are valid before parsing.
- **Statements**: `_parse_statement` switches on `LET`, `RETURN`, `CLASS`; otherwise expression statement (possibly rewritten to `AssignStatement`).
- **Expressions**: Pratt parsing with `_parse_expression(precedence)`, `_parse_prefix`, infix/postfix via precedence comparison with `peek_token`.
- **`_expect_peek(t)`**: If `peek_token` is `t`, advances and returns `True`; else records error and returns `False`. Many statement parsers return `None` on failure—do not swallow errors silently without appending to `errors`.
- **Member / call / index**: After parsing left-hand expression, higher-precedence operators attach `CallExpression`, `IndexExpression`, or `MemberExpression` depending on `peek_token`.

**Critical**: The `while` loop in `_parse_expression` explicitly allows only certain `peek_token` types for infix continuation. **New infix operators must be added to that set** and to `PRECEDENCES`.

**Precedence** names (`LOWEST` … `MEMBER`) are defined at module top; see [reference.md](reference.md) for the full table.

---

## Evaluator conventions (`evaluator.py`)

### Runtime types

- Subclass `MonkeyObject` for every runtime value. Prefer `__slots__` on concrete classes for clarity and small footprint.
- **Singletons**: `TRUE`, `FALSE`, `NULL`—use identity where the code compares `obj is TRUE` etc.
- **String form**: `__repr__` of objects is what the REPL prints when a line evaluates to that value.

### Core dispatch

`monkey_eval` is a large `isinstance` chain. When adding a node type:

1. Add the AST class in `ast_nodes.py`.
2. Add a branch in `monkey_eval` (and helper functions if the case is large).
3. Ensure **errors** from subexpressions propagate (`ErrorObj` short-circuit).

### Control flow

- **Program** vs **block**: `_eval_program` unwraps `ReturnValue` to the bare value at top level; `_eval_block` propagates `ReturnValue` and `ErrorObj` without unwrapping return at block end inside functions.
- **`if`**: `IfExpression` evaluates condition with `_is_truthy`, then consequence or alternative block.

### Functions and calls

- **Literals** `fn(...) { ... }` produce `FunctionObj` with current `env`.
- **`_apply_function`**: For `FunctionObj`, extend env with parameters, eval body; if result is `ReturnValue`, return `.value`. For `BuiltinObj`, call the Python `fn`.

### Arrays and index

- Literals build `ArrayObj`; index requires `IntegerObj` index in range—otherwise `NULL` (no out-of-range error).

### Classes (high level)

- `ClassStatement` builds `ClassObj` with method table `name → (params, body)` and `env` = defining environment.
- `new ClassName(args)` constructs `InstanceObj`, optionally runs `init` with `this` bound.
- `MemberExpression` reads instance properties or returns a **bound method** as `FunctionObj` with `this` in env.
- See [reference.md](reference.md) for precise `this` and `init` behavior.

### Builtins

Register in `BUILTINS` dict mapping name → `BuiltinObj(callable)`. Implement arity and type checks inside the Python function; return `ErrorObj` on misuse.

---

## Style and quality bar for new code

- **Match existing imports**: top-level `from tokens import ...`, `from ast_nodes import ...` with explicit lists where the file already does.
- **Naming**: snake_case functions, PascalCase classes, short private helpers `_eval_*`.
- **No gratuitous abstractions**: avoid introducing a visitor framework or IR unless the user asks; the codebase is intentionally direct.
- **Comments**: Only where non-obvious (e.g. parser quirks). Do not add banner comments or restate the language spec in every file.
- **Tests**: There is no automated test runner in-repo; if you add tests, prefer a small `pytest` or `unittest` module without changing the default `main.py` behavior unless requested.

---

## End-to-end workflow for a new language feature

1. **Specify behavior** on paper (syntax, evaluation order, errors).
2. **Tokens**: `TokenType`, lexer branch, `KEYWORDS` if reserved.
3. **AST**: new dataclasses; wire `parser` imports.
4. **Parser**: statement and/or prefix/infix parsing; update precedence and infix whitelist.
5. **Evaluator**: `monkey_eval` + helpers; extend `MonkeyObject` if new runtime type.
6. **Example**: add a line or function to `examples.monkey` demonstrating the feature.
7. **Manual run**: `python main.py examples.monkey` and REPL spot checks.

---

## Pitfalls specific to this codebase

- **Semicolons**: Often optional; parser looks at `peek_token` for `SEMICOLON` but does not require it everywhere. Do not assume C-style mandatory semicolons.
- **`if` as expression**: Branches are blocks; the **value** of an `if` expression is the value of the evaluated block (last statement’s value in expression-oriented blocks).
- **Division by zero**: Integer `/` and `%` return `ErrorObj("division by zero")`.
- **Method lookup vs field**: Instance `properties` shadow nothing; method binding uses class methods when property not set—see evaluator.
- **Parser loop whitelist**: Forgetting to add a new infix token to `_parse_expression`’s `while` loop causes the new operator to be **ignored** (parse ends early).

---

## Additional documentation

- For deeper detail: [reference.md](reference.md) (precedence matrix, runtime tables, class semantics, builtins).
- Original notes and intent: `PROMPT.md` in the project root (not authoritative for implementation details).
