import org.testng.annotations.Ignore;
import org.testng.annotations.Test;

@Ignore("some message here")
public class TestNGIgnoreDependencyWithOverrideAndEnabled extends TestNGDependenciesBase {
    /*
    this was the proper solution
    does not injects parameteres in the methods
     */
    @Override
    @Test(enabled = false)
    public void testSomething() {

    }
}
