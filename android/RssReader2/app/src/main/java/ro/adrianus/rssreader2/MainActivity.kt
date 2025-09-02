package ro.adrianus.rssreader2

import android.os.Bundle
import android.widget.TextView
import androidx.activity.ComponentActivity
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.Deferred
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.launch
import kotlinx.coroutines.newFixedThreadPoolContext
import kotlinx.coroutines.newSingleThreadContext
import org.w3c.dom.Element
import org.w3c.dom.Node
import javax.xml.parsers.DocumentBuilderFactory

class MainActivity : ComponentActivity() {
    private val defDsp = newSingleThreadContext("ServiceCall")
    private val factory = DocumentBuilderFactory.newInstance()
    private val dispatcher = newFixedThreadPoolContext(2, "IO")

    val feeds = listOf(
        "https://www.npr.org/rss/rss.php?id=1001",
        "http://rss.cnn.com/rss/cnn_topstories.rss",
        "https://feeds.foxnews.com/foxnews/politics?format=xml"
    )
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_main)

        asyncLoadNews()
    }


    private fun asyncLoadNews() = GlobalScope.launch {
        val requests = mutableListOf<Deferred<List<String>>>()

        feeds.mapTo(requests) {
            asyncFetchHeadlines(it, dispatcher)
        }

        requests.forEach {
            it.await()
        }

        val headlines = requests.flatMap {
            it.getCompleted()
        }

        val newsCount = findViewById<TextView>(R.id.newsCount)

        runOnUiThread {
            newsCount.text = "Found ${headlines.size} News in ${requests.size} feeds"
        }
    }

    private fun asyncFetchHeadlines(feed: String, dispatcher: CoroutineDispatcher) = GlobalScope.async(dispatcher) {
        val builder = factory.newDocumentBuilder()
        val xml = builder.parse(feed)
        val news = xml.getElementsByTagName("channel").item(0)

        (0 until news.childNodes.length)
            .map { news.childNodes.item(it) }
            .filter { Node.ELEMENT_NODE == it.nodeType }
            .map { it as Element }
            .filter { "item" == it.tagName }
            .map {
                it.getElementsByTagName("title").item(0).textContent
            }
    }

    private fun fetchRssHeadlines(): List<String> {
        val builder = factory.newDocumentBuilder()
        val xml = builder.parse("https://www.npr.org/rss/rss.php?id=1001")
        val news = xml.getElementsByTagName("channel").item(0)
        return (0 until news.childNodes.length)
            .map { news.childNodes.item(it) }
            .filter { Node.ELEMENT_NODE == it.nodeType }
            .map { it as Element }
            .filter { "item" == it.tagName }
            .map {
                it.getElementsByTagName("title").item(0).textContent
            }
    }
}
