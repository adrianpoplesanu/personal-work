package chapter1;

public class RouterDemo {

	public static void main(String[] args) {
		Router router = new Router();
		router.AddRawRoute();
		router.AddRawRoute("/", "HomeController", "index", "GET");
		router.PrintInfo();
		router.PrintVersion();
	}
}
