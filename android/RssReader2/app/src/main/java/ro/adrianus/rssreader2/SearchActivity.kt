package ro.adrianus.rssreader2

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import ro.adrianus.rssreader2.adapter.SearchArticleAdapter
import ro.adrianus.rssreader2.search.Searcher

class SearchActivity : AppCompatActivity() {
    private lateinit var articles: RecyclerView
    private lateinit var viewAdapter: SearchArticleAdapter
    private lateinit var viewManager: RecyclerView.LayoutManager
    private val searcher = Searcher()


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_search)

        viewManager = LinearLayoutManager(this)
        viewAdapter = SearchArticleAdapter()
        articles = findViewById<RecyclerView>(R.id.articles).apply {
            layoutManager = viewManager
            adapter = viewAdapter
        }

        findViewById<Button>(R.id.searchButton).setOnClickListener {
            viewAdapter.clear()
            GlobalScope.launch {
                search()
            }
        }
    }

    private suspend fun search() {
        val query = findViewById<EditText>(R.id.searchText).text.toString()
        val channel = searcher.search(query)

        while (!channel.isClosedForReceive) {
            val article = channel.receive()
            runOnUiThread {
                viewAdapter.add(article)
            }
        }
    }
}