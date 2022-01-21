package Objects;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Objects;
import java.util.Map.Entry;

public class Noble {
	
	private final String name;
	private final int prestige_point = 3;
	private final HashMap<Token,Integer> bonus_required;
	
	public Noble(String name, int blanc, int bleu, int vert, int rouge, int noir) {
		Objects.requireNonNull(name);
		this.name = name;
		this.bonus_required = init_bonus_required(blanc,bleu,vert,rouge,noir);
	}
	
	//Initialise les bonus requis pour la visite d'un noble
	public HashMap<Token,Integer> init_bonus_required(int blanc, int bleu, int vert, int rouge, int noir){
		var tmp_bonus = new HashMap<Token,Integer>();
		tmp_bonus.put(new Token("blanc"), blanc);
		tmp_bonus.put(new Token("bleu"), bleu);
		tmp_bonus.put(new Token("vert"), vert);
		tmp_bonus.put(new Token("rouge"), rouge);
		tmp_bonus.put(new Token("noir"), noir);
		clear_map(tmp_bonus);
		return tmp_bonus;	
	}
	
	//Supprime les champs egaux à 0 dans le prix de la carte
	public static void clear_map(HashMap<Token,Integer> map) {
		Iterator<Entry<Token, Integer>> it = map.entrySet().iterator();
		while(it.hasNext()) {
			var tmp = it.next();
			if((tmp.getValue().equals(0)))
				it.remove();
		}
	}
	
	@Override
	public String toString() {
		var builder = new StringBuilder();
		builder.append(name + " points prestiges : " +prestige_point+" ");
		for(var val : this.bonus_required.entrySet()) {
			builder.append(val+" ");
		}
		builder.append("\n");
		return builder.toString();
	}

}
