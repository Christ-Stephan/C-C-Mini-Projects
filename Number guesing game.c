/*Number guesing game*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    int random, guess;
    int no_of_guess = 0;
    srand(time(NULL));

    printf("Welcome to the world of guessing gfame\n");
    random = rand() % 100 + 1;/*Generating between 0 to 100*/
    do
    {
        printf("Enter your guess between(1 - 100):");
        scanf("%d", &guess);
        no_of_guess++;
        if (guess < random)
        {
            printf("Guess larger number.\n");
        }
        else if (guess > random)
        {
            printf("Guess a smaller number.\n");
        }
        else
        {
            printf("Congratulations !!!You have successfully guessed the number in %d attempts",no_of_guess);
        }
        
    } while (guess != random);
    printf("\n Bye, Bye, Thanks for playing.");
    printf("\nDeveloped by: StephCoding");
    return 0;
}