package fr.umlv.data;

public class LinkedList<T> {


    private int size;
    private Link<T> head;

    public LinkedList(){
        size = 0;
        this.head = null;
    }


    public void add(T value){
        size++;
        var tmp = head;
        this.head = new Link<T>(value, tmp);
    }

    @Override
    public String toString() {
        var builder = new StringBuilder();
        var tmp = head;
        while(tmp != null){
            builder.append(tmp.value()).append(" ");
            tmp = tmp.next();
        }
        return builder.toString();
    }

    public T get(int index){
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException("Invalid index");
        }
        int i;
        var tmp = head;

        for(i = 0; i != index; i++){
            tmp = tmp.next();
        }
        return tmp.value();
    }

    public boolean contains(Object o){

        for(var tmp = head; tmp != null; tmp = tmp.next()){
            if(o.equals(tmp.value())){
                return true;
            }
        }
        return false;
    }
}
