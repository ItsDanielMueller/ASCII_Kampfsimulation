#include "fight.h"


int main(int argc,char *argv[]) {

	char difficulty[10];
	char board[BOARDHEIGHT][BOARDWIDTH];
	int playerAction = 0;
	srand((unsigned int)time(NULL));


	if (parseAgruements(argc, argv, difficulty) == 1) {
		exit(1);
	}

	
	if (setFighters(difficulty) == 1) {
		exit(1);
	}

	//Zeichnet alles Statische am Spielfeld
	staticBoard(board);

	//Gameloop
	while (1) {
		int computerMove = (rand() % 3) + 1;

		//Tickt die buffs und debuffs herunter und löscht sie falls <0.
		updateStatus(&p1);
		updateStatus(&orc);

		//Zeichnet alles Dynamische am board.
		dynamicBoard(board);


		//Poison check
		if (p1.status & POISONED) {

			p1.hp -= POISON_DMG;
			printStatusMessage(board, MESSAGE_STATUSX, "%s took %d poison dmg", p1.name, POISON_DMG);

		}
		else {

			//Fuellt die Zeile mit Leerzeichen falls der poison status effekt abgelaufen ist.
			for (int i = 0; i < BOARDWIDTH - 1; i++) {
				board[MESSAGE_STATUSX][i] = ' ';
			}
		}
		
		//Gegner Poison check.
		if (orc.status & POISONED) {

			orc.hp -= POISON_DMG;
			printStatusMessage(board, MESSAGE_STATUSX+3, "%s took %d poison dmg", orc.name, POISON_DMG);

		}
		else {

			//Fuellt die Zeile mit Leerzeichen falls der poison status effekt abgelaufen ist.
			for (int i = 0; i < BOARDWIDTH - 1; i++) {
				board[MESSAGE_STATUSX+3][i] = ' ';
			}
		}


		//Zeichnet feld.
		drawBoard(board);


		//Holt Spieler input ein.
		printf("     Choose your action : ");

		int result = scanf_s("%d", &playerAction);

		//Hier wird gerpüft ob die eingabe ein integer ist und wird sonst in 0 verwandelt.
		if (result != 1) {
			// Ungültige Eingabe, Puffer leeren
			while (getchar() != '\n');  // Alles bis zum Zeilenende verwerfen
			playerAction = 0;            // Reset
		}

		//Bei falschen input wird deine Runde uebersprungen. Diese hält aber keine chars aus.
		if (result == 1 && playerAction >= 1 && playerAction <= 3){

			actionHandling(&p1, &orc, playerAction, board, MESSAGE_ACTIONX);
		}
		
		//Behandelt Computer input. Braucht keinen check da Computer keinen Falschen input macht.
		actionHandling(&orc, &p1, computerMove, board,MESSAGE_ACTIONX+3);


		//Cleared den Screen
		system("cls");

	
		
		//Break aus der while loop falls hp <0 fallen.
		if (p1.hp <= 0) {
			printf("\n%s Won!\n", orc.name);
			break;
		}
		if (orc.hp <= 0) {
			printf("\%s Won!\n", p1.name);
			break;
		}

	}


	return 0;
}


