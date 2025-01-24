#include <stdio.h>
#include<string.h>
#include<windows.h>
#include <stdlib.h>
#include <conio.h>
void clrscr()
{
    system("cls");
}

void setcolor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}
int adminMenu();
int menu();
void readAdminorder();
char cancelAdminOrder();
struct cus
{
    char num[12];
    int w1, w2, d, ir;
    char name[100], loc[150];
} s[100];

struct admin
{
    char num[12];
    char pass[17];
} s2[50];

char customerDB[100] = "customerDB.txt";
int n; /// The total number of customers

char admindata[50] = "admindata.txt";
int no; /// The total number of admins
void addAdmin();
void readAdminfile()///nothing
{
    FILE *af;
    af=fopen(admindata,"r");
    fscanf(af,"%d",&no);
    if(af== NULL)
    {
        no=1;
        fclose(af);
        af=fopen(admindata, "w" );
        fprintf(af,"%d\n",no)  ;
        fprintf(af,"01866550873\n");
        fprintf(af,"ahnaf\n");
        fclose(af);
    }
    af=fopen(admindata,"r");
    fscanf(af,"%d",&no);
    for(int i = 0; i<no; i++)
    {
        fscanf(af,"%s",s2[i].num);
        fscanf(af,"%s",s2[i].pass);
    }

    fclose(af);


}
void writeAdminfile()///nothing
{
    FILE *f;
    f= fopen(admindata,"w");
    int i ;
    fprintf(f,"%d\n",no);
    for(int i =0; i<no; i++)
    {
        fprintf(f,"%s\n",s2[i].num);
        fprintf(f,"%s\n",s2[i].pass);

    }
    fclose(f);
}
void addAdmin() ///done//////////////////
{
    readAdminfile();
    clrscr();
    gotoxy(45,2);
    setcolor(1);
    printf("ADD ADMIN ");
    gotoxy(30,6);
    setcolor(10);
    printf("Enter new number : ");
    setcolor(14);
    scanf("%s",s2[no].num);
    gotoxy(30,8);
    setcolor(10);
    printf("Enter new password : ");
    setcolor(14);
    scanf("%s",s2[no].pass);
    no++;
    writeAdminfile();
    clrscr();
    gotoxy(30,6);
    setcolor(14);
    printf("##### New admin is added successfully #####");

    int pc;
    gotoxy(30,8);
    setcolor(4);
    printf("[**PRESS '5' TO GO BACK TO ADMIN PANEL] : ");
    scanf("%d",&pc);
    if(pc==5)
    {
        clrscr();
    }
}
char removeAdmin() /// done///////////////
{
    readAdminfile();
    int l=-1;
    char num[12];
    clrscr();
    gotoxy(45,2);  //goto fun
    setcolor(1);
    printf("NUMBERS of ALL ADMIN");
    for(int i =1 ; i<no;i++)
    {
        gotoxy(30,3+i);//
        setcolor(10);
        printf("%s\n",s2[i].num);
    }
    do
    {
        // clrscr();
        gotoxy(45,no+5);
        setcolor(1);
        printf("REMOVE ADMIN");
        setcolor(10);
        gotoxy(30,no+8);
        printf("                                                                          ");
        gotoxy(30,no+8);
        printf("Enter number to remove[*PRESS '5' TO GO BACK TO ADMIN MENU] : ");
        setcolor(14);
        scanf("%s",num);
        setcolor(10);
        for(int i =0; i<no; i++)
        {
            if(strcmp(num,s2[i].num)==0)
            {
                l=i;
                break;
            }
        }
        if(strcmp(num,"5")==0){
            clrscr();
            return -1;
        }
        if(l == -1)
        {
            gotoxy(30,8);
            printf("Number not found... Try Again!");
        }
    }
    while(l==-1);
    for(int i = l; i < no - 1; i++)
    {
        s2[i] = s2[i + 1];
    }
    no--;
    clrscr();
    gotoxy(30,4);
    setcolor(14);
    printf("### The admin is removed successfully ###");
    writeAdminfile();
    int pc;
    gotoxy(30,6);
    setcolor(4);
    printf("[**PRESS '5' TO GO BACK TO ADMIN PANEL] : ");
    scanf("%d",&pc);
    if(pc==5)
    {
        clrscr();
    }
}
void adminPanel()///almost done/////////////////
{
    char numb[12],pass[17];

    readAdminfile();
    clrscr();
    gotoxy(45,2);
    setcolor(1);
    printf("ADMIN LOG IN");
    gotoxy(30,6);
    setcolor(10);
    printf("Enter your phone number : ");
    setcolor(14);
    scanf("%s",numb);
    gotoxy(30,8);
    setcolor(10);
    printf("Enter your password : ");
    setcolor(14);
    scanf("%s",pass);
    setcolor(10);
    int f=1;
    for(int i =0; i<no; i++)
    {
        if(strcmp(s2[i].num,numb)==0 && strcmp(s2[i].pass,pass)==0)
        {
            f=0;
            break;
        }
    }
    if(f)
    {
        clrscr();
        gotoxy(30,4);
        printf("Invalid phone number or password");
        int pc;
        gotoxy(30,6);
        setcolor(4);
        printf("[**PRESS '5' TO GO BACK TO MAIN MENU] : ");
        scanf("%d",&pc);
        if(pc==5)
        {
            clrscr();
        }
    }
    else
    {
        adminMenu();
    }

}
void readFile()///nothing
{
    int i;
    FILE *f = fopen(customerDB, "r");
    fscanf(f, "%d", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(f, "%s ", &s[i].num);
        fscanf(f, "%[^\n] ", s[i].name);
        fscanf(f, "%[^\n]", s[i].loc);
        fscanf(f, "%d %d %d %d", &s[i].w1, &s[i].w2, &s[i].d, &s[i].ir);
    }
    fclose(f);
}
void writeFile()///nothing
{
    FILE *f;
    f = fopen(customerDB, "w");
    if (f == NULL)
    {
        printf("Error\n");
    }
    fprintf(f, "%d\n", n);
    int i;
    for (i = 0; i < n; i++)
    {
        fprintf(f, "%s\n", s[i].num);
        fprintf(f, "%s\n", s[i].name);
        fprintf(f, "%s\n", s[i].loc);
        fprintf(f, "%d %d %d %d\n", s[i].w1, s[i].w2, s[i].d, s[i].ir);
    }
    fclose(f);
}
void readAllorder() ///done//////////////
{
    readFile();
    clrscr();
    gotoxy(45,2);
    setcolor(1);
    printf("ALL ORDER");
    gotoxy(30,6);
    setcolor(10);
    printf("Contact no");
    printf("             Wash1  |  Wash2  |  Dry    |  Iron");
    gotoxy(30,7);
    printf("---------------------------------------------------------------");
    for(int i =0; i<n; i++)
    {
        gotoxy(30,8+i*3);
        printf("%s~",s[i].num);
        gotoxy(55,8+i*3);
        printf("%d",s[i].w1);
        gotoxy(60,8+i*3);
        printf("|");
        gotoxy(65,8+i*3);
        printf("%d",s[i].w2);
        gotoxy(70,8+i*3);
        printf("|");
        gotoxy(75,8+i*3);
        printf("%d",s[i].d);
        gotoxy(80,8+i*3);
        printf("|");
        gotoxy(85,8+i*3);
        printf("%d",s[i].ir);
        gotoxy(30,9+i*3);
        printf("________________________________________________________________");
    }

    int pc;
    gotoxy(30,3*n+12);
    setcolor(4);
    printf("[**PRESS '5' TO GO BACK TO ADMIN PANEL] : ");
    scanf("%d",&pc);
    if(pc==5)
    {
        clrscr();
    }

}
void cancelOrder()///almost done/////////////
{
    readFile();
    int l=-1;
    char num[12];
    do
    {
        gotoxy(45,2);
        setcolor(1);
        printf("CANCEL ORDER");
        gotoxy(30,6);
        setcolor(10);
        printf("Enter number to cancel : ");
        setcolor(14);
        scanf("%s",num);
        setcolor(10);
        for(int i =0; i<n; i++)
        {
            if(strcmp(num,s[i].num)==0)
            {
                l=i;
            }
        }
        if(l == -1)
        {
            clrscr();
            gotoxy(30,8);
            printf("Number not found... Try Again!");

        }
    }
    while(l==-1);
    for(int i = l; i < n - 1; i++)
    {
        s[i] = s[i + 1];
    }
    n--;
    writeFile();

    gotoxy(30,6);
    printf("### Your order is canceled successfully##");
    int pc;
    gotoxy(30,8);
    setcolor(4);
    printf("[**PRESS '5' TO GO BACK TO MAIN MENU] : ");
    scanf("%d",&pc);
    if(pc==5)
    {
        clrscr();
    }
    /// write S to File




}
void placeOrder()///done
{
    gotoxy(35,2);
    setcolor(8);
    printf("PLEASE GIVE YOUR INFORMATION FIRST");
    /// read all from file to the S
    readFile();
    gotoxy(30,4);
    setcolor(10);
    printf("Enter your name : ");
    setcolor(14);///Color for input
    scanf(" %[^\n]", s[n].name);
    gotoxy(30,6);
    setcolor(10);
    printf("Enter your number : ");
    setcolor(14);
    scanf("%s", s[n].num);
    gotoxy(30,8);
    setcolor(10);
    printf("Enter your location : ");
    setcolor(14);
    scanf(" %[^\n]",s[n].loc);
    clrscr();
    gotoxy(30,1);
    setcolor(1);
    printf("           WELCOME TO LAUNDRY HOBE");

    gotoxy(30,3);
    setcolor(10);
    printf("Please select the category of service you need:");

    gotoxy(30,5);
    setcolor(14);
    printf("1. Wash (Light clothes - under 500g)");
    gotoxy(30,6);
    setcolor(10);
    printf("   Perfect for shirts, pants, t-shirts, and other lightweight clothes.");
    gotoxy(30,7);
    printf("   [per quantity costs 25 TAKA]");

    gotoxy(30,9);
    setcolor(14);
    printf("2. Wash (Heavy Clothes - Over 500g)");
    gotoxy(30,10);
    setcolor(10);
    printf("   Ideal for winter wear, blankets, and bedding items.");
    gotoxy(30,11);
    printf("   [per quantity costs 40 TAKA]");

    gotoxy(30,13);
    setcolor(14);
    printf("3. Dry Wash");
    gotoxy(30,14);
    setcolor(10);
    printf("   Specialized cleaning for delicate and sensitive fabrics.");
    gotoxy(30,15);
    printf("   [per quantity costs 200 TAKA]");

    gotoxy(30,17);
    setcolor(14);
    printf("4. Ironing Service");
    gotoxy(30,18);
    setcolor(10);
    printf("   Get your clothes neatly pressed and ready to wear.");
    gotoxy(30,19);
    printf("   [per quantity costs 15 TAKA]");
    gotoxy(30, 21);
    setcolor(4);
    printf("[**PRESS 'n' TO GO BACK TO MAIN MENU] :");
    gotoxy(30,24);
    setcolor(10);
    printf("Enter the number corresponding to your desired service(1 to 4) : ");



    char t;

    s[n].w1 = 0, s[n].w2 = 0, s[n].d = 0, s[n].ir = 0;
    int g = -3 ;
    do
    {
        scanf("%c", &t);
        g += 3 ;
        switch (t)
        {

        case '1':
            gotoxy(30,25+g);
            printf("Enter the amount of cloths : ");
            scanf("%d", &s[n].w1);
            gotoxy(30,27+g);
            setcolor(4);
            printf("[[ ENTER 'y' TO CONFIRM YOUR FINAL ORDER ]]");
            gotoxy(30,29+g);
            setcolor(10);
            printf("Enter the corresponding number to desired other services : ");
            break;
        case '2':
            gotoxy(30,25+g);
            printf("Enter the amount of cloths :");
            scanf("%d", &s[n].w2);
            gotoxy(30,27+g);
            setcolor(4);
            printf("[[ ENTER 'y' TO CONFIRM YOUR FINAL ORDER ]]");
            gotoxy(30,29+g);
            setcolor(10);
            printf("Enter the corresponding number to desired other services : ");
            break;
        case '3':
            gotoxy(30,25+g);
            printf("Enter the amount of cloths :");
            scanf("%d", &s[n].d);
            gotoxy(30,27+g);
            setcolor(4);
            printf("[[ ENTER 'y' TO CONFIRM YOUR FINAL ORDER ]]");
            gotoxy(30,29+g);
            setcolor(10);
            printf("Enter the corresponding number to desired other services : ");
            break;
        case '4':
            gotoxy(30,25+g);
            printf("Enter the amount of cloths :");
            scanf("%d", &s[n].ir);
            gotoxy(30,27+g);
            setcolor(4);
            printf("[[ ENTER 'y' TO CONFIRM YOUR FINAL ORDER ]]");
            gotoxy(30,29+g);
            setcolor(10);
            printf("Enter the corresponding number to desired other services : ");
            break;
        case 'n':
            clrscr();
            //gotoxy(30, 5);
            //printf("Your order prcess have been canceled!!");
            break;
        case 'y':
            clrscr();
            gotoxy(30,4);
            printf("The total cost is %d BDT",(s[n].w1*25+s[n].w2*40+s[n].d*200+s[n].ir*15));
            gotoxy(30,6);
            printf("***Your order is placed successfully***");
            gotoxy(30,8);
            setcolor(4);
            printf("[**PRESS 'n' TO GO BACK TO MAIN MENU] : ");


        }

    }
    while (t != 'n');
    ///edited below
    if(s[n].w1==0 && s[n].w2==0 && s[n].d==0 && s[n].ir==0){
    }
    else{
    n++;

    writeFile();
    }

}
char showCart()  ////almost done ///////
{
    readFile();
    int l=-1;
    char num[12];
    do
    {
        gotoxy(45,2);
        setcolor(1);
        printf("CART");
        gotoxy(30,6);
        setcolor(10);
        printf("Enter your number[*PRESS '5' TO GO BACK TO MAIN MENU]: ");
        setcolor(14);
        scanf("%s",num);
        setcolor(10);
        for(int i =0; i<n; i++)
        {
            if(strcmp(num,s[i].num)==0)
            {
                l=i;
            }
        }///Edited below, changed void to char in declaring func
       if(strcmp(num,"5")==0){
             clrscr();
             return -1;
        return 0;

       }
        else if(l == -1)
        {
            clrscr();
            gotoxy(30,8);
            printf("Number not found... Try Again!\n");
        }
    }
    while(l==-1);

    clrscr();
    gotoxy(30,2);
    setcolor(14);
    printf("Customer's name : %s",s[l].name);
    gotoxy(30,4);
    printf("Service area    : %s",s[l].loc);
    gotoxy(30,6);
    setcolor(4);
    printf("Your order :");
    gotoxy(30,8);
    setcolor(10);
    printf("Services           Quantity");
    gotoxy(30,10);
    printf("---------------------------");
    gotoxy(30,12);
    printf("1. Wash(under 500gm)     %d   ",s[l].w1);
    gotoxy(30,14);
    printf("2. Wash(Over 500gm)      %d   ",s[l].w2);
    gotoxy(30,16);
    printf("3. Drywash               %d   ",s[l].d);
    gotoxy(30,18);
    printf("4. Ironing               %d   ",s[l].ir);
    gotoxy(30,22);
    printf("The total cost is %d BDT",(s[l].w1*25+s[l].w2*40+s[l].d*200+s[l].ir*15));

    int ps;
    gotoxy(30,24);
    setcolor(4);
    printf("[**PRESS '5' TO GO BACK TO MAIN MENU] : ");
    scanf("%d",&ps);
    if(ps==5)
    {
        clrscr();
    }

}

