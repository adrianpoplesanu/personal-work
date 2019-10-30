package main

import (
    "fmt"
    "net/http"
)

func main() {
    http.Handle("/", http.StripPrefix("/", http.FileServer(http.Dir("/home/ubuntu/Documents/git-projects/personal-work/golang/server4/"))))
    if err := http.ListenAndServe(":8090", nil); err != nil {
        fmt.Print(err)
    }
}
