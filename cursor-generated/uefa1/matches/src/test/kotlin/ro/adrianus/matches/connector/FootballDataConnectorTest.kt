package ro.adrianus.matches.connector

import org.junit.jupiter.api.Test
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.boot.test.context.SpringBootTest
import org.springframework.test.context.ActiveProfiles
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

@SpringBootTest
@ActiveProfiles("test")
class FootballDataConnectorTest {

    @Autowired
    lateinit var connector: FootballDataConnector

    @Test
    fun `get v4 matches returns valid response`() {
        val response = connector.get("/v4/matches")

        assertNotNull(response)
        assertTrue(response.isNotBlank())
        assertTrue(response.contains("matches"))
    }
}
