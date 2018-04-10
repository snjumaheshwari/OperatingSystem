#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
int table_used=1,generated=0,item_gen[2];
char item[3]={'t','p','m'};
sem_t t;
void *agent(void *ar){
int i=0,j=0,k=0;
sem_wait(&t);
if(table_used==1){
i=k;
j=i+1;
if(j==3)
	j=0;
k=j;
item_gen[0]=i;
item_gen[1]=j;
printf("agent produces %s and %s",item[i],item[j]);
generated=1;
table_used=0;
}
sem_post(&t);
pthread_exit(NULL);
}

void *smoker(void *i){
sem_wait(&t);
int *val=(int *)i;
if(table_used==0){
if(generated && item_gen[0]!=*val && item_gen[1]!=*val){
printf("Smoker %d has completed his smoking \n",*val);
table_used=1;
generated=0;
}
}
sem_post(&t);
pthread_exit(NULL);
}

int main(){
pthread_t s1,s2,s0,agent;
sem_init(&t,0,1);
int m=0,j=1,k=2;
printf("Smoker 0 has tobacco\n");
printf("Smoker 1 has paper\n");
printf("Smoker 2 has matches\n");
pthread_create(&agent,NULL,agent,NULL);
pthread_create(&s0,NULL,smoker,(void*)m);
pthread_create(&s1,NULL,smoker,(void*)j);
pthread_create(&s2,NULL,smoker,(void*)k);
pthread_join(agent,NULL);
pthread_join(s0,NULL);
pthread_join(s1,NULL);
pthread_join(s2,NULL);
}
