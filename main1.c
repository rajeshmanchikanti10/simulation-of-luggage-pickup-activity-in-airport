#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include<conio.h>
#include "project.h"

int main(int argc,char **argv)
{       int no_of_passengers=atoi(argv[1]);
        //sendnoofpassengers(no_of_passengers);
	queue *luggages=create_circular_queue();
	passengers_queue *passengers=create_passengers_queue();

	system("cls");
	int choice,choice1,val;
	char ch;
    

	do
	{
		printf("\t\t\t-------------------Luggage pickup area--------------------------\n\n\n");
		printf("Enter 1 to pickup luggage\nEnter 2 to add a  passenger to the queue\nEnter 3 to add luggage\nEnter 4 to quit\n");
		val=scanf("%d%c",&choice,&ch);
                if(choice>0&&choice<=4&&val==2)
		{
			switch(choice)
			{
				case 1:
				pickup_luggage(&luggages,&passengers);
				break;
				case 2:
				addpassenger(&passengers);
				break;
				case 3:
				addluggage_to_the_belt(&luggages);
				break;
				default:
				break;
			}
		}
		else
		{
			printf("\t\t\tinvalid choice please enter valid option!\n");
			delay(1.5);
		}
	delay(0.5);
	system("cls");
	fflush(stdin);
	delay(0.5);
	}while(choice!=4);
	printf("\t\t\tThank you!\n\n\n");
	return 0;
}






























