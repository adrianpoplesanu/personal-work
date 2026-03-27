package ro.adrianus.matches.service

import org.slf4j.LoggerFactory
import org.springframework.stereotype.Service
import ro.adrianus.matches.connector.FootballDataConnector
import ro.adrianus.matches.model.connector.MatchesResponse
import tools.jackson.databind.ObjectMapper

@Service
class FootballDataService(
    private val footballDataConnector: FootballDataConnector,
    private val objectMapper: ObjectMapper
) {

    private val log = LoggerFactory.getLogger(javaClass)

    fun retrieveMatches(): MatchesResponse? {
        log.info("Retrieving matches from football-data API")
        val response = footballDataConnector.get("/v4/matches") ?: return null
        return objectMapper.readValue(response, MatchesResponse::class.java)
    }
}
