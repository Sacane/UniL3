package Objects;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.Scanner;


public class PlayerV2 extends Player{
	
	private final ArrayList<Card> card_reserved; //carte reserve par le joueur
	private final int player_number; //numero du joueur
	private int golden_token = 0; //nb de jetons or
	
	public PlayerV2(String name,int player_number) {
		super(name);
		this.player_number = player_number;
		this.card_reserved = new ArrayList<Card>();
	}
	

	@Override
	public HashMap<Token,Integer> init_token_stacks(){
		var tmp = new HashMap<Token,Integer>();
		tmp.put(new Token("bleu"), 0);
		tmp.put(new Token("vert"), 0);
		tmp.put(new Token("rouge"),0);
		tmp.put(new Token("blanc"), 0);
		tmp.put(new Token("noir"), 0);
		tmp.put(new Token("or"), 0);
		return tmp;
	}
	
	//Ajoute une carte à la liste des cartes reserve
	public void add_new_reserved_card(Card c) {
		Objects.requireNonNull(c,"reserved card is null");
		this.card_reserved.add(c);
	}
	
	//Supprime la carte reserve a l'index index dans la liste des cartes reserves du joueur
	public void delete_reserved_card(int index) {
		if(index > 3 || index <= 0) {throw new IllegalArgumentException("Index invalid");}
		this.card_reserved.remove(index-1);
	}
	
	//Renvoie true si 3 cartes reserve dans la main du joueur
	public boolean too_much_reserved_card() {
		if(this.card_reserved.size()==3) {return true;}
		return false;
	}
	
	//ajoute un jetons or joker au nombre possede par le joueur
	public void add_new_golden_joker() {
		this.golden_token++;
	}
	
	//Renvoie true si le joueur a plus de 10 tokens (joker compris)
	@Override
	public boolean too_much_token() {
		int cpt = 0;
		for(Map.Entry<Token,Integer> elm : this.player_tokens().entrySet()) {
			cpt+= elm.getValue();
		}
		cpt+= this.golden_token;
		if(cpt>10) {return true;}
		return false;
	}
	
	//Renvoi true si le joueur � 9 tokens ou moins sinon false
	public boolean can_get_last_token() {
		int cpt = 0;
		for(Map.Entry<Token,Integer> elm : this.player_tokens().entrySet()) {
			cpt+= elm.getValue();
		}
		cpt+= this.golden_token;
		if(cpt<=9) {return true;}
		return false;
	}
	
	@Override
	public String toString() {
		var builder = new StringBuilder();
		int i = 1;
		builder.append("==="+this.name()+"===\n").append("Points prestiges : "+this.point()+"\n");
		builder.append("=Tokens=\n");
		builder.append("JOKER OR : "+this.golden_token+"\n");
		for(Map.Entry<Token,Integer> elm : this.player_tokens().entrySet()) {
			if(!(elm.getValue().equals(0)))
				builder.append(elm.getKey().toString() + " " +elm.getValue()+"\n");
		}
		builder.append("=Bonus=\n");
		for(Map.Entry<String,Integer> elm : this.player_bonus().entrySet()) {
			if(!(elm.getValue().equals(0)))
				builder.append(elm.getKey().toString() + " " +elm.getValue()+"\n");
		}
		if(!(this.card_reserved.isEmpty())) {
			builder.append("=Reserved_Card=\n");
		}
			for(var elem : this.card_reserved) {builder.append(i+"."+elem.toString()+"\n");
		}
		return builder.toString();
	}
	

}
