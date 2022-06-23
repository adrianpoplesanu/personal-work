import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

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

    private static Mono<List<String>> getAddresses() {
        return Mono.just(Arrays.asList("Buc Noi", "Berceni"));
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

    private static Flux<String> convert(Mono<String> data) {
        return data.flatMapMany(x -> Mono.just(x));
    }

    private static Flux<String> convertAddreses(Mono<List<String>> data) {
        return data.flatMapMany(x -> {
            return Flux.fromIterable(x);
        });
    }

    public static void main(String[] args) {
        testName();
        testAge();
        testCountry();

        String firstElement = convert(getName()).blockFirst();

        System.out.println("...");

        System.out.println(firstElement);

        System.out.println("...");

        Flux<String> addresses = convertAddreses(getAddresses());
        addresses.subscribe(x -> System.out.println(x));
    }
}
