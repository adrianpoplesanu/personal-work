class UrlParser {
    static void main(String[] args) {
        println("running...")
        def data = new URL("https://www.imdb.com").getText()
        println(data);
    }
}
