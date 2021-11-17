import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Path;
import java.time.Duration;

public class Main {

	public static void main(String[] args) throws IOException {
		var laserDisc = new LaserDisc("Jaws");
	    var videoTape = new VideoTape("The Cotton Club", Duration.ofMinutes(128));
	    var laserDiscText = laserDisc.toText();
	    var videoTapeText = videoTape.toText();
	    System.out.println(laserDiscText);
	    System.out.println(videoTapeText);
	    var laserDisc2 = Articles.fromText(laserDiscText);
	    var videoTape3 = Articles.fromText(videoTapeText);
	    System.out.println(laserDisc.equals(laserDisc2));  // true
	    System.out.println(videoTape.equals(videoTape3));  // true
	    //var catalog2 = new Catalog();
	    //catalog2.add(laserDisc);
	    //catalog2.add(videoTape);
	    //catalog2.save(Path.of("catalog.txt"));
	    // var catalog3 = new Catalog();
	    //catalog3.load(Path.of("catalog.txt"));
	    //System.out.println(catalog3.lookup("Jaws"));  // LaserDisc:Jaws
	    //System.out.println(catalog3.lookup("The Cotton Club"));  // VideoTape:The Cotton Club:128
	    var catalog4 = new Catalog();
	    catalog4.add(new LaserDisc("A Fistful of €"));
	    catalog4.add(new VideoTape("For a Few €s More", Duration.ofMinutes(132)));
	    catalog4.save(Path.of("catalog-windows-1252.txt"), Charset.forName("Windows-1252"));

	    var catalog5 = new Catalog();
	    catalog5.load(Path.of("catalog-windows-1252.txt"), Charset.forName("Windows-1252"));
	    System.out.println(catalog5.lookup("A Fistful of €"));
	    System.out.println(catalog5.lookup("For a Few €s More"));
	    
	}
}

//2) The return type of the method "add" must be void.
//The return type of the method lookup must be Articles because we return the article that corresponds to the name otherwise null.
//3)We don't know what is the type of the object recognized between LaserDisc and VideoTape so a static is better for the "fromtext" method.
//Sealed or not ? Yes, you have to use the sealed keyword, you just allow videoTape, LaserDisc.
//Sealed or not, you have to use the keyword sealed, you just allow videoTape, LaserDisc... //it would make a mess with fromText if you add another article.
//4)we use Files.newBufferedWriter(path) to create a writer on a txt file
//To guarantee that the system resource has been released, we use a try-with-resources.
//We must "throws IOException" to manage the input and output.
