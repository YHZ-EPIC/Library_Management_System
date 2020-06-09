#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

struct data{
	int date;
	int month;
	int year;
	int issuedate;
	int issuemonth;
	int issueyear;
	int returndate;
	int returnmonth;
	int returnyear;
	int curdate;
	int curmonth;
	int curyear;
};

struct record
{
	char book[30];
	int id;
	char auth[30];
	char std[30];
	int roll;
	struct data date_data;
}rec;

void login();
void menu(); 
void add();
void del();
void search();
void issue();
void view();
void issuebook();
void searchbook();
void removebook();
int checkdate(struct data *dateptr);
int checkissuedate(struct data *dateptr);
int checkreturndate(struct data *dateptr);
int checkcurdate(struct data *dateptr);
int checkleapyear(int year);
void list();
void update();
void reset();
void calculatepayment();
void close();

int main()
{
	printf("\n\n\n");
	printf("\n\t\t\t  ############################################### \n\t");
	printf("\n\t\t\t    --- WELCOME TO Library Management System --- \n\t");
	printf("\n\t\t\t  ############################################### \n\n\t");
	system("pause");
	system("cls");
	login();
}

void login()
{
	char name[20],pass[20],c;
	char n[20]={"iamfunny"},p[20]={"whoispro"};
	int i;
	
start:	
	
	printf("\n\n");
	printf("\n\t\t\t  ############################################### \n\t");
	printf("\n\t\t\t    -------------- LOGIN MENU  --------------- \n\t");
	printf("\n\t\t\t  ############################################### \n\n\t");	
	
	printf("\n Enter Name : ");
	gets(name);
	printf("\n Enter Password : ");
	for ( i = 0 ; i<15 ; i++ )
    {
        fflush(stdin);
        c = getch();
        pass[i] = c;
        if ( pass[i] == '\b')   // for backspace
        {
            printf("\b \b");
            i-= 2;
            continue;
        }
        if ( pass[i] == ' ' || pass[i] == '\r' )   // for space 
            printf(" ");
        else
            printf("*");
        if ( pass[i]=='\r')
            break;
    }
    pass[i]='\0';
	
	if(strcmp(name,n) == 0 && strcmp(pass,p) == 0)
	{
		printf("\n\n ---------------------> Wait ........................");
		Sleep(1000);
		printf("\n\n\t ------ LOGIN SUCCESSFULLY !!! ------ \n\n\t");
		system("pause");
		system("cls");
		menu();
	}
	else
	{
		printf("\n\n ---------------------> Wait ........................");
		Sleep(1000);
		printf("\n\n\t ------ INVALID PASSWORD !!! ------ \n\n\t");
		system("pause");
		system("cls");
		goto start;
	}
}

void menu()
{
	int n;
	
	printf("\n\n");
	printf("\n\t\t\t  ############################################### \n\t");
	printf("\n\t\t\t    ----------  Welcome To MENU  -------------- \n\t");
	printf("\n\t\t\t  ############################################### \n\n\t");	
	
	printf("\n 1) Add \n 2) Delete \n 3) Search \n 4) Issue \n 5) View Book List \n 6) Edit Book Record \n 7) Reset Database \n 8) Calculate Payment \n 0) Exit \n\n CHOOSE :");
	scanf("%d",&n);
	
	switch(n)
	{
		case 0:
			system("cls");
			close();
			break;
		case 1:
			system("cls");
			add();
			break;
		case 2:
			system("cls");
			del();
			break;
		case 3:
			system("cls");
			search();
			break;
		case 4:
			system("cls");
			issue();
			break;
		case 5:
			system("cls");
			list();
			break;
		case 6:
			system("cls");
			update();
			break;
		case 7:
			system("cls");
			reset();
			break;
		case 8:
			system("cls");
			calculatepayment();
			break;	
		default:
			printf("\n\n\t\t  ----- INVALID !!! ----- \n\n");
			system("pause");
			system("cls");
			menu();
			break;							
	}
}

