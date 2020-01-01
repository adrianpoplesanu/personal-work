package main
import (
    "fmt"
    "net/url"
)

func main() {
    // this is just an URL parser, not a response handler
    fmt.Println("running...")
    u, err := url.Parse("https://www.cursvalutar.ro")
    if err != nil {
        // ...
    }
    fmt.Println(u.Hostname())
}
