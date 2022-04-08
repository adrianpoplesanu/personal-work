import reactor.core.publisher.Mono;

public class MonoTestApplication {
    private static Mono<String> getName() {
        return Mono.just("adrianus per scorillo");
    }

    private static Mono<Integer> getAge() {
        return Mono.just(1);
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

    private static void testAge() {
        Mono<?> monoResult = getAge();
        monoResult.subscribe(x -> {
            if (x instanceof String) {
                System.out.println(x);
                System.out.println(((String) x).contains("adrianus"));
            }
        });
    }

    public static void main(String[] args) {
        testName();
        testAge();
    }
}
