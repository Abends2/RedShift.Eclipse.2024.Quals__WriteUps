#include <stdio.h>

#define SIZE 256
char buff[SIZE] = {0};  // Инициализируем буфер нулями для безопасности

void winner()
{
    printf("EclipseCTF{V3ry_go0deST_7ask1_1n_PW#$}\n");
}

void help()
{
    printf("1 - save data \n2 - print save data\n3 -  exit\n4 - login\n");
    return;
}

void flush_input()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Очистка буфера ввода
}

void data_save()
{
    printf("Hello. Please write save \n data: ");
    flush_input();  // Очищаем буфер ввода перед получением новых данных
    gets(buff);
    printf("Data saved\n");
}

void print_data()
{
    if (buff[0] != '\0')  // Проверяем, не пуста ли строка
    {
        printf("Your data:\n");
        printf("%s\n", buff);
        return;
    }
    printf("no data, please use command 1\n");
}

int main(void)
{   
    setbuf(stdout, NULL);
    help();
    int choice;
    int user_login = 0;
    while (1)
    {
        printf("command: ");
        scanf("%llx", &choice);

        switch (choice)
        {
        case 1:
            if(user_login == 67)
            {
                data_save();
                break;
            }
            else{
                printf("Please login first\n");
            }
        case 2:
            print_data();
            break;
        case 3:
            printf("Goodbye\n");
            return 0;  // Завершаем программу
        case 4:
            char login[SIZE];
            char password[SIZE];

            printf("Enter login:\n");
            flush_input(); 
            fgets(login, SIZE, stdin);
            printf("Enter password:\n");
            fgets(password, SIZE, stdin);
            if(login[0] == 'a' && password[0] == 'b')
            {
                printf("Nice Try\n");
            }
            else
            {
                printf("Login failed\n");
            }
            break;
        default:
            printf("invalid command\n");
            help();
        }
    }
    return 0;
}
