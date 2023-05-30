fun merge(left : List<Int>, right : List<Int>) : List<Int> {
    val result = mutableListOf<Int>()
    var i = 0
    var k = 0
    while (i < left.size && k < right.size) {
        if (left[i] < right[k]) {
            result.add(left[i++])
        } else {
            result.add(right[k++])
        }
    }
    while (i < left.size) {
        result.add(left[i++])
    }
    while (k < right.size) {
        result.add(right[k++])
    }
    return result
}

fun merge_sort(a : List<Int>) : List<Int> {
    if (a.size > 1) {
        val mid = a.size / 2;
        val left = a.subList(0, mid)
        val right = a.subList(mid, a.size)
        return merge(merge_sort(left), merge_sort(right))
    }
    return a
}

fun main(args: Array<String>) {
    var numbers = listOf(7, 4, 6, 2, 8, 3, 9, 1, 5, 0)
    val sorted = merge_sort(numbers)
    println(sorted)
}