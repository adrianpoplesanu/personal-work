package main
import(
    "fmt"
    "html/template"
    "io/ioutil"
    "log"
    "net/http"
    "os/exec"
    "os"
)

func uploadFile(w http.ResponseWriter, r *http.Request) {
    log.Println("POST /upload - File upload endpoint hit")
    r.ParseMultipartForm(50 << 20)
    file, handler, err := r.FormFile("file")
    if err != nil {
	    log.Println("Error retrieving file")
	    log.Println(err)
        return
    }
    defer file.Close()

    log.Println("Uploaded file:", handler.Filename)
    log.Println("File Size:", handler.Size)
    log.Println("MIME Header:", handler.Header)

    tempFile, err := ioutil.TempFile(os.Getenv("APP_HOME") + "/temp-images", "upload-*.jpg")
    if err != nil {
	    log.Println(err)
    }
    defer tempFile.Close()

    fileBytes, err := ioutil.ReadAll(file)
    if err != nil {
	    log.Println(err)
    }

    tempFile.Write(fileBytes)
    log.Println("Destination:", tempFile.Name())

    out, err := exec.Command("python3", os.Getenv("APP_HOME") + "/analyzer.py", tempFile.Name()).Output()
    if err != nil {
        w.Write([]byte(`"status": "error", "message": "Check server console output"`))
	    log.Println(err)
        return
    }
    log.Println("Successfully uploaded file ", handler.Filename)
    w.Write(out)
}

func statusChecker(w http.ResponseWriter, r *http.Request) {
    log.Println("GET /")
    w.Header().Set("Content-Type", "application/json")
    response := `{"responseCode": "200", "status": "OK"}`
    w.Write([]byte (response))
}

func commandExecTest(w http.ResponseWriter, r *http.Request) {
    log.Println("GET /command-exec-test")
    out, err := exec.Command("python3", os.Getenv("APP_HOME") + "/analyzer.py", os.Getenv("APP_HOME") + "/adri.jpg").Output()
    if err != nil {
        w.Write([]byte(`"status": "error", "message": "Check server console output"`))
        fmt.Println(err)
        return
    }
    w.Write(out)
}

func swaggerTemplate(w http.ResponseWriter, r *http.Request) {
    log.Println("GET /swagger")
    tmpl := template.Must(template.ParseFiles(os.Getenv("APP_HOME") + "/swagger.html"))
    tmpl.Execute(w, nil)
}

type LogoHandler struct {
}

func (this *LogoHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
    path := r.URL.Path[1:]
    log.Println("GET /" + string(path))
    data, err := ioutil.ReadFile(os.Getenv("APP_HOME") + "/" + string(path))

    if err == nil {
        w.Header().Add("Content Type", "image/jpeg")
        w.Write(data)
    } else {
        w.WriteHeader(404)
        w.Write([]byte("404 My dear - " + http.StatusText(404)))
    }
}

func setupRoutes() {
    log.Println("setting up routes...")
    http.HandleFunc("/", statusChecker)
    http.Handle("/logo.jpg", new(LogoHandler))
    http.Handle("/logo2.jpg", new(LogoHandler))
    http.HandleFunc("/upload", uploadFile)
    http.HandleFunc("/command-exec-test", commandExecTest)
    http.HandleFunc("/swagger", swaggerTemplate)
    log.Println("listening on 9191...")
    http.ListenAndServe(":9191", nil)
}

func main() {
    f, err := os.OpenFile("ramona1_server.log", os.O_RDWR | os.O_CREATE | os.O_APPEND, 0666)
    if err != nil {
        log.Fatalf("error opening file: %v", err)
    }
    defer f.Close()

    log.SetOutput(f)
    log.Println("=============================================")
    log.Println("= Ramona1 server started...                 =")
    log.Println("=============================================")
    setupRoutes()
}
