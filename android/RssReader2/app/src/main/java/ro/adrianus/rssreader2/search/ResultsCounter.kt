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

    private val actor = GlobalScope.actor<Void?>(context) {
        for (msg in channel) {
            counter++
            notifications.send(counter)
        }
    }

    suspend fun increment() = actor.send(null)
    fun getNotificationChannel() : ReceiveChannel<Int> = notifications
}