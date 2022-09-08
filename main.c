#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>

struct Product
{
    int id;
    char productName[50];
    int quantity;
    char date[12];
} p;

FILE *fp;

struct login
{
    char fname[100];
    char lname[20];
    char username[20];
    char password[20];
} x;

void registe()
{
    FILE *log;
    log = fopen("login12.txt", "w");

    printf("Enter frist name:");
    scanf("%s", x.fname);

    printf("Enter last name:");
    scanf("%s", x.lname);

    printf("Enter Username:");
    scanf("%s", x.username);

    printf("Enter password ");
    scanf("%s", x.password);
    fwrite(&x, sizeof(x), 1, log);

    fclose(log);

    printf("\n\nyour username is UserID\n");
    printf("Now login with UserID and Password\n");
    printf("\nPress any key to continue.....");
    getch();
    system("CLS");
    login();
}

void login()
{
    char username[200], password[20];
    FILE *log;
    log = fopen("login12.txt", "r");
    printf("UserID:");
    scanf("%s", &username);
    printf("Password:");
    scanf("%s", &password);

    while (fread(&x, sizeof(x), 1, log))
    {
        if (strcmp(username, x.username) == 0 && strcmp(password, x.password) == 0)
        {
            menu();
        }
        else if (strcmp(username, x.username) == 1 || strcmp(password, x.password) == 1)
        {
            printf("Please Enter valid UserID and Password");
        }
    }

    fclose(log);
}

void addProduct()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(p.date, myDate);

    fp = fopen("product.txt", "ab");

    printf("Enter Product id:");
    scanf("%d", &p.id);

    printf("Enter Product name:");
    fflush(stdin);
    gets(p.productName);

    printf("Enter Product Quantity:");
    fflush(stdin);
    scanf("%d", &p.quantity);

    printf("\nProduct Added Successfully...");

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void displayProduct()
{

    system("cls");
    printf("<==Product List==>\n\n");
    printf("%-10s %-30s %-30s %s\n", "Id", "Product Name", "Quantity", "Date");
    printf("--------------------------------------------------------------------------------\n");

    fp = fopen("product.txt", "rb");
    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        printf("%-10d %-30s %-30d %s\n", p.id, p.productName, p.quantity, p.date);
    }

    fclose(fp);
}

void updateProduct()
{

    int id, f = 0;

    system("cls");
    printf("<==Update Products ==>\n\n");
    printf("Enter Product id to update:");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("product.txt", "rb+");

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {

        if (id == p.id)
        {
            f = 1;
            printf("Enter new product name:");
            fflush(stdin);
            gets(p.productName);

            printf("Enter new product quantity:");
            fflush(stdin);
            scanf("%d", &p.quantity);

            fseek(fp, -sizeof(p), 1);
            fwrite(&p, sizeof(p), 1, fp);
            fclose(fp);
            break;
        }
    }

    if (f == 1)
    {
        printf("\nProduct updated...");
    }
    else
    {
        printf("\n\nProduct Not Found!");
    }
}

void deleteProduct()
{

    int id, f = 0;

    system("cls");
    printf("<==Delete Products ==>\n\n");
    printf("Enter Product id to delete:");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("product.txt", "rb");

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        if (id == p.id)
        {
            f = 1;
            fclose(fp);
            break;
        }
    }

    if (f == 1)
    {
        printf("\nProduct deleted successfully...");
        del(id);
    }
    else
    {
        printf("\n\nProduct Not Found!");
    }
}

void buy()
{

    int id, num, f = 0;
    system("cls");
    printf("<== Buy Products ==>\n\n");
    printf("Enter Product id to Buy:");
    scanf("%d", &id);

    printf("\nEnter Product quantity to Buy:");
    scanf("%d", &num);

    FILE *ft;

    fp = fopen("product.txt", "rb+");

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {

        if (id == p.id)
        {
            f = 1;
            p.quantity = p.quantity - num;
            fseek(fp, -sizeof(p), 1);
            fwrite(&p, sizeof(p), 1, fp);
            fclose(fp);
            if (p.quantity == 0)
            {
                del(p.id);
            }
            break;
        }
    }

    if (f == 1)
    {
        printf("\nProduct bought successfully...");
    }
    else
    {
        printf("\n\nProduct Not Found!");
    }
}

