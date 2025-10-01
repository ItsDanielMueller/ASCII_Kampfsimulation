#ifndef FIGHT_H
#define FIGHT_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <stdarg.h>
#define BOARDHEIGHT 15
#define BOARDWIDTH 200
#define MESSAGE_ACTIONX 6
#define MESSAGE_STATUSX 7
#define STATUSEFFECTX 2
#define MAX_HP 100
#define HEAL_AMOUNT 8
#define POISONED (1 << 0)
#define STUNNED (1 << 1)
#define BUFFED (1 << 2)
#define SHIELDED (1 << 3)
#define HPBARSTART 5
#define POISON_DMG 2
#define SHIELD_AMOUNT 2
#define BUFF_AMOUNT 2

typedef struct fighter {
    char name[50];
    int hp;
    int attack;
    int healingChance;
    int status;
    int statusDuration[4]; 
} fighter;

fighter p1;
fighter orc;

int dynamicBoard(char board[BOARDHEIGHT][BOARDWIDTH]);
int parseAgruements(int argCount, char* args[], char difficulty[]);
int setFighters(char* difficulty[]);
int staticBoard(char board[BOARDHEIGHT][BOARDWIDTH]);
int drawBoard(char board[BOARDHEIGHT][BOARDWIDTH]);
int printAttackMessage(char board[][BOARDWIDTH], int row, const char* msgFormat, ...);
int updateStatus(fighter* x);
int actionHandling(fighter* attacker, fighter* defender, int action, char board[], int row);
int applyPoison(fighter* x, char board[][BOARDWIDTH], int row);
int printStatusMessage(char board[][BOARDWIDTH], int row, char* msgFormat, ...);

#endif

