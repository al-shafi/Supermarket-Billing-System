#include<stdio.h>
#include<string.h>

float membership(char c,float total);

typedef struct Input
{
    char name[20];
    int quantity;
    float price;
    float t;
}I;
typedef struct Date
{
    char w[10];
    int day,month,year;
}D;

int main()
{
    system("color 2C");
    int i,n,invoice;
    float vat,netTotal,d,due,cash,total,amount=0;
    char c,m[30];
    I item[100];
    D date;
    FILE *f;

    f=fopen("Product.txt", "r");

    printf("Date(day dd mm yyyy): ");
    scanf("%s %d %d %d", &date.w,&date.day,&date.month,&date.year);
    printf("\nNumber of items: ");
    scanf("%d", &n);



    for(i=0;i<n;i++){
        printf("%d.\n",i+1);
        printf("Item: ");
        scanf("%s", &item[i].name);
        printf("Quantity: ");
        scanf("%d", &item[i].quantity);
        printf("Price: ");
        scanf("%f", &item[i].price);

        item[i].t=(float)item[i].quantity * item[i].price;
    }

    for(i=0;i<n;i++){
        amount=(float)amount+item[i].t;
    }
    vat=(float)((amount*5)/100);

    fflush(stdin);
    total=(float)amount+vat;

    printf("\nMembership(i/s/g/p): ");
    scanf("%c", &c);
    switch(c)
    {
    case 'i':
        strcpy(m,"Invalid");
        d=0.00;
        break;
    case 's':
        strcpy(m,"Silver");
        d=(float)(total*5)/100;
        break;
    case 'g':
        strcpy(m,"Gold");
        d=(float)(total*7.5)/100;
        break;
    case 'p':
        strcpy(m,"Platinum");
        d=(float)(total*10)/100;
        break;
    default:
        scanf("%c", &c);
    }

    netTotal=(float)total-d;

    printf("\n\n              CITY STORE CENTER\n");
    printf("        34/6,Block-B,BASHUNDHARA,DHAKA\n");
    printf("     For assistance/inquires, please call:\n");
    printf("                1800-00-0000\n");
    printf("           www.citystorecenter.com\n");
    printf("-------------------------------------------------\n");
    printf("Invoice number: ");
    scanf("%d", &invoice);

    printf("Membership Status: ");
    puts(m);
    printf("Date: %s, %d/%d/%d\n", date.w,date.day,date.month,date.year);
    printf("\nS.L   Item    Quantity    Price       Sub-total\n");
    printf("-------------------------------------------------\n");
    for(i=0;i<n;i++){
    printf("%d.\t%s\t%d\t%.2f\t\t%.2f\n",i+1, item[i].name,item[i].quantity,item[i].price,item[i].t);
    }
    printf("                        -------------------------\n");
    printf("                        Amount          %.2f\n",amount);
    printf("                        Vat(5%%)         %.2f\n",vat);
    printf("                        -------------------------\n");
    printf("                        Total           %.2f\n",total);
    printf("                        Discount        %.2f\n",d);
    printf("                        -------------------------\n");
    printf("                        Net Total       %.2f\n",netTotal);
    printf("                        -------------------------\n");
    printf("                        CASH            ");

    scanf("%f", &cash);
    due=(float)(cash-netTotal);

    printf("                        -------------------------\n");
    printf("                        Change Due      %.2f\n\n", due);
    printf("\nYou were served by Mr. Ahmed");
    printf("\n\n   Thank You For Shopping At CITY STORE CENTER   \n");
    printf("-------------------------------------------------\n");
    printf("         GOODS SOLD ARE NOT REFUNDABLE\n\n\n\n");

    fclose(f);

    return 0;
}
