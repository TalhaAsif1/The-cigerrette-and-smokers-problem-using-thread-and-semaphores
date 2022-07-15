#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <time.h>


sem_t smoker_waits[3];

sem_t smoker_paper;
sem_t smoker_tobacco;
sem_t smoker_match;
sem_t agent;//agent semaphore

   int fd,fd1,fd2; 
  char * myfifo = "/tmp/myfifo"; 
  char *myfifo2="/tmp/myfifo2";
  char *myfifo3="/tmp/myfifo3";

void delaytime(int number_of_seconds)    // function for time delay
{

    int milli_seconds = 1000 * number_of_seconds;
  
 
    clock_t start_time = clock();
  

    while (clock() < start_time + milli_seconds)
        ;
}


void Agentfunction()//start//
{
    while (true)
	{
		sem_wait(&agent);
		int select_item=rand()%3;
		if(select_item==0)
		{
		printf("\nAgent has placed matches and tobacco on the table\n\n");
		sem_post(&smoker_paper);  
		}
		else if(select_item==1)
		{
		printf("\nAgent has placed paper and tobacco on the table\n\n");
		sem_post(&smoker_match);
		}
		else
		{
		printf("\nAgent has placed paper and matches on the table\n\n");
		sem_post(&smoker_tobacco);	
		}
	
		sem_post(&smoker_waits[select_item]);   //unlocks semaphore
		sem_t smoker_waits[3];
	}

}

void* Smoker_paper(void* arg)//Smoker_paper//
{
	while (true)
	{
		sem_wait(&smoker_paper);
		printf("Smoker one with paper received matches and tobacco. Now making cigarette.\n\n");
         char arr1[80]="Smoke 1 is smoking\n";
        int i;
        for (i = 0; i < 10; i++) { delaytime(1); }
        fd = open(myfifo, O_WRONLY,0666,0); 
        write(fd, arr1, strlen(arr1)+1); 
		sem_post(&agent);
	}

	return NULL;
}

void* Smoker_matches(void* arg)//Smoker_matches//
{
	while (true)
	{
		sem_wait(&smoker_match);
		printf("Smoker two with matches received paper and tobacco. Now making cigarette.\n\n");
        char arr2[80]="Smoke 2 is smoking\n";
        int i;
        for (i = 0; i < 10; i++) {  delaytime(1);  }
        fd1 = open(myfifo2, O_WRONLY,0666,0); 
       write(fd1, arr2, strlen(arr2)+1); 
		sem_post(&agent);
	}

	return NULL;
}

void* Smoker_tobacco(void* arg)//Smoker_tobacco//
{
	while (true)
	{
		sem_wait(&smoker_tobacco);
		printf("Smoker three with tobacco received matches and paper. Now making cigarette.\n\n");
        char arr3[80]="Smoke 3 is smoking\n";	
        int i;
        for (i = 0; i < 10; i++) {   delaytime(1);
    }
        fd2 = open(myfifo3, O_WRONLY,0666,0); 
      write(fd2, arr3, strlen(arr3)+1); 
	sem_post(&agent);
	}

	return NULL;
}



int main(int argc, char* arvg[])
{

	sem_init(&agent, 0, 1);

mkfifo(myfifo,0666); 
mkfifo(myfifo2,0666);
mkfifo(myfifo3,0666);

	pthread_t smoker_threads_paper;
	pthread_t smoker_threads_matches;
	pthread_t smoker_threads_tobacco;
	
 pthread_create(&smoker_threads_paper, NULL, Smoker_paper, NULL) ;
 pthread_create(&smoker_threads_matches, NULL, Smoker_matches, NULL) ;
 pthread_create(&smoker_threads_tobacco, NULL, Smoker_tobacco, NULL) ;

    Agentfunction(); 

	pthread_join(smoker_threads_paper, NULL);
	pthread_join(smoker_threads_matches, NULL);
	pthread_join(smoker_threads_tobacco, NULL);
	printf("hi.\n");
	
}
