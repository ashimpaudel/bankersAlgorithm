#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_CUSTOMERS  5
#define NUMBER_OF_RESOURCES  3

typedef struct{
	int id;
	int *Arr;
}Args;

bool isLessThan(int X[], int Y[]);
int release_resources(int customer_num, int release[]);
int request_resources(int customer_num, int request[]);
bool safetyCheck(int id);
void* runnerFunc(void* args);
pthread_mutex_t mutex;

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
	pthread_t    *customer;
	customer  =  (pthread_t*)malloc(NUMBER_OF_CUSTOMERS*sizeof(pthread_t));  

	for(i=0; i<NUMBER_OF_CUSTOMERS; i++){
		Args argm; 
		argm.id = i;
		argm.Arr = &request[i][0];
		pthread_create(&customer[i],NULL,runnerFunc,&argm);
	}
}
void* runnerFunc(void* args){
		 
	int id = ((Args*)args)->id;
	int *Arr = ((Args*)args)->Arr;

	//customer will continually loop requesting and releasing random number of resources
	while (1) {
		sleep(rand()%3); 
		request_resources(id, &Arr);
		release_resources(id, &Arr);
		}
	return NULL;
}

bool safetyCheck(int id ){
	int i;
	int work[NUMBER_OF_RESOURCES];
	int finish[NUMBER_OF_CUSTOMERS];
	memcpy(work, available, sizeof(available));
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++)
		finish[i] = false;
	int counter;
	for(counter=0; counter<NUMBER_OF_CUSTOMERS; counter++){
		//finding an index i such that both Finish[i]== false and Need[i] <= Work
		for(i=0; i<NUMBER_OF_CUSTOMERS; i++){
			if (finish[i] == false && isLessThan(need[i][0], work) ){
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
			counter++;
		if(counter == NUMBER_OF_CUSTOMERS)
			return true;
		return false;


}
}
}
int request_resources(int customer_num, int *req){
	pthread_mutex_lock(&mutex);
	int i;
	if (safetyCheck(customer_num)){
		int sumNeed = 0;
		//if the request is satisfied and the need is 0
		for(i=0; i<NUMBER_OF_RESOURCES; i++)
			sumNeed += req[i];
		if (need == 0){
			//sleep for random amount of time and release the resources
			sleep(rand()%100);
		}
		else{
			//available = available-request
			for(i=0; i<NUMBER_OF_RESOURCES; i++)
				available[i] -= req[i];
			//allocation = Allocationi + requesti
			for(i=0; i<NUMBER_OF_RESOURCES; i++)
				allocation[customer_num][i] += req[i];
			//needi = needi - request
			for(i=0; i<NUMBER_OF_RESOURCES; i++)
				need[customer_num][i] -= req[i];
			

		}
	//if it fails safety check the customer will sleep for a random peroid of time
	//no more than 10 milisecond and try again with same denied request
	sleep(rand()%10);
	request_resources(customer_num, req);
	
	}

}

int release_resources(int customer_num, int release[]){
	return 0;
}

bool isLessThan(int X[], int Y[]){
	int i;
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


