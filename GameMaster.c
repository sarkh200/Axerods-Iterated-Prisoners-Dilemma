#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "./IPD.h"

// Gets a random number between max and min
int random(int min, int max) { return rand() % (max - min + 1) + min; }

// 0 = defect and 1 = cooperate
// If both cooperate: 3, 3
// If one defects 5, 0
// If both defect 1, 1
gameResults game(int player1choice, int player2choice)
{
    gameResults results = {0, 0};

    if (player1choice == player2choice)
    {
        if (player1choice == 0)
        {
            results.player1points = 1;
            results.player2points = 1;
        }
        else if (player1choice == 1)
        {
            results.player1points = 3;
            results.player2points = 3;
        }
    }
    else if (player2choice > player1choice)
    {
        results.player1points = 5;
        results.player2points = 0;
    }
    else if (player2choice < player1choice)
    {
        results.player1points = 0;
        results.player2points = 5;
    }

    return results;
}

// Asks for user input for name of a DLL and returns an instance of the DLL
HINSTANCE getPlayerDLL(int n)
{
    printf("Input name of player %d, and make sure it is in a folder called Strategies \n", n);
    char playerName[101];
    scanf("%100s", playerName);

    char *pathToDLL = malloc((strlen(playerName) + strlen("./Strategies/") + strlen(".dll")) * sizeof(char));

    strcpy(pathToDLL, "./Strategies/");
    strcat(pathToDLL, playerName);
    strcat(pathToDLL, ".dll");

    HINSTANCE playerDLL = LoadLibrary(pathToDLL);
    if (playerDLL == NULL)
    {
        printf("%s not found\n", pathToDLL);
        exit(-1);
    }

    free(pathToDLL);

    return playerDLL;
}

int main(void)
{
    // Sets up rand
    srand(time(NULL));

    // sets the game length to a random int between min and max
    int gameLen = random(200, 220);

    // array that contains the results of each match
    gameResults *results = (gameResults *)malloc(gameLen * sizeof(gameResults));
    int *player1Results = (int *)malloc(gameLen * sizeof(int));
    int *player2Results = (int *)malloc(gameLen * sizeof(int));

    // gets the dlls for player 1 and 2
    HINSTANCE player1DLL = getPlayerDLL(1);
    int (*player1run)(int *results, int indexOfGame) = (int (*)(int *, int))GetProcAddress(player1DLL, "turn");

    HINSTANCE player2DLL = getPlayerDLL(2);
    int (*player2run)(int *results, int indexOfGame) = (int (*)(int *, int))GetProcAddress(player2DLL, "turn");

    int player1Score = 0;
    int player2Score = 0;

    // simulates the game
    for (int i = 0; i < gameLen; i++)
    {
        results[i] = game(player1run(player1Results, i), player2run(player2Results, i));
        player1Results[i] = results[i].player1points;
        player2Results[i] = results[i].player2points;
        player1Score += results[i].player1points;
        player2Score += results[i].player2points;
        printf("%d", results[i].player1points);
        printf("%d\n", results[i].player2points);
    }

    printf("Player 1 score = %d\n", player1Score);
    printf("Player 2 score = %d\n", player2Score);

    return 0;
}