class UrlParser {
    static void main(String[] args) {
        def data = new URL("https://www.cursvalutar.ro/curs-gbp/?curs_from_date=02-05-2018&curs_to_date=02-05-2019").getText()
        def matcher = data =~ /<td>(\d+.\d+)<\/td>/
        float sum = 0.0
        matcher[0..-1].each { elem ->
            sum += elem[1] as Float
        }
        float media = sum / matcher.size()
        println "Media este: " + media
    }
}
