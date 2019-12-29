class UrlParser {
    static void main(String[] args) {
        println("running...")
        def data = new URL("https://www.cursvalutar.ro/curs-gbp/").getText()
        println(data);
    }
}
