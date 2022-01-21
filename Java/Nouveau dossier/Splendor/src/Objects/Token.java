package Objects;

import java.util.Objects;

public record Token(String color) {
	
	public Token {
		Objects.requireNonNull(color, "color is null");
	}
	
	@Override
	public String toString() {
		switch(color.toLowerCase()) {
		case "vert" : return "Jeton emeraude";
		case "blanc" : return "Jeton diamant";
		case "rouge" : return "Jeton rubis";
		case "bleu" : return "Jeton saphir";
		case "noir" : return "Jeton onyx";
		case "or" : return "Jeton joker or";
		default: return "Color doesnt exist";
		}
	}
	
	
}
