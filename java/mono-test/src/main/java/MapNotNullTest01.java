import reactor.core.publisher.Mono;

import java.util.ArrayList;
import java.util.List;

public class MapNotNullTest01 {

    private static void mapTest01(List<String> dogs) {
        Mono<List<String>> elements = Mono.just(dogs);

        Mono<String> result = elements.mapNotNull(el -> {
            if (el.contains("dex")) {
                return "ham ham ham";
            }
            return null;
        });

        System.out.println(result.block());
    }

    public static void main(String[] args) {
        List<String> dogs = new ArrayList<>();

        System.out.println(dogs);
        mapTest01(dogs);

        dogs.add("luna");
        System.out.println(dogs);
        mapTest01(dogs);

        dogs.add("sashi");
        System.out.println(dogs);
        mapTest01(dogs);

        dogs.add("dex");
        System.out.println(dogs);
        mapTest01(dogs);
    }
}
