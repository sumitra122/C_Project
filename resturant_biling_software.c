#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
	char item[20];
	float price;
	int qty;
};
struct orders{
	char custumer[50];
	char date[50];
	int numOfItems;
	
	struct items itm[50];
};

void generateBillHeader(char name[50], char date[30])
{
	printf("\n\n");
	printf("\t ADV.Resturant");
	printf("\t-------------------------");
	printf("\nDate:%s", date);
	printf("\nInvoice to:%s", name);
	printf("\n");
	printf("--------------------------------------------------\n");
	printf("Items\t\t\t");
	printf("Qty\t\t\t\t");
	printf("Total\t\t");
	printf("\n--------------------------------------------------");
	printf("\n\n");
}
void generateBillBody(char item[30], int qty, float price){
	printf("%s\t\t", item);
	printf("%d\t\t", qty);
	printf("%.2f\t\t", qty*price);
	printf("\n");
}

void generateBillFooter(float total){
	printf("\n");
	float dis = 0.1*total;
	float netTotal = total-dis;
	float cgst = 0.09*netTotal, grandTotal=netTotal+2*cgst;
	printf("--------------------------------------------------\n");
	printf("Sub Total \t\t\t%.2f", total);
	printf("\nDiscount @10%s\t\t\t %.2f", "%",dis);
	printf("\n\t\t\t\t-----------------");
	printf("\nNet Total \t\t\t %2f", netTotal);
	printf("\nCGST @9%s\t\t\t%2f","%", cgst);
	printf("\nSGST @9%s\t\t\t%2f", "%", cgst);
	printf("\n--------------------------------------------------");
	printf("\nGrand Total\t\t\t%2f", grandTotal);
	printf("\n--------------------------------------------------\n");
	
}

int main(){
	float total;
	int opt, n;
	int i;
	char name[50];
	struct orders ord;
	struct orders order;
	char saveBill = 'y', countFlag='y';
	FILE *fp;
	while(countFlag == 'y'){
	float total = 0;
	int invoiceFound=0;
	printf("\t*****************RESTURANT BILLING SYSTEM*****************");
	printf("\n 1. Generate Invoice");
	printf("\n 2. Show All Invoices");
	printf("\n 3. Search Invoices");
	printf("\n 4. Exit");
	printf("\n\n Please select your preferred operation:\t");
	scanf("%d", &opt);
	fgetc(stdin);
	switch(opt){
		case 1:
			system("clear");
			printf("\n Please enter th name of the customer:\t");
			fgets(ord.custumer,50,stdin);
			ord.custumer[strlen(ord.custumer)-1]=0;
			strcpy(ord.date, __DATE__);
			printf("\nPlease enter the number of item:\t");
			scanf("%d", &n);
			ord.numOfItems = n;
			for( i=0;i<n;i++){
				fgetc(stdin);
				printf("\n");
				printf("Plase enter the item %d", i+1);
			    fgets(ord.itm[i].item,20,stdin);
			    ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
			    printf("\nPlease enter the quantity:\t");
			    scanf("%d",&ord.itm[i].qty);
			    printf("\nPlease enter the unit price:\t");
			    scanf("%f",&ord.itm[i].price);
			    total += ord.itm[i].qty * ord.itm[i].price;
			}
			
			generateBillHeader(ord.custumer,ord.date);
			int i;
			for(i=0;i<ord.numOfItems;i++){
				generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
				
			}
			generateBillFooter(total);
			
			printf("\n Do you want to save the invoice[y/n]:\t");
			scanf("%s", &saveBill);
			
			if(saveBill=='y'){
				fp = fopen("ResturantBill.dat", "a+");
				fwrite(&ord ,sizeof(struct orders), 1,fp);
				if(fwrite != 0)
				printf("\n Succesfuly saved");
				else
				printf("\nError saving");
				fclose(fp);
			}
			break;
			
			case 2:
				system("clear");
				fp = fopen("ResturantBill.dat", "r");
				printf("\n *******Your Previous Invoice*******\n");
				while(fread(&order,sizeof(struct orders),1,fp)){
					float tot = 0;
					generateBillHeader(order.custumer,order.date);
					int i;
					for(i=0;i<order.numOfItems;i++){
						generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
						tot+=order.itm[i].qty*order.itm[i].price;
					}
					
					generateBillFooter(tot);
				}
				fclose(fp);
				break;
				
				case 3:
					printf("\nEnter the nme of the custumer:\t");
				//	fgetc(stdin);
					fgets(name,50,stdin);
					name[strlen(name)-1]=0;
					system("clear");
				fp = fopen("ResturantBill.dat", "r");
				printf("\n *******Invoice of %s*******\n", name);
				while(fread(&order,sizeof(struct orders),1,fp)){
					float tot = 0;
					if(!strcmp(order.custumer,name)){
							generateBillHeader(order.custumer,order.date);
					int i;
					for(i=0;i<order.numOfItems;i++){
						generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
						tot+=order.itm[i].qty*order.itm[i].price;
					}
					
					generateBillFooter(tot);
					invoiceFound = 1;
					}
				
				}
				if(!invoiceFound){
					printf("sorry the invoice for %s doesnot found", name);
				}
				fclose(fp);
				break;
				
				case 4:
					printf("\n\t\t Bye Bye:)\n\n");
					exit(0);
					break;
					
					default:
						printf("Sorry invalid option");
						break;
					}
			printf("\n Do you want to perform another operation?[y/n]:\t");
			scanf("%s", &countFlag);
	}
}

