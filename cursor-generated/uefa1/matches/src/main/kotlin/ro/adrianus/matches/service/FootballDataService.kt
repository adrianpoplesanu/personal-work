package ro.adrianus.matches.service

import org.slf4j.LoggerFactory
import org.springframework.stereotype.Service
import ro.adrianus.matches.connector.FootballDataConnector

@Service
class FootballDataService(
    private val footballDataConnector: FootballDataConnector
) {

    private val log = LoggerFactory.getLogger(javaClass)

    fun retrieveMatches(): String? {
        log.info("Retrieving matches from football-data API")
        return footballDataConnector.get("/v4/matches")
    }
}
