#include<stdio.h>
#include<string.h>

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

void PRODUCT(I item[], int n, float tt[]);
float AMOUNT(float tt[], int n);
float VAT(float tt[],int n);
float TOTAL(float tt[],int n);
float MEMBERSHIP(char m[], char c, float tt[], int n);
float NET_TOTAL(char m[], char c, float tt[], int n);
void DATE(D date);
void INVOICE(int n, int invoice, float tt[], float due, float cash, char c, char m[], I item[], D date);
void NAME(char name[]);
void PRINT(int n, int invoice, float tt[], float due, float cash, char c, char m[], I item[], D date, char name[]);

int main()
{
    int i,n,invoice;
    float due,cash;
    char c,m[30],cn[30],name[30];
    I item[100];
    D date;
    FILE *f,*ff;

    f=fopen("Product.txt", "r");

    printf("Date(day dd mm yyyy): ");
    scanf("%s %d %d %d", &date.w,&date.day,&date.month,&date.year);
    printf("\nNumber of items: ");
    scanf("%d", &n);

    float tt[n];
    PRODUCT(item,n,tt);

    printf("\nMembership(i/s/g/p): ");
    fflush(stdin);
    scanf("%c", &c);

    printf("\nCustomer name: ");
    fflush(stdin);
    gets(cn);

    printf("Invoice no.: ");
    scanf("%d", &invoice);

    INVOICE(n,invoice,tt,due,cash,c,m,item,date);

    NAME(name);

    fclose(f);

    ff=fopen("Invoice.txt", "w");

    fprintf(ff,"Name: %s\n", cn);
    fprintf(ff,"Invoice number: %d\n", invoice);
    fprintf(ff,"Total: %.2f\n\n", NET_TOTAL(m,c,tt,n));

    fclose(ff);

    PRINT(n,invoice,tt,due,cash,c,m,item,date,name);

    return 0;

}
void PRODUCT(I item[], int n, float tt[])
{
    int i;
    for(i=0;i<n;i++){
        printf("%d.\n",i+1);
        printf("Item: ");

        fflush(stdin);
        scanf("%s", &item[i].name);
        printf("Quantity: ");
        scanf("%d", &item[i].quantity);
        printf("Price: ");
        scanf("%f", &item[i].price);

        item[i].t=(float)item[i].quantity * item[i].price;

        tt[i]=item[i].t;
    }
}
float AMOUNT(float tt[], int n)
{

    int i;
    float AMOUNT=0;

    for(i=0;i<n;i++){
        AMOUNT=(float)AMOUNT+tt[i];
    }
    return AMOUNT;
}
float VAT(float tt[],int n)
{
    float a;
    a=AMOUNT(tt,n);
    float VAT;
    VAT=(float)((a*5)/100);
    return VAT;
}
float TOTAL(float tt[],int n)
{
    float TOTAL;
    float a,b;
    a=AMOUNT(tt,n);
    b=VAT(tt,n);
    TOTAL=(float)a+b;
    return TOTAL;
}
float MEMBERSHIP(char m[], char c, float tt[], int n)
{
    float d,a;
    a=TOTAL(tt,n);
    switch(c)
    {
    case 'i':
        strcpy(m,"Invalid");
        d=0.00;
        break;
    case 's':
        strcpy(m,"Silver");
        d=(float)(a*5)/100;
        break;
    case 'g':
        strcpy(m,"Gold");
        d=(float)(a*7.5)/100;
        break;
    case 'p':
        strcpy(m,"Platinum");
        d=(float)(a*10)/100;
        break;
    default:
        fflush(stdin);
        scanf("%c", &c);
    }
    return d;
}
float NET_TOTAL(char m[], char c, float tt[], int n)
{
    float NET_TOTAL;
    float a,d;
    a=TOTAL(tt,n);
    d=MEMBERSHIP(m,c,tt,n);
    NET_TOTAL=(float)a-d;
    return NET_TOTAL;
}
void DATE(D date)
{
    printf("Date: %s, %d/%d/%d\n", date.w,date.day,date.month,date.year);
}
void INVOICE(int n, int invoice, float tt[], float due, float cash, char c, char m[], I item[], D date)
{
    int i;

    printf("\n\n           CITY STORE CENTER\n");
    printf("         34/6,Block-B,BASHUNDHARA,DHAKA\n");
    printf("     For assistance/inquires, please call:\n");
    printf("                1800-00-0000\n");
    printf("           www.citystorecenter.com\n");
    printf("-------------------------------------------------\n");
    printf("Invoice number: %d", invoice);

    MEMBERSHIP(m,c,tt,n);

    printf("\nMembership Status: ");
    puts(m);

    DATE(date);

    printf("\nS.L     Item    Quantity    Price       Sub-total\n");
    printf("-------------------------------------------------\n");
    for(i=0;i<n;i++){
    printf("%d.\t%s\t%d\t%.2f\t\t%.2f\n",i+1, item[i].name,item[i].quantity,item[i].price,item[i].t);
    }
    printf("                        -------------------------\n");
    printf("                        Amount          %.2f\n",AMOUNT(tt,n));
    printf("                        VAT(5%%)         %.2f\n",VAT(tt,n));
    printf("                        -------------------------\n");
    printf("                        Total           %.2f\n",TOTAL(tt,n));
    printf("                        Discount        %.2f\n",MEMBERSHIP(m,c,tt,n));
    printf("                        -------------------------\n");
    printf("                        Net Total       %.2f\n",NET_TOTAL(m,c,tt,n));
    printf("                        -------------------------\n");
    printf("                        CASH            ");

    fflush(stdin);
    scanf("%f", &cash);

    due=(float)(cash-NET_TOTAL(m,c,tt,n));

    printf("                        -------------------------\n");
    printf("                        Change Due      %.2f\n\n", due);
}
void NAME(char name[])
{

    printf("\nYou were served by ");

    fflush(stdin);

    gets(name);

    printf("\n\n   Thank You For Shopping At CITY STORE CENTER   \n");
    printf("-------------------------------------------------\n");
    printf("         GOODS SOLD ARE NOT REFUNDABLE\n\n\n\n");

}

