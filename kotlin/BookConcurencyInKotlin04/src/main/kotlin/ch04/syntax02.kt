package ch04

import kotlinx.coroutines.*

data class Profile (
    val id: Long,
    val name: String,
    val age: Int
)

interface ProfileServiceRepository {
    fun fetchByName(name: String) : Profile
    fun fetchById(id: Long) : Profile
}

interface AsyncProfileServiceRepository {
    fun asyncFetchByName(name: String) : Deferred<Profile>
    fun asyncFetchById(id: Long) : Deferred<Profile>
}

class ProfileServiceClient : AsyncProfileServiceRepository {
    override fun asyncFetchByName(name: String) = GlobalScope.async {
        Profile(1, name, 28)
    }

    override fun asyncFetchById(id: Long) = GlobalScope.async {
        Profile(id, "Bedus", 28)
    }
}

fun main(args: Array<String>) = runBlocking {
    val client : ProfileServiceClient = ProfileServiceClient()

    val profile = client.asyncFetchById(12).await()
    println(profile)
}