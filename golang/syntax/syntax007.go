// celsius to fahrenheit converter
package main

import "fmt"

func convert_celsius_to_fahrenheit(c float64) float64 {
    return c * 9 / 5 + 32 
}

func convert_fahrenheit_to_celsius(f float64) float64 {
    return (f - 32) * 5 / 9
}

func main () {
    var C float64 = 20
    var F float64 = 68

    var rez float64
    rez = convert_celsius_to_fahrenheit(C)
    fmt.Println (rez)

    rez = convert_fahrenheit_to_celsius(F)
    fmt.Println (rez)
}
