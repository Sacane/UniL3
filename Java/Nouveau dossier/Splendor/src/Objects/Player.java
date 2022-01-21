package Objects;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class Player {
	
	private String name;
	private int point;
	private final HashMap<Token,Integer> player_tokens;
	private final ArrayList<Card> player_cards;
	private final HashMap<String,Integer> player_bonus;
	
	public Player(String name) {
		Objects.requireNonNull(name,"Name is null");
		this.name = name;
		this.point = 0;
		this.player_tokens = init_token_stacks();
		this.player_bonus = init_bonus();
		this.player_cards = new ArrayList<>();
	}
	
	/* @brief : Initializes a HashMap<Token,Integer> containing the different 
	 * fields of different tokens and their numbers. Represents the player's tokens.
	 * @param : void
	 * @return : HashMap<Token,Integer>, Contains data describing tokens owned by the player.
	 * */
	public HashMap<Token,Integer> init_token_stacks(){
		var tmp = new HashMap<Token,Integer>();
		tmp.put(new Token("bleu"), 0);
		tmp.put(new Token("vert"), 0);
		tmp.put(new Token("rouge"),0);
		tmp.put(new Token("blanc"), 0);
		tmp.put(new Token("noir"), 0);
		return tmp;
	}
	
	/* @brief : Initializes a HashMap<String,Integer> containing the different 
	 * fields of bonus and their numbers. Represents the player's bonus.
	 * @param : void
	 * @return : HashMap<String,Integer>, Contains data describing bonus owned by the player.
	 * */
	public HashMap<String,Integer> init_bonus(){
		var tmp = new HashMap<String,Integer>();
		tmp.put("bleu", 0);
		tmp.put("vert", 0);
		tmp.put("rouge",0);
		tmp.put("blanc", 0);
		tmp.put("noir", 0);
		return tmp;
	}
	
	
	/* @brief : Add a bonus s to the player.
	 * @param : String s, Represent the color of the bonus.
	 * @return : void
	 * */
	public void add_bonus(String s) {
		Objects.requireNonNull(s);
		var tmp = this.player_bonus.get(s);
		this.player_bonus.replace(s, tmp+1);
	}

	/* @brief : Add a token t to the player.
	 * @param : Token t, Represent the token.
	 * @return : void
	 * */
	public void add_token_player(Token t) {
		Objects.requireNonNull(t);
		var tmp = this.player_tokens.get(t);
		this.player_tokens.replace(t, tmp+1);
	}
	
	/* @brief : Delete a token t to the player.
	 * @param : Token t, Date representing a token.
	 * @return : void
	 * */
	public void delete_token_player(Token t) {
		Objects.requireNonNull(t);
		var tmp = this.player_tokens.get(t);
		if(!(tmp.equals(0))) {
			this.player_tokens.replace(t, tmp-1);
			return;
		}
	}
	

	/* @brief : Delete the player's tokens according to the price of card he bought.
	 * @param : Card c, Value representing the card bought by the player.
	 * @return : void
	 * */
	public void delete_token_from_purchase(Card c) {
		int cpt;
		for(Map.Entry<Token,Integer> elem : c.price().entrySet()) {
			cpt = elem.getValue() - this.player_bonus.get(elem.getKey().color());
			for(int i = 0; i < cpt;i++) {
				delete_token_player(elem.getKey());
			}
		}
	}
	

	/* @brief : Adds a card to the card(s) owned by the player.
	 * Includes prestige points, bonus and deletion of tokens used in the purchase.
	 * @param : Card c, Value representing the card bought by the player.
	 * @return : void
	 * */
	public void add_card_player(Card c) {
		Objects.requireNonNull(c, "Card is null");
		this.player_cards.add(c);
		this.point+= c.prestige_point();
		delete_token_from_purchase(c);
		add_bonus(c.bonus());
	}
	
	

	/* @brief : Returns a HashMap<Token,Integer> listing the tokens the player owns and applying the addition of these bonuses.
	 * @param : void
	 * @return : HashMap<Token,Integer>, Containing the addition of bonuses and tokens owned by the player.
	 * */
	public HashMap<Token,Integer> get_map_of_owned_tokens(){
		var map = new HashMap<Token,Integer>();
		for(Map.Entry<Token,Integer> elm : this.player_tokens.entrySet()) {
			map.put(elm.getKey(), elm.getValue());
			if(this.player_bonus.containsKey(elm.getKey().color().toLowerCase()) && !(this.player_bonus.get(elm.getKey().color()).equals(0))) {
				var tmp = map.get(elm.getKey());
				if(tmp!=null) {map.replace(elm.getKey(), tmp+this.player_bonus.get(elm.getKey().color()));}
			}
		}
		return map;
	}

	
	/* @brief : Returns True if the player has more than 10 tokens else false.
	 * @param : void
	 * @return : boolean
	 * */
	public boolean too_much_token() {
		int cpt = 0;
		for(Map.Entry<Token,Integer> elm : this.player_tokens.entrySet()) {
			cpt+= elm.getValue();
		}
		if(cpt>10) {return true;}
		return false;
	}
	
	@Override
	public String toString() {
		var builder = new StringBuilder();
		builder.append("==="+this.name+"===\n").append("Points prestiges : "+this.point+"\n");
		builder.append("=Tokens=\n");
		for(Map.Entry<Token,Integer> elm : this.player_tokens.entrySet()) {
			if(!(elm.getValue().equals(0)))
				builder.append(elm.getKey().toString() + " " +elm.getValue()+"\n");
		}
		builder.append("=Bonus=\n");
		for(Map.Entry<String,Integer> elm : this.player_bonus.entrySet()) {
			if(!(elm.getValue().equals(0)))
				builder.append(elm.getKey().toString() + " " +elm.getValue()+"\n");
		}
		return builder.toString();
	}

	/* @brief : Return the name of the player.
	 * @param : void
	 * @return : String name, Name of the current player.
	 * */
	public String name() {
		return this.name;
	}
	
	/* @brief : Return the number of point of the player. 
	 * @param : void
	 * @return : int point, Representing the number of point of the current player.
	 * */
	public int point() {
		return this.point;
	}
	
	public HashMap<String,Integer> player_bonus() {
		return this.player_bonus;
	}
	
	public HashMap<Token,Integer> player_tokens() {
		return this.player_tokens;
	}
	
	public static void change_name(String name, Player p) {
		p.name = name;
	}

}
