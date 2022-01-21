package Objects;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Map;
import java.util.Objects;
import java.util.Scanner;

public class BoardV2 extends Board{
	
	
	private ArrayList<Card> cards_on_board_lvl1; //carte niveau 1 sur le board
	private ArrayList<Card> cards_on_board_lvl2; //carte niveau 2 sur le board
	private ArrayList<Card> cards_on_board_lvl3; //carte niveau 3 sur le board
	private ArrayList<Card> stack_of_cards_lvl1; //pioche de carte lvl 
	private ArrayList<Card> stack_of_cards_lvl2; //pioche de carte lvl 2
	private ArrayList<Card> stack_of_cards_lvl3; //Pioche de carte lvl 3
	private ArrayList<Noble> stack_of_nobles; //Pioches des nobles
	private ArrayList<Noble> nobles_on_board; //Nobles sur le terrain
	
	
	public BoardV2(int nb_players) throws IOException {
		super(nb_players);
		this.stack_of_cards_lvl1 = new ArrayList<Card>();
		this.stack_of_cards_lvl2 = new ArrayList<Card>();
		this.stack_of_cards_lvl3 = new ArrayList<Card>();
		this.stack_of_nobles = new ArrayList<Noble>();
		this.load_card(Paths.get("src/Splendor_Card_list.txt")); //Remplis les tas de cartes a partir du fichier txt
		this.load_nobles(Paths.get("src/Splendor_Nobles.txt")); //Remplis le tas de carte noble a partir du fichier txt
		this.cards_on_board_lvl1 = init_4_cards(stack_of_cards_lvl1);
		this.cards_on_board_lvl2 = init_4_cards(stack_of_cards_lvl2);
		this.cards_on_board_lvl3 = init_4_cards(stack_of_cards_lvl3);
		this.nobles_on_board = init_nobles_on_board(stack_of_nobles);
	}
	
	
	//Renvois la carte correspondant a la ligne lu dans le fichier txt des cartes
	public static Card cardfromText(String s) {
		var tab = s.replaceAll("\\s+","").split(":"); //Separe la ligne recuperer avec ":" comme separateur dans un tableau tab, efface aussi les espaces blancs dans la chaine recuperer
		switch(tab[0]) { //On regarde le debut de la ligne recuperer
			case "niveau_1" : return new Card(1,Integer.parseInt(tab[1]),tab[2],Integer.parseInt(tab[3]),Integer.parseInt(tab[4]),Integer.parseInt(tab[5]),Integer.parseInt(tab[6]),Integer.parseInt(tab[7]));
			
			case "niveau_2" : return new Card(2,Integer.parseInt(tab[1]),tab[2],Integer.parseInt(tab[3]),Integer.parseInt(tab[4]),Integer.parseInt(tab[5]),Integer.parseInt(tab[6]),Integer.parseInt(tab[7]));
			
			case "niveau_3" : return new Card(3,Integer.parseInt(tab[1]),tab[2],Integer.parseInt(tab[3]),Integer.parseInt(tab[4]),Integer.parseInt(tab[5]),Integer.parseInt(tab[6]),Integer.parseInt(tab[7]));
			
			default: throw new IllegalArgumentException();
		}
	}
	
	//Charge les cartes du jeu du fichier txt dans les tas de cartes
	public void load_card(Path path) throws IOException {
		try(var reader = Files.newBufferedReader(path)){
			String line;
			while((line = reader.readLine())!=null){
				if(cardfromText(line).level() == 1) {this.stack_of_cards_lvl1.add(cardfromText(line));} // Si la carte recup est de lvl 1 on l'ajoute au tas de carte lvl 1
				else if(cardfromText(line).level() == 2) {this.stack_of_cards_lvl2.add(cardfromText(line));}
				else if(cardfromText(line).level() == 3) {this.stack_of_cards_lvl3.add(cardfromText(line));}
			}
		}
	}
	
	//Renvoi le noble correpondant a la ligne lu dans le fichier txt
	public static Noble noblefromText(String s) {
		Objects.requireNonNull(s);
		var tab = s.replaceAll("\\s+","").split(":");//Separe la ligne recuperer avec ":" comme separateur dans un tableau tab, efface aussi les espaces blancs dans la chaine recuperer
		return new Noble(tab[0],Integer.parseInt(tab[1]),Integer.parseInt(tab[2]),Integer.parseInt(tab[3]),Integer.parseInt(tab[4]),Integer.parseInt(tab[5])); //renvoi une carte noble avec les infos recup sur la ligne lu dans le fichier txt
	}
	
