#include <iostream>
#include <assert.h> 
#include <atomic> 




namespace utils_thread_safe
{

typedef std::atomic_uint32_t Rank; 

template <typename T> 
struct RingBuffer 
{

    Rank front; 
    Rank rear; 
    size_t capacity_; 
    T* buffer;     

    RingBuffer(size_t capacity= 32):front(0), rear(0),capacity_(capacity)
    {
        static_assert(std::is_default_constructible<T>::value); 
        buffer = new T[capacity_]; 
        if(buffer == nullptr)
        {
            std::cerr << "No enough space" << std::endl; 
        }
    }
    
    ~RingBuffer()
    {
        if(buffer != nullptr)
        {
            // range erase 
            for(size_t r = (size_t)front; r != rear; r = (r + 1) % capacity_)
            {
                buffer[r].~T(); 
            }

            delete [] buffer; 
            buffer = nullptr; 
        }
    }


    bool isEmpty() noexcept  
    {
        return rear == front; 
    }

    bool isFull() noexcept 
    {
        return front == (rear + 1 ) % capacity_;
    }

    T pop_front() 
    {
        assert(!isEmpty()); 
        size_t pos = front; 
        front = (front + 1) % capacity_; 

        return buffer[pos];
    }


    void push_back(const T& value) 
    {
        assert(!isFull()); 
        buffer[rear] = value; 

        rear = (rear +1 ) % capacity_; 
    }

    void push_back(T&& value)
    {
        assert(!isFull()); 
        buffer[rear] = value; 

        rear = (rear + 1) % capacity_; 
    }



}; 







}