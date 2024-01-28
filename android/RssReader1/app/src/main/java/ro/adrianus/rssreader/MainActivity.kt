package ro.adrianus.rssreader

import android.os.Bundle
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.newSingleThreadContext
import org.w3c.dom.Element
import org.w3c.dom.Node
import ro.adrianus.rssreader.ui.theme.RssReader1Theme
import java.net.URL
import javax.xml.parsers.DocumentBuilderFactory

class MainActivity : ComponentActivity() {
    private val dispatcher = newSingleThreadContext("ServiceCall")
    private val defDsp = newSingleThreadContext("ServiceCall2")
    private val factory = DocumentBuilderFactory.newInstance()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        // this is the original generated code, however the example contains an activity_main xml file
        /*setContent {
            RssReader1Theme {
                // A surface container using the 'background' color from the theme
                Surface(modifier = Modifier.fillMaxSize(), color = MaterialTheme.colorScheme.background) {
                    Greeting("Bebe Dex")
                }
            }
        }*/
        setContentView(R.layout.activity_main)
        // TODO first version
        /*GlobalScope.launch(dispatcher) {
            val headlines = fetchRssHeadlines()
            val newsCount = findViewById<TextView>(R.id.newsCount)
            //launch(UI) {
            //    newsCount.text = "Found ${headlines.size} News"
            //}
            // ^^^ this does not work in the new modern AndroidStudio world
            runOnUiThread {
                newsCount.text = "Found ${headlines.size} News"
            }
        }*/
        // TODO second version
        /*GlobalScope.launch(dispatcher) {
            loadNews()
        }*/
        // TODO third version
        asyncLoadNews2()
    }

    private fun asyncLoadNews() = GlobalScope.launch(dispatcher) {
        val headlines = fetchRssHeadlines()
        val newsCount = findViewById<TextView>(R.id.newsCount)
        runOnUiThread {
            newsCount.text = "Found ${headlines.size} News"
        }
    }

    private fun asyncLoadNews2(dispatcher: CoroutineDispatcher = defDsp) =
        GlobalScope.launch(dispatcher) {
            val headlines = fetchRssHeadlines()
            val newsCount = findViewById<TextView>(R.id.newsCount)
            runOnUiThread {
                newsCount.text = "Found ${headlines.size} News"
            }
        }
    private fun loadNews() {
        val headlines = fetchRssHeadlines()
        val newsCount = findViewById<TextView>(R.id.newsCount)
        runOnUiThread {
            newsCount.text = "Found ${headlines.size} News"
        }
    }

    override fun onResume() {
        // this is bad, this is blocking the UI thread
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

    private fun fetchAdrianusHomepage() {
        val data = URL("https://adrianus.ro").readText()
        println(data)
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    RssReader1Theme {
        Greeting("Android")
    }
}