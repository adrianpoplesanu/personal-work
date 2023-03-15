import reactor.core.publisher.Mono;

import java.util.Optional;

public class EmptinessTest {

    public static void testEmtiness1() {
        Mono<String> a = Mono.just("aaa");
        Mono<String> b = Mono.just("bbb");
        Mono<String> c = Mono.empty();

        Mono<String> result = Mono.zip(a, b, c).flatMap(data -> Mono.just(data.getT1() + data.getT2() + data.getT3()));
        System.out.println(result.block());
    }

    public static void testEmtiness2() {
        Mono<String> a = Mono.just("aaa");
        Mono<String> b = Mono.just("bbb");
        Mono<Optional<Object>> c = Mono.empty().map(Optional::of).defaultIfEmpty(Optional.empty());

        Mono<String> result = Mono.zip(a, b, c).flatMap(data -> Mono.just(data.getT1() + data.getT2() + (data.getT3().orElse(null) == null ? "opa" : "ok")));
        System.out.println(result.block());
    }

    private class Dog {
        private String name;
        private String type;
        private String word;

        public Dog(String name, String type, String word) {
            this.name = name;
            this.type = type;
            this.word = word;
        }

        @Override
        public String toString() {
            return "Dog{" +
                    "name='" + name + '\'' +
                    ", type='" + type + '\'' +
                    ", word='" + word + '\'' +
                    '}';
        }
    }

    public void testEmtiness3() {
        Mono<String> a = Mono.just("bebe dex");
        Mono<String> b = Mono.just("catel");
        Mono<Optional<Object>> c = Mono.empty().map(Optional::of).defaultIfEmpty(Optional.empty());

        Mono<Dog> result = Mono.zip(a, b, c).flatMap(data -> Mono.just(new Dog(data.getT1(), data.getT2(), (String) data.getT3().orElse(null))));
        System.out.println(result.block());
    }

    public void testEmtiness4() {
        Mono<Dog> result = Mono.zip(
                Mono.just("bebe dex"),
                Mono.just("catel"),
                Mono.just("dragutz")
                        .map(Optional::of)
                        .defaultIfEmpty(Optional.empty()))
                .flatMap(data -> Mono.just(new Dog(data.getT1(), data.getT2(), (String) data.getT3().orElse(null))));
        System.out.println(result.block());
    }

    public void testEmtiness5(Mono<String> a, Mono<String> b, Mono<String> c) {
        Mono<Dog> result = Mono.zip(
                a,
                b,
                c
                        .map(Optional::of)
                        .defaultIfEmpty(Optional.empty()))
                .flatMap(data -> Mono.just(new Dog(data.getT1(), data.getT2(), data.getT3().orElse(null))));
        System.out.println(result.block());
    }

    private Mono<String> getName() {
        return Mono.just("bebe dex");
    }

    private Mono<String> getType() {
        return Mono.just("bebe dex");
    }

    private Mono<String> getWord() {
        return Mono.empty();
    }

    private Mono<String> getWord2() {
        return Mono.just("ham ham ham");
    }

    public static void main(String[] args) {
        testEmtiness1();
        testEmtiness2();

        EmptinessTest emptinessTest = new EmptinessTest();
        emptinessTest.testEmtiness3();

        emptinessTest.testEmtiness4();

        emptinessTest.testEmtiness5(Mono.just("dexiciul"), Mono.just("catelus"), Mono.just("drabutz"));
        emptinessTest.testEmtiness5(Mono.just("dexiciul"), Mono.just("catelus"), Mono.empty());
        emptinessTest.testEmtiness5(emptinessTest.getName(), emptinessTest.getType(), emptinessTest.getWord());
        emptinessTest.testEmtiness5(emptinessTest.getName(), emptinessTest.getType(), emptinessTest.getWord2());
    }
}
