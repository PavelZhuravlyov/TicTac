#include <stdio.h>
#include <stdlib.h>
#define ROW 3 
#define COL 3
#define ESC_CODE 27

void printMap(char (*map)[3]);
int setPoint(char (*map)[3], int x, int y, char currentRole);
char setNextRole(char currentRole);
void setStepCoords(char (*map)[3], char stepSymbol);
char changeRole(char role);

int main(void) {
  char map[ROW][COL] = { {}, {}, {} };
  char role;
  char gameStatus;  

	printf("Enter your role(X or O): ");
	scanf("%c", &role);

	do {
  	printMap(map);
		setStepCoords(map, role);
		role = changeRole(role);
	} while(1);

	return 0;
}

char changeRole(char role) {
	return role == 'x' ? 'o' : 'x';
}

void printMap(char (*map)[3]) {
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

void setStepCoords(char (*map)[3], char stepSymbol) {
	int coordX, coordY;
	char *point;
	char currentPositionSymbol;
	int isCorrectStep = -1;	

	do {
		printf("Step of '%c': \n", stepSymbol);
 	  printf("Enter coords(format: x y): ");
		scanf("%d %d", &coordX, &coordY);

 		point = &map[coordX - 1][coordY - 1];

		if (!*point) {
 			*point = stepSymbol;
			isCorrectStep = 1;
		}
	} while(isCorrectStep != 1);
}

int setPoint(char (*map)[3], int x, int y, char currentRole) {
	char position = map[x - 1][y - 1];

	if (!position) {
    map[x - 1][y - 1] = currentRole;
		return 0;
	} else {
  	printf("Error: ");
	}
	
	return -1;
}

