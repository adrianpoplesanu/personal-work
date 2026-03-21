# Monkey Language - Test Results

| # | Source | Expected | Actual | Status |
|---|--------|----------|--------|--------|
| 1 | `1 + 2 * 3` | `7` | `7` | PASS |
| 2 | `let x = 10; x` | `10` | `10` | PASS |
| 3 | `let x = 5; let y = 10; x + y` | `15` | `15` | PASS |
| 4 | `"hello" + " " + "world"` | `hello world` | `hello world` | PASS |
| 5 | `let add = fn(a, b) { a + b }; add(3, 4)` | `7` | `7` | PASS |
| 6 | `let factorial = fn(n) { if (n < 2) { 1 } else { n * factorial(n - 1) } }; factorial(5)` | `120` | `120` | PASS |
| 7 | `if (10 > 5) { "yes" } else { "no" }` | `yes` | `yes` | PASS |
| 8 | `!true` | `false` | `false` | PASS |
| 9 | `-5` | `-5` | `-5` | PASS |
| 10 | `let arr = [1, 2, 3]; arr[1]` | `2` | `2` | PASS |
| 11 | `len("hello")` | `5` | `5` | PASS |
| 12 | `let adder = fn(x) { fn(y) { x + y } }; let addTwo = adder(2); addTwo(5)` | `7` | `7` | PASS |
| 13 | `return 42` | `42` | `42` | PASS |
| 14 | `5 % 3` | `2` | `2` | PASS |
| 15 | `10 == 10` | `true` | `true` | PASS |
| 16 | `10 != 9` | `true` | `true` | PASS |

**Result: 16/16 tests passed**
