import org.testng.annotations.Test;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class Main {

    public static void main(String[] args) {

        Class clazz = null;
        try {
            clazz = Class.forName("student.Student");

        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        System.out.println();
        System.out.println("The methods are:");
        assert clazz != null;
        Method[] methodList = clazz.getDeclaredMethods();
        for (Method method : methodList) {
            System.out.println(method.toString());
        }

        System.out.println();
        System.out.println("The constructors are:");
        Constructor[] constructorList = clazz.getDeclaredConstructors();
        for (Constructor constructor : constructorList) {
            System.out.println(constructor.toString());
        }

        System.out.println();
        System.out.println("The fields are:");
        Field[] fieldList = clazz.getDeclaredFields();
        for (Field field : fieldList) {
            System.out.println(field.toString());
        }

        System.out.println();
        System.out.println("The test methods are:");
        Method[] methodList2 = clazz.getDeclaredMethods();
        for (Method method : methodList2) {
            if (method.isAnnotationPresent(Test.class) == true) {
                System.out.println(method);
            }
        }

    }

}
