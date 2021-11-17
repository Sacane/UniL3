import java.time.Duration;
import java.util.Objects;

public sealed interface Articles permits VideoTape, LaserDisc {
	
	static final String LASER_DISC ="LaserDisc";
	static final String VIDEO_TAPE ="VideoTape";
	
	
	public String name();
	
	public boolean equals(Articles a);

	default Duration duration() {
		return null;
	}
	
	//Prend un article est le transforme en string
	default String toText() {
		Objects.requireNonNull(this,"Articles is null");			
		return this.toString();
	}
	
	//Prend un string est le transforme en article
	public static Articles fromText(String s) {
		var tab = s.split(":");
		switch(tab[0]) {
			case LASER_DISC: return new LaserDisc(tab[1]);
			
			case VIDEO_TAPE: return new VideoTape(tab[1],Duration.ofMinutes(Integer.parseInt(tab[2])));
			
			default: throw new IllegalArgumentException();
		}
	}
}
