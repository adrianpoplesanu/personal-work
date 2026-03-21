package ro.adrianus.rssreader2.search

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.channels.ReceiveChannel
import kotlinx.coroutines.channels.actor
import kotlinx.coroutines.newSingleThreadContext

object ResultsCounter {
    private val context = newSingleThreadContext("counter")
    private var counter = 0
    private val notifications = Channel<Int>(Channel.CONFLATED)

    enum class Action {
        INCREMENT,
        RESET
    }

    private val actor = GlobalScope.actor<Action>(context) {
        for (msg in channel) {
            when(msg) {
                Action.RESET -> counter = 0
                Action.INCREMENT -> counter++
            }
            notifications.send(counter)
        }
    }

    suspend fun increment() = actor.send(Action.INCREMENT)
    suspend fun reset() = actor.send(Action.RESET)
    fun getNotificationChannel() : ReceiveChannel<Int> = notifications
}