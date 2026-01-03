package ro.adrianus.rssreader2

import android.os.Bundle
import android.view.View
import android.widget.ProgressBar
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.compose.ui.node.ViewAdapter
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Deferred
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import kotlinx.coroutines.joinAll
import kotlinx.coroutines.launch
import kotlinx.coroutines.newFixedThreadPoolContext
import kotlinx.coroutines.newSingleThreadContext
import org.w3c.dom.Element
import org.w3c.dom.Node
import ro.adrianus.rssreader2.adapter.ArticleAdapter
import ro.adrianus.rssreader2.model.Article
import ro.adrianus.rssreader2.model.Feed
import javax.xml.parsers.DocumentBuilderFactory

class MainActivity : ComponentActivity() {
    private val factory = DocumentBuilderFactory.newInstance()
    private val dispatcher = newFixedThreadPoolContext(2, "IO")

    private lateinit var articles: RecyclerView
    private lateinit var viewAdapter: ArticleAdapter
    private lateinit var viewManager: RecyclerView.LayoutManager

    private val feeds = listOf(
        Feed("npr", "https://www.npr.org/rss/rss.php?id=1001"),
        Feed("cnn", "http://rss.cnn.com/rss/cnn_topstories.rss"),
        //Feed("fox", "https://feeds.foxnews.com/foxnews/politics?format=xml"),
        Feed("fox", "https://moxie.foxnews.com/google-publisher/politics.xml?format=xml"),
        Feed("inv", "htt://adrianus.ro")
    )
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        viewManager = LinearLayoutManager(this)
        viewAdapter = ArticleAdapter()
        articles = findViewById<RecyclerView>(R.id.articles).apply {
            layoutManager = viewManager
            adapter = viewAdapter
        }

        asyncLoadNews()
    }


    private fun asyncLoadNews() = GlobalScope.launch {
        val requests = mutableListOf<Deferred<List<Article>>>()

        feeds.mapTo(requests) {
            asyncFetchArticles(it, dispatcher)
        }

        requests.joinAll()

        val articles = requests
            .filter { !it.isCancelled }
            .flatMap { it.getCompleted() }

        val failedCount = requests
            .filter { it.isCancelled }
            .size

        val obtained = requests.size - failedCount

        runOnUiThread {
            findViewById<ProgressBar>(R.id.progressBar).visibility = View.GONE
            viewAdapter.add(articles)
        }
    }

    private fun asyncFetchArticles(feed: Feed, dispatcher: CoroutineDispatcher) = GlobalScope.async(dispatcher) {
        delay(1000)
        val builder = factory.newDocumentBuilder()
        val xml = builder.parse(feed.url)
        val news = xml.getElementsByTagName("channel").item(0)

        (0 until news.childNodes.length)
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
}
