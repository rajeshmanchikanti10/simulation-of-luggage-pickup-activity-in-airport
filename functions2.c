#include<stdio.h>
#include<stdlib.h>
#include "project.h"
#include <time.h> 
int  MAX_LUGGAGES_ON_BELT;
int MAX_passengers_queue; 
int luggagecount=0;
int luggageidentifyingdata=0;
int max_luggage;
int max;
#define min 1
int arr[100]={0},ind=0;
void sendnoofpassengers(int number_of_passengers)
{ 
 MAX_LUGGAGES_ON_BELT=number_of_passengers/2;
 MAX_passengers_queue=number_of_passengers;
  max_luggage=number_of_passengers;
  max=number_of_passengers+1;
}

//function to add delay to the program during  execution.
void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
}






int search(int number)
{
  for (int i = 0; i <max_luggage; i++)      //search for a newly generated luggage number in the array ,Containing the luggage number's which has been generated before.
 {  
    if (arr[i] == number)  
       return 1;
 }
  return 0;
}
void addtoexistingluggage(int number)
{
  for(int i=0;i<max_luggage;i++)
  {
  if(arr[i]==0)
    {
     arr[i]=number;
     break;
    }
  }
}



queue * create_circular_queue(void)
{
 queue *luggages=malloc(sizeof(queue));
 luggages->front=luggages->tail=NULL;
 luggages->no_of_luggages=0;
 return luggages;
}


//function which creates a luggage with random luggage number
LUGGAGE * newluggages(void)
{
 static int count=0;
 if(count<10)
 {
 LUGGAGE *luggage=malloc(sizeof(LUGGAGE)); 
 luggage->next=luggage;
 int number=(rand() %  (max- min)) +min;  // to generate random number
 while(search(number))
 {
    number=(rand()%(max-min))+min;          //generate's  random numbers until a unique random number is generated
 }
 luggage->data=number;                   //luggage with unique luggage number
 addtoexistingluggage(number);            //add's the new unique luggage to the existing luggage list.
 count++;
 return luggage;

}
 else 
 return 0;
}

//function to create new passenger

LUGGAGE *passenger(void)
{
 LUGGAGE *person=malloc(sizeof(LUGGAGE));
 person->next=NULL;
 person->data=++luggageidentifyingdata;
 return person;
}


//another implementation for create new passenger

LUGGAGE *passenger1(void)
{
 LUGGAGE *person=malloc(sizeof(LUGGAGE));
 person->next=NULL;
 return person;
}




//creates passengers queue

passengers_queue * create_passengers_queue(void)
{
 passengers_queue * persons=malloc(sizeof(passengers_queue));
 persons->front=persons->tail=NULL;
 persons->passengerscount=0;
}

//function to pickup luggage from the luggage belt.
void pickup_luggage(queue **luggages,passengers_queue**passengers)
{
	if(isEmpty((*luggages)))
	{
		printf("\t\t\tNO Luggages bags are found!\n\n\n");
		delay(2);
		return;
	}
	if(isEMPTYpassengersqueue(*passengers))	
	{
		printf("\t\t\tNO passenger's in the queue!\n\n\n");
		delay(2);
	}
	else
	{
		int data=removepassenger(passengers);   //first dequeue the passengers.
		int lastluggagecount=(*luggages)->no_of_luggages;
		if(data==(*luggages)->front->data)     //if luggage number associated with passenger  is equal to front luggage in the luggage belt then enters the loop.
		{ 
			if((*luggages)->tail==(*luggages)->front)
			{

				free((*luggages)->front);
				(*luggages)->front=NULL;
				(*luggages)->tail=NULL;
				(*luggages)->no_of_luggages--;
			}
			else
			{
				LUGGAGE *temp=((*luggages)->front);
				(*luggages)->front=(*luggages)->front->next;
				(*luggages)->tail->next=(*luggages)->front;
				//free(temp);
				(*luggages)->no_of_luggages--;
			}
		}
		else
		{                                 //if passengers find's his luggage some where in the middle of luggage belt.

			LUGGAGE *current=((*luggages)->front->next),*prev=(*luggages)->front;

			while(current!=(*luggages)->tail)
			{
				if(data==current->data)
				{
					prev->next=current->next;
					free(current);
					(*luggages)->no_of_luggages--;
					break;
				}
				current=current->next;
				prev=prev->next;
			}
			if(current==(*luggages)->tail&&current->data==data)
			{
				prev->next=current->next;
				(*luggages)->tail=prev;
				free(current);
				(*luggages)->no_of_luggages--;
			}
		}
		if(lastluggagecount==(*luggages)->no_of_luggages)   //if passenger doesn't find his luggage then is added back of passengers queue.
		{
			printf("\t\t\tYour luggage is not found can you please wait for some time!\n\n\n");
			addpassengerbysecondmethod(passengers,data);        //function invoking to add passenger at the last of queue.
			delay(2);
		}
		else
		{	
 			printf("\t\t\tThank you for waiting we hope your luggages is in good terms!\n\n\n");
			delay(2);
		}
		}
		}

