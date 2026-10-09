/*Snake Game*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include "winsock2.h"/*for the function fd_set*/
// #include"termios.h"
#define HIENGTH 20
#define WIDTH 60

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGTH,
    STOP
};
enum Direction dir;

int score = 0;
int fruit_x, fruit_y;
int head_x, head_y;
int tail_length;
int tail_x[100];
int tail_y[100];

void setup();
void claer_screen();
void draw();
// struct termios old_props;
// void set_terminal_attributes();
// void reset_terminal_attribute();
int input_available();
void game_play();
void input();

int main()
{
    srand(time(NULL));
    // set_terminal_attributes();
    setup();
    while (1)
    {
        draw();
        input();
        game_play();
        int sleep_time = 999999 / (score != 0 ? score : 10);//for the speed of the snake for each fruit eaten
        sleep(sleep_time);
        //usleep(sleep_time);
    }
    return 0;
}
void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
/*Changing terminal properties*/
// void set_terminal_attributes()
// {

//     tcgetattr(STDERR_FILENO, &old_props);
//     atexit(reset_terminal_attribute);
//     struct termios old_props, new_props;
//     new_props.c_lflag &= ~(ECHO | ICANON);
//     tcsetattr(STDERR_FILENO, TCSANOW, &new_props);
// }
// void reset_terminal_attribute()
// {
//     tcsetattr(STDERR_FILENO, TCSANOW, &old_props);
// }
void input()
{
    if (input_available())
    {
        char ch = getchar();
        switch (ch)
        {
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGTH;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            exit(0);
            break;
        default:
            break;
        }
    }
    
}
void game_play()
{
    int x = head_x, y = head_y;
    for (int i = tail_length - 1; i > 0; i--)
    {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }
    tail_x[0] = head_x;
    tail_y[0] = head_y;

    switch (dir)
    {
    case UP:
        head_y--;
        break;
    case DOWN:
        head_y++;
        break;
    case LEFT:
        head_x--;
        break;
    case RIGTH:
        head_y--;
        break;
    case STOP:
        //do nothing
        break;
    }
    if (head_x < 0)
    {
        head_x = WIDTH - 1;
    }
    else if (head_x > WIDTH)
    {
        head_x = 0;
    }

    if (head_y < 0)
    {
        head_x = HIENGTH - 1;
    }
    else if (head_y > HIENGTH)
    {
        head_y = 0;
    }

    for (int i = 0; i < tail_length; i++)/*if the snake touches its body then the game will stop*/
    {
        if (tail_x[i] == head_x && tail_y[i] == head_y)
        {
            printf("\nYou have hit your tail ,Game Over!!");
            exit(0);
        }
        
    }
    
    if (head_x == fruit_x && head_y == fruit_y)
    {
        score += 10;
        tail_length++;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HIENGTH;
    }
    
}
/*Is input availble from the keyboard*/
int input_available()/*NB: This function needs to be edited */
{
    typedef struct
    {
        int OL;
        int OR;   
    }timeval;
    const timeval tv = {.OL = 0L, .OR = 0L};
    fd_set fds;
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}
void setup()
{
    head_x = WIDTH / 2;
    head_y = HIENGTH / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HIENGTH;
    dir = STOP;
    score = 0;
    tail_length = 0;
}
void draw()
{
    clear_screen();
    printf("\n\tWelcome to the world of Snake Game.\n\n");
    printf("\n");
    for (int i = 0; i < WIDTH + 2 ; i++)
    {
        printf("#");
    }

    for (int i = 0; i < HIENGTH; i++)
    {
        printf("\n#");
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == head_y && j == head_x)
            {
                printf("O");
            }
            else if (i == fruit_y && j == fruit_x)
            {
                printf("F");
            }
            else
            {
                int tail_found = 0;
                for (int k = 0; k < tail_length; k++)
                {
                    if (tail_x[k] == j && tail_y[k] == i)
                    {
                        printf("o");
                        tail_found = 1;
                        break;
                    }
                }
                if (!tail_found)
                {
                    printf(" ");
                }
            }
        }
        printf("#");
    }
    printf("\n");
    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("#");
    }
    printf("\nScore: %d\n", score);
}
