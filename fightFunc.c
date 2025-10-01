#include "fight.h"

int parseAgruements(int argCount,char *args[],char difficulty[]) {

	//Checkt ob ein argument geliefert worden ist.
	if (argCount < 2) {
		printf("\nArguements missing. Please refer to --help\n");
		return 1;
	}

	//Gibt --help aus.
	if (strcmp(args[1], "--help") == 0 && argCount < 4) {
		printf("\n	    === Guide ===\n");
		printf("\n[Playername] [Enemyname] [Difficulty]\n");
		printf("\nYou can choose between 3 difficulties: [Easy] [Normal] [Hard]");
		printf("\nEach difficulty setting will impact player and enemy stats.\n");
		printf("\nYou can receive BUFFED(attack +2) and SHIELDED(damage received -2)");
		printf("\nYou can also inflict POISON(2 damage for 2 turns) and STUNNED (cannot act for 1 round)");
		printf("\nBUFFED and SHIELDED have a chance to be gained through healing yourself");
		printf("\nPOISONED and STUNNED have a chance to be inflicted via the special attack.");
		printf("\n");
	}
	else if (argCount != 4) {			//Checkt ob zuviele Argumente eingegeben worden sind
		printf("\nThis function needs 3 arguements. Please refer to --help\n");
		return 1;
	}


	//Hier wird geprueft ob eignaben des Users zu groß sind.
	if (strlen(args[1]) < sizeof(p1.name)) {
		strcpy_s(p1.name,sizeof(p1.name), args[1]);
	}
	else {
		printf(" \nPlayer name is too long. Maximun is 50 characters.\n");
		return 1;
	}

	if (strlen(args[2]) < sizeof(orc.name)) {
		strcpy_s(orc.name,sizeof(orc.name), args[2]);
	}
	else {
		printf("\nEnemy name is too long. Maximum is 50 characters.\n");
		return 1;
	}
	
	//Checkt ob eingabe zu groß ist.
	if (strlen(args[3]) < sizeof(difficulty)) {
		strcpy_s(difficulty, sizeof(difficulty), args[3]);
	}
	else {
		printf("Invalid difficulty. Please refer to --help");
		return 1;
	}



	//Verwandelt den Schwierigkeits input in lower case damit Groß- Kleinschreibung nicht beachtet wird bei der eingabe.
	size_t len = strlen(difficulty);
	for (int i = 0; i < len; i++) {
		difficulty[i] = (char)tolower((unsigned char)difficulty[i]);
	}

	//Hier wird geprueft ob eingabe zu groß ist und in folge dessen ob die Eingabe richtig ist.
	if (strlen(args[3]) >= 10) {
		printf("\nArgument 3 invalid. Please refer to --help.\n");
		return 1;
	}
	else if (strcmp(difficulty, "easy")!=0 && strcmp(difficulty, "normal")!=0 && strcmp(difficulty, "hard")!=0) {
		printf("\nInvalid difficulty. Please refer to --help.\n");
		return 1;
	}
	


	return 0;
}


int setFighters(char *difficulty[]) {

	
	if (strcmp(difficulty, "easy") == 0) {
		p1.attack = 6;
		p1.healingChance = 90;
		p1.status = 0;
		p1.hp = MAX_HP;

		orc.attack = 3;
		orc.healingChance = 20;
		orc.status = 0;
		orc.hp = MAX_HP;
	}

	if (strcmp(difficulty, "normal") == 0) {
		p1.attack = 5;
		p1.healingChance = 60;
		p1.status = 0;
		p1.hp = MAX_HP;

		orc.attack = 4;
		orc.healingChance = 40;
		orc.status = 0;
		orc.hp = MAX_HP;
	}
	
	if (strcmp(difficulty, "hard") == 0) {
		p1.attack = 4;
		p1.healingChance = 40;
		p1.status = 0;
		p1.hp = MAX_HP;

		orc.attack = 6;
		orc.healingChance = 50;
		orc.status = 0;
		orc.hp = MAX_HP;
	}
	return 0;
}


