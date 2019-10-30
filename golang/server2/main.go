package main

import (
    "fmt"
    "log"
    "net/http"
    "os"
)

func hello(w http.ResponseWriter, req *http.Request) {
    fmt.Fprintf(w, "hello endpoint go lang")
    log.Println("/hello enpoint hit")
}

func main() {
    f, err := os.OpenFile("testlogfile", os.O_RDWR | os.O_CREATE | os.O_APPEND, 0666)
    if err != nil {
        log.Fatalf("error opening file: %v", err)
    }
    defer f.Close()

    log.SetOutput(f)
    log.Println("Server started!")

    http.HandleFunc("/hello", hello)
    http.ListenAndServe(":8090", nil)
}
