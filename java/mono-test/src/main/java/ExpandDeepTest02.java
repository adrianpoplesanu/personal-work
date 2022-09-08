import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

import java.util.List;

public class ExpandDeepTest02 {

    public static void testSimpleExpandDeepImplementation1() {
        Mono<Integer> numbers = Mono.just(4);
        Flux<Integer> result = numbers.expandDeep(number -> {
            return Mono.empty();
        });

        List<Integer> numbersList = result.collectList().block();
        System.out.println(numbersList);
    }

    public static void testSimpleExpandDeepImplementation2() {
        Mono<Integer> numbers = Mono.just(5);
        Flux<Integer> result = numbers.expandDeep(number -> {
            System.out.println(number);
            if (number == 0) return Mono.empty();
            return Mono.just(number - 1);
        });
        result.subscribe();
    }

    private static Mono<Integer> getNumber(int number) {
        return Mono.just(number);
    }

    public static void testGenerationMethod() {
        Flux<Integer> result = getNumber(3).expandDeep(number -> {
            if (number == 0) return Mono.empty();
            return getNumber(number - 1);
        });
        List<Integer> numbers = result.collectList().block();
        System.out.println(numbers);
    }

    public static void main(String[] args) {
        testSimpleExpandDeepImplementation1();
        testSimpleExpandDeepImplementation2();
        testGenerationMethod();
    }
}