int drawBoard(char board[BOARDHEIGHT][BOARDWIDTH]) {

	//Zeichnet das Spielfeld.
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < BOARDWIDTH; j++) {
			printf("%c", board[i][j]);
		}
		printf("\n");
	}

	return 0;
}


int dynamicBoard(char board[BOARDHEIGHT][BOARDWIDTH]) {
	// Berechnung wieviele Segmente ich habe.
	int playerhpSegments = (p1.hp * 20) / MAX_HP;
	int orchpSegments = (orc.hp * 20) / MAX_HP;

	// HP-Leiste Spieler
	for (int i = 0; i < 20; i++) {
		board[1][HPBARSTART + i] = (i < playerhpSegments) ? '#' : '-';
	}

	// HP-Leiste Gegner
	for (int i = 0; i < 20; i++) {
		board[1][HPBARSTART + 50 + i] = (i < orchpSegments) ? '#' : '-';
	}

	int nameRow = 2;
	int nameColumn = 6;

	// Spielername
	for (int i = 0; p1.name[i] != '\0' && (nameColumn + i) < BOARDWIDTH; i++) {
		board[nameRow][nameColumn + i] = p1.name[i];
	}

	// Gegnername
	for (int i = 0; orc.name[i] != '\0' && (nameColumn + 50 + i) < BOARDWIDTH; i++) {
		board[nameRow][nameColumn + 50 + i] = orc.name[i];
	}

	// Statuszeil  leeren
	int statusRow = nameRow + 1;
	for (int i = 0; i < BOARDWIDTH; i++)
		board[statusRow][i] = ' ';

	// --- Spielerstatus ---
	int offset = 0;
	int col = nameColumn;
	if (p1.status & STUNNED) {
		const char* s = "STUNNED ";
		for (int i = 0; s[i] != '\0' && (col + offset + i) < BOARDWIDTH; i++)
			board[statusRow][col + offset + i] = s[i];
		offset += strlen(s);
	}
	if (p1.status & POISONED) {
		const char* s = "POISONED ";
		for (int i = 0; s[i] != '\0' && (col + offset + i) < BOARDWIDTH; i++)
			board[statusRow][col + offset + i] = s[i];
		offset += strlen(s);
	}
	if (p1.status & BUFFED) {
		const char* s = "BUFFED ";
		for (int i = 0; s[i] != '\0' && (col + offset + i) < BOARDWIDTH; i++)
			board[statusRow][col + offset + i] = s[i];
		offset += strlen(s);
	}
	if (p1.status & SHIELDED) {
		const char* s = "SHIELDED ";
		for (int i = 0; s[i] != '\0' && (col + offset + i) < BOARDWIDTH; i++)
			board[statusRow][col + offset + i] = s[i];
		offset += strlen(s);
	}

	// --- Gegnerstatus ---
	offset = 0;
	col = nameColumn + 50;
	if (orc.status & STUNNED) {
		const char* s = "STUNNED ";
		for (int i = 0; s[i] != '\0' && (col + offset + i) < BOARDWIDTH; i++)
			board[statusRow][col + offset + i] = s[i];
		offset += strlen(s);
	}
	if (orc.status & POISONED) {
		const char* s = "POISONED ";
		for (int i = 0; s[i] != '\0' && (col + offset + i) < BOARDWIDTH; i++)
			board[statusRow][col + offset + i] = s[i];
		offset += strlen(s);
	}
	if (orc.status & BUFFED) {
		const char* s = "BUFFED ";
		for (int i = 0; s[i] != '\0' && (col + offset + i) < BOARDWIDTH; i++)
			board[statusRow][col + offset + i] = s[i];
		offset += strlen(s);
	}
	if (orc.status & SHIELDED) {
		const char* s = "SHIELDED ";
		for (int i = 0; s[i] != '\0' && (col + offset + i) < BOARDWIDTH; i++)
			board[statusRow][col + offset + i] = s[i];
		offset += strlen(s);
	}

	return 0;
}


