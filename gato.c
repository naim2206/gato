
#include "gato.h"
#include <stdio.h>
#include <stdlib.h>

struct GameState
{
    char currentPlayer;
    char board[3][3];
};

void displayBoard(struct GameState* g)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("[%c]", g->board[i][j]);
        printf("\n");
    }
}

char determineCurrentPlayer(Game* g)
{
    int contx = 0, conto = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (g->board[i][j] == 'x')
            {
                contx++;
            }
            else if (g->board[i][j] == 'o')
            {
                conto++;
            }
        }
    }
    if (contx > conto)
    {
        return 'o';
    }
    else
    {
        return 'x';
    }
}



Game* newGame()
{
    Game* g = malloc(sizeof(Game));

    g->currentPlayer = 'o';

    int counter = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            g->board[i][j] = '0' + counter++;

    return g;
}

char getWinner(struct GameState* g)
{
    int full = 1;

    for (int i = 0; i < 3; i++)
    {
        if (g->board[i][0] == g->currentPlayer &&
            g->board[i][1] == g->currentPlayer &&
            g->board[i][2] == g->currentPlayer
            )
            return g->currentPlayer;
    }

    for (int i = 0; i < 3; i++)
    {
        if (g->board[0][i] == g->currentPlayer &&
            g->board[1][i] == g->currentPlayer &&
            g->board[2][i] == g->currentPlayer
            )
            return g->currentPlayer;
    }


    if (g->board[0][0] == g->currentPlayer &&
        g->board[1][1] == g->currentPlayer &&
        g->board[2][2] == g->currentPlayer)
    {
        return g->currentPlayer;
    }

    if (g->board[0][2] == g->currentPlayer &&
        g->board[1][1] == g->currentPlayer &&
        g->board[2][0] == g->currentPlayer)
    {
        return g->currentPlayer;
    }


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0;j < 3; ++j)
        {
            if (g->board[i][j] != 'x' && g->board[i][j] != 'o')
            {
                full = 0;
            }
        }
    }

    return full;

}

char getCurrentPlayer(Game* g)
{
    return g->currentPlayer;
}

void makeMove(Game* g)
{
    int place;
    int row = 0, col = 0;
    int cont = 0;

    do
    {
        if ((g->board[row][col] == 'x' || g->board[row][col] == 'o' || place > 9 || place < 0) && cont == 1)
        {
            puts("Error, seleccione otra vez");
        }
        fscanf(stdin, "%d", &place);

        if (place == 9)
        {
            saveGame(g);
            puts("Se guardo el juego");
            exit(1);
        }
        row = place / 3;
        col = place % 3;
        cont = 1;

    } while (g->board[row][col] == 'x' || g->board[row][col] == 'o' || place > 9 || place < 0);


    g->board[row][col] = g->currentPlayer;
}



void switchPlayer(Game* g)
{
    if (g->currentPlayer == 'o')
        g->currentPlayer = 'x';
    else
        g->currentPlayer = 'o';
}



Game* loadGame(const char* path)
{
    FILE* f = fopen(path, "rb");
    Game* g = malloc(sizeof(Game));
    if (f != NULL)
    {
        fread(g->board, sizeof(g->board), 1, f);
        fclose(f);
        g->currentPlayer = determineCurrentPlayer(g);
        switchPlayer(g);
        return g;
    }
    fclose(f);
    puts("No existe");
    return newGame();
}


void saveGame(Game* g)
{
    FILE* f = fopen("loadedGame.txt", "wb");
    fwrite(g->board, sizeof(g->board), 1, f);
    fclose(f);
}

