
#include <stdio.h>
#include "playerStruct.h"
#include <string.h>

#define boardSize  3

void printTitleScreen();
void setName(struct Player *player);
void printBoard(char board[][3]);
void placePiece(char board[][boardSize], struct Player player);
void printBoardWithAreaMarkers();
void gameLoop(struct Player *player1, struct Player *player2);


int main(){

	// Creates Structs that hold data for both Player1 & PLayer 2
	struct Player player1;
	player1.playerNum = 1;
	struct Player player2;
	player2.playerNum = 2;

	printTitleScreen();
	player1.piece = 'X';
	player2.piece = 'O';

	setName(&player1);
	setName(&player2);

	
	gameLoop(&player1, &player2);
	
}

void printBoardWithAreaMarkers(){
	printf("\n");
	printf(" 1 | 2 | 3 \n");
	printf("=== === ===\n");
	printf(" 4 | 5 | 6 \n");
	printf("=== === ===\n");
	printf(" 7 | 8 | 9 \n");
	printf("\n");
}

// Pre: None
// Post: Prints out the tic-tac-toe board
void printBoard(char board[][boardSize]){
	int row, col;
	for(row = 0; row < boardSize; row++){

		for(col = 0; col < boardSize; col++){
			if(col != 2)
				printf(" %c |", board[row][col]);
			else
				printf(" %c ", board[row][col]);
		}
		printf("\n");
		if(row != 2){
			printf("=== === ===\n");
		}
	}
}

// Pre:
// Post: places the piece of the given player struct at the specified location
void placePiece(char board[][boardSize], struct Player player){

		int coordinates[9][2] = {{0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0} , {2,1}, {2,2}};
		int *areaSelection;
		do{
			printBoardWithAreaMarkers();
			printf(" %s (Player %d), Where do you want to place your piece?", player.playerName, player.playerNum);
			
			scanf("%d", areaSelection);
			*areaSelection = *areaSelection - 1;

			if(*areaSelection < 0 || *areaSelection > 8 || board[coordinates[*areaSelection][0]][coordinates[*areaSelection][1]] != ' ' ){
				printf("That is an invalid place to place a \'%c\'!\n", player.piece);
				printBoard(board);
			}
			
		}while(*areaSelection < 0 || *areaSelection > 8 || board[coordinates[*areaSelection][0]][coordinates[*areaSelection][1]] != ' ');

		board[coordinates[*areaSelection][0]][coordinates[*areaSelection][1]] = player.piece;
}

void printTitleScreen(){
	printf("\n");
    printf("########## ########## ########## ########## ########## ########## ########## ########## ##########	\n");
    printf("\n");
	printf("#########   #######     ####        #########       #        ####     #########   ####   #####		\n");
	printf("    #          #       #    #           #          # #      #    #        #      #    #  #			\n");
	printf("    #          #       #                #         #####     #             #      #    #  #####		\n");
	printf("    #          #       #    #           #        #     #    #    #        #      #    #  #			\n");
	printf("    #       #######     ####            #       #       #    ####         #       ####   #####		\n");
	printf("\n");
    printf("########## ########## ########## ########## ########## ########## ########## ########## ##########	\n");
    printf("\n");
}

void setName(struct Player *player){
	printf("Player %d, Please Enter your name:", player->playerNum);
	scanf("%s", player->playerName);
}

int checkWinner(char board[][boardSize], char playerPiece){
	// Check horizontal Rows
	int row1;
	for(row1 = 0; row1 < boardSize; row1++){
		if(board[row1][0] == playerPiece && board[row1][1] == playerPiece && board[row1][2] == playerPiece ){
			return 1;
		}
	}

	// Check Vertical Columns
	int col1;
	for(col1 = 0; col1 < boardSize; col1++){
		if(board[0][col1] == playerPiece && board[1][col1] == playerPiece && board[2][col1] == playerPiece ){
			return 1;
		}
	}

	// Check Diagonals
	if(board[0][0] == playerPiece && board[1][1] == playerPiece && board[2][2] == playerPiece)
		return 1;
	else if(board[0][2] == playerPiece && board[1][1] == playerPiece && board[2][0] == playerPiece)
		return 1;
	
	return 0;
}

void gameLoop(struct Player *player1, struct Player *player2){
	int isWinner = 0;
	int isTie = 0;
	int numMoves = 0;
	char board[boardSize][boardSize] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
	
	while( !isTie && !isWinner){
		
		printBoard(board);
		placePiece(board, *player1);
		numMoves++;
		isWinner = checkWinner(board, player1->piece);
		if(isWinner){
			printBoard(board);
			printf("%s\n Wins! \n", player1->playerName);
		}

		if(numMoves == 9){
			printf("Tie! \n");
			break;
		}

		if(!isWinner){
			printBoard(board);
			placePiece(board, *player2);
			numMoves++;
			isWinner = checkWinner(board, player2->piece);
			if(isWinner){
				printBoard(board);
				printf("%s\n Wins! \n", player2->playerName);
			}
		}
	}

}
