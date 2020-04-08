//when a new user signs up, create a new account number and give it to them
//keep pin and account number column in account.txt
//check account number and pin before withdrawing/crediting
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void check_bal()
{
	system("cls");
	printf("********************************************CHECK YOUR BALANCE*******************************\n");
	FILE *fp1;
	int acc_no, bal, pin_no, acc, pin, found = 0;
	fp1 = fopen("Account.txt", "r");
	printf("Enter your account number: ");
	scanf("%d", &acc);
	printf("Enter your pin: ");
	scanf("%d", &pin);
	while(!feof(fp1) && (found == 0))
	{
		fscanf(fp1, "%d %d %d", &pin_no, &acc_no, &bal);
		if((acc_no == acc) && (pin_no == pin))
			found = 1;
	}
	if(found == 1)
		printf("\n\nBalance is %d\n", bal);
	else
		printf("Check account number or pin and try again\n");
	fclose(fp1);
}

void withdraw()
{
	system("cls");
	printf("********************************************WITHDRAWALS*******************************\n");
	FILE *fp;
	FILE *temp;
	fp = fopen("Account.txt", "r");
	temp = fopen("Temp.txt", "w");
	int account, withdraw, acc_no, bal, new_bal, pin_no, pin, found = 0;
	char check;
	printf("Enter account number: ");
	scanf("%d", &account);
	printf("Enter your pin: ");
	scanf("%d", &pin);
	printf("Enter amount to withdraw: ");
	scanf("%d", &withdraw);
	while(!feof(fp))
	{
		fscanf(fp, "%d %d %d", &pin_no, &acc_no, &bal);
		if((account == acc_no) && (pin == pin_no))
		{
			found = 1;
			if(bal < withdraw)
			{
				printf("Withdrawal is more than balance\n");
				fprintf(temp, "%d %d %d\n", pin_no, acc_no, bal);
			}
			
			else
			{
				new_bal = bal-withdraw;
				fprintf(temp, "%d %d %d\n", pin_no, acc_no, new_bal);
			}
		}
		else
		{
			fprintf(temp, "%d %d %d\n", pin_no, acc_no, bal);
		}
	}
	fclose(fp);
	fclose(temp);
	
	FILE *fp1;
	FILE *temp1;	
	fp1 = fopen("Account.txt", "w");
	temp1 = fopen("Temp.txt", "r");
	while(!feof(temp1))
	{
		fscanf(temp1, "%d %d %d", &pin_no, &acc_no, &bal);
		fprintf(fp1, "%d %d %d\n", pin_no, acc_no, bal);
	}
	fclose(fp1);
	fclose(temp);
	if(found == 1)
	{
		printf("Would you like to check your balance?(y/n): ");
		fflush(stdin);
		scanf("%c", &check);
		if((check == 'Y') || (check == 'y'))
			check_bal();
	}
	else
		printf("Check account number or pin and try again\n");
	
}

void credit()
{
	system("cls");
	printf("********************************************CREDITS*******************************\n");
	FILE *fp;
	FILE *temp;
	fp = fopen("Account.txt", "r");
	temp = fopen("Temp.txt", "w");
	int account, credit, acc_no, bal, new_bal, pin_no, pin;
	char check;
	printf("Enter account number: ");
	scanf("%d", &account);
	printf("Enter your pin: ");
	scanf("%d", &pin);
	printf("Enter amount to deposit: ");
	scanf("%d", &credit);
	while(!feof(fp))
	{
		fscanf(fp, "%d %d %d", &pin_no, &acc_no, &bal);
		if((account == acc_no) && (pin == pin_no))
		{	
			new_bal = bal + credit;
			fprintf(temp, "%d %d %d\n", pin_no, acc_no, new_bal);
		}
		else
		{
			fprintf(temp, "%d %d %d\n", pin_no, acc_no, bal);
		}
	}
	fclose(fp);
	fclose(temp);
	
	FILE *fp1;
	FILE *temp1;	
	fp1 = fopen("Account.txt", "w");
	temp1 = fopen("Temp.txt", "r");
	while(!feof(temp1))
	{
		fscanf(temp1, "%d %d %d", &pin_no, &acc_no, &bal);
		fprintf(fp1, "%d %d %d\n", pin_no, acc_no, bal);
	}
	fclose(fp1);
	fclose(temp);
	
	printf("Would you like to check your balance?(y/n): ");
	fflush(stdin);
	scanf("%c", &check);
	if((check == 'Y') || (check == 'y'))
		check_bal();
}

