# 0-1 knapsack — the two for-loops

The two loops solve: for every item, and for every capacity, keep the better of skipping that item or taking it.

Each item may be taken at most once. The printed answer is the best total value that fits in capacity `W`.

## What the arrays mean

- `w[i]` = weight of item `i`
- `v[i]` = value of item `i`
- `dp[i][j]` = best value using items `1..i` with capacity exactly up to `j`

Row `0` and column `0` stay `0`: no items, or no capacity, yields nothing.

Items and capacities are 1-based. `dp[i][j]` is filled only from the previous row, so item `i` is considered once.

## Outer loop: `for (i = 1; i <= n; i++)`

Bring in one new item at a time.

`i` is the item we are deciding **now**.  
When we compute row `i`, row `i - 1` is already the best packing of the earlier items.

## Inner loop: `for (j = 1; j <= W; j++)`

For that fixed item, try every capacity `j`.

- `j < w[i]`: the item does not fit. Copy the previous answer, `dp[i - 1][j]`.
- Otherwise choose the larger of:
  - skip it: `dp[i - 1][j]`
  - take it: `v[i] + dp[i - 1][j - w[i]]`

The remainder `j - w[i]` was already solved without item `i`.

```text
dp[i][j] = max( skip item i , value(i) + best(items 1..i-1, capacity j-w[i]) )
```

After both loops finish, `dp[n][W]` is the answer.

## Example

```text
echo 3 10 60 20 100 30 120 50 | ./program072
```

Three items, capacity 50:

| item `i` | weight `w[i]` | value `v[i]` |
|----------|---------------|--------------|
| 1 | 10 | 60 |
| 2 | 20 | 100 |
| 3 | 30 | 120 |

Cells shown are the capacities where a choice changes. Values stay flat in between.

| `i \ j` | 0 | 10 | 20 | 30 | 40 | 50 |
|---------|---|----|----|----|----|-----|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | **60** | 60 | 60 | 60 | 60 |
| 2 | 0 | 60 | **100** | **160** | 160 | 160 |
| 3 | 0 | 60 | 100 | 160 | **180** | **220** |

How the interesting cells are chosen:

| cell | skip | take | best |
|------|------|------|------|
| `dp[1][10]` | 0 | `60 + dp[0][0] = 60` | 60 |
| `dp[2][20]` | 60 | `100 + dp[1][0] = 100` | 100 (item 2 alone) |
| `dp[2][30]` | 60 | `100 + dp[1][10] = 160` | 160 (items 1 and 2) |
| `dp[3][40]` | 160 | `120 + dp[2][10] = 180` | 180 (items 1 and 3) |
| `dp[3][50]` | 160 | `120 + dp[2][20] = 220` | **220** (items 2 and 3) |

`dp[2][20]` is 100, item 2 only. Adding item 3 uses the remaining 30 and reaches weight 50 with value `100 + 120 = 220`.

Items 1 and 2 together are only 160. Items 1 and 3 are only 180. The program prints `220`.

## Mental model

- **Outer** = “the first `i` items are available”
- **Inner** = “for capacity `j`, skip item `i` or take it if it fits”

Same shape as the rod-cutting loops in `program060.md`: the outer loop grows the subproblem, the inner loop picks the max of the choices that subproblem allows. Here each item is used at most once, so a take always reads the **previous row**.
