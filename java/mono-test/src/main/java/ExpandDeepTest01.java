import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

import java.util.Collections;

public class ExpandDeepTest01 {
    public static void main(String[] args) {
        Mono<Integer> numbers = Mono.just(5);
        Flux<Integer> result = numbers.expandDeep(number -> {
            System.out.println(number);
            if (number == 0) return Mono.empty();
            return Mono.just(number - 1);
        });
        result.subscribe();
    }
}
