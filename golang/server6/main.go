package main

import (
    "net/http"
    "io/ioutil"
)

type MyHandler struct {
}

func (this *MyHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
    data, err := ioutil.ReadFile("logo.jpg")

    if err == nil {
        w.Header().Add("Content Type", "image/jpeg")
        w.Write(data)
    } else {
        w.WriteHeader(404)
        w.Write([]byte("404 My dear - " + http.StatusText(404)))
    }
}

func main() {
    http.Handle("/logo.jpg", new(MyHandler))
    http.ListenAndServe(":8090", nil)
}
