import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Iterators01 {

    private static void testImbricatedIterators() {
        Mono<String> nameMono = Mono.just("adish");
        List<String> addresses = Arrays.asList("Bdul Buc Noi", "Str Anton Bacal", "One American Road");

        Flux<String> infoFlux = nameMono.flatMapMany(name -> Flux.fromIterable(addresses).map(x -> name + ": " + x ));

        List<String> info = infoFlux.collectList().block();
        System.out.println(info);
    }

    private static void testImbricatedCartesianProduct() {
        Flux<String> namesFlux = Flux.just("adish", "bedush");
        List<String> addresses = Arrays.asList("Bdul Buc Noi", "Str Anton Bacal", "Oltenitei");

        Flux<String> infoFlux = namesFlux.flatMap(name -> Flux.fromIterable(addresses).map(x -> name + ": " + x));

        List<String> info = infoFlux.collectList().block();
        System.out.println(info);
    }

    private static void testImbricatedFlux() {
        Mono<String> nameMono = Mono.just("adish");
        Flux<String> addressesFlux = Flux.just("Bdul Buc Noi", "Str Anton Bacal", "One American Road");

        Flux<String> infoFlux = nameMono.flatMapMany(name -> addressesFlux.map(x -> name + ": " + x));

        List<String> info = infoFlux.collectList().block();
        System.out.println(info);
    }

    private static void testImbricatedFluxCartesianProduct() {
        Flux<String> namesFlux = Flux.just("adish", "bedush");
        Flux<String> addressesFlux = Flux.just("Bdul Buc Noi", "Str Anton Bacal", "Oltenitei");

        Flux<String> infoFlux = namesFlux.flatMap(name -> addressesFlux.map(x -> name + ": " + x));

        List<String> info = infoFlux.collectList().block();
        System.out.println(info);
    }

    private static void testThen() {
        Mono<String> nameMono = Mono.just("adish");
        List<String> addresses = Arrays.asList("Bdul Buc Noi", "Str Anton Bacal", "Oltenitei");

        Mono<Void> monoResult =
                nameMono.flatMap(name -> Flux.fromIterable(addresses)
                                             .flatMap(address -> { System.out.println(name + ": " + address); return Mono.empty(); })
                                             .then());
        monoResult.block();
    }

    public static void main(String[] args) {
        testImbricatedIterators();
        testImbricatedCartesianProduct();
        testImbricatedFlux();
        testImbricatedFluxCartesianProduct();
        testThen();
    }
}
