import org.testng.annotations.Ignore;

@Ignore("some message here")
public class TestNGIgnoreDependencyWithOverride extends TestNGDependenciesBase {
    /*
    nu functioneaza 100% cum ma asteptam, la run se ruleaza testSomething() de aici
    care e gol, drept urmare nu se mai "ruleaza" testul
    ma asteptam sa nu se mai ruleze deloc
     */
    @Override
    public void testSomething() {

    }
}
