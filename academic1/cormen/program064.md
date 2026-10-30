# Matrix-chain parenthesization

`matrix_chain_order` finds the cheapest way to parenthesize a product of matrices. `print_optimal_parens` prints that parenthesization.

The matrices are not multiplied. Only the parenthesization is printed. The minimum number of scalar multiplications is stored in `m[1][n]` and left unprinted.

## Input

The first integer is `n`, the number of matrices. The next `n + 1` integers are the dimensions `p[0] … p[n]`.

Matrix `Ai` has dimensions `p[i - 1] × p[i]`. Neighboring matrices are compatible: `Ai` is `p[i - 1] × p[i]` and `A(i+1)` is `p[i] × p[i + 1]`.

## What the arrays mean

- `p[i]` = a shared dimension
- `m[i][j]` = minimum scalar multiplications needed for the product `Ai … Aj`
- `s[i][j]` = the split index `k` that achieves that minimum. The product is `(Ai … Ak)(A(k+1) … Aj)`

`m[i][i]` is `0`: a single matrix needs no multiplication. `s[i][i]` is never used.

## `matrix_chain_order`

Chains are solved from short to long, so a split always reads answers that are already filled.

### Length 1: `for (i = 1; i <= n; i++)`

Set the diagonal. `m[i][i] = 0`.

### Chain length: `for (l = 2; l <= n; l++)`

`l` is the number of matrices in the chain being solved **now**. Length `2` is a single product of two matrices. Length `n` is the full product.

### Start index: `for (i = 1; i <= n - l + 1; i++)`

`i` is the first matrix of this chain. The last matrix is `j = i + l - 1`. The chain is `Ai … Aj`.

`m[i][j]` starts at `INT_MAX`, then every legal split tries to lower it.

### Split: `for (k = i; k <= j - 1; k++)`

Cut the chain after matrix `Ak`.

- Left chain `Ai … Ak` already costs `m[i][k]`
- Right chain `A(k+1) … Aj` already costs `m[k + 1][j]`
- The two results are matrices of size `p[i - 1] × p[k]` and `p[k] × p[j]`. Multiplying them costs `p[i - 1] * p[k] * p[j]`

```text
q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
```

If `q` is smaller than `m[i][j]`, store it and set `s[i][j] = k`.

After the three loops, `m[1][n]` is the minimum cost of `A1 … An`, and `s` records a split for every chain of length at least `2`.

## `print_optimal_parens`

`main` calls `print_optimal_parens(s, 1, n)`.

- `i == j`: the chain is one matrix. Print `Ai`.
- Otherwise the best split is `k = s[i][j]`. Print `(`, the left chain `i … k`, the right chain `k + 1 … j`, then `)`.

There are no spaces. A chain of six matrices comes out as one parenthesized string.

## Example

```text
echo 6 30 35 15 5 10 20 25 | ./program064
```

Six matrices:

| matrix | dimensions |
|--------|------------|
| `A1` | 30 × 35 |
| `A2` | 35 × 15 |
| `A3` | 15 × 5 |
| `A4` | 5 × 10 |
| `A5` | 10 × 20 |
| `A6` | 20 × 25 |

`m[i][j]` after the loops. Rows are `i`, columns are `j`. The diagonal is the length-1 base case.

| `i \ j` | 1 | 2 | 3 | 4 | 5 | 6 |
|---------|---|------|------|------|-------|-------|
| 1 | 0 | 15750 | 7875 | 9375 | 11875 | **15125** |
| 2 |  | 0 | 2625 | 4375 | 7125 | 10500 |
| 3 |  |  | 0 | 750 | 2500 | 5375 |
| 4 |  |  |  | 0 | 1000 | 3500 |
| 5 |  |  |  |  | 0 | 5000 |
| 6 |  |  |  |  |  | 0 |

The split table `s[i][j]`:

| `i \ j` | 2 | 3 | 4 | 5 | 6 |
|---------|---|---|---|---|---|
| 1 | 1 | 1 | 3 | 3 | **3** |
| 2 |  | 2 | 3 | 3 | 3 |
| 3 |  |  | 3 | 3 | 3 |
| 4 |  |  |  | 4 | 5 |
| 5 |  |  |  |  | 5 |

The full product is the cell `m[1][6]`. Each `k` is one place to cut `A1 … A6`:

| `k` | left + right + final multiply | cost |
|-----|-------------------------------|------|
| 1 | `0 + 10500 + 30·35·25` | 36750 |
| 2 | `15750 + 5375 + 30·15·25` | 32375 |
| 3 | `7875 + 3500 + 30·5·25` | **15125** |
| 4 | `9375 + 5000 + 30·10·25` | 21875 |
| 5 | `11875 + 0 + 30·20·25` | 26875 |

`s[1][6] = 3`, so the top split is `(A1 A2 A3)(A4 A5 A6)`. The printer then follows `s` on each side:

| call | `s[i][j]` | prints |
|------|-----------|--------|
| `(1, 6)` | 3 | `( … )` around chains 1–3 and 4–6 |
| `(1, 3)` | 1 | `( A1  … )` around chains 1 and 2–3 |
| `(2, 3)` | 2 | `(A2A3)` |
| `(4, 6)` | 5 | `( … A6)` around chains 4–5 and 6 |
| `(4, 5)` | 4 | `(A4A5)` |

The program prints:

```text
((A1(A2A3))((A4A5)A6))
```

That parenthesization costs `15125` scalar multiplications. The number stays in `m[1][6]`.

## Mental model

- **Length loop** = “solve every chain of `l` matrices”
- **Start loop** = “this chain begins at `Ai`”
- **Split loop** = “cut after `Ak` and keep the cheapest cut”
- **Printer** = “read `s` from the outside in and put parentheses around each chosen cut”

## Complexity

Time is Θ(n³). Space is Θ(n²).

**Time.** There are Θ(n²) chains `Ai … Aj` with `1 ≤ i ≤ j ≤ n`. A chain of length `l` tries `l - 1` splits, and each split is Θ(1) because both subchains are already in `m`. Summing over chain length:

```text
work = Σ_{l=2..n} (n - l + 1) · (l - 1) = Θ(n³)
```

For `n = 6` the split loop runs `5·1 + 4·2 + 3·3 + 2·4 + 1·5 = 35` times.

**Space.** `m` and `s` are `n × n` tables, Θ(n²). `print_optimal_parens` recurses once per matrix along any root-to-leaf path, so the call stack is O(n).
