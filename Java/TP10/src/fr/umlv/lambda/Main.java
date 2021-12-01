package fr.umlv.lambda;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        var list = new ArrayList<String>();

        list.add("foo");
        list.add("bar");
        list.add("foo");
        Lambdas.upperCaseAll(list);
        System.out.println(Lambdas.occurences(list));
    }
}
