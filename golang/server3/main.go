package main

import (
    "fmt"
    "io/ioutil"
    "strings"
)

func main() {
    data, err := ioutil.ReadFile("api_client_key.txt")
    if err != nil {
        fmt.Println(err)
    }
    fmt.Println("read:")
    fmt.Println(strings.TrimSuffix(string(data), "\n"))
}
