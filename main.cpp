#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ROW 3
#define COL 3
#define MAP_SIZE 3
#define ESC_CODE 27

void printMap(char (*map)[MAP_SIZE]);
int setPoint(char (*map)[MAP_SIZE], int x, int y, char currentRole);
char setNextRole(char currentRole);
void setStepCoords(char (*map)[MAP_SIZE], char stepSymbol);
int checkWinner(char (*map)[MAP_SIZE], char role);
char changeRole(char role);
int mapIsFill(char (*map)[MAP_SIZE]);

int main(void) {
  char map[ROW][COL] = { {}, {}, {} };
  char role;
  char gameStatus;
	int winner = -1;
	bool validRole = false;
	bool gameIsOver = false;

	char buffer[5];

	do {
		system("clear");
		printf("Enter your role(X or 0): ");

		fgets(buffer, 99, stdin);
		sscanf(buffer, "%c", &role);

		if (toupper(role) == 'X') {
			validRole = true;
		}

		if (role == '0') {
			validRole = true;
		}
	} while(!validRole);

	do {
		role = toupper(role);

  	printMap(map);
		setStepCoords(map, role);

		winner = checkWinner(map, role);

		if (winner > 0) {
			system("clear");
			printMap(map);
			printf("Winner: %c\nGAME OVER!\n", toupper((char)winner));
			gameIsOver = true;
		} else if (mapIsFill(map) == 0) {
			printf("No Winner!\nGAME OVER!\n");
		} else {
			role = changeRole(role);
			continue;
		}

		gameIsOver = (winner != -1) || (mapIsFill(map) == 0);
	} while(gameIsOver != 1);

	return 0;
}

char changeRole(char role) {
	return role == 'X' ? '0' : 'X';
}

void printMap(char (*map)[MAP_SIZE]) {
	system("clear");

	for (int i = 0; i < ROW; i++) {
  	for (int j = 0; j < COL; j++) {
      if (j == 0)
				printf("%c|", map[i][j] | ' ');
    	else if ((j + 1) % 3 == 0)
				printf("|%c", map[i][j] | ' ');
			else				
				printf("%c", map[i][j] | ' ');
  	}

		printf("\n");
  }
}

void setStepCoords(char (*map)[MAP_SIZE], char stepSymbol) {
	int coordX, coordY;
	char *point;
	char currentPositionSymbol;
	int isCorrectStep = -1;	

	do {
		printf("Step of '%c': \n", stepSymbol);
 	  printf("Enter coords(format: x y): ");
		scanf("%d %d", &coordX, &coordY);

		if (coordX > ROW || coordY > COL) {
			continue;
		}

 		point = &map[coordX - 1][coordY - 1];

		if (!*point) {
 			*point = stepSymbol;
			isCorrectStep = 1;
		}
	} while(isCorrectStep != 1);
}

int setPoint(char (*map)[MAP_SIZE], int x, int y, char currentRole) {
	char position = map[x - 1][y - 1];

	if ((int)position == 0) {
    map[x - 1][y - 1] = currentRole;
		return 0;
	}
	
	return -1;
}

int checkWinner(char (*map)[MAP_SIZE], char role) {
	int i = 0;

	for (; i < MAP_SIZE; i++) {
		if (map[i][0] == role && map[i][1] == role && map[i][2] == role) {
			return (int)role;
		}
	}

	for (i = 0; i < MAP_SIZE; i++) {
		if (map[0][i] == role && map[1][i] == role && map[2][i] == role) {
			return (int)role;
		}
	}

	if (map[0][0] == role && map[1][1] == role && map[2][2] == role) {
		return (int)role;
	}

	if (map[0][2] == role && map[1][1] == role && map[2][0] == role) {
		return (int)role;
	}

	return -1;
}

int mapIsFill(char (*map)[MAP_SIZE]) {
	int emptyPlaces = 0;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			emptyPlaces += ((int)map[i][j] != 0 ? 0 : 1);
		}
	}

	return emptyPlaces;
}