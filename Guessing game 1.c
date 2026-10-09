/* Guessing game 1*/
#include<stdio.h>
int main()
{
    int guessNumber = 5;
    int guess;
    int guessCount = 0;
    int guessLimit = 3;
    int OutOfGuesses = 0;

    while (guess != guessNumber && OutOfGuesses == 0)
    {
        if (guessCount < guessLimit)
        {
            printf("Enter a number: ");
            scanf("%d", &guess);
            guessCount++;
        }
        else
        {
            OutOfGuesses = 1;
        }
    }
    if (OutOfGuesses == 1)
    {
        printf("Out of guesses");
        printf("\nSorry you Lost");
    }
    else
    {
        printf("You win!");   
    }
    return 0;
}