package Main;

import java.io.IOException;

import Objects.*;

public class Main {

	public static void main(String[] args) throws IOException {

		//var jeu = new GameAction();
		//jeu.jeu_v1();
		
		var jeu2 = new GameActionV2();
		System.out.println(jeu2);
		jeu2.reserve_a_card();
		System.out.println(jeu2);

		
	}

}



/*TO DO*/

//Avoir toutes les couleurs en minuscules
//Utiliser toLowerCase() chaque entre de couleur pour le choix des tokens
//Pb : faire en sorte que les deux joueurs ait des noms differents
//ToLowerCase pour les bonus fonctionnes
//Mais pas pour les tokens car token est un record


/* RESERVER UNE CARTE, AJOUTE LES METHODES DANS BOARDV2 SUPPRIMER UNE CARTE SUR LE BOARD
 * 
 * Gerer les Actions de jeu, choix du nombre de joueur, reservation des cartes avec tokens dores, Visite de noble
 * Achats des cartes avec jetons joker
 * Faire un tostring de Board V2
 * modifier l'achat pour prendre en compte l'utilisation de joker
 * Ajouts des tuiles nobles au joueurs
 * 
 */

/*
 * GESTION DES JOUEURS A REFAIRE, PEUT ETRE REPARTIR D'UNE VER precedente
 * 
 */