//function to add luggage to luggage belt.
void addluggage_to_the_belt(queue **luggages)
{
    if(isFULL((*luggages)))
    {
        printf("\t\t\tLuggage Belt is full\n\n\n");
        delay(2);
         return;
     }

     else
     {
         LUGGAGE *new_luggage=newluggages();
         if(new_luggage==NULL)
         {
             printf("NO Luggages are Left!\n");
             delay(2);
             return;
         }
        if((*luggages)->tail==NULL)
       {
        (*luggages)->tail=(*luggages)->front=new_luggage;
         (*luggages)->no_of_luggages++;
       }
     else
     {
        (*luggages)->tail->next=new_luggage;
        new_luggage->next=(*luggages)->front;
        (*luggages)->tail=new_luggage;
        (*luggages)->no_of_luggages++;
     }
   }
}



//function to add passenger to the passenger queue
void addpassenger(passengers_queue **passengers)
{
   
	LUGGAGE *newpassenger=passenger();
	if(newpassenger->data<MAX_passengers_queue)
		{
			if((*passengers)->passengerscount<10)
			{
				if((*passengers)->passengerscount==0)    
				{ 
					(*passengers)->front=NULL;
					(*passengers)->tail=NULL;
				}

			if((*passengers)->tail==NULL)
			{
				(*passengers)->tail=newpassenger;
				(*passengers)->front=newpassenger;
				(*passengers)->passengerscount++;
			}
			else
			{
				(*passengers)->tail->next=newpassenger;
				(*passengers)->tail=newpassenger;
				(*passengers)->passengerscount++;
			}
			}
			
			}
	else
	{
		printf("\t\t\tNO passengers are left !\n\n\n");
 		delay(2);
	}
}


//another implementation of add passenger to the passenger queue.(multi thread)
void addpassengerbysecondmethod(passengers_queue **passengers,int data)
{
	if((*passengers)->passengerscount<10)
		{
			LUGGAGE *newpassenger=passenger1();
			newpassenger->data=data;
			if((*passengers)->tail==NULL) 
				{
					(*passengers)->tail=newpassenger;
					(*passengers)->front=newpassenger;
					(*passengers)->passengerscount++;
				}
				else
				{
					(*passengers)->tail->next=newpassenger;
					(*passengers)->tail=newpassenger;
					(*passengers)->passengerscount++;
				}
		}
	else
		{
			printf("\t\t\tpassengers queue is full kindly wait for some time!\n\n\n");
			delay(2);
		}
}




//function to remove passenger from the passengers queue
int removepassenger(passengers_queue **passengers)
{
	int temp1;
	if((*passengers)->front==(*passengers)->tail)
		{
			temp1=(*passengers)->front->data;
			free((*passengers)->front);
			(*passengers)->front=NULL;
			(*passengers)->tail=NULL;                           // enters if we want to remove passenger when only one passenger in the passenger queue
			(*passengers)->passengerscount=0;
			return temp1;
		}
	else
		{

			LUGGAGE *temp=(*passengers)->front;
			temp1=temp->data;
			(*passengers)->front=(*passengers)->front->next;    //enters when we have more than one passenger in the passenger queue
			free(temp);
			(*passengers)->passengerscount--;

			return temp1;
		}
}




//function to check whether the luggage belt is empty or not
int isEmpty(queue *luggages)
{
	return luggages->no_of_luggages==0;
}



//function to check whether the luggage belt is full or not
int isFULL(queue *luggages)
{
	return (MAX_LUGGAGES_ON_BELT==luggages->no_of_luggages);
}



//functions to check whether the queue is full or not
int isFULLpassengersqueue(passengers_queue *passengers)
{
	return (MAX_passengers_queue==passengers->passengerscount);
}



//function to check whether the queue is empty or not
int isEMPTYpassengersqueue(passengers_queue *passengers)
{
	return (passengers->passengerscount==0);
}