void change_pin()
{
	system("cls");
	int old_pin, new_pin, p, a, b, acc;
	char n[100], u[100]; 
	FILE *og;
	FILE *temp;
	og = fopen("Users.txt", "r");
	temp = fopen("Temp_user.txt", "w");
	printf("Enter your old pin: ");
	scanf("%d", &old_pin);
	printf("Enter your new pin: ");
	scanf("%d", &new_pin);
	printf("Enter your account number: ");
	scanf("%d", &acc)
	while(!feof(og))
	{
		fscanf(og, "%s %s %d %d", &n, &u, &p, &a);
		if((p == old_pin) && (a == acc))
			fprintf(temp, "%s %s %d %d\n", n, u, new_pin, a);
		else
			fprintf(temp, "%s %s %d %d\n", n, u, p, a);
	}
	fclose(og);
	fclose(temp);
	
	og = fopen("Temp_user.txt", "r");
	temp = fopen("Users.txt", "w");
	while(!feof(og))
	{
		fscanf(og, "%s %s %d %d", &n, &u, &p, &a);
		fprintf(temp, "%s %s %d %d\n", n, u, p, a);
	}
	fclose(og);
	fclose(temp);
	
	og = fopen("Account.txt", "r");
	temp = fopen("Temp.txt", "w");
	while(!feof(og))
	{
		fscanf(og, "%d %d %d", &p, &a, &b);
		if((p == old_pin) && (a == acc))
			fprintf(temp, "%d %d %d\n", new_pin, a, b);
		else
			fprintf(temp, "%d %d %d\n", p, a, b);
	}
	fclose(og);
	fclose(temp);
	
	og = fopen("Temp.txt", "r");
	temp = fopen("Account.txt", "w");
	while(!feof(og))
	{
		fscanf(og, "%d %d %d", &p, &a, &b);
		fprintf(temp, "%d %d %d\n", p, a, b);
	}
	fclose(og);
	fclose(temp);
	printf("Your pin has been successfully changed!\n");
}

int login_function()
{
	int check;
	system("cls");
	FILE *fPointer;
	int found = 0;
	char name[100], user[100], pw[100], username[100], password[100];
	int acc_no;
	fPointer = fopen("Users.txt", "r");
	printf("Enter your username: ");
	scanf("%s", &username);
	printf("Enter your pin: ");
	scanf("%s", password);
	while((!feof(fPointer)) && (found == 0))
	{
		fscanf(fPointer, "%s", name);
		fscanf(fPointer, "%s", user);
		fscanf(fPointer, "%s", pw);
		fscanf(fPointer, "%d", &acc_no);
		if(!strcmp(username,user) && !strcmp(password, pw))
			found = 1;
	}
	fclose(fPointer);
	
	if(found == 1)
	{
		system("cls");
		printf("Successfully logged in!\n");
		printf("1.Withdraw\n2.Deposit\n3.Check Balance\n4.Change pin\n");
		printf("Enter choice[1-4]: ");
		scanf("%d", &check);
		switch(check)
		{
		case 1:
			withdraw();
			break;
			
		case 2:
			credit();
			break;

		case 3:
			check_bal();
			break;
		
		case 4:
			change_pin();
			break;

		default:
			printf("Invalid option!\n");
			break;
		}
	}
	return found;
}

int signup_function()
{
	system("cls");
	FILE *fPointer;
	FILE *fp;
	fp = fopen("Account.txt", "a");
	fPointer = fopen("Users.txt", "a");
	char name[100], user[100];
	int pw, bal, acc_no;
	printf("Enter your name: ");
	scanf("%s", &name);
	printf("Hello %s!\n", name);
	printf("Enter your new username: ");
	scanf("%s", &user);
	printf("Enter your new pin: ");
	scanf("%d", &pw);
	srand(time(0));
	acc_no = (1000 * (rand()%9 + 1)) + (100 * (rand()%10)) + (10 * (rand()%10)) + (rand()%10);
	printf("Your new account number is: %d\n", acc_no);
	fprintf(fPointer, name);
	fprintf(fPointer, "\t");
	fprintf(fPointer, user);
	fprintf(fPointer, "\t");
	fprintf(fPointer, "%d\t%d", pw, acc_no);
	fprintf(fPointer, "\n");
	printf("Enter your new balance: ");
	scanf("%d", &bal);
	fprintf(fp, "%d %d", pw, acc_no);
	fprintf(fp, " ");
	fprintf(fp, "%d\n", bal);
	fclose(fPointer);
	fclose(fp);
	return 1;
}

int main()
{
	int choice, res;
	char again;
	do
	{
		system("cls");
		printf("1.Login\n2.Sign Up\n");
		printf("Enter choice[1-2]: ");
		scanf("%d", &choice);
		switch(choice)
		{	
			case 1:
				res = login_function();
				if(res == 0)
					printf("Account doesn't exist\n");
				break;
			
			case 2:
				if(signup_function())
					printf("New account created!\n");
				break;
					
			default:
				printf("Invalid answer!\n");
		}
		printf("Would you like to enter again?(y/n): ");
		scanf("%s", &again);
	}while((again == 'y') || (again == 'Y'));
	return 0;
}
