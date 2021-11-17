import java.time.Duration;
import java.util.Objects;

public sealed interface Articles permits Articles.LaserDisc, VideoTape {

    String LASER_DISC ="LaserDisc";
    String VIDEO_TAPE ="VideoTape";

    String name();

    //Prend un article est le transforme en string
    default String toText() {
        return this.toString();
    }

    //Prend un string est le transforme en article
    static Articles fromText(String s) {
        var tab = s.split(":");
        return switch (tab[0]) {
            case LASER_DISC -> new LaserDisc(tab[1]);
            case VIDEO_TAPE -> new VideoTape(tab[1], Duration.ofMinutes(Integer.parseInt(tab[2])));
            default -> throw new IllegalArgumentException();
        };
    }

    record LaserDisc(String name) implements Articles{
        public LaserDisc {
            Objects.requireNonNull(name, "Name is null");
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            LaserDisc laserDisc = (LaserDisc) o;
            return Objects.equals(name, laserDisc.name);
        }

        @Override
        public int hashCode() {
            return Objects.hash(name);
        }

        @Override
        public String toString() {
            return LASER_DISC + ":" + name;
        }
    }
}
