package tp5;

public record Dog(String name, int weight){
	public Dog{
		java.util.Objects.requireNonNull(name);
		if(weight <=0) {
			throw new IllegalArgumentException("weight <=0");
		}
	}
}
