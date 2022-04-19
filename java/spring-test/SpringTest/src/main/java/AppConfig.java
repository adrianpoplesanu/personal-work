import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class AppConfig {
    @Bean
    Greeter getGreeter() {
        return new GreeterImp();
    }

    @Bean
    GreeterService getGreeterService() {
        return new GreeterService();
    }
}
