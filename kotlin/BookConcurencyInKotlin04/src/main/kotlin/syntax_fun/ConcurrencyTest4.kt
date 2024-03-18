package syntax_fun

import kotlinx.coroutines.*

data class Result(var value: Int)

suspend fun task1(result: Result): Result {
    delay(1000) // Simulate some work for 1 second
    result.value += 10
    return result
}

suspend fun task2(result: Result): Result {
    delay(2000) // Simulate some work for 2 seconds
    result.value += 20
    return result
}

suspend fun executeTasks(): List<Result> {
    // Initialize result object
    val result = Result(0)

    // Create a list of tasks
    val tasks = listOf(::task1, ::task2)

    // Launch all tasks asynchronously and gather results
    return tasks.map { task ->
        GlobalScope.async {
            task(result.copy()) // Pass a copy of the result to each task
        }
    }.map { it.await() }
}

suspend fun combineResults(results: List<Result>): Int {
    // Combine or reduce the results (example: sum)
    return results.map { it.value }.sum()
}

suspend fun main() {
    val results = executeTasks()

    // Combine the results
    val combinedResult = combineResults(results)

    println("Combined result: $combinedResult")
}
