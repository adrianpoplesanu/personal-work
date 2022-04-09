import reactor.core.publisher.Mono;

public class MonoTestApplication {
    private static Mono<String> getName() {
        return Mono.just("adrianus per scorillo");
    }

    private static Mono<Integer> getAge() {
        return Mono.just(1);
    }

    private static Mono<String> getCountry() {
        return Mono.just("UZB");
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

    private static void testCountry() {
        Mono<?> monoResult = getCountry();
        monoResult.doOnSuccessOrError((res, throwable) -> {
            System.out.println("received this country iso3 code:");
            System.out.println(res);
        }).subscribe(x -> System.out.println("doing something with the retrieved country") );
    }

    public static void main(String[] args) {
        testName();
        testAge();
        testCountry();
    }
}
