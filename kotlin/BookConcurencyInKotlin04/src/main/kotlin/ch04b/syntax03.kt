package ch04b

import kotlinx.coroutines.runBlocking

data class Profile(
    val id: Long,
    val name: String,
    val age: Int
)

interface ProfileServiceRepository {
    suspend fun fetchByName(name: String) : Profile
    suspend fun fetchById(id: Long) : Profile
}

class ProfileServiceClient : ProfileServiceRepository {
    override suspend fun fetchByName(name: String): Profile {
        return Profile(1, name, 28)
    }

    override suspend fun fetchById(id: Long): Profile {
        return Profile(id, "Bedus", 28)
    }
}

fun main(args: Array<String>) = runBlocking {
    val profileServiceRepository: ProfileServiceRepository = ProfileServiceClient()

    val profile = profileServiceRepository.fetchById(12)
    println(profile)
}