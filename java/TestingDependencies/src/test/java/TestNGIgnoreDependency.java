import org.testng.annotations.Ignore;
import org.testng.annotations.Test;

@Ignore
public class TestNGIgnoreDependency extends TestNGDependenciesBase {
    @Test
    public void testSomething2() {
        System.out.println("testSomething2()");
    }
}