void ourServices(); ///under main function//////done

// Menu for admins
int adminMenu()///done //////
{
    int choice;
    do
    {
        clrscr();
        gotoxy(30,2);
        setcolor(1);
        printf("--- ADMIN MENU ---");
        gotoxy(30,6);
        setcolor(10);
        printf("1. View All Orders");
        gotoxy(30,8);
        printf("2. Cancel/Remove Order");
        gotoxy(30,10);
        printf("3. Add Admin");
        gotoxy(30,12);
        printf("4. Remove Admin");
        gotoxy(30,14);
        printf("5. Back to main menu");
        gotoxy(30,16);
        printf("Enter your choice (1 to 5): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            readAllorder();
            break;
        case 2:
            readAdminorder();
            cancelAdminOrder();
            break;
        case 3:
            addAdmin();
            break;
        case 4:
            removeAdmin();
            break;
        case 5:
            clrscr();
            break;
        default:
            printf("Invalid choice. Please try again.");
        }
    }
    while (choice != 5);
}
// Menu for customeer
void areas();/// under main function

int menu()///done///
{
    gotoxy(30,2);
    setcolor(1);
    printf("**************** MAIN MENU ****************");
    setcolor(10);
    gotoxy(30,6);
    printf("1. Place a order.");
    gotoxy(30,8);
    printf("2. Cancel my order.");
    gotoxy(30,10);
    printf("3. Show my cart.");
    gotoxy(30,12);
    printf("4. Our services.");
    gotoxy(30,14);
    printf("5. Serving areas.");
    gotoxy(30,16);
    printf("6. Admin login.");
    gotoxy(30,18);
    printf("7. Exit.");
    gotoxy(30,20);
    printf("Choose an option(1 to 7) : ");
    int m;
    scanf("%d", &m);
    clrscr();

    return m;
}

