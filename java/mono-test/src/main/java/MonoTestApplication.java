import reactor.core.publisher.Mono;

public class MonoTestApplication {
    private static Mono<String> getName() {
        return Mono.just("adrianus per scorillo");
    }

    private static void testName() {
        Mono<?> monoResult = getName();
        monoResult.subscribe(x -> {
            if (x instanceof String) {
                System.out.println(x);
                System.out.println(((String) x).contains("adrianus"));
            }
        });
    }

    public static void main(String[] args) {
        testName();
    }
}
