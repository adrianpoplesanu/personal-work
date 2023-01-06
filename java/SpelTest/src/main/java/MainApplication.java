import org.springframework.expression.EvaluationContext;
import org.springframework.expression.Expression;
import org.springframework.expression.ExpressionParser;
import org.springframework.expression.spel.standard.SpelExpressionParser;
import org.springframework.expression.spel.support.StandardEvaluationContext;

import java.util.HashMap;

public class MainApplication {

    private void simpleTest() {
        ExpressionParser parser = new SpelExpressionParser();
        Expression exp = parser.parseExpression("'Hello World'.concat('!')");
        String message = (String) exp.getValue();
        System.out.println(message);
    }

    private void inferenceTest() {
        TestObject testObject = new TestObject(5);
        ExpressionParser parser = new SpelExpressionParser();
        Expression exp = parser.parseExpression("a");
        EvaluationContext context = new StandardEvaluationContext(testObject);
        int value = (Integer) exp.getValue(context);
        System.out.println(value);
    }

    private void inferenceTest2() {
        TestObject testObject = new TestObject(5);
        ExpressionParser parser = new SpelExpressionParser();
        Expression exp = parser.parseExpression("a == 6");
        EvaluationContext context = new StandardEvaluationContext(testObject);
        boolean value = (Boolean) exp.getValue(context);
        System.out.println(value);
    }

    private void inferenceTest3() {
        HashMap<String, String> cities = new HashMap<String, String>() {
            {
                put("New York", "5 star");
                put("Vienna", "4 star");
                put("Cairo", "2 star");
                put("Mulano", "7 star");
            }
        };

        ExpressionParser parser = new SpelExpressionParser();
        EvaluationContext context = new StandardEvaluationContext(cities);
        Expression exp = parser.parseExpression("get(\"New York\")");
        String result = (String) exp.getValue(context);
        System.out.println(result);
    }

    public static void main(String[] args) {
        MainApplication mainApplication = new MainApplication();
        mainApplication.simpleTest();
        mainApplication.inferenceTest();
        mainApplication.inferenceTest2();
        mainApplication.inferenceTest3();
    }
}
