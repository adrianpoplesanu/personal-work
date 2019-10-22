package main
import(
    "fmt"
    "io/ioutil"
    "net/http"
)

func uploadFile(w http.ResponseWriter, r *http.Request) {
    fmt.Println("File upload endpoint hit")
    r.ParseMultipartForm(10 << 20)
    file, handler, err := r.FormFile("file")
    if err != nil {
        fmt.Println("Error retrieving file");
        fmt.Println(err)
        return
    }
    defer file.Close()

    fmt.Printf("Uploaded file: %+v\n", handler.Filename)
    fmt.Printf("File Size: %+v\n", handler.Size)
    fmt.Printf("MIME Header: %+v\n", handler.Header)

    tempFile, err := ioutil.TempFile("temp-images", "upload-*.jpg")
    if err != nil {
        fmt.Println(err)
    }
    defer tempFile.Close()

    fileBytes, err := ioutil.ReadAll(file)
    if err != nil {
        fmt.Println(err)
    }

    tempFile.Write(fileBytes)
    fmt.Fprintf(w, "Successfully uploaded file %+v\n", handler.Filename)
}

func setupRoutes() {
    http.HandleFunc("/upload", uploadFile)
    http.ListenAndServe(":9191", nil)
}

func main() {
    fmt.Println("running Ramona1 sever with /upload POST endpoint...")
    setupRoutes()
}
