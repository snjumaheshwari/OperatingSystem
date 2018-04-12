#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t teacher,student,waitingroom; //waiting room is mutex for updating the seats
int seats=3;  //no. of free seats in waiting room
void *teacherteaching()
{
	do
	{
		sem_wait(&student); //decrease student
		sem_wait(&waitingroom); 
		
		seats+=1;	//increase the no. of seating in waiting room
		printf("teacher is teaching the student\n");
		sleep(1);	//let teacher take 1 sec to resolve query
		
		sem_post(&waitingroom);
		printf("teacher is going back to sleep as no students came\n");
		sem_wait(&teacher);  //after resolving query teacher sleeps
	}while(1);
}

void *studentcoming()
{
	sem_wait(&waitingroom);
	if(seats>0)
	{
		printf("student has come\n");
		seats=seats-1;
		sem_post(&student);
		sem_post(&waitingroom);
		printf("student in waiting room\n");
		sem_post(&teacher);
	}
	else //for no seats available
	{
		sem_post(&waitingroom);
		printf("student came but no free seats in waiting room\n");
	}
}

int main()
{
	pthread_t tea,stu[100];	
	sem_init(&teacher,0,1);
	sem_init(&waitingroom,0,1);
	sem_init(&student,0,0);

	printf("Teacher sleeping\n");
	sem_wait(&teacher);//to make sem 0, to make teacher sleep initially
	
	pthread_create(&tea,NULL,teacherteaching,NULL);
	for(int i=0;i<100;i++)
		pthread_create(&stu[i],NULL,studentcoming,NULL);
//	sleep(1);
	
	
	for(int i=0;i<100;i++)
		pthread_join(stu[i],NULL);
	pthread_join(tea,NULL);
}
