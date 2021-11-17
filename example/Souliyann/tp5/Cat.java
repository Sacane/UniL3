package tp5;

public record Cat(String name, int biscuits) {
	
	public Cat{
		java.util.Objects.requireNonNull(name);
		if(biscuits <=0) {
			throw new IllegalArgumentException("biscuits <=0");
		}
	}
}