int staticBoard(char board[BOARDHEIGHT][BOARDWIDTH]) {

	//Füllt das array mit leerzeichen.
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < BOARDWIDTH; j++) {
			board[i][j] = ' ';
		}
	}

	//Eingabe Hilfe.
	char* menu[] = {"1 - Attack","2 - Special Attack","3 - Heal"};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; menu[i][j] != '\0'; j++) {
			board[12 + i][5 + j] = menu[i][j];
		}
	}
	return 0;
}


int dealDamage(fighter *target,int amount) {

	//Zeigt auf die HP des angegriffenen und zieht den Schaden ab.
	target->hp -= amount;

	return 0;
}


int specialAttack(fighter *attacker,int rolls) {

	//Checkt ob man noch rolls hat.
	if (rolls == 0) {
		return 0;
	}
	//Rollt zwischen 1 und Attack stat und ruft sich noch 2 mal erneut auf.
	int roll = (rand() % attacker->attack - 1 ) + 1;
	return roll + specialAttack(attacker,rolls - 1);

}


int printAttackMessage(char board[][BOARDWIDTH], int row, const char* msgFormat, ...) {
	char msg[200];
	va_list args;
	va_start(args, msgFormat);
	vsnprintf(msg, sizeof(msg), msgFormat, args);
	va_end(args);

	if (row < 0 || row >= BOARDHEIGHT) {
		printf("Error: printAttackMessage row %d out of bounds!\n", row);
		return -1;
	}

	// Alte Nachricht löschen
 	for (int i = 0; i < BOARDWIDTH - 1; i++) {
		board[row][i] = ' ';
	}
	board[row][BOARDWIDTH - 1] = '\0';

	// Nachricht ins Board kopieren
	int maxLen = BOARDWIDTH - 5 - 1;
	for (int i = 0; i < maxLen && msg[i] != '\0'; i++) {
		board[row][i + 5] = msg[i];
	}

	return 0;
}


int printStatusMessage(char board[][BOARDWIDTH], int row,  char* msgFormat, ...) {


	//Temporary buffer
	char msg[200];

	//Variadic argumente bearbeite. C kann jetzt nun variabel viele agruemente in dieser funktion bearbeiten.
	va_list args;
	va_start(args, msgFormat);
	vsnprintf(msg, sizeof(msg), msgFormat, args); //Gibt die Nachricht aus nachdem alle argumente bearbeitet wurden.
	va_end(args);

	//Löscht alte Nachricht.
	for (int i = 0; i < BOARDWIDTH; i++) {
		board[row][i] = ' ';
	}

	//NULLTERMINIEREN
	board[row][BOARDWIDTH - 1] = '\0';

	//Speicher neue Nachricht
	for (int i = 0; i < BOARDWIDTH - 1 && msg[i] != '\0'; i++) {
		board[row][i + 5] = msg[i];
	}

	return 0;
}


int heal(fighter* attacker, int row, char board[][BOARDWIDTH]) {
	// Prüfen, ob Heal erfolgreich ist
	if ((rand() % 100) < attacker->healingChance) {
		// overheal behandeln
		attacker->hp += HEAL_AMOUNT;
		if (attacker->hp > MAX_HP) {
			attacker->hp = MAX_HP;
		}

		// Buff / Shield Chance
		int gotBuffed = 0;
		int gotShielded = 0;

		if ((rand() % 100) < 20) {        
			attacker->status |= BUFFED;
			attacker->statusDuration[2] = 2;
			gotBuffed = 1;
		}
		if ((rand() % 100) < 25) {       
			attacker->status |= SHIELDED;
			attacker->statusDuration[3] = 2; 
			gotShielded = 1;
		}

		// Nachricht ausgeben
		if (gotBuffed && gotShielded) {
			printAttackMessage(board, row, "%s healed for %d and got buffed and shielded!", attacker->name, HEAL_AMOUNT);
		}
		else if (gotBuffed) {
			printAttackMessage(board, row, "%s healed for %d and got buffed!", attacker->name, HEAL_AMOUNT);
		}
		else if (gotShielded) {
			printAttackMessage(board, row, "%s healed for %d and is shielded!", attacker->name, HEAL_AMOUNT);
		}
		else {
			printAttackMessage(board, row, "%s healed for %d HP!", attacker->name, HEAL_AMOUNT);
		}

	}
	else {
		printAttackMessage(board, row, "%s failed to heal!", attacker->name);
	}

	return 0;
}


