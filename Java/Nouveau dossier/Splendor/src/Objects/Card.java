package Objects;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Objects;

public class Card {
	
	private final int level;
	private final int prestige_point;
	private final String bonus; //bonus
	private final HashMap<Token,Integer> price;
	private final boolean reserved;
	
	public Card(String bonus) {
		Objects.requireNonNull(bonus,"Color is null");
		this.level = 1;
		this.prestige_point = 1;
		this.bonus = bonus; //bonus
		this.price = init_price_smp();
		this.reserved = false;
	}
	
	public Card(int level, int prestige_point, String bonus, int blanc, int bleu, int vert, int rouge, int noir) {
		Objects.requireNonNull(bonus,"bonus is null");
		if((level <= 0 || level > 3) || (prestige_point <= 0)) {
			throw new IllegalArgumentException("level is negative or superior to 3 OR prestige point is negative");
		}
		this.level = level;
		this.prestige_point = prestige_point;
		this.bonus = bonus;
		this.price = init_price(blanc, bleu, vert, rouge, noir);
		this.reserved = false;
	}
	
	
	//Initialise le prix d'une carte pour la phase2
	public HashMap<Token,Integer> init_price(int blanc, int bleu, int vert, int rouge, int noir){
		var tmp_price = new HashMap<Token,Integer>();
		tmp_price.put(new Token("blanc"), blanc);
		tmp_price.put(new Token("bleu"), bleu);
		tmp_price.put(new Token("vert"), vert);
		tmp_price.put(new Token("rouge"), rouge);
		tmp_price.put(new Token("noir"), noir);
		clear_map(tmp_price);
		return tmp_price;	
	}
	
	//Supprime les champs egaux � 0 dans le prix de la carte phase 2
	public static void clear_map(HashMap<Token,Integer> map) {
		Iterator<Entry<Token, Integer>> it = map.entrySet().iterator();
		while(it.hasNext()) {
			var tmp = it.next();
			if((tmp.getValue().equals(0)))
				it.remove();
		}
	}
	
	
	
	
	/* @brief : Initializes the "price" field of a card from phase 1 and returns it.
	 * @param : void
	 * @return :HashMap<Token,Integer>, Contains data describing the price of a card.
	 * */
	public HashMap<Token,Integer> init_price_smp() {
		String[] color = {"vert","blanc","rouge","bleu","noir"};
		ArrayList<String> sublist = new ArrayList<String>(Arrays.asList(color));
		HashMap<Token,Integer> tmp = new HashMap<>();;
		for(var elm : sublist) {
			if(elm.equals(this.bonus)) {
				tmp.put(new Token(elm), 3);
			}
		}
		return tmp;
	}
	
	@Override
	public String toString() {
		var builder = new StringBuilder();
		builder.append("Card : level-> "+level+", ").append("prestige_point-> "+prestige_point+", ");
		builder.append("Color-> "+bonus+", ");
		for(Map.Entry<Token,Integer> elem : price.entrySet()) {
			if(!(elem.getValue().equals(0)))
				builder.append(elem.getKey().toString()+" : "+elem.getValue()+", ");
		}
		builder.append("\n");
		return builder.toString();
	}
	
	/* @brief : Return "prestige_point" field of a card.
	 * @param : void
	 * @return : int prestige_point, Field corresponding to the points obtained when purchasing a card.
	 * */
	public int prestige_point() {
		return this.prestige_point;
	}
	
	/* @brief : Return "bonus" field of a card.
	 * @param : void
	 * @return : String bonus, Value describing the bonus of a card (his color).
	 * */
	public String bonus() {
		return this.bonus.toLowerCase();
	}
	
	
	/* @brief : Return "price" field of a card.
	 * @param : void
	 * @return : HashMap<Token,Integer>, Contains data describing the price of a card. 
	 * */
	public HashMap<Token,Integer> price(){
		return this.price;
	}
	
	public int level() {
		return this.level;
	}
	
	public boolean reserved() {
		return this.reserved;
	}
	

}
