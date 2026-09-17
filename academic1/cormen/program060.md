# `extended_bottom_up_cut_rod` — the two for-loops

The two loops solve: for every rod length, try every first cut and keep the best.

## What the arrays mean

- `a[i]` = price of a piece of length `i`
- `r[j]` = best revenue for a rod of length `j`
- `s[j]` = best first cut length for a rod of length `j` (the “extended” part)

## Outer loop: `for (j = 1; j <= n; j++)`

Build answers from short rods up to long ones.

`j` is the rod length we are solving **now**.  
When we compute `r[j]`, every smaller `r[0] … r[j-1]` is already known.

## Inner loop: `for (i = 1; i <= j; i++)`

For that fixed length `j`, try every possible first piece:

- Cut off a piece of length `i` → get `a[i]`
- Remaining length is `j - i` → already optimally solved as `r[j - i]`
- Total: `a[i] + r[j - i]`

So the candidate for cut `i` is:

```text
revenue = price(first piece i) + best revenue(remainder j-i)
```

If that candidate beats the current best `q`, update:
- `q` = that revenue  
- `s[j] = i` (remember: first cut should be `i`)

After the inner loop finishes, `r[j] = q`.

## Tiny example (`n = 4`, prices `1,5,8,9,…`)

| `j` | tries (`i`) | best | `s[j]` |
|-----|-------------|------|--------|
| 1 | `i=1`: `1+r[0]=1` | 1 | 1 |
| 2 | `i=1`: `1+r[1]=2`; `i=2`: `5+r[0]=5` | **5** | 2 |
| 3 | `i=1`: `1+5=6`; `i=2`: `5+1=6`; `i=3`: `8+0=8` | **8** | 3 |
| 4 | `i=1`: `1+8=9`; `i=2`: `5+5=10`; `i=3`: `8+1=9`; `i=4`: `9+0=9` | **10** | 2 |

So for length 4, best first cut is 2 (`s[4]=2`), then remaining 2 also wants cut 2 → pieces `2 2`.

## Mental model

- **Outer** = “solve length `j`”
- **Inner** = “among all first cuts `1…j`, pick the max”

Same structure as `bottom_up_cut_rod` in `program059.cpp`; the only extra is storing `s[j]` so `print_cut_rod_solution` can reconstruct the cuts.
