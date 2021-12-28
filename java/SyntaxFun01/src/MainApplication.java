import com.adrianpoplesanu.function01.FunctionPointerTest;
import com.adrianpoplesanu.function01.PredicatePointerTest;

public class MainApplication {
    public static void main(String[] args) {
        System.out.println("running all syntax fun snippets...");
        FunctionPointerTest functionPointerTest = new FunctionPointerTest();
        functionPointerTest.testFunctionMethod();

        PredicatePointerTest predicatePointerTest = new PredicatePointerTest();
        predicatePointerTest.testPredicatePointer();
        predicatePointerTest.testPredicatePointer2();
    }
}
