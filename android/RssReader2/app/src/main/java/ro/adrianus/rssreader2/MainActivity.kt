package ro.adrianus.rssreader2

import android.os.Bundle
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
import kotlinx.coroutines.launch
import kotlinx.coroutines.newSingleThreadContext
import org.w3c.dom.Element
import org.w3c.dom.Node
import ro.adrianus.rssreader2.ui.theme.RssReader2Theme
import java.net.URL
import javax.xml.parsers.DocumentBuilderFactory

class MainActivity : ComponentActivity() {
    private val defDsp = newSingleThreadContext("ServiceCall")
    private val factory = DocumentBuilderFactory.newInstance()

    val feeds = listOf(
        "https://www.npr.org/rss/rss.php?id=1001",
        "http://rss.cnn.com/res/cnn_topstories.rss",
        "http://feeds.foxnews.com/foxnews/politics?format=xml"
    )
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.activity_main)

        asyncLoadNews()
    }


    private fun asyncLoadNews(dispatcher: CoroutineDispatcher = defDsp) =
        GlobalScope.launch(dispatcher) {
            val headlines = fetchRssHeadlines()
            val newsCount = findViewById<TextView>(R.id.newsCount)
            runOnUiThread {
                newsCount.text = "Found ${headlines.size} News"
            }
        }

    override fun onResume() {
        super.onResume()
        //Thread.sleep(5000)
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
