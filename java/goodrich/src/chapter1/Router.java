package chapter1;

public class Router extends RouterAbstract {

	@Override
	public void AddRawRoute() {
		System.out.println("call to AddRawRoute()");
	}

	@Override
	public void AddRawRoute(String route, String controller, 
			String action, String method) {
		System.out.println("call to AddRawRoute(String, String, String, String");
		this.route = route;
		this.controller = controller;
		this.action = action;
		this.method = method;
	}
	
	public void PrintInfo() {
		System.out.println("ROUTE[" + this.route + "; " + 
							this.controller + "; " + 
							this.action + "; " + 
							this.method + "]");
	}
	
	public void PrintVersion() {
		System.out.println(GetVersion());
	}
}
