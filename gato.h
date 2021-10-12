
#ifndef GATO_GATO_H
#define GATO_GATO_H

typedef struct GameState Game;

void displayBoard(Game* g);
Game* newGame();
char getWinner(Game* g);
char getCurrentPlayer(Game* g);
void makeMove(Game* g);
void switchPlayer(Game* g);
Game* loadGame(const char* path);
void saveGame(Game* g);

#endif //GATO_GATO_H