void animation();   ////////animation fun

int main()
{
    animation();

    system("color 02");
    int m;


    do
    {
        m = menu();

        if (m == 1)
        {
            placeOrder();
        }

        if (m == 2)
        {
            cancelOrder();

        }

        if(m == 3)
        {
            showCart();
        }

        if(m == 4)
        {
            ourServices();
        }

        if(m == 5)
        {
            areas();

        }

        if(m == 6)
        {
            adminPanel();
        }
    }

    while (m != 7);
}

char cancelAdminOrder()///almost done/////////////
{
    readFile();
    int l=-1 ;
    char num[12];
    do
    {
        gotoxy(45,3*n+12);
        setcolor(1);
        printf("CANCEL ORDER");
        setcolor(10);
        gotoxy(30,3*n+16);
        printf("                                                                          ");
        gotoxy(30,3*n+16);
        printf("Enter number to cancel[*PRESS '5' TO GO BACK TO ADMIN MENU]: ");
        setcolor(14);
        scanf("%s",num);
        setcolor(10);
        for(int i =0; i<n; i++)
        {
            if(strcmp(num,s[i].num)==0)
            {
                l=i;
            }
        }
               if(strcmp(num,"5")==0){
             clrscr();
             return -1;


       }
        else if(l == -1)
        {
            gotoxy(30,3*n+18);
            printf("Number not found... Try Again!");

        }
    }
    while(l==-1);

    for(int i = l; i < n - 1; i++)
    {
        s[i] = s[i + 1];
    }
    n--;
    writeFile();
    clrscr();
    gotoxy(30,6);
    printf("### The order is removed successfully##");
    int pc;
    gotoxy(30,8);
    setcolor(4);
    printf("[**PRESS '5' TO GO BACK TO ADMIN PANEL] : ");
    scanf("%d",&pc);
    if(pc==5)
    {
        clrscr();
    }
    /// write S to File




}



