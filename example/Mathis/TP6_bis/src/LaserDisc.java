import java.util.Objects;

public final class LaserDisc implements Articles {
	private final String name;
	
	public LaserDisc(String name) {
		Objects.requireNonNull(name,"Name is null");
		this.name = name;
	}
	
	@Override
	public String toString() {
		return LASER_DISC+":"+name;
	}

	@Override
	public String name() {
		return this.name;
	}
	
	@Override
	public boolean equals(Articles a) {
		if(this.name.equals(a.name())) {
			return true;
		}
		return false;
	}
}
