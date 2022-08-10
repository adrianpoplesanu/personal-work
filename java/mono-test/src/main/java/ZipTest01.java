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

    public static void main(String[] args) {
        testMonoZip01();
        testMonoZip02();
    }
}