void readAdminorder() ///done//////////////
{
    readFile();
    clrscr();
    gotoxy(45,2);
    setcolor(1);
    printf("ALL ORDER");
    gotoxy(30,6);
    setcolor(10);
    printf("Contact no");
    printf("             Wash1  |  Wash2  |  Dry    |  Iron");
    gotoxy(30,7);
    printf("---------------------------------------------------------------");
    for(int i =0; i<n; i++)
    {
        gotoxy(30,8+i*3);
        printf("%s~",s[i].num);
        gotoxy(55,8+i*3);
        printf("%d",s[i].w1);
        gotoxy(60,8+i*3);
        printf("|");
        gotoxy(65,8+i*3);
        printf("%d",s[i].w2);
        gotoxy(70,8+i*3);
        printf("|");
        gotoxy(75,8+i*3);
        printf("%d",s[i].d);
        gotoxy(80,8+i*3);
        printf("|");
        gotoxy(85,8+i*3);
        printf("%d",s[i].ir);
        gotoxy(30,9+i*3);
        printf("________________________________________________________________");
    }

}


void ourServices()
{
    int y = 2;

    gotoxy(30, y);
    setcolor(1);
    printf("                         WELCOME TO LAUNDRY HOBE ");
    y+=2;

    gotoxy(30, y);
    setcolor(10);
    printf("At Laundry Hobe!, we are committed to providing high-quality, efficient, and affordable laundry services.");
    y+=2;

    gotoxy(30, y);
    printf("We understand the importance of clean, fresh, and well-maintained clothing and linens.");
    y += 2;

    gotoxy(30, y);
    printf("Our services include:");
    y += 2;

    gotoxy(30, y);
    setcolor(14);
    printf("1. Washing Clothes under 500g:");
    y+=2;

    gotoxy(30, y);
    setcolor(10);
    printf("   - Designed for your everyday wear such as shirts, pants, t-shirts, and other lightweight garments.");
    y+=2;

    gotoxy(30, y);
    printf("   - Quick and efficient wash cycles to save your time while ensuring a thorough clean.");
    y += 2;

    gotoxy(30, y);
    setcolor(14);
    printf("2. Washing Clothes over 500g:");
    y+=2;

    gotoxy(30, y);
    setcolor(10);
    printf("   - Ideal for heavier items such as bedsheets, blankets, curtains, and other bulky fabrics.");
    y+=2;

    gotoxy(30, y);
    printf("   - Special care taken to handle larger loads effectively, leaving them fresh and spotless.");
    y += 3;

    gotoxy(30, y);
    setcolor(14);
    printf("3. Dry Wash:");
    y+=2;

    gotoxy(30, y);
    setcolor(10);
    printf("   - Perfect for delicate and premium clothing like suits, sarees, dresses, and specialty fabrics.");
    y+=2;

    gotoxy(30, y);
    printf("   - Gentle cleaning process to maintain fabric integrity and enhance the lifespan of your garments.");
    y += 3;

    gotoxy(30, y);
    setcolor(14);
    printf("4. Ironing:");
    y+=2;

    gotoxy(30, y);
    setcolor(10);
    printf("   - Professional ironing services to give your clothes a crisp and polished look.");
    y+=2;

    gotoxy(30, y);
    printf("   - Say goodbye to wrinkles and enjoy perfectly pressed attire for any occasion.");
    y += 2;

    gotoxy(30, y);
    setcolor(14);
    printf("Why choose Laundry Hobe?");
    y+=2;

    gotoxy(30, y);
    setcolor(10);
    printf("- Affordable pricing for all services, ensuring value for money.");
    y+=2;

    gotoxy(30, y);
    printf("- State-of-the-art equipment and eco-friendly detergents for superior results.");
    y+=2;

    gotoxy(30, y);
    printf("- Friendly and experienced staff dedicated to meeting your laundry needs.");
    y += 2;

    gotoxy(30, y);
    printf("Visit Laundry Hobe! today and let us take care of your laundry needs with professionalism and care.");
    y +=4;

    int ps;
    gotoxy(30,y);
    setcolor(4);
    printf("[**PRESS '5' TO GO BACK TO MAIN MENU] : ");
    scanf("%d",&ps);
    if(ps==5)
    {
        clrscr();
    }
}


