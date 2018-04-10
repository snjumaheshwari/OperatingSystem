#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t r1,r2;
void *pro1(){
pthread_mutex_lock(&r1);
pthread_mutex_lock(&r2);
printf("Process1\n");
sleep(20);
pthread_mutex_unlock(&r2);
pthread_mutex_unlock(&r2);
pthread_exit(NULL);
}
void *pro2(){
pthread_mutex_lock(&r2);
pthread_mutex_lock(&r1);
printf("Process2\n");
pthread_mutex_unlock(&r1);
pthread_mutex_unlock(&r2);
pthread_exit(NULL);
}

int main(){
pthread_t p1,p2;
pthread_create(&p1,NULL,pro1,NULL);
pthread_create(&p2,NULL,pro2,NULL);
pthread_join(p1,NULL);
pthread_join(p2,NULL);
}
