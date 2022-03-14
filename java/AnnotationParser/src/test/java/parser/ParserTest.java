package parser;

import annotations.Version;
import objects.Person;
import org.testng.annotations.Test;

import java.lang.annotation.Annotation;
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
        Field[] fields = person.getClass().getDeclaredFields();
        List<String> actualFieldNames = new ArrayList<String>();
        for (Field field : fields) {
            actualFieldNames.add(field.getName());
        }
        assertTrue(Arrays.asList("name", "age").containsAll(actualFieldNames));
    }

    @Test
    public void testAnnotationOnField() {
        Object person = new Person();
        Field[] fields = person.getClass().getDeclaredFields();
        //List<String> actualFieldNames = new ArrayList<String>();
        for (Field field : fields) {
            //if (field.isAnnotationPresent(Version.class)) {
            //    System.out.println(field.getName() + " are Version");
            //}
            System.out.println(field.getName());
            Annotation[] annotations = field.getAnnotations();
            for (Annotation annotation : annotations) {
                System.out.println(annotation.annotationType().getName());
            }
        }
    }
}