void areas()
{
    int y = 1; // Starting vertical position for the list of locations

    gotoxy(30, y);
    setcolor(1);
    printf("AVAILABLE SERVICE SHOP LOCATIONS:");
    y += 2; // Space between the title and the list

    gotoxy(30, y);
    setcolor(10);
    printf("1. Agrabad");
    y += 2; // Space after each location

    gotoxy(30, y);
    printf("2. Lalkhan Bazar");
    y += 2;

    gotoxy(30, y);
    printf("3. WASA");
    y += 2;

    gotoxy(30, y);
    printf("4. Khulshi");
    y += 2;

    gotoxy(30, y);
    printf("5. AK Khan");
    y += 2;

    gotoxy(30, y);
    printf("6. Boropol");
    y += 2;

    gotoxy(30, y);
    printf("7. Halishahar");
    y += 2;

    gotoxy(30, y);
    printf("8. Choumohon");
    y += 2;

    gotoxy(30, y);
    printf("9. Dewanhaat");
    y += 2;

    gotoxy(30, y);
    printf("10. GEC");
    y += 2;

    gotoxy(30, y);
    printf("11. Chawkbazar");
    y += 2;

    gotoxy(30, y);
    printf("12. 2 No Gate");
    y += 2;

    gotoxy(30, y);
    printf("13. Bohoddarhaat");
    y += 2;

    gotoxy(30, y);
    printf("14. Potenga");
    y += 2;

    gotoxy(30, y);
    printf("15. Sea Beach");
    y+=2;
    int ps;
    gotoxy(30,y);
    setcolor(4);
    printf("[**PRESS '5' TO GO BACK TO MAIN MENU] : ");
    scanf("%d",&ps);
    if(ps==5)
    {
        clrscr();
    }

}



