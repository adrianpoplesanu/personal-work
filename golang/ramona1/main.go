package main
import(
    "fmt"
    "io/ioutil"
    "net/http"
    "os/exec"
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
    fmt.Printf("Destination: %+v\n", tempFile.Name())

    out, err := exec.Command("python3", "analyzer.py", tempFile.Name()).Output()
    if err != nil {
        w.Write([]byte(`"status": "error", "message": "Check server console output"`))
        fmt.Println(err)
        return
    }
    //fmt.Fprintf(w, "Successfully uploaded file %+v\n", handler.Filename)
    w.Write(out)
}

func statusChecker(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "application/json")
    response := `{"responseCode": "200", "status": "OK"}`
    w.Write([]byte (response))
}

func commandExecTest(w http.ResponseWriter, r *http.Request) {
    out, err := exec.Command("python3", "analyzer.py", "adri.jpg").Output()
    if err != nil {
        w.Write([]byte(`"status": "error", "message": "Check server console output"`))
        fmt.Println(err)
        return
    }
    w.Write(out)
}

func setupRoutes() {
    http.HandleFunc("/", statusChecker)
    http.HandleFunc("/upload", uploadFile)
    http.HandleFunc("/command-exec-test", commandExecTest)
    http.ListenAndServe(":9191", nil)
}

func main() {
    fmt.Println("running Ramona1 sever with /upload POST endpoint...")
    fmt.Ptintln("CTRL + C to exit process")
    setupRoutes()
}
