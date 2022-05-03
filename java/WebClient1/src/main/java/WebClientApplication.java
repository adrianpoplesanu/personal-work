import com.fasterxml.jackson.databind.JsonNode;
import model.ApiResponse;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.web.reactive.function.client.ExchangeStrategies;
import org.springframework.web.reactive.function.client.WebClient;
import reactor.core.publisher.Mono;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class WebClientApplication {

    private static void test0() throws IOException {
        // https://chillyfacts.com/java-send-http-getpost-request-and-read-json-response/
        String url = "https://api.football-data.org/v2/competitions/PL/matches";
        URL obj = new URL(url);
        HttpURLConnection con = (HttpURLConnection) obj.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("X-Auth-Token", "f5c1f45ccb174b739541ad43203c7183");
        int responseCode = con.getResponseCode();
        System.out.println("\nSending 'GET' request to URL : " + url);
        System.out.println("Response Code : " + responseCode);
        BufferedReader in = new BufferedReader(
                new InputStreamReader(con.getInputStream()));
        String inputLine;
        StringBuffer response = new StringBuffer();
        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
        }
        in.close();
        System.out.println(response.toString());
    }

    private static void test() {
        final int size = 16 * 1024 * 1024;
        ExchangeStrategies strategies = ExchangeStrategies.builder()
                .codecs(codecs -> codecs.defaultCodecs().maxInMemorySize(size))
                .build();
        // https://stackoverflow.com/questions/59735951/databufferlimitexception-exceeded-limit-on-max-bytes-to-buffer-webflux-error

        WebClient webClient2 = WebClient.builder()
                .exchangeStrategies(strategies)
                .baseUrl("https://api.football-data.org")
                .defaultHeader(HttpHeaders.CONTENT_TYPE, MediaType.APPLICATION_JSON_VALUE)
                .defaultHeader("X-Auth-Token", "f5c1f45ccb174b739541ad43203c7183")
                .build();

        JsonNode jsonNode = webClient2.get()
                .uri("/v2/competitions/PL/matches")
                .retrieve()
                .bodyToMono(JsonNode.class)
                .block();

        System.out.println(jsonNode);
    }

    private static void test2() {
        final int size = 16 * 1024 * 1024;
        ExchangeStrategies strategies = ExchangeStrategies.builder()
                .codecs(codecs -> codecs.defaultCodecs().maxInMemorySize(size))
                .build();
        // https://stackoverflow.com/questions/59735951/databufferlimitexception-exceeded-limit-on-max-bytes-to-buffer-webflux-error

        WebClient webClient2 = WebClient.builder()
                .exchangeStrategies(strategies)
                .baseUrl("https://api.football-data.org")
                .defaultHeader(HttpHeaders.CONTENT_TYPE, MediaType.APPLICATION_JSON_VALUE)
                .defaultHeader("X-Auth-Token", "f5c1f45ccb174b739541ad43203c7183")
                .build();

        Mono<String> monoResult = webClient2.get()
                .uri("/v2/competitions/PL/matches")
                .retrieve()
                .bodyToMono(String.class);

        String text = monoResult.block();

        System.out.println(text);
    }

    private static void test3() {
        final int size = 16 * 1024 * 1024;
        ExchangeStrategies strategies = ExchangeStrategies.builder()
                .codecs(codecs -> codecs.defaultCodecs().maxInMemorySize(size))
                .build();
        // https://stackoverflow.com/questions/59735951/databufferlimitexception-exceeded-limit-on-max-bytes-to-buffer-webflux-error

        WebClient webClient2 = WebClient.builder()
                .exchangeStrategies(strategies)
                .baseUrl("https://api.football-data.org")
                .defaultHeader(HttpHeaders.CONTENT_TYPE, MediaType.APPLICATION_JSON_VALUE)
                .defaultHeader("X-Auth-Token", "f5c1f45ccb174b739541ad43203c7183")
                .build();

        Mono<ApiResponse> monoResult = webClient2.get()
                .uri("/v2/competitions/PL/matches")
                .retrieve()
                .bodyToMono(ApiResponse.class);

        ApiResponse response = monoResult.block();

        System.out.println(response);
    }

    public static void main(String[] args) throws IOException {
        System.out.println("running WebClientApplication");

        test3();
        // https://www.baeldung.com/spring-5-webclient
        // https://mvnrepository.com/artifact/org.springframework.boot/spring-boot-starter-webflux

        /*WebClient client = WebClient.create("https://api.football-data.org");
        // /v2/competitions/PL/matches

        Mono<Response> responseMono = client.get()
                .uri("/v2/competitions/{id}/matches", "PL")
                .retrieve()
                .bodyToMono(Response.class);

        responseMono.subscribe(response -> System.out.println(response));*/
    }
}
