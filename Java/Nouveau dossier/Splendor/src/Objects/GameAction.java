package Objects;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class GameAction {
	
	private final Player p1;
	private final Player p2;
	private final Board board;
	private Player actual_player;
	
	public GameAction() {
		this.p1 = init_player(1);
		this.p2 = init_player(2);
		this.board = new Board();
		this.actual_player = this.p1;//Le jeu commence avec le joueurs 1
	}								  //A modifier pour rajouter une methode pour decider
								     // qui commence/
	
        
	public GameAction(Board n,PlayerV2 n1,PlayerV2 n2) {
		this.p1 = n1;
		this.p2 = n2;
		this.board = n;
		this.actual_player = n1; //Le jeu commence avec le joueurs 1
	}	
	
		/* @brief : Change the field of the actual player with the other player.
		 * @param : void
		 * @return : void
		 * */
	    public void change_actual_player() {
			if(actual_player.equals(this.p1)) {change_player(p2);;}
			else {change_player(p1);}
		}
		
		/* @brief : Initialize the fields of a new player and return it.
		 * @param : int nb_player, the number of the player (if it's p1 or p2)
		 * @return : Player, player created.
		 * */
		public Player init_player(int nb_player) {
			if(nb_player<=0)
				throw new IllegalArgumentException("Number of player is negative or equal to 0");
			Scanner scan;
			String name = "";
			while(name.length()<=0) {
				System.out.println("Pseudo du joueur "+nb_player+" : ");
				scan = new Scanner(System.in);
				name = scan.nextLine();
			}
			return new Player(name);
		}
		

		/* @brief : Prints a reminder of the correspondence between tokens and colors.
		 * @param : void
		 * @return : void
		 * */
		public void rappel_color_tokens() {
			System.out.println("=======REMINDER======\n");
			System.out.println("Jeton saphir => bleu\n");
			System.out.println("Jeton rubis => rouge\n");
			System.out.println("Jeton emeraude => vert\n");
			System.out.println("Jeton onyx => noir\n");
			System.out.println("Jeton diamant => blanc\n");
			System.out.println("====================\n");
		}
		

		/* @brief : Returns true if the color in argument matches a token/color in the game.
		 * @param : String c, Color tested.
		 * @return : boolean
		 * */
		public static boolean color_exist(String c) {
			String[] color = {"vert","blanc","rouge","bleu","noir"};
			ArrayList<String> sublist = new ArrayList<String>(Arrays.asList(color));
			return sublist.contains(c);
		}
		
	
		/* @brief :Perform the necessary actions so that the player takes 3 tokens of different colors.
		 * Collect the tokens, check that they are valid and that they have not been chosen before.
		 * Check if there are tokens in the stack.
		 * if yes add the token to the list of chosen tokens.
		 * remove token from the stack on the board
		 * and add the token to the current player.
		 * @param : void
		 * @return : void
		 * */
		public void take_3_differents_tokens() {
			int essais,cpt = 0;
			var check = new ArrayList<String>();
			Scanner s;
			String res;
			rappel_color_tokens();
			while(cpt != 3) {
				essais = 0;
				do {
					System.out.println("Choix 1 : Quel couleur de jeton voulez vous prendre ("+this.actual_player.name()+")"+"(essais "+essais+") : ");
					s = new Scanner(System.in);
					res = s.nextLine();
					essais++;
				}while(!(color_exist(res.toLowerCase()) && !(check.contains(res.toLowerCase()))));
				if(this.board.check_0_token_in_stack(new Token(res.toLowerCase()))) {
					System.out.println("0 jeton disponible choisissez un autre\n");
				}else {
					check.add(res);
					this.board.delete_token_board(new Token(res.toLowerCase()));
					this.actual_player.add_token_player(new Token(res.toLowerCase()));
					cpt++;
				}
			}
		}
		

		/* @brief : Carry out the action of taking 2 tokens from the same stack only if there are at least 4 left.
		 * @param : void
		 * @return : void
		 * */
		public void take_2_same_tokens() {
			Scanner scan = new Scanner(System.in);
			String res;
			do {
				System.out.println("Couleur de la pile ou vous voulez prendre 2 jetons ? ("+this.actual_player.name()+")");
				res = scan.nextLine();
				while(!(color_exist(res.toLowerCase()))) {
					System.out.println("Ce n'est pas une couleur qui existe, reessayer : ");
					res = scan.nextLine();
				}
			}while(!(this.board.check_4_tokens_in_stack(new Token(res.toLowerCase()))));
			this.board.delete_token_board(new Token(res.toLowerCase()));
			this.board.delete_token_board(new Token(res.toLowerCase()));
			this.actual_player.add_token_player(new Token(res.toLowerCase()));
			this.actual_player.add_token_player(new Token(res.toLowerCase()));
		}
		

		/* @brief : Lets the current player buy a card, ask him which card he wants to buy,  
		 * check if he can afford it and add the card to the player.  
		 * Remove it from the board and add a new card to the board.
		 * @param : void
		 * @return : void
		 * */
		public void buy_card() {
			System.out.println(this.actual_player.name()+" veut acheter");
			Card tmp = this.board.choose_card();
			while(!(this.board.can_buy_a_card(actual_player, tmp))) {
				System.out.println("Vous ne pouvez pas acheter cette carte, prennez en une autre");
				tmp = this.board.choose_card();
			}
			this.board.put_tokens_back_in(tmp.price(),actual_player); //Remet les tokens dans le tas
			this.actual_player.add_card_player(tmp); //ajoute la carte au joueur
			this.board.delete_card_on_board(tmp); //supprime la carte du board
			this.board.add_new_card_on_board(); //ajoute une nouvelle carte au board
		}
		
		public boolean test() {
			return this.board.can_buy_card(actual_player);
		}
		
		/* @brief : Return true if the actual player has won.
		 * @param : void
		 * @return : boolean
		 * */
		public boolean end_game() {
			if(this.actual_player.point() == 15){
				return true;
			}
			return false;	
		}
		
		/* @brief : Ask the player what actions he wants to perform during his turn. 
		 * If he wants to buy a card, check if he can afford it.
		 *  If he wants to take 2 tokens in a row, check if there are at least 4 tokens
		 * @param : void
		 * @return : int choice, Number corresponding to the action wanted
		 * */
		public int choose_action() {
			int action_number = -1;
			int flag = 0;
			Scanner s = new Scanner(System.in);
			do {
				System.out.println("Quel action voulez vous effectuer ?");
				while(!(s.hasNextInt())) {
					System.out.println("Reessayer");
					s.next();
				}
				action_number = s.nextInt();
				if(action_number == 3 && !(this.board.can_buy_card(actual_player))){
					System.out.println("Vous n'avez pas de quoi acheter une carte");
					flag =1;
				}else if(action_number == 2 && !(this.board.check_one_4tokens_stack_exist())){
					System.out.println("Plus de tas d'au moins 4 jetons");
					flag=1;
				}else {flag = 0;}
			}while(action_number < 1 || action_number >3 || flag == 1);
			return action_number;
		}
		

		/* @brief : Management of a player's turn and his action during the turn.
		 * Passes to the next player at the end.
		 * @param : void
		 * @return : void
		 * */
		public void Player_turn() {
			int action;
			System.out.println("========================================");
			System.out.println("Le joueur : "+this.actual_player.name()+" commence a jouer");
			System.out.println("========================================");
			action = choose_action();
			switch(action) {
			case 1 : take_3_differents_tokens();
					 break;
			case 2 : take_2_same_tokens();
					 break;
					 
			case 3 : buy_card();
					 break;
			default : throw new IllegalArgumentException("Action dosnt exist");
			}
			
			if(this.actual_player.too_much_token()) {delete_too_much_tokens();}
			change_actual_player();
		}
		
		
		/* @brief : Asks which tokens the player wants to remove if he has too many and puts them back in their piles on the board.
		 * @param : void
		 * @return : void
		 * */
		public void delete_too_much_tokens() {
			Scanner s = new Scanner(System.in);
			String res;
			System.out.println("Oh mon dieu vous avez trop de jetons veuillez en remettre sur le plateau!");
			do {
				System.out.println("Quel jeton voulez vous remettre ? (couleur)");
				res = s.nextLine();
				while(!(color_exist(res.toLowerCase())) || res.toLowerCase().equals("or")) {
					System.out.println("Ce n'est pas une couleur qui existe, reessayer !");
					res = s.nextLine();
				}
				this.actual_player.delete_token_player(new Token(res.toLowerCase()));
				this.board.add_token_to_stack(new Token(res.toLowerCase()));
			}while(this.actual_player().too_much_token());
		}
		
		
		@Override
		public String toString() {
			var builder = new StringBuilder();
			builder.append("======GAME SITUATION======\n");
			builder.append(this.board.toString()+"\n");
			builder.append(this.p1.toString()+"\n");
			builder.append(this.p2.toString()+"\n");
			return builder.toString();
		}
		
		/* @brief : Return the actual player
		 * @param : void
		 * @return : Player p, current player
		 * */
		public Player actual_player() {
			return this.actual_player;
		}
		
		/*public PlayerV2 actual_player_v2() {
			return this.actual_player_v2;
		}*/
		
		public Player p1() {
			return this.p1;
		}
		
		public Player p2() {
			return this.p2;
		}
		
		public void change_player(Player p) {
			this.actual_player = p;
		}
		
		public static void change_actual_playerv2(PlayerV2 p, PlayerV2 actual) {
			actual = p;
		}
		
		
		/* @brief : Method launching the game in phase 1.
		 * Shows the winning player at the end.
		 * @param : void
		 * @return : void
		 * */
		public void jeu_v1() {
			System.out.println(this);
			while(!(this.end_game())){
				Player_turn();
				if(this.end_game()) {break;}
				System.out.println(this);
				Player_turn();
				System.out.println(this);
			}
			
			System.out.println("LE GAGNANT EST : "+actual_player());
		}

}