	//charge les nobles depuis un fichier txt dans le tas de noble
	public void load_nobles(Path path) throws IOException {
		try(var reader = Files.newBufferedReader(path)){
			String line;
			while((line = reader.readLine())!=null){
				this.stack_of_nobles.add(noblefromText(line));
			}
		}
	}
	
	//renvoie une carte au hasard dans la tas de carte c
	public Card draw(ArrayList<Card> c) {
		int n = (int)(Math.random() * c.size());
		var draw_card = c.get(n);
		c.remove(n);
		return draw_card;
	}
	
	//init 4 cartes du tas correposndant card
	public ArrayList<Card> init_4_cards(ArrayList<Card> card) {
		var lst = new ArrayList<Card>();
		for(int i = 0;i < 4;i++) {
			var tmp = draw(card);
			lst.add(tmp);
		}
		return lst;
	}
	
	//renvoie une carte au hasard dans la tas de noble 
		public Noble draw_noble(ArrayList<Noble> noble) {
			int n = (int)(Math.random() * noble.size());
			var draw_card = noble.get(n);
			noble.remove(n);
			return draw_card;
		}
		
	//init 4 cartes sur le board des nobles
	public ArrayList<Noble> init_nobles_on_board(ArrayList<Noble> noble) {
		var lst = new ArrayList<Noble>();
		for(int i = 0;i < nb_players() +1;i++) {
			var tmp = draw_noble(noble);
			lst.add(tmp);
		}
		return lst;
	}
	
	//Renvoie la carte choisis dans la liste c
	public Card choose_card_V2(ArrayList<Card> c) {
		Scanner s = new Scanner(System.in);
		int res;
		do {
			System.out.println("Quels cartes voulez vous choisir (1-4) ?");
			while(!(s.hasNextInt())){
				System.out.println("Reessayer");
				s.next();
			}
			res = s.nextInt();
		}while(res<1 || res >4);		
		return c.get(res-1);
	}
	
	//renvoie la liste de carte sur le board correspondant au level
	public ArrayList<Card> which_board_list(int level){
		switch(level) {
		case 1 : return this.cards_on_board_lvl1;
		case 2 : return this.cards_on_board_lvl2;
		case 3 : return this.cards_on_board_lvl3;
		default : throw new IllegalArgumentException("Invalid level");
		}
	}
	
	//renvoie la pile de carte correspondant au level
	public ArrayList<Card> which_stack_of_card(int level){
		switch(level) {
		case 1 : return this.stack_of_cards_lvl1;
		case 2 : return this.stack_of_cards_lvl2;
		case 3 : return this.stack_of_cards_lvl3;
		default : throw new IllegalArgumentException("Invalid level");
		}
	}
	
	//renvoi le nb de joker restant
	public int number_of_golden_token() {
		return this.stacks_of_tokens().get(new Token("or"));
	}
	
	@Override
	public String toString() {
		var builder = new StringBuilder();
		int i = 1; //Number of the card
		for(Map.Entry<Token,Integer> elm : this.stacks_of_tokens().entrySet()) { //Affiche les tas de tokens
			builder.append(elm.getKey().toString() + " " +elm.getValue()+"\n");
		}
		
		builder.append("========Card_Nobles========\n");
		for(var elm : this.nobles_on_board) {
			builder.append(elm.toString()+"\n");
		}
		
		builder.append("========Card_level_3========\n");
		for(var elm : this.cards_on_board_lvl3) {
			builder.append(i+"."+elm.toString()+"\n");
			i++;
		}
		builder.append("========Card_level_2========\n");
		for(var elm : this.cards_on_board_lvl2) {
			builder.append(i+"."+elm.toString()+"\n");
			i++;
		}
		builder.append("========Card_level_1========\n");
		for(var elm : this.cards_on_board_lvl1) {
			builder.append(i+"."+elm.toString()+"\n");
			i++;
		}
		
		
		return builder.toString();
	}
		
	
	
	
	
	
	public static void main(String[] args) throws IOException {
		var test = new BoardV2(4);
		System.out.println(test);
		
		
	}

}
