/*User Management System 
NB: We couldn't input the masking password feature using the the <termios.h> header file becuse its 
directory id not include in out compiler path */
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<termios.h>

#define MAX_USERS 10
#define CRIDENTIAL_LENGTH 50

void register_user();
int login_user();/*returns the user index*/
void fix_fgets_input(char *);
void input_password(char *);
void input_credentials(char* username, char* password);

typedef struct 
{
    char user_name[CRIDENTIAL_LENGTH];
    char password[CRIDENTIAL_LENGTH];
}User;

User users[MAX_USERS];
int user_count = 0;

int main()
{
    int option;
    int user_index;
    while (1)
    {
        printf("\n Welcome to User Management");
        printf("\n1.Register");
        printf("\n2.Login");
        printf("\n3.Exit");
        printf("\nSelect an option: ");
        scanf("%d", &option);
        getchar();/*consume extra enter*/      

        switch (option)
        {
        case 1:
        register_user();
            break;
        case 2:
            user_index = login_user();
            if (user_index >= 0)
            {
                printf("\nLogin successfull, welcome, %s!\n", users[user_index].user_name);
            }
            else
            {
                printf("\nLogin failed! Incorrect username or password.\n");
            }            
            break;
        case 3:
            printf("\nExiting program.\n");
            return 0;
        default:
            printf("\nInvalid option please try again\n");
            break;
        }  
    }
    return 0;
}
void register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("\nMaximum %d users are supported! No more registrations Allowed!!!\n", MAX_USERS);
        return;
    }

    int new_index = user_count;
    printf("\nRegiter a new User.");
    input_credentials(users[new_index].user_name, users[new_index].password);
    user_count++;
    printf("\nRegistration Successful.\n");
    
}
int login_user()
{
    char username[CRIDENTIAL_LENGTH];
    char password[CRIDENTIAL_LENGTH];
    
    input_credentials(username, password);
    // printf("\n-%s-%s-", username, password);
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].user_name) == 0 && strcmp(password, users[i].password) == 0)
        {
            return i;/* index matches the cridentials*/
        }
    }
    return -1;
}
void input_credentials(char* username, char * password)
{
    printf("\nEnter user name:");
    fgets(username, CRIDENTIAL_LENGTH, stdin);
    fix_fgets_input(username);

    printf("Enter password:");
    fgets(password, CRIDENTIAL_LENGTH, stdin);
    fix_fgets_input(password);
}
void fix_fgets_input(char* string)
{
    int index = strcspn(string,"\n");
    string[index] = '\0';
}