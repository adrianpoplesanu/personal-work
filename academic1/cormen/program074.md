# Huffman codes

`huffman` builds a prefix code by merging the two least frequent trees until one tree remains. `print_codes` walks that tree and prints each character's code.

A left edge is the bit `0`. A right edge is the bit `1`. The path from the root to a leaf is that character's code.

## Input

The first integer is `n`, the number of characters. The next `n` pairs are a character and its frequency.

```text
echo 6 a 45 b 13 c 12 d 16 e 9 f 5 | ./program074
```

## What a node means

- `frequency` = the character's frequency, or the sum of the frequencies in a merged subtree
- `character` = the symbol stored at a leaf. An internal node stores `'\0'`
- `left` / `right` = the two subtrees. Both are null at a leaf

The queue `q` is a 1-based min-heap of node pointers, ordered by `frequency`. `q[1]` is the least frequent tree. `PARENT(i)`, `LEFT(i)`, and `RIGHT(i)` are the usual heap index formulas: `i / 2`, `2i`, and `2i + 1`.

## Building the heap

`read` writes the `n` leaves into `q[1] … q[n]`. `build_min_heap` then walks from index `n / 2` down to `1` and calls `min_heapify` at each index, so the array satisfies the min-heap property before the first merge.

## `huffman`

`size` is the number of trees currently in the heap. It starts at `n`. The loop itself runs `n - 1` times, once per merge, and does not use `size` as its bound.

Each pass:

1. `x = extract_min(q)` — the least frequent tree
2. `y = extract_min(q)` — the next least frequent tree
3. Allocate `z` with `z.frequency = x.frequency + y.frequency`, `z.left = x`, `z.right = y`
4. `insert(q, z)` — put the merged tree back

`extract_min` keeps `q[1]`, moves the last entry to the root, shrinks `size`, and restores the heap from the root. `insert` appends the new node and swaps it upward while its parent has a larger frequency.

After `n - 1` merges, one tree is left. The final `extract_min` returns its root.

## `print_codes`

The walk starts at the root with an empty `code` buffer.

- A leaf at depth `0` is the only character. Print `character 0`.
- Any other leaf ends the buffer and prints the character followed by the bits gathered on the way down.
- An internal node writes `'0'` and recurses left, then writes `'1'` and recurses right.

Every character is a leaf, so no code is a prefix of another code.

## Example

Six characters:

| character | frequency |
|-----------|-----------|
| a | 45 |
| b | 13 |
| c | 12 |
| d | 16 |
| e | 9 |
| f | 5 |

`build_min_heap` leaves the array as `f5, e9, c12, d16, b13, a45`. The root is `f`.

The first node taken out of a pair becomes the left child.

| step | left `x` | right `y` | new frequency | heap afterward |
|------|----------|-----------|---------------|----------------|
| 1 | f:5 | e:9 | 14 | c12, b13, a45, d16, 14 |
| 2 | c:12 | b:13 | 25 | 14, d16, a45, 25 |
| 3 | 14 | d:16 | 30 | 25, a45, 30 |
| 4 | 25 | 30 | 55 | a45, 55 |
| 5 | a:45 | 55 | 100 | 100 |

The finished tree:

```text
                 100
               /     \
             a:45     55
                    /    \
                  25      30
                 /  \    /  \
               c:12 b:13 14  d:16
                        /  \
                      f:5  e:9
```

| character | path | code | bits | frequency × bits |
|-----------|------|------|------|------------------|
| a | left | 0 | 1 | 45 |
| c | right, left, left | 100 | 3 | 36 |
| b | right, left, right | 101 | 3 | 39 |
| f | right, right, left, left | 1100 | 4 | 20 |
| e | right, right, left, right | 1101 | 4 | 36 |
| d | right, right, right | 111 | 3 | 48 |

The weighted cost is `45 + 36 + 39 + 20 + 36 + 48 = 224`. That is the number of bits used to encode one file with these frequencies. Frequent `a` sits next to the root. Rare `f` and `e` were merged first, so they sit deepest.

`print_codes` meets the leaves in walk order:

```text
a 0
c 100
b 101
f 1100
e 1101
d 111
```

In this example every frequency compared during a merge is unique, so the pairing does not depend on how the heap breaks ties. When two frequencies are equal, either tree may come out first. Both results are optimal prefix codes. The bits can differ.

## Mental model

- The heap holds the trees built so far. The cheapest tree is at the root.
- One merge deletes two trees and inserts one tree whose frequency is their sum.
- A left edge appends `0` and a right edge appends `1`.
- Rare characters are merged early and end up deep. Frequent characters stay close to the root and keep short codes.

## Complexity

Time is Θ(n log n). Space is Θ(n).

**Time.** `build_min_heap` is Θ(n). The merge loop runs `n - 1` times. Each pass extracts twice and inserts once. The heap never holds more than `n` trees, so each of those operations is Θ(log n).

```text
work = Θ(n) + (n - 1) · Θ(log n) = Θ(n log n)
```

`print_codes` visits each of the `2n - 1` tree nodes once, which is Θ(n).

For the six-character example the merge loop runs 5 times.

**Space.** The heap stores at most `n` pointers. The tree has `n` leaves and `n - 1` internal nodes. The code buffer holds at most `n - 1` bits, and the `print_codes` recursion is that deep on the longest code.
