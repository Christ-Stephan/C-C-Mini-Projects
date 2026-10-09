/*Bank Mananagement System*/
#include<stdio.h>
#include<string.h>
void create_account();
void deposit_money();
void withdarw_money();
void check_balance();
const char* ACOUNT_FILE = "account.dat";
typedef struct 
{   
    char name[50];
    int acc_no;
    float balance;
}Account;
int main()
{
    while (1)
    {
        int choice;
        printf("\n*** Bank Management System*** \n");
        printf("\n1.create account.");
        printf("\n2. Deposit money.");
        printf("\n3. Withdraw Money.");
        printf("\n4. Check Balance.");
        printf("\n5.Exit.");
        printf("\nEntr your choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdarw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            printf("Invalid choice!");
        default:
            printf("\nClosing the bank, Thanks for your visit\n");
            return 0;
        }
    }   
}

void create_account()
{
    Account acc;
    char c;
    FILE *file = fopen(ACOUNT_FILE, "ab+");
    if (file == NULL)
    {
        printf("\nUnable to open file!\n");
        return;
    }
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0';
    printf("\nEnter your account number: ");
    scanf("%d", &acc.acc_no);
    acc.balance = 0; 
    
    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\nAccount created successfully!");
}
void deposit_money()
{
    FILE *file = fopen(ACOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("Unable to open account file!!");
        return;
    }
    int acc_no;
    float money;
    Account acc_r;
    printf("Enter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &money);
    while (fread(&acc_r, sizeof(acc_r), 1, file))/*read and search current file where our balance is first
    saved to add or overwrite the balance with the new balance    */
    {
        if (acc_r.acc_no == acc_no)/*checking if entered acc_no exist */
        {
            acc_r.balance += money;
            fseek(file, -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);
            fclose(file);
            printf("Successfully deposited $%.2f \nNew balance is $%.2f", money, acc_r.balance);
            return;
        }   
    }
    fclose(file);
    printf("Money could not be deposited since account no %d was not found in records.", acc_no);
}
void withdarw_money()
{
    FILE *file = fopen(ACOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("Unable to open account file!!");
        return;
    }
    int acc_no;
    float money;
    Account acc_r;/*Reading account*/
    printf("Enter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to withdraw: ");
    scanf("%f", &money);

    while (fread(&acc_r, sizeof(acc_r), 1, file) != EOF)
    {
        if (acc_r.acc_no == acc_no)/*checking if account number exist*/
        {
            if (acc_r.balance >= money)/*if acc_no exist then check if acc_balance >= money to be withdrawn*/
            {
                acc_r.balance -= money;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                printf("Successfully Withdrawn $%.2f\nRemaining balance is $%.2f", money, acc_r.balance);
            }
            else
            {
                printf("Insufiicient balance!");
            }
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Money could not be withdrawn since account no %d was not found in records.", acc_no);
}
void check_balance()
{
    FILE *file = fopen(ACOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\nUnable to open file!");
        return;
    }

    int acc_no;
    Account acc_read;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)/*checking if account no exist or is created*/
        {
            printf("\nYour current balance is $%.2f", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\nAccoount No:%d was not found.\n", acc_no);
}