package ro.adrianus.rssreader

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
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
    private val factory = DocumentBuilderFactory.newInstance()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            RssReader1Theme {
                // A surface container using the 'background' color from the theme
                Surface(modifier = Modifier.fillMaxSize(), color = MaterialTheme.colorScheme.background) {
                    Greeting("Bebe Dex")
                }
            }
        }
        GlobalScope.launch(dispatcher) {
            val headlines = fetchRssHeadlines()
            println(headlines)
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