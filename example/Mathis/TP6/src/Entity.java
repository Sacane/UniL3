public class Entity {

    private String name;
    private int age;
    private boolean isStudent;


    public Entity(String name, int age, boolean isStudent){
        this.age = age;
        this.name = name;
        this.isStudent = isStudent;
    }

    public Entity(String name, int age){
        this.isStudent = true;
        this.age = age;
        this.name = name;
    }

    public boolean doSmth() throws IllegalStateException{
        if(age + 100 < 130){
            throw new IllegalStateException("Age exception");
        }
        return true;
    }




    @Override
    public String toString() {
        return "Entity{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", isStudent=" + isStudent +
                '}';
    }
}
