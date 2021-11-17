package tp5;

public class Main {
	
	public static void main(String[] args){
		/*
		var shelter = new Shelter();
		var scooby = new Dog("scooby doo", 21);
		var idefix = new Dog("idefix", 2);
		
		shelter.add(idefix);
		shelter.add(scooby);
		
		System.out.println(shelter);*/
		
		
		var shelter2 = new Shelter();
		shelter2.add(new Dog("scooby doo", 21));
		shelter2.add(new Dog("idefix", 2));
		shelter2.add(new Dog("pongo", 15));
		
		System.out.println(shelter2);
		System.out.println("biscuits " + shelter2.biscuits());
	    
	}
}
