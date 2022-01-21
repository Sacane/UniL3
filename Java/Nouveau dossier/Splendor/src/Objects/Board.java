package Objects;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.Scanner;

public class Board {
	
	private int nb_players = 2;
	private ArrayList<Card> stack_of_cards; // Tas de cartes
	private ArrayList<Card> cards_on_board; //Cartes sur le terrain (4)
	private HashMap<Token,Integer> stacks_of_tokens; // Tas de tokens
	
	
	public Board() {
		this.stack_of_cards = init_stack_cards_smp();
		this.cards_on_board = init_4_cards();
		this.stacks_of_tokens = init_stacks_tokens_smp();
	}
	
	//Constructeur utilise pour la phase 2
	public Board(int number_of_player) {
		this.nb_players = number_of_player;
		this.stack_of_cards = null;
		this.cards_on_board = null;
		this.stacks_of_tokens = init_stacks_tokens();
	}

	

	/* @brief : Returns an ArrayList of cards as described in the description (8 cards of each color).
	 * @param : void
	 * @return : ArrayList<Card>, Describing a stack of 40 cards.
	 * */
	public static ArrayList<Card> initStackCardsSmp(){
		String[] color = {"vert","blanc","rouge","bleu","noir"};
		ArrayList<Card> stack_cards = new ArrayList<Card>();
		int i = 0;
		while(i < 5) {
			for(int j = 0; j < 8;j++) {
				stack_cards.add(new Card(color[i]));
			}
			i++;			
		}		
		return stack_cards;
	}
	
	//Initialise le tas de tokens en fonction du nombre de joueur
	public HashMap<Token,Integer> init_stacks_tokens(){
		HashMap<Token,Integer> tmp = new HashMap<>();
		int taille;
		if(nb_players == 4) {taille = 7;} //C'est mieux de faire un switch ici
		else if(nb_players == 3) {taille = 5;}
		else if(nb_players == 2) {taille = 4;}
		else {throw new IllegalArgumentException("Invalid number of players");}
		tmp.put(new Token("bleu"), taille);
		tmp.put(new Token("vert"), taille);
		tmp.put(new Token("rouge"), taille);
		tmp.put(new Token("blanc"), taille);
		tmp.put(new Token("noir"), taille);
		tmp.put(new Token("or"),5);
		return tmp;
	}
	

	/* @brief : Returns a HashMap<Token,Integer> describing the token stacks on the field at the beginning of the game.
	 * @param : void
	 * @return : HashMap<Token,Integer>
	 * */
	public static HashMap<Token,Integer> init_stacks_tokens_smp(){
		HashMap<Token,Integer> tmp = new HashMap<>();
		tmp.put(new Token("bleu"), 7);
		tmp.put(new Token("vert"), 7);
		tmp.put(new Token("rouge"), 7);
		tmp.put(new Token("blanc"), 7);
		tmp.put(new Token("noir"), 7);
		return tmp;
	}
	

	/* @brief : Returns a random card from the deck stack_of_cards.
	 * @param : void
	 * @return : Card draw_card, Card selected randomly in the deck. 
	 * */
	public Card draw() {
		int n = (int)(Math.random() * this.stack_of_cards.size());
		var draw_card = this.stack_of_cards.get(n);
		this.stack_of_cards.remove(n);
		return draw_card;
	}
	

	/* @brief : Returns an ArrayList of cards describing the cards visible on the field at the beginning of the game.
	 * @param : void
	 * @return : ArrayList<Card> lst, List containing cards showed on the board at beginning of the game.
	 * */
	public ArrayList<Card> init_4_cards() {
		var lst = new ArrayList<Card>();
		for(int i = 0;i < 4;i++) {
			var tmp = draw();
			lst.add(tmp);
		}
		return lst;
	}
	

	/* @brief : Return true if there is at least 4 tokens of the token t category.
	 * @param : Token t, Check the stack of this token.
	 * @return : boolean
	 * */
	public boolean check_4_tokens_in_stack(Token t) {
		Objects.requireNonNull(t);
		var value = this.stacks_of_tokens.get(t);
		if(value>=4) {return true;}
		return false;
	}
	
	/* @brief : Return true if the token t category stack is empty.
	 * @param : Token t, Check the stack of this token.
	 * @return : boolean
	 * */
	public boolean check_0_token_in_stack(Token t) {
		Objects.requireNonNull(t);
		var value = this.stacks_of_tokens.get(new Token(t.color().toLowerCase()));
		if(value<=0) {return true;}
		return false;
	}
	
