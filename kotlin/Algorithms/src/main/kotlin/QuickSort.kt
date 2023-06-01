fun partition(a : ArrayList<Int>, p : Int, q : Int) : Int {
    val pivot = a[q]
    var k = p
    for (i in p..q) {
        if (a[i] < pivot) {
            a[i] = a[k].also { a[k] = a[i] }
            k++
        }
    }
    a[k] = a[q].also { a[q] = a[k] }
    return k
}

fun quicksort(a : ArrayList<Int>, p : Int, q : Int) {
    if (p < q) {
        val mid = partition(a, p, q)
        quicksort(a, p, mid - 1)
        quicksort(a, mid + 1, q)
    }
}

fun main(args : Array<String>) {
    var a = arrayListOf(7, 3, 8, 2, 6, 4, 5, 1, 9, 0)
    quicksort(a, 0, 9)
    println(a)
}