import reactor.core.publisher.Mono;

public class ErrorHandlingTest01 {

    class AaaException extends RuntimeException {

    }

    public Mono<String> generateDate(int a) {
        //if (a < 0) throw new AaaException();
        if (a < 0) return Mono.error(new AaaException());
        return Mono.just("number" + a);
    }

    public static void main(String[] args) {
        ErrorHandlingTest01 errorHandlingTest01 = new ErrorHandlingTest01();
        Mono<String> monoResult = errorHandlingTest01.generateDate(-5).onErrorMap(AaaException.class, ex -> new RuntimeException("bbb"));
        String result = monoResult.block();
        System.out.println(result);
    }
}
