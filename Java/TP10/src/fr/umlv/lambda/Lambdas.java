package fr.umlv.lambda;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Lambdas {

    public static void upperCaseAll(List<String> strList){
        strList.replaceAll(String::toUpperCase);
    }

    public static <T> Map<T, Integer> occurences(List<T> strList){
        var map = new HashMap<T, Integer>();

        strList.forEach(s -> map.merge(s, 1, Integer::sum));

        return map;
    }


}
