package fr.umlv.data.Main;


import fr.umlv.data.LinkedList;

public class main {

    public static void main(String[] args) {
        var linkedList = new LinkedList<Integer>();

        linkedList.add(10);
        linkedList.add(143);
        System.out.println(linkedList);
        System.out.println(linkedList.get(1));

        System.out.println("Exo 2 ======");

        var l2 = new LinkedList<String>();
        l2.add("object 1");
        l2.add("object 2");

        System.out.println((l2.get(1)).length());

        System.out.println(l2.contains("object 1")); // true
        System.out.println(l2.contains("object 3")); // false
        System.out.println(l2.contains(2));         // false
    }
}
