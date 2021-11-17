import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Objects;

public class Catalog {
	private final ArrayList <Articles> catalog;
	
	public Catalog() {
		this.catalog = new ArrayList<>();
	}
	
	public void add(Articles a) {
		Objects.requireNonNull(a,"Articles is null");
		
		for(var tmp : this.catalog) {
			if(tmp.name().equals(a.name())) {
				throw new IllegalStateException("Already Exist Article with same name");
			}	
		}
		this.catalog.add(a);	
	}
	
	public Articles lookup(String name) {
		for(var tmp : this.catalog) {
			if(tmp.name().equals(name)) {
				return tmp;
			}
		}
		return null;
	}
	
	public void save(Path path, Charset c) throws IOException {
		try(var writer = Files.newBufferedWriter(path,c)){
			for(var line: this.catalog) {
				writer.write(line.toText());
				writer.newLine();
			}
		}
	}
	
	public void load(Path path, Charset c) throws IOException {
		try(var reader = Files.newBufferedReader(path,c)){
			String line;
			while((line = reader.readLine())!=null){
				this.catalog.add(Articles.fromText(line));
			}
		}
		
	}
	
}
