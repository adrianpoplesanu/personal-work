package main

import (
    "fmt"
    "crypto/sha1"
)

func main() {
    text := "ai un mare noroc, ghinioane deloc"
    hash := sha1.New()
    hash.Write([]byte(text))
    bs := hash.Sum(nil)
    fmt.Println(text)
    fmt.Printf("%x\n", bs)
}