import org.testng.annotations.Test;

public class TestNGDependenciesBase {
    @Test
    public void testSomething() {
        System.out.println("testSomething()");
    }

    @Test
    public void testWithParams(String text) {

    }
}