int applyPoison(fighter* x, char board[][BOARDWIDTH], int row) {

	if (x->status & POISONED) {
		x->hp -= POISON_DMG;
		if (x->hp < 0) x->hp = 0;
		printStatusMessage(board, row, "%s takes %d poison damage!", x->name, POISON_DMG);
	}

	return 0;
}


int actionHandling(fighter* attacker, fighter* defender, int action, char board[], int row) {

	int hasEffect = 0;
	int damage;



	//Behandelt die einzelnen Aktionen und ueberprüft ob attacker beteupt ist.
	switch (action) {
	case 1:
		if ((attacker->status & STUNNED) == 0) {

			//Setzt Schaden.
			damage = attacker->attack;

			//Bearbeitet die einzelnen Statuseffekte.
			if (defender->status & SHIELDED && attacker->status & BUFFED) {

				damage = attacker->attack;
			} 
			else if (defender->status & SHIELDED) {
				damage = attacker->attack - SHIELD_AMOUNT;
			}
			else if (attacker->status & BUFFED) {
				damage = attacker->attack + BUFF_AMOUNT;
			}

			printAttackMessage(board, row, "%s deals %d damage!", attacker->name, damage);

		}
		else {
			printAttackMessage(board, row, "%s is stunned!", attacker->name);
		}
		break;


	case 2:
		if ((attacker->status & STUNNED) == 0) {
			damage = specialAttack(attacker, 3);
			dealDamage(defender, damage);

			//Bearbeitet die einzelnen Statuseffekte.
			if (defender->status & SHIELDED && attacker->status & BUFFED) {

				damage = attacker->attack;
			}
			else if (defender->status & SHIELDED) {
				damage = attacker->attack - SHIELD_AMOUNT;
			}
			else if (attacker->status & BUFFED) {
				damage = attacker->attack + BUFF_AMOUNT;
			}

			//Chance auf Stunned
			if ((rand() % 100) < 20) {
				defender->status |= STUNNED;
				defender->statusDuration[1] = 2;
				printAttackMessage(board, row, "%s hits for %d damage and %s is stunned!", attacker->name, damage, defender->name);
				hasEffect = 1;
			}

			//Chance auf Poison
			if ((rand() % 100) < 15) {
				defender->status |= POISONED;
				defender->statusDuration[0] = 3;
				printAttackMessage(board, row, "%s hits for %d and %s is poisoned!", attacker->name, damage, defender->name);
				hasEffect = 1;
			}
			if (hasEffect == 0) {
				printAttackMessage(board, row, "%s deals %d damage!", attacker->name, damage);
			}

		}
		else {
			printAttackMessage(board, row, "%s is stunned!", attacker->name);
		}
		break;
	case 3:
		if ((attacker->status & STUNNED) == 0) {
			heal(attacker, row, board);
		}
		break;
	}
	return 0;
}


int updateStatus(fighter* x) {

	//Hier wird der buff oder debuff runtergezählt und dann gelöscht.
	for (int i = 0; i < 4; i++) { 
		int flag = (1 << i);
		if ((x->status & flag) && x->statusDuration[i] > 0) {
			x->statusDuration[i]--;        // Dauer runterzählen
			if (x->statusDuration[i] == 0) {
				x->status &= ~(1 << i);        // Flag entfernen
			}
		}
	}
	return 0;
}