#include <stdio.h>
#include <stdlib.h>
#include "gato.h"

int main()
{
    int saved = 0;
    Game* juego;

    puts("Si tiene un juego guardado presione 1, si no, presione otro numero");
    scanf("%d", &saved);

    if (saved == 1)
        juego = loadGame("loadedGame.txt");
    else
        juego = newGame();


    while (!getWinner(juego))
    {
        switchPlayer(juego);
        displayBoard(juego);
        printf("Es el turno del jugador: %c (9 para guardar)\n", getCurrentPlayer(juego));
        makeMove(juego);
    }

    if (getWinner(juego) == 1)
    {
        puts("No hay ganador");
        main();
    }
    else
        printf("El ganador es: %c\n", getWinner(juego));


    return 0;
}
