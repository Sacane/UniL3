import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Objects;

public class Catalog {
    /* <Nom d'article, article> */
    private final static HashMap<String, Articles> catalog = new HashMap<>();

    public void add(Articles a) throws IllegalStateException {
        Objects.requireNonNull(a,"Articles is null");

        var result = catalog.putIfAbsent(a.name(), a);
        if(result != null){
            throw new IllegalStateException("Already an article with the name " + a.name());
        }

    }
    public Articles lookup(String name){
        Objects.requireNonNull(name);
        return catalog.get(name);
    }



    public void save(Path path) throws IOException {
            var writer = Files.newBufferedWriter(path);
            for (var article : catalog.entrySet()) {
                writer.write(article.getValue().toText());
                writer.newLine();
            }
            writer.close();
    }


    public static void load(Path path, Charset c) throws IOException {
        try(var reader = Files.newBufferedReader(path,c)){
            String line;
            while((line = reader.readLine()) != null){
                var article = Articles.fromText(line);
                catalog.put(article.name(), article);
            }
        }

    }

}
