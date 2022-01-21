package Objects;

import java.io.IOException;
import java.nio.file.*;
import java.util.ArrayList;

public class test {
	private ArrayList<Card> Card_lvl1;
	private ArrayList<Card> Card_lvl2;
	private ArrayList<Card> Card_lvl3;
	
	public test() {
		this.Card_lvl1 = new ArrayList<Card>();
		this.Card_lvl2 = new ArrayList<Card>();
		this.Card_lvl3 = new ArrayList<Card>();
	}
	
	public static Card cardfromText(String s) {
		var tab = s.replaceAll("\\s+","").split(":");
		switch(tab[0]) {
			case "niveau_1" : return new Card(1,Integer.parseInt(tab[1]),tab[2],Integer.parseInt(tab[3]),Integer.parseInt(tab[4]),Integer.parseInt(tab[5]),Integer.parseInt(tab[6]),Integer.parseInt(tab[7]));
			
			case "niveau_2" : return new Card(2,Integer.parseInt(tab[1]),tab[2],Integer.parseInt(tab[3]),Integer.parseInt(tab[4]),Integer.parseInt(tab[5]),Integer.parseInt(tab[6]),Integer.parseInt(tab[7]));
			
			case "niveau_3" : return new Card(3,Integer.parseInt(tab[1]),tab[2],Integer.parseInt(tab[3]),Integer.parseInt(tab[4]),Integer.parseInt(tab[5]),Integer.parseInt(tab[6]),Integer.parseInt(tab[7]));
			
			default: throw new IllegalArgumentException();
		}
	}
	
	
	public void load_card(Path path) throws IOException {
		try(var reader = Files.newBufferedReader(path)){
			String line;
			while((line = reader.readLine())!=null){
				if(cardfromText(line).level() == 1) {this.Card_lvl1.add(cardfromText(line));}
				else if(cardfromText(line).level() == 2) {this.Card_lvl2.add(cardfromText(line));}
				else if(cardfromText(line).level() == 3) {this.Card_lvl3.add(cardfromText(line));}
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		var t = new test();
		//Path test = Paths.get("Splendor_Card_list.txt");
		//System.out.println(test);
		t.load_card(Paths.get("src/Splendor_Card_list.txt"));
		System.out.println(t.Card_lvl1);
	}
}
