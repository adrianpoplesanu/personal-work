package ro.adrianus.matches.service

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.extension.ExtendWith
import org.mockito.Mock
import org.mockito.junit.jupiter.MockitoExtension
import org.mockito.kotlin.whenever
import ro.adrianus.matches.connector.FootballDataConnector
import tools.jackson.databind.ObjectMapper
import tools.jackson.module.kotlin.jacksonObjectMapper
import kotlin.test.assertEquals
import kotlin.test.assertNotNull
import kotlin.test.assertNull

@ExtendWith(MockitoExtension::class)
class FootballDataServiceTest {

    @Mock
    lateinit var footballDataConnector: FootballDataConnector

    private val objectMapper: ObjectMapper = jacksonObjectMapper()

    private val footballDataService: FootballDataService by lazy {
        FootballDataService(footballDataConnector, objectMapper)
    }

    @Test
    fun `retrieveMatches deserializes response from connector`() {
        val json = """
            {
                "filters": {"dateFrom": "2026-02-28", "dateTo": "2026-03-01", "permission": "TIER_ONE"},
                "resultSet": {"count": 1, "competitions": "PL", "first": "2026-02-28", "last": "2026-02-28", "played": 0},
                "matches": [{
                    "id": 538055,
                    "utcDate": "2026-02-28T12:30:00Z",
                    "status": "TIMED",
                    "matchday": 28,
                    "stage": "REGULAR_SEASON",
                    "homeTeam": {"id": 1044, "name": "AFC Bournemouth", "shortName": "Bournemouth", "tla": "BOU"},
                    "awayTeam": {"id": 71, "name": "Sunderland AFC", "shortName": "Sunderland", "tla": "SUN"},
                    "score": {"winner": null, "duration": "REGULAR", "fullTime": {"home": null, "away": null}, "halfTime": {"home": null, "away": null}}
                }]
            }
        """.trimIndent()
        whenever(footballDataConnector.get("/v4/matches")).thenReturn(json)

        val result = footballDataService.retrieveMatches()

        assertNotNull(result)
        assertEquals("2026-02-28", result.filters?.dateFrom)
        assertEquals(1, result.resultSet?.count)
        assertEquals(1, result.matches.size)
        assertEquals(538055L, result.matches[0].id)
        assertEquals("AFC Bournemouth", result.matches[0].homeTeam?.name)
        assertEquals("Sunderland AFC", result.matches[0].awayTeam?.name)
        assertEquals("TIMED", result.matches[0].status)
    }

    @Test
    fun `retrieveMatches returns null when connector returns null`() {
        whenever(footballDataConnector.get("/v4/matches")).thenReturn(null)

        val result = footballDataService.retrieveMatches()

        assertNull(result)
    }
}