void animation()
{
    sleep(2);
    setcolor(2);
    printf("\n\n\n\n\n\n");
    printf("                                         ooooo              .o.       ooooo     ooo ooooo      ooo oooooooooo.   ooooooooo.   oooooo   oooo \n");
    printf("                                         `888'             .888.      `888'     `8' `888b.     `8' `888'   `Y8b  `888   `Y88.  `888.   .8'  \n");
    printf("                                          888             .8\"888.      888       8   8 `88b.    8   888      888  888   .d88'   `888. .8'   \n");
    printf("                                          888            .8' `888.     888       8   8   `88b.  8   888      888  888ooo88P'     `888.8'    \n");
    printf("                                          888           .88ooo8888.    888       8   8     `88b.8   888      888  888`88b.        `888'     \n");
    printf("                                          888       o  .8'     `888.   `88.    .8'   8       `888   888     d88'  888  `88b.       888      \n");
    printf("                                         o888ooooood8 o88o     o8888o    `YbodP'    o8o        `8  o888bood8P'   o888o  o888o     o888o     \n");
    printf("\n");
    printf("\n");
    setcolor(3);
    printf("                                                        ooooo   ooooo   .oooooo.   oooooooooo.  oooooooooooo                            \n");
    printf("                                                        `888'   `888'  d8P'  `Y8b  `888'   `Y8b `888'     `8                            \n");
    printf("                                                         888     888  888      888  888     888  888                                    \n");
    printf("                                                         888ooooo888  888      888  888oooo888'  888oooo8                               \n");
    printf("                                                         888     888  888      888  888    `88b  888    \"                               \n");
    printf("                                                         888     888  `88b    d88'  888    .88P  888       o                            \n");
    printf("                                                        o888o   o888o  `Y8bood8P'  o888bood8P'  o888ooooood8                            \n");


    sleep(2);
    gotoxy(50,30);
    setcolor(5);
    printf("Loading");
    sleep(1);
    printf(". . ");
    sleep(1);
    printf(". . ");
    sleep(1);
    printf(".");
    sleep(1);
    clrscr();
}





