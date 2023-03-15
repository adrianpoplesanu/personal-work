import reactor.core.publisher.Mono;

public class ZipTest01 {

    private static void testMonoZip01() {
        String result = Mono.zip(
                Mono.just("aaa"),
                Mono.just("bbb")
        ).map(tuple -> tuple.getT1() + ":::" + tuple.getT2())
                .block();
        System.out.println(result);
    }

    private static void testMonoZip02() {
        Mono<Void> a = Mono.zip(
                Mono.just("aaa"),
                Mono.just("bbb"))
                .map(tuple -> tuple.getT1() + ":::" + tuple.getT2())
                .flatMap(x -> {
                    System.out.println(x);
                    return Mono.empty();
                });
        a.subscribe();
    }

    private static void testMonoZip03() {
        Mono<String> name = Mono.just("Bebe Dex");
        Mono<Integer> age = Mono.just(12);
        Mono<Boolean> scump = Mono.just(true);
        Mono<String> composite = Mono.zip(name, age, scump).flatMap(data -> Mono.just(data.getT1() + data.getT2() + data.getT3()));
        System.out.println(composite.block());
    }

    public static void main(String[] args) {
        testMonoZip01();
        testMonoZip02();
        testMonoZip03();
    }
}
