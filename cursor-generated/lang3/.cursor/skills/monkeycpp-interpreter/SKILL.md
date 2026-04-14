---
name: monkeycpp-interpreter
description: >-
  Guides implementation of the Monkey-style C++ interpreter in lang2 (lexer,
  parser, AST, objects, environment, evaluator, REPL). Use when adding language
  features, fixing parser/eval bugs, or changing the REPL; use when the user
  mentions monkeycpp, lang2, or this interpreter codebase.
---

# Monkey-style C++ interpreter (lang2)

## Architecture

Data flow: **Lexer** (`token.h`, `lexer.*`) → **Parser** (`parser.*`, `ast.h`) → **Evaluator** (`evaluator.*`) using **Environment** (`environment.*`) and **Value** (`object.*`). Builtins: **`builtins.*`**. Entry: **`main.cpp`** (REPL or `argv[1]` file).

| Layer | Responsibility |
|--------|----------------|
| `Token` / `Lexer` | Keywords, literals, `[` `]` `%` `<=` `>=`, etc. |
| `ast.h` | Arrays (`ArrayLiteralExpr`), index (`IndexExpressionExpr`), `ThisExpressionExpr`, … |
| `Parser` | Pratt loop: calls `(`, index `[`, member `.`, assign `=`; precedence **INDEX** before **MEMBER**. |
| `Value` (`object.*`) | `Kind` includes **Array**, **Builtin**; arrays use `shared_ptr<vector<Value>>`. |
| `Environment` | `tryGet` (optional), `get` (throws), `set`, `assign`. |
| `builtins.*` | `len`, `puts`, `first`, `last`, `rest`, `push`; `builtinMap()` + `evalIdentifier` fallback after `tryGet`. |
| `Evaluator` | `applyFunction` **returns last block expression value** (like lang1); `callValue` handles **Builtin**. |

## Project conventions

- **C++17**, sources under `src/`, include path **`-I src`** (or CMake `target_include_directories` on `src`).
- **Match existing style**: minimal comments, straightforward `dynamic_cast` for AST dispatch, `std::shared_ptr` for env and heap objects, `std::unique_ptr` for AST owned by `Program`.
- **Do not** add unrelated refactors or new docs unless asked.

## Critical invariants

1. **AST lifetime**  
   `FunctionObject` / `ClassObject` methods hold **`BlockStatement*`** (and similar) into the parse tree. The REPL keeps **`std::vector<std::unique_ptr<Program>> program_storage`** in `main.cpp` so closures survive across lines. Any new code path that stores AST pointers must keep the owning `Program` alive for as long as those pointers are used.

2. **`this` in methods**  
   `applyFunction(..., this_binding)` sets **`this`** on the function env. Member access requires **`Value::Kind::Instance`**.

3. **Parser pitfalls (already fixed once; preserve behavior)**  
   - **`new Name(arg)`**: After `(`, decide empty vs args using **`curTokenIs(RPAREN)`**, not `peekTokenIs` only—otherwise a single arg is skipped when `peek` is already `)`.  
   - **Empty `()`** in `parseFunctionParameters`: do not advance past `)` twice; parent uses **`expectPeek(LBRACE)`** for method body.  
   - **Class body**: parse methods while **`curTokenIs(FUNCTION)`**, then expect closing **`}`**; stray `;` after `}` is handled by **`parseProgram`** skipping leading `;`.

## How to add a language feature

Work in order; compile after each step.

1. **`token.h` / `token.cpp`**  
   New `TokenType` and `Token::typeName` entry.

2. **`lexer.cpp`**  
   Single-char tokens in `nextToken`; `lookupIdent` for new keywords.

3. **`ast.h`**  
   New node types; statement vs expression; ownership (`unique_ptr` for child AST).

4. **`parser.h` / `parser.cpp`**  
   - New **statement**: branch in `parseStatement`.  
   - New **prefix**: branch in `parsePrefixExpression`.  
   - New **infix**: extend `parseExpression` loop / `peekPrecedence` / `tokenToPrecedence` (e.g. `[` for index = between **CALL** and **MEMBER** or as specified).

5. **`object.h` / `object.cpp`**  
   Extend `Value::Kind` and `inspect()` if a new runtime type is needed (e.g. array for indexing).

6. **`evaluator.cpp`**  
   New `dynamic_cast` branches in `evalStatement` / `evalExpression`; update `callValue` if new callable type.

7. **`main.cpp`**  
   If REPL should print new expression forms, adjust the single-statement print rule (currently skips printing **null**).

## Build

```bash
c++ -std=c++17 -Wall -Wextra -o monkeycpp src/main.cpp src/token.cpp src/lexer.cpp src/parser.cpp src/object.cpp src/environment.cpp src/builtins.cpp src/evaluator.cpp -I src
```

Or CMake: `cmake -B build -S . && cmake --build build` (add new `.cpp` files to `CMakeLists.txt`).

## File map

| File | Role |
|------|------|
| `src/main.cpp` | REPL loop, `program_storage`, parse errors, runtime errors |
| `src/lexer.*` | Scanning |
| `src/parser.*` | Parsing |
| `src/ast.h` | AST definitions only |
| `src/object.*` | Runtime values |
| `src/environment.*` | Scopes |
| `src/evaluator.*` | Execution |
| `src/builtins.*` | Builtin implementations and registry |
| `CMakeLists.txt` | Executable sources list |
