package ro.adrianus.matches.service

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.extension.ExtendWith
import org.mockito.InjectMocks
import org.mockito.Mock
import org.mockito.junit.jupiter.MockitoExtension
import org.mockito.kotlin.whenever
import ro.adrianus.matches.connector.FootballDataConnector
import kotlin.test.assertEquals
import kotlin.test.assertNull

@ExtendWith(MockitoExtension::class)
class FootballDataServiceTest {

    @Mock
    lateinit var footballDataConnector: FootballDataConnector

    @InjectMocks
    lateinit var footballDataService: FootballDataService

    @Test
    fun `retrieveMatches returns response from connector`() {
        val expectedResponse = """{"matches":[{"id":1}]}"""
        whenever(footballDataConnector.get("/v4/matches")).thenReturn(expectedResponse)

        val result = footballDataService.retrieveMatches()

        assertEquals(expectedResponse, result)
    }

    @Test
    fun `retrieveMatches returns null when connector returns null`() {
        whenever(footballDataConnector.get("/v4/matches")).thenReturn(null)

        val result = footballDataService.retrieveMatches()

        assertNull(result)
    }
}
