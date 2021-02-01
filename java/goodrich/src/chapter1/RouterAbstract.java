package chapter1;

public abstract class RouterAbstract {
	protected String route;
	protected String controller;
	protected String action;
	protected String method;
	
	public abstract void AddRawRoute();
	public abstract void AddRawRoute(String route, String controller, 
			String action, String method);
	
	public static final String GetVersion() {
		return "1.0.0";
	}
}
