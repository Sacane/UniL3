import java.time.Duration;
import java.util.Objects;

public final class VideoTape implements Articles {
	private final String name;
	private final Duration duration;
	
	public VideoTape(String name, Duration duration) {
		Objects.requireNonNull(name,"Name is null");
		Objects.requireNonNull(duration,"Duration is null");
	
		if(duration.isZero() || duration.isNegative()) {
			throw new IllegalArgumentException("Duration negative or equal to zero");
		}
		
		this.name = name;
		this.duration = duration;
	}
	
	@Override
	public String toString() {
		return VIDEO_TAPE+":"+this.name()+":"+this.duration().toMinutes();
	}

	@Override
	public String name() {
		return this.name;
	}
	
	@Override
	public Duration duration() {
		return this.duration;
	}
	
	@Override
	public boolean equals(Articles a) {
		if(this.name.equals(a.name()) && this.duration.equals(a.duration())) {
			return true;
		}
		return false;
	}
	
}
