#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct maincourse{
int m_food_idno;
char m_name[300];
float m_rating;
float m_price;
struct maincourse *prev;
struct maincourse *next;
}*mfirst,*mlast;

struct appetizers{
int a_food_idno;
char a_name[300];
float a_rating;
float a_price;
struct appetizers *next;
struct appetizers *prev;
}*afirst,*alast;

struct beverages{
int b_food_idno;
char b_name[300];
float b_rating;
float b_price;
struct beverages *next;
struct beverages *prev;
}*bfirst,*blast;

struct combo {
    int combo_idno;
    char combo_name[300];
    char items[3][300];
    float combo_price;
    struct combo *prev;
    struct combo *next;
} *cfirst, *clast;

struct order_hist{
int customer_id;
int items[10][2];
float amount;
char date[11];
char name[22];
 struct order_hist *left;
    struct order_hist *right;
} *root;


int cust_id=1;
int today_customer=0;
float total_income=0;
struct order_hist *newNode_hist(int cust_id, float amount, char name[22],char date[11]) {
    struct order_hist *nn;
    nn = (struct order_hist *)malloc(sizeof(struct order_hist));
    nn->customer_id = cust_id;
    nn->amount = amount;
    strcpy(nn->date, date);
    strcpy(nn->name,name);
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

struct order_hist *insert_bst(struct order_hist *node, int cust_id, float amount,char name[22], char date[11]) {
    if (node == NULL) {
        return newNode_hist(cust_id, amount,name, date);
    }
    if (cust_id < node->customer_id) {
        node->left = insert_bst(node->left, cust_id, amount,name, date);
    } else if (cust_id > node->customer_id) {
        node->right = insert_bst(node->right, cust_id, amount,name, date);
    }
    return node;
}

void display_inorder(struct order_hist *node) {
    if (node != NULL) {
        display_inorder(node->left);
        printf("\t%d\t     %s\t\t      %s\t\t     %f\t\n", node->customer_id, node->date,node->name, node->amount);
        display_inorder(node->right);
    }
}

void display_ord_hist() {
    printf("----------------------------------------------------------------------------------\n");
    printf("----------------------------------ORDER HISTORY-----------------------------------\n");
    printf("----------------------------------------------------------------------------------\n");
    if (root == NULL) {
        printf("NO ORDERS TODAY :)\n");
    } else {
           printf("	OR_NO	    	DATE	         NAME OF CUSTOMER\t  	AMOUNT		\n");
        display_inorder(root);
    }
}

void cdisplay() {
    struct combo *temp = cfirst;
    printf("  ID_NO\t  COMBO NAME\t  ITEMS\t\t\t\t\t\t\tPRICE\n");
    if (cfirst == NULL)
        printf("SORRY! WE DON'T HAVE ANY COMBOS\n");
    while (temp != NULL) {
        printf("  %d        %s        %s, %s, %s          %f\n", temp->combo_idno, temp->combo_name, temp->items[0], temp->items[1], temp->items[2], temp->combo_price);
        temp = temp->next;
    }
}

void cdelete(int id) {
    struct combo *temp = cfirst;
    while (temp != NULL && temp->combo_idno != id) {
        temp = temp->next;
    }
    if (temp != NULL) {
        if (temp == cfirst) {
            cfirst = cfirst->next;
            if (cfirst != NULL) {
                cfirst->prev = NULL;
            }
        } else if (temp == clast) {
            clast = clast->prev;
            clast->next = NULL;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        free(temp);
        printf("Combo with ID %d deleted successfully.\n", id);
    } else {
        printf("Combo with ID %d not found.\n", id);
    }
}
void cinsert(char name[], char items[][300], float price, int idno) {
    struct combo *nn;
    nn = (struct combo *)malloc(sizeof(struct combo));
    nn->combo_idno = idno;
    strcpy(nn->combo_name, name);
    for (int i = 0; i < 3; i++) {
        strcpy(nn->items[i], items[i]);
    }
    nn->combo_price = price;
    nn->next = NULL;
    nn->prev = NULL;
    if (cfirst == NULL) {
        cfirst = nn;
    } else {
        nn->prev = clast;
        clast->next = nn;
    }
    clast = nn;
}
void minsert(char a[],float p,int idno){
struct maincourse *nn;
nn=(struct maincourse*)malloc(sizeof(struct maincourse));
nn->m_food_idno=idno;
strcpy(nn->m_name,a);
nn->m_rating=4.0;
nn->m_price=p;
nn->next=NULL;
nn->prev=NULL;
if(mfirst==NULL){
mfirst=nn;
}
else{
nn->prev=mlast;
mlast->next=nn;
}
mlast=nn;
}
void ainsert(char a[],float p,int idno){
struct appetizers *nn;
nn=(struct appetizers*)malloc(sizeof(struct appetizers));
nn->a_food_idno=idno;
strcpy(nn->a_name,a);
nn->a_price=p;
nn->a_rating=4.0;
nn->next=NULL;
nn->prev=NULL;
if(afirst==NULL){
afirst=nn;
alast=nn;
}
else
{
nn->prev=alast;
alast->next=nn;
alast=nn;
}
}
void binsert(char a[],float p,int idno){
struct beverages *nn;
nn=(struct beverages*)malloc(sizeof(struct beverages));
nn->b_food_idno=idno;
strcpy(nn->b_name,a);
nn->b_rating=4.0;
nn->b_price=p;
nn->next=NULL;
nn->prev=NULL;
if(bfirst==NULL){
bfirst=nn;
blast=nn;
}else{
nn->prev=blast;
blast->next=nn;
blast=nn;
}
}

void adisplay(){
struct appetizers *temp=afirst;
printf("  ID_NO\t\t  ITEMNAME\t\t        PRICE\t\t        RATING	\n");
if(afirst==NULL)
printf("SORRY! WE DON'T HAVE ANY DESSERTS\n");
while(temp!=NULL){
printf("  %d\t\t%s\t\t%f\t\t%f  \n",temp->a_food_idno,temp->a_name,temp->a_price,temp-> a_rating);
temp=temp->next;
}
}
void mdisplay(){
struct maincourse*temp=mfirst;
printf("  ID_NO\t\t  ITEMNAME\t\t        PRICE\t\t        RATING	\n");
if(mfirst==NULL)
printf("SORRY! WE DON'T HAVE ANY MAINCOURSE\n");
while(temp!=NULL){
printf("  %d\t\t%s\t\t%f\t\t%f  \n",temp->m_food_idno,temp->m_name,temp->m_price,temp-> m_rating);
temp=temp->next;
}
}
void bdisplay(){
struct beverages *temp=bfirst;
printf("  ID_NO\t\t  ITEMNAME\t\t        PRICE\t\t        RATING  \n");
if(bfirst==NULL)
printf("SORRY! WE DON'T HAVE ANY BEVERAGES\n");
while(temp!=NULL){
printf("  %d\t\t%s\t\t%f\t\t%f  \n",temp->b_food_idno,temp->b_name,temp->b_price,temp->b_rating);
temp=temp->next;
}
}
int login(){
char username[50];
char userpaswd[11];
char ch;
int i;
printf("WELCOME :) \n");
printf("\n\nEnter your Username:");
scanf("%s",username);
fflush(stdin);
printf("Enter your password:");
fflush(stdin);
for(i=0;i<7;i++){
ch=getch();
printf("*");
userpaswd[i]=ch;
}
userpaswd[i]='\0';
if(!(strcmp(username,"Admin")&&(strcmp(userpaswd,"rishi12")))){
printf("\nLogged In Successfully\n\n");
return 1;
}
else{
printf("\nIncorrect username or password>>Please try again\n");
return 0;
}
}
void order() {
    int a[50][2], b[50][2], m[50][2], c[50][2];
    int n, j = 0, y = 0, x = 0, z = 0, n1, k = 0;
    float total_amount = 0.0;
    struct appetizers *atemp;
    struct beverages *btemp;
    struct maincourse *mtemp;
    struct combo *ctemp;
    char date[11];
    char name_cust[200];

    do {
        printf("Enter \n1.TO ORDER FROM MAINCOURSE\n2.TO ORDER FROM BEVERAGES\n3.TO ORDER FROM DESSERTS\n4.TO ORDER FROM COMBOS\n5.TO EXIT\n");
        scanf("%d", &n1);
        switch (n1) {
            case 1:
                do {
                    printf("Please enter the FOOD IDNO AND ITS QUANTITY IN MAINCOURSE: \n");
                    scanf("%d %d", &m[y][0], &m[y][1]);
                    y++;
                    printf("Do you want more items in maincourse\n1.Yes\n2.No\n");
                    scanf("%d", &n);
                } while (n == 1);
                break;
            case 2:
                do {
                    printf("Please enter the FOOD IDNO and ITS QUANTITY IN BEVERAGES: \n");
                    scanf("%d %d", &b[j][0], &b[j][1]);
                    j++;
                    printf("Do you want more items in beverages\n1.Yes\n2.No\n");
                    scanf("%d", &n);
                } while (n == 1);
                break;
            case 3:
                do {
                    printf("Please enter the FOOD IDNO and ITS QUANTITY IN DESSERTS: \n");
                    scanf("%d %d", &a[x][0], &a[x][1]);
                    x++;
                    printf("Do you want more items in desserts\n1.Yes\n2.No\n");
                    scanf("%d", &n);
                } while (n == 1);
                break;
            case 4:
                cdisplay();
                printf("Please enter the COMBO IDNO and ITS QUANTITY IN COMBO: \n");
                scanf("%d %d", &c[z][0], &c[z][1]);
                z++;
                break;
        }
    } while (n1 != 5);

    printf("Enter your name: ");
    scanf("%s", name_cust);
    printf("Enter today's date: ");
    scanf("%s", date);
    printf("\n--------------------------------------------------------------------------------\n");
    printf("                                      BILL                                        \n");
    printf("Name: %s\n", name_cust);
    printf("Date: %s\n", date);

    for (k = 0; k < y; k++) {
        mtemp = mfirst;
        while (mtemp != NULL && mtemp->m_food_idno != m[k][0]) {
            mtemp = mtemp->next;
        }
        if (mtemp != NULL) {
            printf("----------------------------------------------------------------------------------\n");
            printf("%d\t%s\t%d\t\t%f\n", mtemp->m_food_idno, mtemp->m_name, m[k][1], m[k][1] * (mtemp->m_price));
            total_amount += (m[k][1] * (mtemp->m_price));
        }
    }

    for (k = 0; k < j; k++) {
        btemp = bfirst;
        while (btemp != NULL && btemp->b_food_idno != b[k][0]) {
            btemp = btemp->next;
        }
        if (btemp != NULL) {
            printf("----------------------------------------------------------------------------------\n");
            printf("%d\t%s\t%d\t\t%f\n", btemp->b_food_idno, btemp->b_name, b[k][1], b[k][1] * (btemp->b_price));
            total_amount += (b[k][1] * (btemp->b_price));
        }
    }

    for (k = 0; k < x; k++) {
        atemp = afirst;
        while (atemp != NULL && atemp->a_food_idno != a[k][0]) {
            atemp = atemp->next;
        }
        if (atemp != NULL) {
            printf("----------------------------------------------------------------------------------\n");
            printf("%d\t%s\t%d\t\t%f\n", atemp->a_food_idno, atemp->a_name, a[k][1], a[k][1] * (atemp->a_price));
            total_amount += (a[k][1] * (atemp->a_price));
        }
    }

    for (k = 0; k < z; k++) {
        ctemp = cfirst;
        while (ctemp != NULL && ctemp->combo_idno != c[k][0]) {
            ctemp = ctemp->next;
        }
        if (ctemp != NULL) {
            printf("----------------------------------------------------------------------------------\n");
            printf("Combo: %d - %s\n", ctemp->combo_idno, ctemp->combo_name);
            for (int i = 0; i < 3; i++) {
                if (strcmp(ctemp->items[i], "") != 0) {
                    printf("%s\n", ctemp->items[i]);
                }
            }
            printf("Quantity: %d\n", c[k][1]);
            printf("Price: %f\n", c[k][1] * ctemp->combo_price);
            total_amount += (c[k][1] * ctemp->combo_price);
        }
    }

    printf("----------------------------------------------------------------------------------\n");
    printf("Total Payable amount is: %f\n", total_amount);
    printf("----------------------------------------------------------------------------------\n");
    printf("THANK YOU AND WELCOMING YOU AGAIN :)\n");

    struct order_hist *new_order = (struct order_hist *)malloc(sizeof(struct order_hist));
    new_order->amount = total_amount;
    new_order->customer_id = cust_id++;
    strcpy(new_order->date, date);
    strcpy(new_order->name,name_cust);
    new_order->left = new_order->right = NULL;
    if (root == NULL) {
        root = new_order;
    } else {
        insert_bst(root, new_order->customer_id, new_order->amount, new_order->name,new_order->date);
    }
    today_customer++;
    total_income += total_amount;
}



void delete_item(int id, int category) {
    if (category == 1) { // Main Course
        struct maincourse *temp = mfirst;
        while (temp != NULL && temp->m_food_idno != id) {
            temp = temp->next;
        }
        if (temp != NULL) {
            if (temp == mfirst) {
                mfirst = mfirst->next;
                if (mfirst != NULL) {
                    mfirst->prev = NULL;
                }
            } else if (temp == mlast) {
                mlast = mlast->prev;
                mlast->next = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Main course item with ID %d deleted successfully.\n", id);
        } else {
            printf("Main course item with ID %d not found.\n", id);
        }
    } 
    else if (category == 2) { // Beverages
        struct beverages *temp = bfirst;
        while (temp != NULL && temp->b_food_idno != id) {
            temp = temp->next;
        }
        if (temp != NULL) {
            if (temp == bfirst) {
                bfirst = bfirst->next;
                if (bfirst != NULL) {
                    bfirst->prev = NULL;
                }
            } else if (temp == blast) {
                blast = blast->prev;
                blast->next = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Beverage item with ID %d deleted successfully.\n", id);
        } else {
            printf("Beverage item with ID %d not found.\n", id);
        }
    } else if (category == 3) { // Desserts
        struct appetizers *temp = afirst;
        while (temp != NULL && temp->a_food_idno != id) {
            temp = temp->next;
        }
        if (temp != NULL) {
            if (temp == afirst) {
                afirst = afirst->next;
                if (afirst != NULL) {
                    afirst->prev = NULL;
                }
            } else if (temp == alast) {
                alast = alast->prev;
                alast->next = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("Desserts item with ID %d deleted successfully.\n", id);
        } else {
            printf("Desserts item with ID %d not found.\n", id);
        }
    } else {
        printf("Invalid category. Please choose a valid category.\n");
    }
}

void cadd() {
    int idno;
    char name[300];
    char items[3][300];
    float price;

    printf("Enter the combo ID: ");
    scanf("%d", &idno);

    printf("Enter the combo name: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < 3; i++) {
        printf("Enter item %d: ", i + 1);
        scanf(" %[^\n]", items[i]);
    }

    printf("Enter the combo price: ");
    scanf("%f", &price);

    cinsert(name, items, price, idno);
    printf("New combo added successfully.\n");
}

void main(){
int x,e,choice,ch,fin,k,t;
float p;
char n[40];
void cedit(int);
void cdelete(int);
minsert("VEGGIE BURGER    ",99.0,1);
minsert("MUSHROOM BURGER  ",299.0,2);
minsert("BBQ CHICKEN PIZZA",299.0,3);
minsert("MARGHERITA PIZZA ",249.0,4);
minsert("GRILLED SANDWICH ",199.0,5);
minsert("CHEESE PASTA     ",149.0,6);
minsert("EGG PASTA        ",199.0,7);
minsert("CHICKEN WRAP     ",249.0,8);
minsert("FRENCH FRIES     ",99.0,9);
minsert("PIRI PIRI FRIES  ",149.0,10);
minsert("CHICKEN WINGS    ",199.0,11);
binsert("WATER            ",30.0,1);
binsert("TEA              ",40.0,2);
binsert("COFFEE           ",99.0,3);
binsert("MOCKTAIL         ",120.0,4);
binsert("SMOOTHIE         ",149.0,5);
binsert("MILK SHAKE       ",149.0,6);
binsert("SODA             ",99.0,7);
binsert("COOL DRINKS      ",79.0,8);
ainsert("ICECREAM SCOOP   ",99.0,1);
ainsert("CHOCOLATE BROWNIE",199.0,2);
ainsert("TRIPPLE SUNDAE   ",249.0,3);
ainsert("CHOCO LAVA FUDGE ",249.0,4);
ainsert("APRICOT DELIIGHT ",249.0,5);
ainsert("GULAB JAMUN      ",149.0,6);
ainsert("MANGO PUDDING    ",199.0,7);
char combo1_items[3][300] = {"BURGER","FRENCH FRIES", "COOL DRINKS        "};
        char combo2_items[3][300] = {"MARGHERITA PIZZA", "PIRI PIRI FRIES", "MOJITO"};
        char combo3_items[3][300] = {"CHEESE PASTA", "FRENCH FRIES", "MILK SHAKE   "};
        char combo4_items[3][300] = {"CHICKEN WRAP", "COLD COFFEE", "GULAB JAMUN   "};
        char combo5_items[3][300] = {"BBQ PIZZA", "COLD COFFEE ", "PIRI PIRI FRIES "};

        cinsert("Combo 1", combo1_items, 599.0, 1);
        cinsert("Combo 2", combo2_items, 599.0, 2);
        cinsert("Combo 3", combo3_items, 499.0, 3);
        cinsert("Combo 4", combo4_items, 399.0, 4);
        cinsert("Combo 5", combo5_items, 599.0, 5);
do{
printf("\n--------------------------------------------------------------------------------\n");
printf("\n1.----FOOD PART----\n");
printf("\n2.----ADMIN PANEL---\n");
printf("\n3.----EXIT----\n");
printf("\nEnter your choice: ");
scanf("%d",&choice);
switch(choice){
case 1:
do{
printf("\n1.---FOOD LIST---\n");
printf("\n2.---ORDER---\n");
scanf("%d",&e);
switch(e){
case 1:printf("\n-------------------------------------------------------------------------\n");
printf("----------------------------MENU--------------------------------------------------\n");
printf("----------------------------------------------------------------------------------\n");
printf("\nMAIN COURSE\n");
mdisplay();
printf("\nBEVERAGES\n");
bdisplay();
printf("\nDESSERTS\n");
adisplay();
printf("\nCOMBOS\n");
cdisplay();
break;
case 2:
order();
break;
}
printf("\n1.---FOOD PART---\n2.---MAIN PAGE---\n3.---EXIT---\n");
scanf("%d",&x);
}
while(x==1);
break;
case 2:
printf("\n");
k=login();
if(k==1){
do{
                            printf("1.ADD NEW DISH\n");
                            printf("2.DELETE EXISTING DISH\n");
                            printf("3.CHECK TODAY'S TOTAL INCOME\n");
                            printf("4.CHECK TODAY'S TOTAL NO OF CUSTOMERS\n");
                            printf("5.ORDER HISTORY\n");
                            printf("6.LIST OF ITEMS\n");
                            printf("7. ADD NEW COMBO\n");
                            printf("8. DELETE COMBO\n");
                            printf("9. EXIT\n");
                            scanf("%d", &ch);
switch(ch){
case 1:
printf(" ");
printf("Enter the name of the item: ");
scanf("%s",n);
fflush(stdin);
printf("Enter the price of the %s item: ",n);
scanf("%f",&p);
fflush(stdin);
printf("Enter thr food_idno of that item: ");
scanf("%d",&fin);
fflush(stdin);
printf("Enter the type of menu you are adding\n1.MAINCOURSE\n2.BEVERAGES\n3.DESSERTS\n");
scanf("%d",&t);
if(t==1)
minsert(n,p,fin);
if(t==2)
binsert(n,p,fin);
else
ainsert(n,p,fin);
printf("----------------------------------------------------------------------------------\n");
printf("---------------------------NEW ITEEM ADDED SUCCESSFULLY---------------------------\n");
printf("----------------------------------------------------------------------------------\n");
break;
case 2:
int id, category;
printf("Enter the ID of the item you want to delete: ");
scanf("%d", &id);
printf("Enter the category of the item you want to delete (1 for Main Course, 2 for Beverages, 3 for Desserts): ");
scanf("%d", &category);
delete_item(id, category);
case 3:
printf("----------------------------------------------------------------------------------\n");
printf("TODAY'S TOTAL INCOME IS:- %f\n",total_income);
printf("----------------------------------------------------------------------------------\n");
break;
case 4:
printf("----------------------------------------------------------------------------------\n");
printf("TODAY'S TOTAL NO OF CUSTOMERS VISITED: %d\n",today_customer);
printf("----------------------------------------------------------------------------------\n");
break;
case 5:
display_ord_hist();
printf("\n");
break;
case 6:
printf("\nMAINCOURSE\n");
mdisplay();
printf("\nBEVERAGES\n");
bdisplay();
printf("\nDESSERTS\n");
adisplay();
printf("\nCOMBOS\n");
cdisplay();
break;
case 7:
cadd();
break;
case 8:
    printf("Enter the ID of the combo you want to delete: ");
    scanf("%d", &fin);
    cdelete(fin);
    break;
                                case 9:
                                    break;
                            }
                        } while(ch!=9); 
}
}
}
while(choice!=3);
}
