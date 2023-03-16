import reactor.core.publisher.Mono;

import java.util.Optional;

public class MiscTest1 {
    public static void main(String[] args) {
        //Mono<String> a = Mono.empty();
        Mono<String> a = Mono.just("aaa");
        Mono<String> b = Mono.zip(a.map(Optional::of).defaultIfEmpty(Optional.empty()),
                Mono.just("bbb"))
                .flatMap(data -> {
                    System.out.println(data.getT1().orElse(null));
                    System.out.println(data.getT2());
                    return Mono.empty();
                });
        b.block();
    }
}
