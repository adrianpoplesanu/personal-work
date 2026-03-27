package ro.adrianus.matches.model.connector

import com.fasterxml.jackson.annotation.JsonIgnoreProperties

@JsonIgnoreProperties(ignoreUnknown = true)
data class MatchesResponse(
    val filters: Filters? = null,
    val resultSet: ResultSet? = null,
    val matches: List<Match> = emptyList()
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Filters(
    val dateFrom: String? = null,
    val dateTo: String? = null,
    val permission: String? = null
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class ResultSet(
    val count: Int = 0,
    val competitions: String? = null,
    val first: String? = null,
    val last: String? = null,
    val played: Int = 0
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Match(
    val id: Long = 0,
    val utcDate: String? = null,
    val status: String? = null,
    val matchday: Int? = null,
    val stage: String? = null,
    val group: String? = null,
    val lastUpdated: String? = null,
    val area: Area? = null,
    val competition: Competition? = null,
    val season: Season? = null,
    val homeTeam: Team? = null,
    val awayTeam: Team? = null,
    val score: Score? = null,
    val odds: Odds? = null,
    val referees: List<Referee> = emptyList()
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Area(
    val id: Long = 0,
    val name: String? = null,
    val code: String? = null,
    val flag: String? = null
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Competition(
    val id: Long = 0,
    val name: String? = null,
    val code: String? = null,
    val type: String? = null,
    val emblem: String? = null
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Season(
    val id: Long = 0,
    val startDate: String? = null,
    val endDate: String? = null,
    val currentMatchday: Int? = null,
    val winner: String? = null
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Team(
    val id: Long = 0,
    val name: String? = null,
    val shortName: String? = null,
    val tla: String? = null,
    val crest: String? = null
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Score(
    val winner: String? = null,
    val duration: String? = null,
    val fullTime: ScoreDetail? = null,
    val halfTime: ScoreDetail? = null
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class ScoreDetail(
    val home: Int? = null,
    val away: Int? = null
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Odds(
    val msg: String? = null
)

@JsonIgnoreProperties(ignoreUnknown = true)
data class Referee(
    val id: Long = 0,
    val name: String? = null,
    val type: String? = null,
    val nationality: String? = null
)