void add()
{
	int valid=0;
	char ch;
	FILE *fp;
	fp = fopen("Data.txt", "a");
	 
	do{
		 printf("\n\n");
	     printf("\n\t\t\t  ############################################### \n\t");
	   	 printf("\n\t\t\t    ----------------- ADD RECORD -------------- \n\t");
	     printf("\n\t\t\t  ############################################### \n\n\t");
		 fflush(stdin);
		 printf("\n\n Enter Book Name:");
		 gets(rec.book);
		 printf("\n Enter Book ID:");
		 scanf("%d", &rec.id);
		 fflush(stdin);
		 printf("\n Enter Author Name:");
		 gets(rec.auth);
		 do{
            printf("\n Enter Date (Day/Month/Year): ");
            scanf("%d/%d/%d",&rec.date_data.date,&rec.date_data.month,&rec.date_data.year);
            valid = checkdate(&rec.date_data);
            if (!valid)
            {
                printf("\n     Oh!! Please Enter a Valid Date.\n");
            }
        }
        while(!valid);
		 
		 fwrite(&rec, sizeof(rec), 1, fp);
		 printf("\n\n Record Entered Successfully !!\n\n");
		 
		 printf("--> Wonna Enter Another Record ? (Y/N) :");
		 ch = getche();
		 system("cls");
		 
	 }while(ch == 'y' || ch == 'Y');
	 fflush(stdin);
	 
	 system("pause");
	 system("cls");
	 fclose(fp);
	 menu();
}

int checkdate(struct data *dateptr)
{
    if (dateptr->year > 2030 || dateptr->year < 1900)
        return 0;
    if (dateptr->month < 1 || dateptr->month > 12)
        return 0;
    if (dateptr->date < 1 || dateptr->date > 31)
        return 0;
    if (dateptr->month == 2)
    {
        if (checkleapyear(dateptr->year))
            return (dateptr->date <= 29);
        else
            return (dateptr->date <= 28);
    }
    if (dateptr->month == 4 || dateptr->month == 6 ||
            dateptr->month == 9 || dateptr->month == 11)
        return (dateptr->date <= 30);
    return 1;
}

int checkissuedate(struct data *dateptr)
{
    if (dateptr->issueyear > 2030 || dateptr->issueyear < 1900)
        return 0;
    if (dateptr->issuemonth < 1 || dateptr->issuemonth > 12)
        return 0;
    if (dateptr->issuedate < 1 || dateptr->issuedate > 31)
        return 0;
    if (dateptr->issuemonth == 2)
    {
        if (checkleapyear(dateptr->issueyear))
            return (dateptr->issuedate <= 29);
        else
            return (dateptr->issuedate <= 28);
    }
    if (dateptr->issuemonth == 4 || dateptr->issuemonth == 6 ||
            dateptr->issuemonth == 9 || dateptr->issuemonth == 11)
        return (dateptr->issuedate <= 30);
    return 1;
}

int checkreturndate(struct data *dateptr)
{
    if (dateptr->returnyear > 2030 || dateptr->returnyear < 1900)
        return 0;
    if (dateptr->returnmonth < 1 || dateptr->returnmonth > 12)
        return 0;
    if (dateptr->returndate < 1 || dateptr->returndate > 31)
        return 0;
    if (dateptr->returnmonth == 2)
    {
        if (checkleapyear(dateptr->returnyear))
            return (dateptr->returndate <= 29);
        else
            return (dateptr->returndate <= 28);
    }
    if (dateptr->returnmonth == 4 || dateptr->returnmonth == 6 ||
            dateptr->returnmonth == 9 || dateptr->returnmonth == 11)
        return (dateptr->returndate <= 30);
    return 1;
}