	/* @brief : Delete a token of type Token t in his stack.
	 * @param : Token t, Check the stack of this token/
	 * @return : void
	 * */
	public void delete_token_board(Token t) {
		Objects.requireNonNull(t);
		var tmp = this.stacks_of_tokens.get(t);
		if(!(tmp.equals(0))) {
			this.stacks_of_tokens.replace(t, tmp-1);
			return;
		}
		throw new IllegalStateException("Impossible to delete non-existent tokens");	
	}
	

	/* @brief : Return true if the Player p can buy a card on the board else false.
	 * @param : Player p, player checked.
	 * @return : boolean
	 * */
	public boolean can_buy_card(Player p) {
		var map = new HashMap<Token,Integer>();
		map = p.get_map_of_owned_tokens(); 
		int buyable = 4;
		if(map.isEmpty()) {return false;}
		for(var card : this.cards_on_board) {
			for(Map.Entry<Token,Integer> price : card.price().entrySet()) {
				
				if(!(map.containsKey(price.getKey()))) {
						buyable--;
						break;
				}
				var tmp = map.get(price.getKey());
				if(tmp < price.getValue()) { //if the number of tokens of the player is lower than the price of the card
					buyable--;
					break;
				}
			}
		}
		if(buyable <= 0) {return false;}
		return true;
	}
	

	/* @brief : Return true if the Player p can buy the Card c else false.
	 * @param : Player P, player checked.
	 * 			Card c, Card the player wanted to bought.
	 * @return : boolean
	 * */
	public boolean can_buy_a_card(Player p,Card c) {
		var map = new HashMap<Token,Integer>();
		map = p.get_map_of_owned_tokens();//Token du joueur
		for(Map.Entry<Token,Integer> price : c.price().entrySet()) {//On parcours les tokens du prix de la carte
			if(!(map.containsKey(price.getKey()))) {return false;}
			else if(price.getValue() > map.get(price.getKey())) {return false;}
		}
		return true;
	}
	

	/* @brief : Return card on the board chosen by the current player.
	 * @param : void
	 * @return : Card
	 * */
	public Card choose_card() {
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
		return this.cards_on_board.get(res-1);
	}
	
	
	/* @brief : Removes the Card c from the visible cards on the field.
	 * @param : Card card, Card deleted.
	 * @return : void
	 * */
	public void delete_card_on_board(Card card) {
		Objects.requireNonNull(card,"card is null");
		this.cards_on_board.remove(card);
	}
	
	/* @brief : Draw a card of the stack of cards and put it on the board.
	 * @param : void
	 * @return : void
	 * */
	public void add_new_card_on_board() {
		Card tmp = draw();
		this.cards_on_board.add(tmp);
	}
	
	
	/* @brief : Return true if there is a pile of tokens with at least 4 tokens left on the board.
	 * @param : void
	 * @return : boolean
	 * */
	public boolean check_one_4tokens_stack_exist() {
		int check = 0;
		for(Map.Entry<Token,Integer> elm : this.stacks_of_tokens.entrySet()) {
			if(check_4_tokens_in_stack(elm.getKey())) {check++;}
		}
		if(check>0) {return true;}
		return false;
	}
	

	/* @brief : Add a Token t in his stack.
	 * @param : Token t,
	 * @return : void
	 * */
	public void add_token_to_stack(Token t) {
		Objects.requireNonNull(t);
		var tmp = this.stacks_of_tokens.get(t);
		this.stacks_of_tokens.replace(t, tmp+1);
	}
	
	
	@Override
	public String toString() {
		int i = 1; //Number of the card
		var builder = new StringBuilder();
		builder.append("Taille du paquet de carte : "+this.stack_of_cards.size()+"\n");
		for(Map.Entry<Token,Integer> elm : this.stacks_of_tokens.entrySet()) {
			builder.append(elm.getKey().toString() + " " +elm.getValue()+"\n");
		}
		builder.append("\n");
		for(var elm : this.cards_on_board) {
			builder.append(i+"."+elm.toString()+"\n");
			i++;
		}
		return builder.toString();
	}
	
	//Remet dans le tas de jetons la liste de jetons lst
	public void put_tokens_back_in(HashMap<Token,Integer> lst,Player actual) {
		for(Map.Entry<Token,Integer> elem : lst.entrySet()) {
			this.stacks_of_tokens.replace(elem.getKey(), (this.stacks_of_tokens.get(elem.getKey()) + elem.getValue())-actual.player_bonus().get(elem.getKey().color()));
		}
		
	}
	
	
	
	
	public HashMap<Token,Integer> stacks_of_tokens(){
		return this.stacks_of_tokens;
	}
	
	public int nb_players() {
		return this.nb_players;
	}

}
