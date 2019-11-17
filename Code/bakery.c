#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <string.h>
  
#define MEMBAR __sync_synchronize() 
#define Th_count 8 
// VOLATILE used to prevent the compiler   
volatile int token[Th_count]; 
volatile int choosing[Th_count]; 
volatile int resource; 
void Resource_Use(int thrd){  // Critical Section  
    if (resource != 0) { 
        printf("Resource is used by %d, and  still in use by %d!\n",thrd, resource); 
    } 
  
    resource = thrd; 
    printf("%d Resource is Using:\n", thrd); 
  
    MEMBAR; 
    sleep(2); 
    resource = 0; 
    return;
} 
void Unlock(int thrd)   // exit fun  
{ 
    MEMBAR; 
    token[thrd] = 0;
    return; 
}   
void Fun_Lock(int thrd) 
{ 
    choosing[thrd] = 1; 
    MEMBAR;   
    int tictMax = 0; 
    for (int i = 0; i < Th_count; ++i) { 
        int ticket = token[i]; 
        tictMax = ticket > tictMax ? ticket : tictMax; 
    } 
    token[thrd] = tictMax + 1; 
    MEMBAR; 
    choosing[thrd] = 0; 
    MEMBAR; 
    for (int i = 0; i < Th_count; i++) { 
        // bakery algorithm conditions 
        while (choosing[i]) { 
        } 
        MEMBAR; 
        while (token[i] != 0 && (token[i] < token[thrd] || (token[i] == token[thrd] && i < thrd))) { 
        } 
    } 
} 
void* Thrd_Body(void* arg){ 
    long thrd = (long)arg; 
    Fun_Lock(thrd); 
    Resource_Use(thrd); 
    Unlock(thrd); 
    return NULL; 
} 
  
int main(int argc, char** argv) 
{ 
  
    memset((void*)token, 0, sizeof(token)); 
    memset((void*)choosing, 0, sizeof(choosing)); 
    resource = 0; 
    pthread_t thrds[Th_count]; 
  
    for (int i = 0; i < Th_count;i++){ 
        pthread_create(&thrds[i], NULL, &Thrd_Body, (void*)((long)i)); 
    } 
  
    for (int i = 0; i < Th_count;i++) { 
        pthread_join(thrds[i], NULL); 
    } 
    return 0; 
} 