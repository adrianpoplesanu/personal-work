package main

import(
    "fmt"
)

func main() {
    fmt.Println("running secvential find minimum")
    a := []int{1, 2, 3, 4, -5, 6}
    min := a[0]
    for _, element := range(a) {
        if (element < min) {
            min = element
        }
    }
    fmt.Println(min)
}