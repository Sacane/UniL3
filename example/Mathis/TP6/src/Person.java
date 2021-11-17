public class Person {

    private int age;

    public Person(int age){
        if(age < 0){
            throw new IllegalArgumentException("Age can't be negativ");
        }
    }
}
