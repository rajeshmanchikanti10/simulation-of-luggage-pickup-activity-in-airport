typedef struct node
{
int data;
struct node *next;
}LUGGAGE;


typedef struct cir
{
LUGGAGE *front;
LUGGAGE *tail;
int no_of_luggages;
}queue;

typedef struct per
{
LUGGAGE *front;
LUGGAGE *tail;
int passengerscount;
}passengers_queue;

queue *create_circular_queue(void);
passengers_queue *create_passengers_queue(void);
void addluggage_to_the_belt(queue **);
void pickup_luggage(queue**,passengers_queue**);
int isEmpty(queue *);
int isFULL(queue *);
LUGGAGE * newluggages(void);
LUGGAGE *passenger(void);
void addpassenger(passengers_queue**);
int removepassenger(passengers_queue **);
void addpassengerbysecondmethod(passengers_queue**,int);
int isEMPTYpassengersqueue(passengers_queue *passengers);
int isFULLpassengersqueue(passengers_queue *passengers);
LUGGAGE *passenger1(void);
void delay(int number_of_seconds);
void addtoexistingluggage(int number);
void sendnoofpassengers(int number_of_passengers);