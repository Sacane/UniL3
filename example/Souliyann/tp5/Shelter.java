package tp5;

import java.util.Objects;
import java.util.ArrayList;
import java.util.List;

public class Shelter {
	
	private final ArrayList<Dog>shelter;
	
	public Shelter(){
		this.shelter = new ArrayList<Dog>();
	}
	
	public void add(Dog dog){
		Objects.requireNonNull(dog);
		shelter.add(dog);
	}
	
	public List<Dog> removeAll(String name){
		
		var it  = shelter.iterator();
		List<Dog> list2 = new ArrayList<Dog>();
		
		while (it.hasNext()){
			var b = it.next();
			if(b.name().equals(name)){
				list2.add(b);
				it.remove();
				break;
			}
		}
		return list2;
	}
	
	public int biscuits(){
		
		int res = 0;
		var it  = shelter.iterator();
		while (it.hasNext()){
			var b = it.next();
			res += 7.3*b.weight();
		}
		return res;
	}
	
	
	@Override
    public String toString(){
		
    	StringBuilder chaine = new StringBuilder() ;
    	
    	for(var element : this.shelter){
    		chaine.append('\n');
    		chaine.append(element);
    	}
    	return chaine.toString();
    }

	
}
