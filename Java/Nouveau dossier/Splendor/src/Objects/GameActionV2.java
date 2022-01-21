package Objects;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;

public class GameActionV2 extends GameAction {
	
	private final PlayerV2 p3;
	private final PlayerV2 p4;
	private final BoardV2 board;
	//private PlayerV2 actual_player_v2;
	
	public GameActionV2() throws IOException {
		super(null,new PlayerV2("P1",1),new PlayerV2("P2",1));
		change_p1_p2_name();
		int nb_players = ask_how_many_players();
		if(nb_players == 3) {
			this.p3 = init_player(3);
			this.p4=null;
		}else if(nb_players == 4) {
			this.p3 = init_player(3);
			this.p4 = init_player(4);
		}else {
			this.p3=null;
			this.p4=null;
		}
		this.board = new BoardV2(nb_players);
	}
	
	
	public void add_joker_to_player(PlayerV2 p) {
		Objects.requireNonNull(p, "Player is null");
		p.add_new_golden_joker();
		this.board.delete_token_board(new Token("or"));
	}
	
	
	//Demande le nom du joueuer numero player number
	public String ask_name(int player_number) {
		Scanner scan;
		String name = "";
		while(name.length()<=0) {
			System.out.println("Pseudo du joueur "+player_number+" : ");
			scan = new Scanner(System.in);
			name = scan.nextLine();
		}
		return name;
	}
	
	//Change le nom de p1 et p2
	public void change_p1_p2_name() {
		Player.change_name(ask_name(1), p1());
		Player.change_name(ask_name(2), p2());
	}
	
	//Init PlayerV2
	@Override
	public PlayerV2 init_player(int nb_player) {
		if(nb_player<=0)
			throw new IllegalArgumentException("Number of player is negative or equal to 0");
		Scanner scan;
		String name = "";
		while(name.length()<=0) {
			System.out.println("Pseudo du joueur "+nb_player+" : ");
			scan = new Scanner(System.in);
			name = scan.nextLine();
		}
		return new PlayerV2(name,nb_player);
	}
	
	//Renvoie le nombre de joueur a participe au jeu
	public int ask_how_many_players() {
		int tmp;
		var s = new Scanner(System.in);
		System.out.println("COMBIEN DE JOUEUR ?\n");
		do {
			while(!(s.hasNextInt())){
				System.out.println("Reessayer");
				s.next();
			}
			tmp = s.nextInt();
		}while(tmp<2 || tmp>4);
		return tmp;
	}
	
	@Override
	public void change_actual_player() {
		if(actual_player().equals(this.p1())) {change_player(p2());}
		else if(this.actual_player().equals(this.p2())) {change_player(p3);}
		else if(this.actual_player().equals(this.p3)) {change_player(p4);}
		else {change_player(p1());}
	
	}
	

	
	
	//Demande dans quel niveaux de carte il veut
	public int ask_stack_number(){
		Scanner s = new Scanner(System.in);
		int val;
		System.out.println("Quel niveau de carte voulez vous ?\n");
		do {
			while(!(s.hasNextInt())){
				System.out.println("Reessayer");
				s.nextInt();
			}
			val = s.nextInt();
		}while(val<1 || val > 3);
		return val;
	}
	
	
	
	//reserve une carte pour l'actuel player
	public void reserve_a_card() {
		Scanner s = new Scanner(System.in);
		Card tmp;
		int val = -1, card_level = -1;
		System.out.println(this.actual_player().name()+" veut reserver une carte");
		do {
			System.out.println("1 pour piocher une carte, 2 pour reserver une carte sur le board \n");
			while(!(s.hasNextInt())){
				System.out.println("Reessayer");
				s.next();
			}
			val = s.nextInt();
		}while(val!=1 || val!=2);//1 pour une carte sur le board, 2 pour une carte tire dans un paquet
		card_level = ask_stack_number();// demande dans quel niveau de carte il veut
		if(val == 1) {
			tmp = this.board.choose_card_V2(this.board.which_board_list(card_level)); //On recup une carte dans la liste card on board de level level
		}else {
			tmp = this.board.draw(this.board.which_stack_of_card(card_level)); //On recup la carte dans le bon tas de carte
		}
		((PlayerV2) this.actual_player()).add_new_reserved_card(tmp);
		if(this.board.number_of_golden_token() > 0) {
			add_joker_to_player((PlayerV2) actual_player());
		}
		if(this.actual_player().too_much_token()) {delete_too_much_tokens();}
	}
	
	
	@Override
	public String toString() {
		var builder = new StringBuilder();
		builder.append("======GAME SITUATION======\n");
		builder.append(this.board.toString()+"\n");
		builder.append(this.p1().toString()+"\n");
		builder.append(this.p2().toString()+"\n");
		if(p3!=null) {builder.append(this.p3.toString()+"\n");}
		if(p4!=null) {builder.append(this.p4.toString()+"\n");}
		return builder.toString();
	}
	

}