int checkcurdate(struct data *dateptr)
{
    if (dateptr->curyear > 2030 || dateptr->curyear < 1900)
        return 0;
    if (dateptr->curmonth < 1 || dateptr->curmonth > 12)
        return 0;
    if (dateptr->curdate < 1 || dateptr->curdate > 31)
        return 0;
    if (dateptr->curmonth == 2)
    {
        if (checkleapyear(dateptr->curyear))
            return (dateptr->curdate <= 29);
        else
            return (dateptr->curdate <= 28);
    }
    if (dateptr->curmonth == 4 || dateptr->curmonth == 6 ||
            dateptr->curmonth == 9 || dateptr->curmonth == 11)
        return (dateptr->curdate <= 30);
    return 1;
}

int checkleapyear(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

void del()
{
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    ----------------- DELETE RECORD ----------- \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	
	FILE *fp,*ft;
	int x,flag=0,n;
	
	printf("\n Enter BOOK ID To Delete:");
	scanf("%d",&x);
	
	fp = fopen("Data.txt","r");
	ft = fopen("temp.txt","w");
	
	while(fread(&rec,sizeof(rec),1,fp))
	{
		if(rec.id == x)
		{
			flag=1;
		}
		if(rec.id != x)
		{
			fwrite(&rec,sizeof(rec),1,ft);
		}
	}
	
	if(flag == 1)
	{
		printf("\n Record Available \n\n Confirm To Delete ??? \n\n");
		system("pause");
		fclose(fp);
		fclose(ft);
		
	  	remove("Data.txt");
		rename("temp.txt","Data.txt");
		
		printf("\n\n ----------> Removing .............");
	    Sleep(1000);
	  	printf("\n\n ******* Record Deleted ********* \n\n");
	  	
	  	system("pause");
	  	system("cls");
	  	menu();
	}
	else
	{
		printf("\n\n --> Record Not FOUND !!! \n");
		fclose(fp);
		fclose(ft);
		printf("\n 1) Enter Again \n 2) Back To Menu \n\n CHOOSE:");
		scanf("%d",&n);
		if(n == 1)
		{
			printf("\n\n");
			system("pause");
			system("cls");
			del();
		}
		if(n == 2)
		{
			printf("\n\n");
			system("pause");
	  		system("cls");
	  		menu();
		}
	}
}

void search()
{
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    ----------------- SEARCH RECORD ----------- \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	
	int x,flag=0;
	FILE *fp;
	
	fp = fopen("Data.txt","r");
	
	rewind(fp);
	
	printf("\n ENTER Book ID TO SEARCH:");
	scanf("%d",&x);

	while (fread(&rec, sizeof(rec), 1, fp))
	{
		if(x == rec.id)
		{
			flag=1;
			printf("\n ------------------------------------------------------- \n");
			printf("\n Book Name = %s", rec.book);
		    printf("\n Book ID = %d", rec.id);
		    fflush(stdin);
		    printf("\n Author = %s", rec.auth);
		    printf("\n Book Record Entered Date = %d/%d/%d",rec.date_data.date,rec.date_data.month,rec.date_data.year); 
			printf("\n\n ------------------------------------------------------- \n");
		}
	}
	if(flag == 0)
	{
		printf("\n--------- RECORD NOT FOUND ------------\n");
	}
	
	fclose(fp);
	
	printf("\n\n\t");
	system("pause");
  	system("cls");
  	menu();
}

void issue()
{
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    ----------------- ISSUE RECORD ------------ \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	
	int x;
	
	printf("\n\n 1) Issue a Book \n 2) View Issued Books \n 3) Search Issued Books \n 4) Remove Issued Books \n 5) Main Menu \n\n CHOOSE:");
	scanf("%d",&x);
	
	switch(x)
	{
		case 1:
			system("cls");
			issuebook();
			break;
		case 2:
			system("cls");
			view();
			break;
		case 3:
			system("cls");
			searchbook();
			break;
		case 4:
			system("cls");
			removebook();
			break;
		case 5:
			system("cls");
			menu();
			break;	
		default:
		 	printf("\n\n\t\t  ----- INVALID !!! ----- \n\n");
			system("pause");
			system("cls");
			issue();
			break;			
	}
}

void issuebook()
{
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    ----------------- ISSUE BOOKS ------------- \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	
	int valid1=0,valid2=0,x,flag=0;
	char ch;
	FILE *fp,*fp1;
	
	fp1 = fopen("Data.txt","r");
	fp = fopen("issue.txt","a");
	
	printf("\n Enter Book ID to Issue:");
	scanf("%d",&x);
	
	fflush(stdin);
		
	while(fread(&rec,sizeof(rec),1,fp1))
	{
		if(x == rec.id)
		{
			printf("\n\t --> Book is Available.");
			fflush(stdin);
			printf("\n Enter Student Name:");
			gets(rec.std);
			printf("\n Enter Student ID:");
			scanf("%d", &rec.roll);
			fflush(stdin);
		do{
            printf("\n Enter Issue Date (Day/Month/Year): ");
            scanf("%d/%d/%d",&rec.date_data.issuedate,&rec.date_data.issuemonth,&rec.date_data.issueyear);
            valid1 = checkissuedate(&rec.date_data);
            if (!valid1)
            {
                printf("\n     Oh!! Please Enter a Valid Date.\n");
            }
        }
        while(!valid1);
        
        do{
            printf("\n Enter Returning Date (Day/Month/Year): ");
            scanf("%d/%d/%d",&rec.date_data.returndate,&rec.date_data.returnmonth,&rec.date_data.returnyear);
            valid2 = checkreturndate(&rec.date_data);
            if (!valid2)
            {
                printf("\n     Oh!! Please Enter a Valid Date.\n");
            }
        }
        while(!valid2);
        
       	flag=1;
		fwrite(&rec,sizeof(rec),1,fp);
		}
	}
		
	if(flag == 1)
	{
		printf("\n BOOK ISSUED SUCCESSFULLY!!");	
	}
	else
	{
		printf("\n\t --> Book is Not Available. \n\n");
		printf("\n BOOK IS NOT ISSUED");
	}
	
	printf("\n\n Wonna Issue More Books ? (Y/N) :");
 	ch = getche();
 	
 	if(ch == 'y' || ch == 'Y')
 	{
 		fclose(fp);
		fclose(fp1);		
		system("cls");
		issuebook();
	}
 	else
 	{
		fclose(fp);
		fclose(fp1);		
		printf("\n\n\t");
		system("pause");
		system("cls");
		issue();
	}
}

void view()
{
	printf("\n\n");
 
 	system("cls");
	FILE *fp1;
 	fp1 = fopen("issue.txt", "r");
 	
 	rewind(fp1);
 	
	printf("\n\t\t\t  ############################################### \n\t");
	printf("\n\t\t\t   -------------  ISSUED BOOKS LIST -------------- \n\t");
	printf("\n\t\t\t  ############################################### \n\n\t");	
	
 	printf("\n ------------------------------------------------------------------------------------ \n");
 	while (fread(&rec, sizeof(rec), 1, fp1))
 	{
		printf("\n Book : %s \n ID : %d \n Author : %s \n Student : %s \n Roll No : %d \n", rec.book,rec.id,rec.auth,rec.std,rec.roll);
 		printf("\n Book Record Entered Date = %d/%d/%d",rec.date_data.date,rec.date_data.month,rec.date_data.year);
		printf("\n Book Issued Date = %d/%d/%d",rec.date_data.issuedate,rec.date_data.issuemonth,rec.date_data.issueyear);
		printf("\n Book Returning Date = %d/%d/%d",rec.date_data.returndate,rec.date_data.returnmonth,rec.date_data.returnyear);  
		printf("\n ------------------------------------------------------------------------------------ \n");
	}
	fclose(fp1);	
	
	printf("\n\n\t");
	system("pause");
  	system("cls");
  	issue();
}

void searchbook()
{
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    ------------ Search ISSUED BOOKS ---------- \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	
	int x,flag=0;
	FILE *fp;
	
	fp = fopen("issue.txt","r");
	
	rewind(fp);
	
	printf("\n ENTER ISSUED BOOK ID TO SEARCH:");
	scanf("%d",&x);

	while (fread(&rec, sizeof(rec), 1, fp))
	{
		if(x == rec.id)
		{
			fflush(stdin);
			flag=1;
			printf("\n ------------------------------------------------------- \n");
			printf("\n Book Name = %s", rec.book);
		    printf("\n Book ID = %d", rec.id);
		    printf("\n Author Name= %s", rec.auth);
		   	printf("\n Student Name= %s", rec.std);
		   	printf("\n Roll Number = %d", rec.roll);
		   	fflush(stdin);
		   	printf("\n Book Record Entered Date = %d/%d/%d",rec.date_data.date,rec.date_data.month,rec.date_data.year);
		    printf("\n Book Issued Date = %d/%d/%d",rec.date_data.issuedate,rec.date_data.issuemonth,rec.date_data.issueyear);
		    printf("\n Book Returning Date = %d/%d/%d",rec.date_data.returndate,rec.date_data.returnmonth,rec.date_data.returnyear);  
			printf("\n\n\n ------------------------------------------------------- \n");
		}
	}
	if(flag == 0)
	{
		printf("\n--------- RECORD NOT FOUND ------------\n");
	}
	
	fclose(fp);
	
	printf("\n\n\t");
	system("pause");
  	system("cls");
  	issue();
}

void removebook()
{
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    ------------ Delete ISSUED BOOKS ---------- \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	
	FILE *fp,*ft;
	int x,flag=0,n;
	
	printf("\n Enter BOOK ID To Delete:");
	scanf("%d",&x);
	
	fp = fopen("issue.txt","r");
	ft = fopen("tempo.txt","w");
	
	while(fread(&rec,sizeof(rec),1,fp))
	{
		if(x == rec.id)
		{
			flag = 1;
		}
		if(rec.id != x)
		{
			fwrite(&rec,sizeof(rec),1,ft);
		}
	}
	
	if(flag == 1)
	{
		printf("\n Record Available \n\n Confirm To Delete \n\n");
		system("pause");
		fclose(fp);
		fclose(ft);
		
	  	remove("issue.txt");
		rename("tempo.txt","issue.txt");
		printf("\n\n ----------> Removing .............");
		Sleep(1000);
	  	printf("\n\n ******* Record Deleted ********* \n\n");
	  	
	  	system("pause");
	  	system("cls");
	  	issue();
	}
	else
	{
		printf("\n\n --> Record Not FOUND !!! \n");
		fclose(fp);
		fclose(ft);
		printf("\n 1) Enter Again \n 2) Back To Menu \n\n CHOOSE:");
		scanf("%d",&n);
		if(n == 1)
		{
			printf("\n\n");
			system("pause");
			system("cls");
			removebook();
		}
		if(n == 2)
		{
			printf("\n\n");
			system("pause");
	  		system("cls");
	  		issue();
		}
	}
}

void list()
{
	printf("\n\n");
	
	system("cls");
	FILE *fp1;
 	fp1 = fopen("Data.txt", "r");
 	
 	rewind(fp1);
 	
	printf("\n\t\t\t  ############################################### \n\t");
	printf("\n\t\t\t   -------------  Available BOOKS -------------- \n\t");
	printf("\n\t\t\t  ############################################### \n\n\t");	
	
 	printf("\n ------------------------------------------------------------------------------------ \n");
 	while (fread(&rec, sizeof(rec), 1, fp1))
 	{
		printf("\n Book : %s \n ID : %d \n Author : %s",rec.book,rec.id,rec.auth);
 		printf("\n Book Record Entered Date = %d/%d/%d",rec.date_data.date,rec.date_data.month,rec.date_data.year);
		printf("\n\n ------------------------------------------------------------------------------------ \n");
	}
	fclose(fp1);	
	
	printf("\n\n\t");
	system("pause");
  	system("cls");
  	menu();
}

void update()
{
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    ----------------- UPDATE RECORD ----------- \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	
	int no, found = 0;
	
	FILE *file;
	
    printf("\n\n Please Enter The ID: ");
    scanf("%d",&no);
    
    file = fopen("Data.txt", "r+");
    
	while ((fread(&rec, sizeof(rec), 1, file)) > 0 && found == 0)
    {
        if (rec.id == no)
        {
            printf("\n ********* Record Found **********\n");
			 fflush(stdin);
			 printf("\n\n Enter Book Name:");
			 gets(rec.book);
			 printf("\n Enter Book ID:");
			 scanf("%d", &rec.id);
			 fflush(stdin);
			 printf("\n Enter Author Name:");
			 gets(rec.auth);
	        
			fseek(file,  - (long)sizeof(rec), 1);
	        fwrite(&rec, sizeof(rec), 1, file);
	        printf("\n\n\t");
	        system("pause");
			printf("\n\n ----------> Updating .............");
			Sleep(1000);
	        printf("\n\n ******* Record Updated ********* \n\n");
    		fclose(file);
	        found = 1;
	        system("pause");
	        system("cls");
	        menu();
        } 
    }
    if (found == 0)
    {
        printf("\n Record Not Found \n\n");
		system("pause");
	    system("cls");
	    menu();
	}
}

void reset()
{
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    --------------- RESET DATABASE ------------ \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	system("pause");
	printf("\n\n ----------> Resetting .............");
	Sleep(1000);
	
	FILE *fp,*ft;
	
	fp=fopen("Data.txt","w");
	ft=fopen("issue.txt","w");
	
	fclose(fp);
	fclose(ft);
	
	printf("\n\n ******* DONE Resetting ********* \n\n");
	system("pause");
	system("cls");
	menu();
}

void calculatepayment()
{
	int n,x,flag=0,valid=0,datediff=0,mondiff=0,yeardiff=0,diff=0;
	printf("\n\n");
			printf("\n\t\t\t  ############################################### \n\t");
			printf("\n\t\t\t    ------------ CALCULATE PAYMENT ---------- \n\t");
			printf("\n\t\t\t  ############################################### \n\n\t");
	
 	FILE *fp,*ft;
	
	fp = fopen("issue.txt","r");
	
	rewind(fp);
	
	printf("\n ENTER ISSUED BOOK ID TO CALCULATE THE PAYMENT:");
	scanf("%d",&x);

	while (fread(&rec, sizeof(rec), 1, fp))
	{
		if(x == rec.id)
		{
			flag=1;
			printf("\n ------------------------------------------------------- \n");
			printf("\n Book Name = %s", rec.book);
		    printf("\n Book ID = %d", rec.id);
		    printf("\n Author Name= %s", rec.auth);
		   	printf("\n Student Name= %s", rec.std);
		   	printf("\n Roll Number = %d", rec.roll);
		   	fflush(stdin);
		    printf("\n Book Issued Date = %d/%d/%d",rec.date_data.issuedate,rec.date_data.issuemonth,rec.date_data.issueyear);
		    printf("\n Book Returning Date = %d/%d/%d",rec.date_data.returndate,rec.date_data.returnmonth,rec.date_data.returnyear);  
		    printf("\n\n ------------------------------------------------------- \n");
		}
	} 
	
	if(flag == 0)
	{
		printf("\n---------SORRY!! RECORD NOT FOUND ------------\n");
		fclose(fp);
	    printf("\n\n\t");
	    system("pause");
  	    system("cls");
  	    menu();
	}
	
    do{
            printf("\n Enter Current Date (Day/Month/Year): ");
            scanf("%d/%d/%d",&rec.date_data.curdate,&rec.date_data.curmonth,&rec.date_data.curyear);
            valid = checkcurdate(&rec.date_data);
            if (!valid)
            {
                printf("\n     Oh!! Please Enter a Valid Date.\n");
            }
        }
        while(!valid);
        
    printf("\n\n ----------> Generating Payment .............");
    Sleep(1500);
    
    if(rec.date_data.curdate==rec.date_data.returndate && rec.date_data.curmonth==rec.date_data.returnmonth && rec.date_data.curyear==rec.date_data.returnyear){    
    	printf("\n\n\n                       Receipt");
		printf("\n -------------------------------------------------------\n");
		printf("                Payment Amount: Rs500\n");
		printf("                Due           : Rs000\n");
		printf(" -------------------------------------------------------\n");
		printf("                Net Amount    : Rs500\n");
		printf(" -------------------------------------------------------\n\n\n");
	}
	else{
		    if(rec.date_data.returndate<rec.date_data.curdate)
    {     
        if(rec.date_data.returnmonth==3)
        {
            if((rec.date_data.returnyear%4==0 && rec.date_data.returnyear%100!=0) || (rec.date_data.returnyear%400==0)) 
            {
                rec.date_data.returndate+=29;
            }   
            else
            {
                rec.date_data.returndate+=28;
            }                        
        }
        else if (rec.date_data.returnmonth==5 || rec.date_data.returnmonth==7 || rec.date_data.returnmonth==10 || rec.date_data.returnmonth==12)         
        {
           rec.date_data.returndate+=30; 
        }
        else
        {
           rec.date_data.returndate+=31;
        }
        rec.date_data.returnmonth=rec.date_data.returnmonth - 1;
    }
    if (rec.date_data.returnmonth<rec.date_data.curmonth)
    {
        rec.date_data.returnmonth+=12;
        rec.date_data.returnyear-=1;
    }          
    
    datediff=rec.date_data.returndate-rec.date_data.curdate;
    mondiff=rec.date_data.returnmonth-rec.date_data.curmonth;
    yeardiff=rec.date_data.returnyear-rec.date_data.curyear;
    
    diff=((yeardiff*365)+(mondiff*30)+datediff);
    
    if(diff>0){
    	printf("\n\n\n                       Receipt");
		printf("\n -------------------------------------------------------\n");
		printf("                Payment Amount: Rs500\n");
		printf("                Due           : Rs000\n");
		printf(" -------------------------------------------------------\n");
		printf("                Net Amount    : Rs500\n");
		printf(" -------------------------------------------------------\n\n\n");
	}
	else if(diff<0)
	{
    	printf("\n\n\n                       Receipt");
		printf("\n -------------------------------------------------------\n");
		printf("                Payment Amount: Rs500\n");
		printf("                Due           : Rs200\n");
		printf(" -------------------------------------------------------\n");
		printf("                Net Amount    : Rs700\n");
		printf(" -------------------------------------------------------\n\n\n");
	}
	}
   
   
	ft = fopen("tempo.txt","w");
	
	while(fread(&rec,sizeof(rec),1,fp))
	{
		if(x == rec.id)
		{
			flag = 1;
		}
		if(rec.id != x)
		{
			fwrite(&rec,sizeof(rec),1,ft);
		}
		
	}
	
	if(flag == 1)
	{

		fclose(fp);
		fclose(ft);
		
	  	remove("issue.txt");
		rename("tempo.txt","issue.txt");
	}
	
	system("pause");
	system("cls");
    menu();
}

void close()
{	
	printf("\n\n\n\n");
	printf("\n\t\t\t  ############################################### \n\t");
	printf("\n\t\t\t    --------- THANKS FOR SUPPORTING US --------   \n\t");
	printf("\n\t\t\t  ############################################### \n\n\t");	
	
	system("pause");
	exit(1);
}
