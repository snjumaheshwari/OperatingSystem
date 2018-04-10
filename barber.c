#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t br,wr,cr;
//br-barber_ready wr-waiting_room cr-customer_ready
int seats=4;  //no of free seatsi
void *barber(){

sem_wait(&cr);
sem_wait(&wr);
seats+=1;
sem_post(&br);
sem_post(&wr);
printf("barber is ready-get your hair cut\n");
pthread_exit(NULL);
}


void *customer(){
sem_wait(&wr);
if(seats>0){
seats-=1;
sem_post(&cr);
sem_post(&wr);
sem_wait(&br);
printf(" hair cut done\n");
}
else{
sem_post(&wr);
printf("no free seat");
}
pthread_exit(NULL);
}

int main(){
pthread_t b,r;	
sem_init(&br,0,1);
sem_init(&wr,0,1);
sem_init(&cr,0,4);

sem_wait(&br);//to make sem 0
 
pthread_create(&b,NULL,barber,NULL);
pthread_create(&r,NULL,customer,NULL);
pthread_join(b,NULL);
pthread_join(r,NULL);
}
