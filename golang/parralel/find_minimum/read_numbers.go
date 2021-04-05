package main

import (
    "fmt"
    "io/ioutil"
    "strings"
    "strconv"
)

func check(e error) {
    if e != nil {
        panic(e)
    }
}

func main() {
    fmt.Println("reading file contents...")
    data, err := ioutil.ReadFile("numbers.txt")
    check(err)
    fmt.Println(string(data))
    words := strings.Fields(string(data))
    var numbers []int
    for _, word := range words {
        number, err := strconv.Atoi(word)
        check(err)
        numbers = append(numbers, number)
    }
    fmt.Println(words)
    fmt.Println(numbers)
}