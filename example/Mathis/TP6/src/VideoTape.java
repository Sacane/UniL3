import java.time.Duration;
import java.util.Objects;

public record VideoTape(String name, Duration duration) implements Articles {

    public VideoTape {
        Objects.requireNonNull(name, "Name is null");
        Objects.requireNonNull(duration, "Duration is null");

        if (duration.isZero() || duration.isNegative()) {
            throw new IllegalArgumentException("Duration negative or equal to zero");
        }
    }

    @Override
    public String toString() {
        return VIDEO_TAPE + ":" + name + ":" + duration.toMinutes();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        VideoTape videoTape = (VideoTape) o;
        return Objects.equals(name, videoTape.name) && Objects.equals(duration, videoTape.duration);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, duration);
    }


}
