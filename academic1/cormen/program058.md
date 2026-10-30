# `memoized_cut_rod` — top-down with a cache

The function solves the same rod-cutting recurrence as `program057.cpp`, and writes each length’s best revenue into `r` the first time that length is solved. Later calls for that length return the stored value.

`main` asks for length `4`. With the usual prices the program prints `10`.

## What the arrays mean

- `a[i]` = price of a piece of length `i`
- `r[j]` = best revenue for a rod of length `j`, or `-1` if that length has not been solved yet

`memoized_cut_rod` sets `r[0] … r[n]` to `-1`, then calls the helper on `n`.

## The helper: `memoized_cut_rod_aux`

Three steps, in order.

1. **Cache hit.** If `r[n] >= 0`, that length is already solved. Return it.
2. **Solve it.**
   - Length `0` is worth `0`.
   - Otherwise try every first piece `i` from `1` to `n`. A piece of length `i` pays `a[i]`, and the remainder `n - i` is the same problem, solved by a recursive call.
3. **Store it.** Write the best of those choices into `r[n]` and return it.

```text
revenue(n) = max over i = 1..n of  price(i) + revenue(n - i)
revenue(0) = 0
```

The first time a length is reached, the recursion does the work. Every later request for that length stops at step 1.

## Call order for length 4

Prices `1, 5, 8, 9`. The first recursive branch always tries a first cut of `1`, so it walks `4 → 3 → 2 → 1 → 0` and fills every smaller length before the other cuts of length `4` run.

| call | what happens | `r` after the call returns |
|------|----------------|----------------------------|
| `aux(0)` | base case, `q = 0` | `r[0] = 0` |
| `aux(1)` | only `i = 1`: `1 + r[0] = 1` | `r[1] = 1` |
| `aux(2)` | `i = 1`: `1 + 1 = 2`; `i = 2`: `5 + r[0] = 5` | `r[2] = 5` |
| `aux(3)` | `i = 1`: `1 + 5 = 6`; `i = 2`: `5 + r[1] = 6`; `i = 3`: `8 + 0 = 8` | `r[3] = 8` |
| `aux(4)` | `i = 1`: `1 + 8 = 9`; `i = 2`: `5 + r[2] = 10`; `i = 3`: `8 + 1 = 9`; `i = 4`: `9 + 0 = 9` | `r[4] = 10` |

Inside `aux(4)`, the calls for lengths `2`, `1`, and `0` are cache hits. They were stored on the way down the first branch.

Best revenue for length 4 is `10`: a first piece of length `2` plus another piece of length `2`. This program stores only the revenue. Reconstructing the cuts is `program060.cpp`.

## Mental model

- `r[j] == -1` means “not solved yet”
- a recursive call either returns the stored answer or computes it, then stores it
- the left spine (first cut `1` all the way down) fills `r[0] … r[n - 1]` before the other first cuts of length `n` are tried

`bottom_up_cut_rod` in `program059.cpp` fills the same `r[1] … r[n]` with a loop from short rods to long ones. This version fills an entry the first time some longer rod asks for it. Both print `10` for length `4`.

## Complexity

Time is Θ(n²). Space is Θ(n).

**Time.** Lengths `0` through `n` are `n + 1` different subproblems. The test `r[j] >= 0` fails once per length, so the loop that tries every first cut runs once per length.

Length `j` tries `j` cuts. After the first visit, a recursive call returns the stored revenue in constant time, so each try costs Θ(1). Charge that loop to length `j`, and do not charge it again to the caller.

```text
work = Θ(1) + Θ(2) + … + Θ(n) = Θ( n(n + 1) / 2 ) = Θ(n²)
```

Initialization of `r` is Θ(n) and is absorbed by Θ(n²).

For the length-4 walk above the loops run `1 + 2 + 3 + 4 = 10` times, and `4 · 5 / 2 = 10`.

The left spine reaches every smaller length, so this program always does the full sum. It does not skip any `j`.

**Space.** `r` holds `n + 1` integers, Θ(n). The deepest recursion is the chain of first cuts of length `1`, which is `n` frames, also Θ(n).

**Without the cache.** `cut_rod` in `program057.cpp` uses the same recurrence and never stores an answer. Let `T(n)` be the number of calls on a rod of length `n`:

```text
T(0) = 1
T(n) = 1 + T(0) + T(1) + … + T(n - 1)
```

That solves to `T(n) = 2ⁿ`. Check: `T(0) = 1 = 2⁰`, and if `T(j) = 2ʲ` for every `j < n`, then

```text
T(n) = 1 + (2⁰ + 2¹ + … + 2ⁿ⁻¹) = 1 + (2ⁿ - 1) = 2ⁿ
```

The cache replaces those `2ⁿ` calls with `n(n + 1) / 2` tries.
