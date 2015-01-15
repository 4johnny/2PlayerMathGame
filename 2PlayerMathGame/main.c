//
//  main.c
//  2PlayerMathGame
//
//  Created by Johnny on 2015-01-14.
//  Copyright (c) 2015 Empath Solutions. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//
// Macros
//

#define INIT_LIVES 3

//
// Types
//

typedef enum Operator {
	PLUS = 0,
	MINUS = 1,
	MULTIPLY = 2
} Operator;

typedef struct Challenge {
	int val1;
	int val2;
	Operator op;
	char opChar;
	int soln;
} Challenge;

typedef struct Player {
	char* name;
	int lives;
	int score;
} Player;

//
// Definitions
//

void initPlayer(Player* player, char name[], int lives) {
	player->name = name;
	player->lives = lives;
	player->score = 0;
}

void printPlayer(Player* player) {
	printf("%s: {lives: %d, score: %d}", player->name, player->lives, player->score);
}

void generateChallenge(Challenge* challenge) {
	
	challenge->val1 = arc4random_uniform(20) + 1;
	challenge->val2 = arc4random_uniform(20) + 1;
	
	Operator op = arc4random_uniform(3);
	switch (op) {
			
		case MINUS:
			challenge->soln = challenge->val1 - challenge->val2;
			challenge->opChar = '-';
			break;
			
		case MULTIPLY:
			challenge->soln = challenge->val1 * challenge->val2;
			challenge->opChar = '*';
			break;
			
		default:
		case PLUS:
			challenge->soln = challenge->val1 + challenge->val2;
			challenge->opChar = '+';
			break;
	}
}

int attemptChallenge(Player* player) {
	
	Challenge challenge; generateChallenge(&challenge);
	
	printf("%s's Turn: %d %c %d? ", player->name, challenge.val1, challenge.opChar, challenge.val2);
	int answer; scanf("%d", &answer);
	
	if (answer == challenge.soln) {
		player->score++;
		return 1;
	} else {
		player->lives--;
		return 0;
	}
}

void runTurn(Player* challenger, Player players[]) {
	
	if (attemptChallenge(challenger)) {
		printf("Score!\n");
	} else {
		printf("Epic Fail!\n");
	}
	
	printPlayer(&players[0]); printf("\n");
	printPlayer(&players[1]); printf("\n");
	
	printf("\n");
}

//
// Main
//

int main(int argc, const char * argv[]) {
	
	printf("Math Game\n=========\n\n");
	
	char player1Name[256];
	printf("Player1 Name: "); scanf("%s", player1Name);
	
	char player2Name[256];
	printf("Player2 Name: "); scanf("%s", player2Name);
	
	Player players[2];
	initPlayer(&players[0], player1Name, INIT_LIVES);
	initPlayer(&players[1], player2Name, INIT_LIVES);
	
	
	// Play game repeatedly until bored.
	char playAgain;
	do {
		// Reset lives
		players[0].lives = INIT_LIVES;
		players[1].lives = INIT_LIVES;
		
		// Play game until at least one player runs out of lives
		printf("Let's Play!\n\n");
		do {
			runTurn(&players[0], players);
			runTurn(&players[1], players);
			
		} while (players[0].lives > 0 && players[1].lives > 0);
		
		// Final results
		if (players[0].score == players[1].score) {
			printf("You are both LOSERS!\n");
		} else {
			printf("%s for the WIN!\n", players[0].score > players[1].score ? players[0].name : players[1].name);
		}
		
		// Play again?
		printf("Play again? "); scanf(" %c", &playAgain);
		
	} while (tolower(playAgain) == 'y');
	
	return 0;
}
