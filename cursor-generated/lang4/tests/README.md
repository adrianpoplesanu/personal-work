# Tests Overview

This folder contains interpreter functional tests for core language/runtime behavior, async/spawn behavior, preemption/cancellation, and delay-based parallel scheduling checks.

## How to run

From `cursor-generated/lang3`:

- Single test:
  - `./main tests/<file>.ad`
- Existing convenience target:
  - `make test-compare`

## Baseline tests

- `test01.ad`
  - Class/method behavior with `spawn` + `join`.
  - Expected: prints updated `dog.age` (`17`).

- `sequential_fib.ad`
  - Sequential CPU baseline.
  - Expected: `92736`.

- `parallel_threads.ad`
  - Parallel CPU baseline with two spawned fib tasks.
  - Expected: `92736`.

- `async_await.ad`
  - Basic `async fn` / `await` + spawn interop.
  - Expected:
    - `7`
    - `42`
    - `100`

## Preemption/cancellation tests

- `preemption_metrics.ad`
  - Verifies task status/metrics/join plumbing.
  - Typical output pattern:
    - status string (`ready` or `running` or `completed`)
    - metrics array length (`4`)
    - task result value
    - final status `completed`

- `preemption_fairness.ad`
  - Long CPU tasks + quick task fairness signal.
  - Expected:
    - quick task prints first (`1`)
    - sum of fib tasks (`35422`)

- `preemption_cancel.ad`
  - Cancellation path for a long-running task.
  - Expected:
    - `true`
    - runtime error: `task cancelled`

## Delay-based parallelism tests

- `parallel_delay_basic.ad`
  - One delayed spawned task.
  - Expected: `11`.

- `parallel_delay_staggered.ad`
  - Multiple tasks with different delays.
  - Expected sum: `6`.

- `parallel_delay_many_tasks.ad`
  - Many short delayed tasks.
  - Expected sum: `36`.

- `parallel_delay_nested_spawn.ad`
  - Parent task spawning child delayed tasks.
  - Expected: `11`.

- `parallel_delay_join_order.ad`
  - Joining in non-completion order.
  - Expected:
    - `30`
    - `10`
    - `20`

- `parallel_delay_async_await.ad`
  - `delay` inside async function.
  - Expected:
    - `11`
    - `42`

- `parallel_delay_spawn_async_mix.ad`
  - Mixed spawn + async/await with delay.
  - Expected: `18`.

- `parallel_delay_status_metrics.ad`
  - Delay with status + metrics checks.
  - Typical output pattern:
    - status string (`ready`/`running`/`completed`)
    - metrics array length (`4`)
    - result (`99`)
    - final status `completed`

- `parallel_delay_fairness_with_sleepers.ad`
  - Sleep-heavy tasks plus quick task.
  - Expected:
    - `1`
    - `9`

- `parallel_delay_cancelled.ad`
  - Cancel one delayed task.
  - Expected:
    - `true`
    - runtime error: `task cancelled`

- `parallel_delay_cancel_many.ad`
  - Cancel multiple delayed tasks.
  - Expected:
    - `true`
    - `true`
    - runtime error: `task cancelled`

## Notes

- Status output can vary slightly based on timing (`ready` vs `running`) for tests that inspect state immediately after spawn.
- Cancellation tests intentionally trigger runtime errors to validate cancellation propagation.
