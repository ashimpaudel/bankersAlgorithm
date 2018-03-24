#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUMBER_OF_CUSTOMERS  5
#define NUMBER_OF_RESOURCES  3

typedef struct{
	int id;
	int *Arr;
}Args;
void timestamp();
bool isLessThan(int *X, int *Y, int size);
int release_resources(int customer_num, int *release);
int request_resources(int customer_num, int request[]);
bool safetyCheck();
void* runnerFunc(void* args);
pthread_mutex_t mutex;

int available[NUMBER_OF_RESOURCES];                         //available amt of each resource, m
int maximum[NUMBER_OF_CUSTOMERS] [NUMBER_OF_RESOURCES];     //max demand of each customer, nxm
int allocation[NUMBER_OF_CUSTOMERS] [NUMBER_OF_RESOURCES];  //amt currently allocated to each customer, nxm
int need[NUMBER_OF_CUSTOMERS] [NUMBER_OF_RESOURCES];        //remaining need of each customer, nxm

void main(int argc, char**argv){
	int i, j;
	srand(time(NULL));
	//Generating the random values for available
	for(i=0; i<NUMBER_OF_RESOURCES; i++)
		available[i] = atoi(argv[i+1]);	
	//initializing the maximum array, need and allocation array
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++){
		for(j=0; j<NUMBER_OF_RESOURCES; j++){
			int lessRand = rand()%(available[j]+1);
			maximum[i][j] = lessRand;
			allocation[i][j] = 0;
			need[i][j] = maximum[i][j];
		}
	}	
	//Generating request Matrix
	int request[NUMBER_OF_CUSTOMERS] [NUMBER_OF_RESOURCES];
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++){
		for(j=0; j<NUMBER_OF_RESOURCES; j++){
			int lessRand = rand()%(1+need[i][j]);
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
	for(i=0; i<NUMBER_OF_CUSTOMERS; i++){
		pthread_join(customer[i],NULL);
	}

	exit(0);
}
void* runnerFunc(void* args){
	int id = ((Args*)args)->id;
	int *rArr = ((Args*)args)->Arr;
	//customer will continually loop requesting and releasing random number of resources
	while (1) {
		request_resources(id, &rArr[0]);
		}
	
}

int request_resources(int customer_num, int *req){
	int i;
	pthread_mutex_lock(&mutex);
	timestamp();
	printf("customer id: %d ",customer_num);
	printf("Requests");
	for (i=0; i<NUMBER_OF_RESOURCES; i++){
		printf(" %d,",*req);
		req++;
	}
	printf("\n");
//raise an error condition if request is greater than Need
	if(! isLessThan(&req[0], &need[customer_num][0], NUMBER_OF_RESOURCES)){
	//	printf ("cannot perform the request as request is greater than the need\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand()%100);
		//exit (0);
	}
	else if (isLessThan(&req[0], &available[0], NUMBER_OF_RESOURCES)){
		//printf("now locking available %d\n", *req);

		//printf("pinter %d", *req);
		//available = available-request
		for(i=0; i<NUMBER_OF_RESOURCES; i++){
		    available[i] -= *req;
		   allocation[customer_num][i] += *req;
		    need[customer_num][i] -= *req;
			req++;
		}

		if(safetyCheck){
			int countNeed;
			for(i=0; i<NUMBER_OF_RESOURCES; i++)
				countNeed += need[customer_num][i];

			//request approved and need 0
			if (countNeed == 0){
				printf("request approved, customer id %d\n",customer_num);
				release_resources(customer_num,&req[0]);
				}
			//request approved and need > 0
			else{
				int j;
				//request_resources(
				for(j=0; j<NUMBER_OF_RESOURCES; j++){
					int lessRand = rand()%(need[customer_num][j]+1);
					*req= lessRand;
					req++;
		
				}
				sleep(rand()%10);
				pthread_mutex_unlock(&mutex);

			}
		}
//		safety check failed
		else{
			timestamp();
			printf("request denied\n");
			for(i=0; i<NUMBER_OF_RESOURCES; i++){
			    available[i] += *req;
			   allocation[customer_num][i] -= *req;
			    need[customer_num][i] += *req;
				req++;}
				//if the request is denied 
			pthread_mutex_unlock(&mutex);
			sleep(rand()%10);
			request_resources(customer_num, &req[0]);
		}	
	}
				
	
	else{

		//else if the reqeuest is greater than available, it must wait
		//printf("it must wait\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand()%10);
		request_resources(customer_num, &req[0]);
	}
	sleep(rand()%10);

}

bool safetyCheck( ){
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
			if (finish[i] == false && isLessThan(&need[i][0], &work[0],NUMBER_OF_RESOURCES) ){
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
bool isLessThan(int *X, int *Y, int size){
	int i;
	for(i=0; i<size; i++){
		if(*X > *Y)
			return false;
		X++;
		Y++;
	}
	return true;	
}

//resource-request Algorithm

int release_resources(int customer_num, int *request){
	sleep(rand()%100);
	int j;
		for(j=0; j<NUMBER_OF_RESOURCES; j++){
			int lessRand = rand()%(available[j]+1);
			maximum[customer_num][j] = lessRand;
			allocation[customer_num][j] = 0;	
			need[customer_num][j] = maximum[customer_num][j];
	}
		for(j=0; j<NUMBER_OF_RESOURCES; j++){
			int lessRand = rand()%need[customer_num][j];
			*request = lessRand;
			request++;
		}
	timestamp();
	printf("resource released");
	pthread_mutex_unlock(&mutex);
return 1;
}
void timestamp()
{
	    time_t ltime; /* calendar time */
	        ltime=time(NULL); /* get current cal time */
		    printf("%s",asctime( localtime(&ltime) ) );
}
