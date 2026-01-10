package ro.adrianus.rssreader2.producer

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.newFixedThreadPoolContext
import org.w3c.dom.Element
import org.w3c.dom.Node
import ro.adrianus.rssreader2.model.Article
import ro.adrianus.rssreader2.model.Feed
import javax.xml.parsers.DocumentBuilderFactory
import kotlinx.coroutines.channels.produce

object ArticleProducer {
    private val feeds = listOf(
        Feed("npr", "https://www.npr.org/rss/rss.php?id=1001"),
        Feed("cnn", "http://rss.cnn.com/rss/cnn_topstories.rss"),
        Feed("fox", "https://moxie.foxnews.com/google-publisher/politics.xml?format=xml"),
    )

    private val factory = DocumentBuilderFactory.newInstance()
    private val dispatcher = newFixedThreadPoolContext(2, "IO")

    private fun fetchArticles(feed: Feed): List<Article> {
        val builder = factory.newDocumentBuilder()
        val xml = builder.parse(feed.url)
        val news = xml.getElementsByTagName("channel").item(0)

        return (0 until news.childNodes.length)
            .map { news.childNodes.item(it) }
            .filter { Node.ELEMENT_NODE == it.nodeType }
            .map { it as Element }
            .filter { "item" == it.tagName }
            //.filter { it.getElementsByTagName("description").item(0) != null } // this works, it could handle the todo mentioned below
            .map {
                val title = it.getElementsByTagName("title")
                    .item(0)
                    .textContent

                var summary: String
                try {
                    summary = it.getElementsByTagName("description")
                        .item(0)
                        .textContent
                } catch (e: Exception) {
                    // IMPORTANT: a trebuit sa fac asta pentru ca feed-urile sunt diferite
                    // cnn si fox, iar cnn nu are mereu description
                    // TODO: sa adaug filtering, daca nu are tag description sa sara peste
                    summary = it.getElementsByTagName("link")
                        .item(0)
                        .textContent
                }

                if (!summary.startsWith("<div") && summary.contains("<div")) {
                    summary = summary.substring(0, summary.indexOf("<div"))
                }

                Article(feed.name, title, summary)
            }
    }

    val producer = GlobalScope.produce(dispatcher) {
        feeds.forEach {
            send(fetchArticles(it))
        }
    }
}