#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUMBER_OF_CUSTOMERS  5
#define NUMBER_OF_RESOURCES  3

int request_resources(int customer_num, int request[]);

int available[NUMBER_OF_RESOURCES];                         //available amt of each resource, m
int maximum[NUMBER_OF_CUSTOMERS] [NUMBER_OF_RESOURCES];     //max demand of each customer, nxm
int allocation[NUMBER_OF_CUSTOMERS] [NUMBER_OF_RESOURCES];  //amt currently allocated to each customer, nxm
int need[NUMBER_OF_CUSTOMERS] [NUMBER_OF_RESOURCES];        //remaining need of each customer, nxm

void main(){
	int i, j;
	srand(time(NULL));
	//Generating the random values for available
	for(i=0; i<NUMBER_OF_RESOURCES; i++)
		available[i] = rand()%10;	
	//initializing the maximum array, need and allocation array
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++){
		for(j=0; j<NUMBER_OF_RESOURCES; j++){
			int lessRand = rand()%10;
			while(lessRand > available[j])
				lessRand = rand()%10;
			maximum[i][j] = lessRand;
			allocation[i][j] = 0;
			need[i][j] = maximum[i][j];
		}
	}
	//Generating request Matrix
	int request[NUMBER_OF_CUSTOMERS] [NUMBER_OF_RESOURCES];
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++){
		for(j=0; j<NUMBER_OF_RESOURCES; j++){
			int lessRand = rand()%10;
			while(lessRand > need[i][j])
				lessRand = rand()%10;
			request[i][j] = lessRand;
		
		}
	}

}
int i;
//safety algorithm
int work[NUMBER_OF_RESOURCES];
int finish[NUMBER_OF_CUSTOMERS];
memcpy(work, available, sizeof(available));
for(i=0; i<NUMBER_OF_CUSTOMERS; i++)
	finish[i] = false
int counter;
for(counter=0; counter<NUMBER_OF_CUSTOMERS; counter++){
	//finding an index i such that both Finish[i]== false and Need[i] <= Work
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++){
		if (finish[i] == false && isLessThan(need[i][0], Work) ){
			//work = work + allocation
			int j;
			for(j=0; j<NUMBER_OF_RESOURCES; j++){
				work[j] += allocation[i][j];
			}
			finish[i] = true;
		}
	}
//check if finish[i]== true for all is 
counter = 0;
for(i=0; i<NUMBER_OF_CUSTOMERS;i++){
	if(finish[i] = true)
		counter++
	if(counter == NUMBER_OF_CUSTOMERS)
		return true
	return false

//Customers

//creating n customer threads that request and release resources from the bank


pthread_t    *threads;
threads	=    (pthread_t*)malloc(NUMBER_OF_CUSTOMERS*sizeof(pthread_t));  //threads = customers

//requests are releases resources in a loop
while(1){
	request_resources(customer_num, request);
	release_resources(customer_num, release);
}

int request_resources(int customer_num, int request[]){
	return 0
}

int release_resources(int customer_num, int release[]){
	return 0
}

bool isLessThan(int X[], int Y[]){
	int numLess = 0;
	for(i=0; i<sizeof(X); i++){
		if(X[i] > Y[i])
			return false;
		else if(X[i] < Y[i])
			numLess++;
	}
	if (numLess > 0)
		return true;
	return false;	
}

//resource-request Algorithm


