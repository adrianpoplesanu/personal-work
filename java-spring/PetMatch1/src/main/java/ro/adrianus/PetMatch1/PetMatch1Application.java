package ro.adrianus.PetMatch1;

import org.springframework.boot.Banner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ApplicationContext;

import java.util.Arrays;

@SpringBootApplication
public class PetMatch1Application {

	/*public static void main(String[] args) {
		SpringApplication.run(PetMatch1Application.class, args);
	}*/

	/*public static void main(String[] args) {
		SpringApplication app = new SpringApplication(PetMatch1Application.class);
		app.setHeadless(false);
		app.setBannerMode(Banner.Mode.OFF);
		app.setLogStartupInfo(false);
		app.run(args);
	}*/

	/*public static void main(String[] args) {
		new SpringApplicationBuilder(PetMatch1Application.class)
				.headless(false)
				.bannerMode(Banner.Mode.OFF)
				.logStartupInfo(false)
				.run(args);
	}*/

	public static void main(String[] args) {
		ApplicationContext ctx = SpringApplication.run(PetMatch1Application.class, args);
		Arrays.stream(ctx.getBeanDefinitionNames())
				.sorted()
				.forEach(System.out::println);
	}
}
