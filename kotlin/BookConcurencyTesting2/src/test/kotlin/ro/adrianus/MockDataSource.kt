package ro.adrianus

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.async
import kotlinx.coroutines.delay
import java.util.Calendar

class MockDataSource(private val scope: CoroutineScope): DataSource {
    override fun getNameAsync(id: Int) = scope.async {
        delay(200)
        "Bebe Dex"
    }

    override fun getAgeAsync(id: Int) = scope.async {
        delay(500)
        Calendar.getInstance().get(Calendar.YEAR) - 2009
    }

    override fun getProfessionAsync(id: Int) = scope.async {
        delay(2000)
        "watch dog"
    }
}