#include <unistd.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <sys/time.h> 

#define NTHR    8                      // number of threads 
#define NUMNUM  8000000L                // number of numbers to sort 
#define TNUM    (NUMNUM/NTHR)           // number to sort per thread 



long nums[NUMNUM]; 
long snums[NUMNUM]; 


int complong(const void * arg1, const void *arg2)
{
    long l1 = *(long *)arg1; 
    long l2 = *(long *)arg2; 

    if(l1 < l2) return -1; 
    else if(l1 > l2) return 1; 
    else return 0;  
}

void *thr_fn(void *arg)
{
    long idx = (long)arg; 

    heapsort(&nums[idx], TNUM, sizeof(long), complong); 
    // pthread_barrier_wait(&b); 

    return((void *)0);
}

void 
merge(void)
{
    long idx[NTHR]; 
    long i, minidx, sidx, num; 

    for(i = 0; i < NTHR; ++i)
    {
        idx[i] = i * TNUM; 
    }

    for(sidx = 0; sidx < NUMNUM; sidx++)
    {
        num = LONG_MAX; 
        for(i = 0; i < NTHR; i++)
        {
            if((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num ))
            {
                num = nums[idx[i]];
                minidx = i; 
            }
        }

        snums[sidx] = nums[idx[minidx]];
        idx[minidx]++; 
    }
}




int main(int argc, char** argv)
{
    unsigned long       i; 
    struct timeval      start, end; 
    long long           startusec, endusec; 
    double              elapsed; 
    int err; 
    pthread_t           tid[NTHR]; 

    srandom(1); 

    for(i = 0; i < NUMNUM; ++i)
    {
        nums[i] = random(); 
    }

    gettimeofday(&start, NULL); 
    // pthread_barrier init 

    for(i = 0; i < NTHR; ++i)
    {
        pthread_create(&tid[i], NULL, thr_fn, (void*)(i * TNUM)); 
    }

    // pthread_barrier wait 

    for(i = 0; i < NTHR; ++i)
    {
        pthread_join(tid[i], NULL);
    }




    merge(); 
    gettimeofday(&end, NULL); 

    // print the sort list 
    startusec = start.tv_sec* 1000000 + start.tv_usec; 
    endusec = end.tv_sec* 1000000 + end.tv_usec; 

    elapsed = (double)(endusec - startusec) / 1000000.0; 
    printf("sort took %.5f seconds\n", elapsed); 




    return 0; 
}
