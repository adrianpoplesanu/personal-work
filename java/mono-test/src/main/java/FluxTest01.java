import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

import java.util.HashMap;
import java.util.Map;

public class FluxTest01 {

    private static Map<String, Integer> mapper = new HashMap<String, Integer>() {
        {
            put("zero", 0);
            put("unu", 1);
            put("doi", 2);
            put("trei", 3);
            put("patru", 4);
            put("cinci", 5);
            put("sase", 6);
            put("sapte", 7);
            put("opt", 8);
            put("noua", 9);
        }
    };

    public static void testConvertMonoToFlux() {
        Mono<String> addressMono;
        Flux<String> addressFlux;
        addressMono = Mono.just("aaa");
        addressFlux = addressMono
                .flatMapMany(x -> Mono.just(x.toUpperCase()));
        addressFlux.subscribe(System.out::println);
    }

    public static void testConvertFluxToFlux() {
        Flux<String> numbersStrings = Flux.just("unu", "unu", "doi", "doi");
        Flux<Integer> numbersInts;
        numbersInts = numbersStrings.map(x -> mapper.get(x));
        numbersStrings.subscribe(System.out::println);
        numbersInts.subscribe(System.out::println);
    }

    public static void main(String[] args) {
        testConvertMonoToFlux();
        testConvertFluxToFlux();
    }
}
