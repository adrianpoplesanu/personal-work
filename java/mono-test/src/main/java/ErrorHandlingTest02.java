import reactor.core.publisher.Mono;

public class ErrorHandlingTest02 {

    public Mono<String> createUser(String value) {
        System.out.println("created:" + value);
        return Mono.just("user:" + value);
    }

    public Mono<Void> createAlias(String user) {
        System.out.println(user + "+alias");
        return Mono.empty();
    }

    public Mono<Void> addGroup(String user) {
        System.out.println(user + "+group");
        return Mono.empty();
    }

    public void testFunctionality() {
        Mono<String> resultMono = createUser("adi").flatMap( // replace this with dex for testing
                user -> createAlias(user).then(Mono.defer(() -> {
                    if (user.equals("user:adi")) return Mono.error(new RuntimeException("AAA"));
                    return addGroup(user);
                })).thenReturn("adi updatat cu de toate")
        );

        String result = resultMono.block();
        System.out.println(result);
    }

    public static void main(String[] args) {
        ErrorHandlingTest02 errorHandlingTest02 = new ErrorHandlingTest02();
        /*Mono<String> resultMono = errorHandlingTest02.createUser("adi").flatMap(
                user -> errorHandlingTest02.createAlias(user)).then(Mono.defer(() -> {
                    return errorHandlingTest02.addGroup(user);
                }).thenReturn("cucu mucu")
        );

        resultMono.block();*/
        errorHandlingTest02.testFunctionality();
    }
}