void del(int id)
{
    int f = 0;

    FILE *ft;

    fp = fopen("product.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&p, sizeof(p), 1, fp) == 1)
    {

        if (id == p.id)
        {
            f = 1;
        }
        else
        {
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("product.txt");
    rename("temp.txt", "product.txt");
}

int menu()
{
    int ch;
    while (1)
    {
        system("cls");
        printf("successful login\n\n\n");
        printf("<==Store Management System==>\n");
        printf("1.Add Product\n");
        printf("2.Display Products\n");
        printf("3.Update Product\n");
        printf("4.Delete Product\n");
        printf("5.Buy Product\n");
        printf("0.Exit\n\n");
        printf("Enter your choice:");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            exit(0);
        case 1:
            addProduct();
            break;
        case 2:
            displayProduct();
            break;
        case 3:
            updateProduct();
            break;
        case 4:
            deleteProduct();
            break;
        case 5:
            buy();
            break;
        default:
            printf("Invalid Choice...\n\n");
        }
        printf("\n\nPress Any Key To Continue...");
        getch();
    }
}

int main()
{
    int cho;

    printf("=**********.\n");
    printf(".@@@@@@@@@@@#\n");
    printf(".@@@@@@@@@@@@:\n");
    printf(":********@@@+\n");
    printf("*@@#\n");
    printf("-@@@\n");
    printf(".@@@=\n");
    printf(" @@@%\n");
    printf(" +@@@::::::::::::::::::::::::::::::::::::.\n");
    printf("  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@=\n");
    printf("  %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%\n");
    printf("  #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%\n");
    printf("  =@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%\n");
    printf("  .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+\n");
    printf("   %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("   *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+\n");
    printf("   -@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:\n");
    printf("   :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%\n");
    printf("    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-\n");
    printf("    +@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.\n");
    printf("    :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*\n");
    printf("     .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.\n");
    printf("      %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#\n");
    printf("      *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+\n");
    printf("      :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.\n");
    printf("       %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#\n");
    printf("       #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-\n");
    printf("       +@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.\n");
    printf("        -@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*\n");
    printf("        .@@@%######################### \n");
    printf("         #@@#                           \n");
    printf("         =@@@                           \n");
    printf("         :@@@-                          \n");
    printf("         .@@@@%%%%%%%%%%%%%%%%%%%%%%%%%*\n");
    printf("          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*\n");
    printf("          =@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+\n");
    printf("          ============================:\n");
    printf("                                         \n");
    printf("             .-:             .:         \n");
    printf("           .#@@@%.            .%@@@*     \n");
    printf("          .@@@@@@@:        -@@@@@@%      \n");
    printf("          *@@@@@@@%.        .%@@@@@@@*    \n");
    printf("          @@@@@@@@@.      :@@@@@@@@%     \n");
    printf("          @@@@@@@@@.      =@@@@@@@@%     \n");
    printf("          @@@@@@@@@.      :@@@@@@@@%     \n");
    printf("          +@@@@@@@#       .@@@@@@@+     \n");
    printf("           #@@@@@%.         :@@@@@@#      \n");
    printf("            +@@@*           .%@@@+      \n");
    printf("              .               ..        \n");

    sleep(5);
    system("cls");

    printf("Press '1' for register \nPress '2' for login\n\n");
    scanf("%d", &cho);
    if (cho == 1)
    {
        system("CLS");
        registe();
    }
    else if (cho == 2)
    {
        system("CLS");
        login();
    }
}
