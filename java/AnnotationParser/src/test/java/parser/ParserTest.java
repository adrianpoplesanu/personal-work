package parser;

import objects.Person;
import org.testng.annotations.Test;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.testng.Assert.assertTrue;

public class ParserTest {
    @Test
    public void test() {
        System.out.println("buna dimineata...");
    }

    @Test
    public void testReflection() {
        Object person = new Person();
        Field[] fields = person.getClass().getFields();
        List<String> actualFieldNames = new ArrayList<String>();
        for (Field field : fields) {
            actualFieldNames.add(field.getName());
        }
        assertTrue(Arrays.asList("name", "age").containsAll(actualFieldNames));
    }
}
