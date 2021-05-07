package main

import (
    "fmt"
)

func worker() int {
    values := []int{4, 20, 0, -11, -10}

    min := values[0]
    for _, v := range values {
        if (v < min) {
            min = v
        }
    }
    return min
}

func main() {
    rez := worker()
    fmt.Println(rez)
}
