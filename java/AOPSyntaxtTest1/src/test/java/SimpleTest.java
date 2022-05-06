import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.TestComponent;

@TestComponent
public class SimpleTest {

    @Test
    void testSomething() {
        System.out.println("test");
    }
}
