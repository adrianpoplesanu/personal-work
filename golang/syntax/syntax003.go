package main
import (
    "fmt"
    "io/ioutil"
    "net/http"
)

func main() {
    fmt.Println("running...")
    resp, err := http.Get("http://www.cursvalutar.ro")
    if err != nil {
        fmt.Println("there was an error! code 1")
    }
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        fmt.Println("there was an error! code 2")
    }
    fmt.Println(string(body))
}
