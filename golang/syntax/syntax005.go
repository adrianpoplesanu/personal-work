// print tests and string manipulation
package main
import(
    "fmt"
)

func main() {
    fmt.Println("test")

    var a string = "abc"
    fmt.Println(a)

    a = "qwe"
    fmt.Println(a)

    var b string;
    b = "qwe"
    fmt.Println(a == b)

    // use the compiler to automatically determine the type based on instantiation
    c := "hello"
    fmt.Println(c)
}