void PRINT(int n, int invoice, float tt[], float due, float cash, char c, char m[], I item[], D date, char name[])
{
    int i;
    FILE *f;

    f = fopen("Print.txt", "w");
    if(f!=NULL){
    fprintf(f,"\n\n           CITY STORE CENTER\n");
    fprintf(f,"         34/6,Block-B,BASHUNDHARA,DHAKA\n");
    fprintf(f,"     For assistance/inquires, please call:\n");
    fprintf(f,"                1800-00-0000\n");
    fprintf(f,"           www.citystorecenter.com\n");
    fprintf(f,"-------------------------------------------------\n");
    fprintf(f,"Invoice number: %d", invoice);

    MEMBERSHIP(m,c,tt,n);

    fprintf(f,"\nMembership Status: ");
    fprintf(f,m);

    fprintf(f,"\nDate: %s, %d/%d/%d\n", date.w,date.day,date.month,date.year);

    fprintf(f,"\nS.L     Item    Quantity    Price       Sub-total\n");
    fprintf(f,"-------------------------------------------------\n");
    for(i=0;i<n;i++){
    fprintf(f,"%d.\t%s\t%d\t%.2f\t\t%.2f\n",i+1, item[i].name,item[i].quantity,item[i].price,item[i].t);
    }
    fprintf(f,"                        -------------------------\n");
    fprintf(f,"                        Amount          %.2f\n",AMOUNT(tt,n));
    fprintf(f,"                        VAT(5%%)         %.2f\n",VAT(tt,n));
    fprintf(f,"                        -------------------------\n");
    fprintf(f,"                        Total           %.2f\n",TOTAL(tt,n));
    fprintf(f,"                        Discount        %.2f\n",MEMBERSHIP(m,c,tt,n));
    fprintf(f,"                        -------------------------\n");
    fprintf(f,"                        Net Total       %.2f\n",NET_TOTAL(m,c,tt,n));
    fprintf(f,"                        -------------------------\n");

    fflush(stdin);

    fprintf(f,"                        CASH            %.2f", cash);
    fprintf(f,"\n                        -------------------------\n");
    fprintf(f,"                        Change Due      %.2f\n\n", due);
    fprintf(f,"\nYou were served by ");
    fprintf(f,name);

    fprintf(f,"\n\n   Thank You For Shopping At CITY STORE CENTER   \n");
    fprintf(f,"-------------------------------------------------\n");
    fprintf(f,"         GOODS SOLD ARE NOT REFUNDABLE\n\n\n\n");

    fclose(f);
    }

}
