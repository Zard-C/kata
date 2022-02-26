#include <iostream> 
#include <vector> 
#include "ringbuffer.hpp"
#include <chrono>  
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>


class Test
{
public:
   Test(int id = 0, int value = 0)
   {
	this->id = id;
        this->value = value;
	sprintf(data, "id = %d, value = %d\n", this->id, this->value);
   }
   void display()
   {
 	printf("%s", data);
   }


    Test(Test&& t)
    {
        id = t.id; 
        value = t.value; 
        memcpy(data, t.data, sizeof(data));
    }

    Test(const Test& t)
    {
        id = t.id; 
        value = t.value; 
        memcpy(data, t.data, sizeof(data));
    }

    Test& operator=(const Test& t)
    {
        this->id = t.id; 
        this->value = t.value; 
        memcpy(this->data, t.data, sizeof(data));
        return *this; 
    }


   int id;
   int value;
   char data[128];



};

double getdetlatimeofday(struct timeval *begin, struct timeval *end)
{
    return (end->tv_sec + end->tv_usec * 1.0 / 1000000) -
           (begin->tv_sec + begin->tv_usec * 1.0 / 1000000);
}

utils::RingBuffer<Test> queue(1 << 12);

#define N (10 * (1 << 20))

void produce()
{
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    while(i < N)
    {
        if(!queue.isFull())
        {
            queue.push_back(Test(i % 1024, i)); 
            ++i;
        }
        //std::cout << i << std::endl;
    }
    
    gettimeofday(&end, NULL);
    double tm = getdetlatimeofday(&begin, &end);
    printf("[%lu] producer: %f MB/s %f msg/s elapsed= %f, size= %u\n", pthread_self(), N * sizeof(Test) * 1.0 / (tm * 1024 * 1024), N * 1.0 / tm, tm, i);
}

void consume()
{
    //sleep(1);
    Test test;
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    size_t count = 0; 
    while(i < N)
    {
        if(!queue.isEmpty())
        {
            test = queue.pop_front(); 
            if(test.value == i)
            {
                ++count;
            }
            ++i; 
        }
    }
    printf("seq: %s\n", count == i ? "success" : " failed"); 
    gettimeofday(&end, NULL);
    double tm = getdetlatimeofday(&begin, &end);
    printf("[%lu] consumer: %f MB/s %f msg/s elapsed= %f, size= %u \n", pthread_self(), N * sizeof(Test) * 1.0 / (tm * 1024 * 1024), N * 1.0 / tm, tm, i);
}



int main(int argc, char const *argv[])
{
    std::thread producer1(produce);
    std::thread consumer(consume);
    producer1.join();
    consumer.join(); 

    return 0;
}
