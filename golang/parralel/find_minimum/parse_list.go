package main

import (
    "fmt"
    "sync"
)

func worker(wg *sync.WaitGroup, a []int) {
    defer wg.Done()
    for _, num := range a {
        fmt.Println(num)
    }
}

func main() {
    a := []int {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50}
    var wg sync.WaitGroup

    for i := 0; i < 5; i++ {
        wg.Add(1)
        go worker(&wg, a)
    }
    wg.Wait() // commenting this out and removing sync.WaitGroup altogheter makes this not wait for worker
}
