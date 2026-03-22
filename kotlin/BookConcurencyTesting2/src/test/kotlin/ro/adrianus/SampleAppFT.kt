package ro.adrianus

import kotlinx.coroutines.runBlocking
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Test
import java.util.Calendar

class SampleAppFT {
    @Test
    fun testHappyPath() = runBlocking {
        val manager = UserManager(MockDataSource(this))

        val user = manager.getUser(10)
        assertTrue { user.name == "Bebe Dex" }
        assertTrue { user.age == Calendar.getInstance().get(Calendar.YEAR) - 2009 }
        assertTrue { user.profession == "watch dog" }
    }

    @Test
    fun testOppositeOrder() = runBlocking {
        val manager = UserManager(MockSlowDbDataSource(this))

        val user = manager.getUser(10)
        assertTrue { user.name == "Bebe Dex" }
        assertTrue { user.age == Calendar.getInstance().get(Calendar.YEAR) - 2009 }
        assertTrue { user.profession == "watch dog" }
    }
}