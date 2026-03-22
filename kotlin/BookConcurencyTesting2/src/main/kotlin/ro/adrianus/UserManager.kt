package ro.adrianus

class UserManager(private val dataSource: DataSource) {
    suspend fun getUser(id: Int): User {
        val name = dataSource.getNameAsync(id)
        val age = dataSource.getAgeAsync(id)
        val profession = dataSource.getProfessionAsync(id)

        //profession.await()
        return User(
            name.await(),
            age.await(),
            profession.await()
        )
    }
}