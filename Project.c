#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int cancellation();

typedef struct
{
	char Name[50];
	char ID[8];
	char Gender;
	int Phone;
	int Passport;
	char email[50];

}Customer;

void create_file(char *filename, FILE * cinf)
{
	int underscore = 0;
		if((cinf = fopen(filename,"r")) == NULL)
	{
		cinf = fopen("customers_information.txt","w");
		fprintf(cinf,"%-10s	%-10s	%-30s	%-5s	%-15s	%-15s	%-30s\n",  "Customer","ID","Name", "Gender","Phone", "Passport", "Email");
		for(underscore = 0; underscore < 150; underscore++)
			{
				fprintf(cinf,"_");
			}
		fclose(cinf);
	}

}

int countlines(char *filename)
{
	int lines = 0;
	char ch;
	FILE* cinf=fopen(filename, "r");
 	while((ch = fgetc(cinf))!= EOF)
	{
 	if(ch == '\n')
  		{
    		lines++;
	  	}
	}
	fclose(cinf);
    return lines;

}

Customer *fill_custinfo( int i, Customer *list_ofcust )
{

 printf("Name : ");
 scanf("%s", list_ofcust[i].Name);
 fflush(stdin);
//  gets(list_ofcust[i].Name ) ;


 printf("ID : ");
 scanf("%s",list_ofcust[i].ID);

 printf("Gender : ");
 scanf(" %c",&list_ofcust[i].Gender);

 printf("Phone Number : ");
 scanf("%d", &list_ofcust[i].Phone);

 printf("Passport: ");
 scanf("%d", &list_ofcust[i].Passport);

 printf("Email: ");
 scanf("%s", list_ofcust[i].email);

 return list_ofcust;
}

void displayinf(int i, Customer *list_ofcust)
{
	printf("Customer Name: %s\n", list_ofcust[i].Name);
	printf("Customer ID: %s\n",list_ofcust[i].ID);
	printf("Customer Gender: %c\n",list_ofcust[i].Gender);
	printf("Customer Phone :%d\n",list_ofcust[i].Phone);
	printf("Customer Passport :%d\n",list_ofcust[i].Passport);
	printf("Customer Email :%s\n",list_ofcust[i].email);
}

void stock_info(int i,char *filename, Customer *list_ofcust)
{
	FILE * cinf;
	cinf = fopen(filename,"a");
	fprintf(cinf,"\n%-10d	%-10s	%-30s	%-5c	0%-15d	%-15d	%-30s", i,list_ofcust[i].ID , list_ofcust[i].Name,
		list_ofcust[i].Gender,list_ofcust[i].Phone ,list_ofcust[i].Passport,list_ofcust[i].email);
	fclose(cinf);

}

void print_menu()
{
	printf("\n\n				MAIN MENU.				");
	printf("\n\n\n\n\n\n");
	printf("\t\t1.Reserve a room.\n"); // fill info //check availability //check in
	printf("\t\t2.Cancel reservation\n");//r u sure //compare name with existing names//names dont match
	printf("\t\t3.Check weekly restaurant menu.\n");
	printf("\t\t4.About.\n");
	printf("\t\t5.Quit\n");

}

int choices(int i, Customer *list_ofcust)
{
	system("clear");
	int quit=0,option;
	do
	{
		system("clear");
		print_menu();
		system("color F");
		scanf("%d",&option);
		switch(option)
		{
			case 1 :
		           {
		           	FILE * cinf;
					create_file("customers_information.txt", cinf);
					int lines = countlines("customers_information.txt");
					i = lines;
		           	system("clear");
		           	fill_custinfo( i, list_ofcust );
		           	system("clear");
		           	stock_info(i,"customers_information.txt",list_ofcust);
		           	printf("Reservation successful!\n");
		           	displayinf( i,list_ofcust);
		           	printf("That is your rank on our list : %d",i);
		           	sleep(5);
		           	system("clear");
	                break;
	               }
	        case 2:
	        	    {
					 cancellation();
					break;
				    }
			case 3:
				{
					// restaurant
					break;
				}
			case 4:
				{
					//about
					break;
				}
			case 5:
			   	{

	   				quit=1;
					system("color 4");
					system("clear");
					//remove("customers_information.txt");
	   				break;
				}
		    default:
				{
				printf("ENTREE INVALIDE\n");
				system("color 4");
				sleep(1);
				system("clear");
				break;
				}
	   }

	}



while(quit==0);
}

int cancellation()
{
	char c;
	int rank;
	FILE *cancellation;
	printf("Are you sure you want to cancel? [y/n]: ");
	scanf(" %c", &c);
	if(c == 'y')
	{
		cancellation = fopen("cancellation_requests.txt", "a");
		printf("What is your rank : ");
		scanf("%d", &rank);
		fprintf(cancellation,"A customer has requested a cancellation : rank is %d \n", rank );
		printf("Your request has been sent to the admin.");
		sleep(2);
	}
	else if(c == 'n')
		printf("Cancel request.\n");
	else
		printf("ENTREE INVAILDE");
	return 0;
}

void print_adminmenu()
{
	printf("\n\n				ADMIN MENU.				");
	printf("\n\n\n\n\n\n");
	printf("\t\t1.Check list of customers.\n"); // fill info //check availability //check in
	printf("\t\t2.Check cancel request.2\n");//r u sure //compare name with existing names//names dont match
	printf("\t\t3.Quit\n");
}

int admin_cancellation()
{
	FILE * cancellation;
	char ch;
	system("clear");
	cancellation = fopen("cancellation_requests.txt", "r+");
	printf("\n		Canceallation Requests		\n");
	while((ch = fgetc(cancellation)) != EOF)
      printf("%c", ch);

   fclose(cancellation);
   return 0;
}

int print_listofcustomers()
{
	FILE * cinf;
	char ch;
	system("clear");
	cinf = fopen("customers_information.txt" , "r");
	printf("\n		List of Customers		\n");
	while((ch = fgetc(cinf)) != EOF)
      printf("%c", ch);

   fclose(cinf);

}

void adminsection()
{
	system("clear");
	int quiT=0,optioN;
	do
	{
		system("clear");
		print_adminmenu();
		system("color F");
		scanf("%d",&optioN);
		switch(optioN)
		{
			case 1 :
		           {
					print_listofcustomers();
		        //   	sleep(10);
		           	getch();
		           	system("clear");
	                break;
	               }
	        case 2:
	        	    {
					admin_cancellation();
		         //   sleep(1);
		         getch();
		           	system("clear");
					break;
				    }
			case 3:
			   	{
	   				quiT=1;
					system("color 4");
					system("clear");
	   				break;
				}
		    default:
				{
				printf("ENTREE INVALIDE\n");
				system("color 4");
				sleep(1);
				system("clear");
				break;
				}
	   }

	}
	while(quiT == 0);
}

int main()
{
	char c;
	char password[20];
	int v ;
	int individu = 0;
	Customer *list_ofcust = (Customer *) malloc(26 * sizeof(Customer));



	printf("Login as admin? [y/n] \n");
	scanf("%c" , &c);
	if((c == 'n')||(c=='N'))
	{
		choices(individu, list_ofcust);

	}
	if((c == 'y')||(c=='Y'))
	{
		do
		{
		printf("Enter password : ");
		scanf("%s", password);
		v = strcmp(password, "shihaja");
		}
		while(v != 0) ;

		printf("You have logged in successfully :)");
		sleep(1);
		adminsection();

	}
}







