package main

import (
    "fmt"
    "time"
    "os/exec"
)

func worker1(id string) {
    out, err := exec.Command("ls", "-la").Output()
    if (err != nil) {
        fmt.Println(err)
    } else {
        fmt.Println(id + string(out))
    }
    fmt.Println("worker1" + id)
}

func worker2() {
    fmt.Println("worker2")
}

func main() {
    fmt.Println("running concurent threads")

    go worker1("a")
    go worker1("b")
    go worker1("c")
    go worker1("d")
    go worker1("e")
    go worker1("d")

    worker2()
    time.Sleep(time.Millisecond * 500)
}
