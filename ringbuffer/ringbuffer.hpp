#ifndef _RINGBUFFER_HPP_
#define _RINGBUFFER_HPP_ 

#include <iostream> 
#include <cassert>  

namespace utils
{

typedef size_t Rank;
constexpr int N = 32; 
template <typename T> 
struct RingBuffer 
{
    Rank front; 
    Rank rear; 
    size_t capacity_; 
    T* buffer; 

    RingBuffer(size_t buffer_size = N): front(0), rear(0), capacity_(buffer_size)
    {
        static_assert(std::is_default_constructible<T>::value); 
        buffer = new T[capacity_]; 
        if(buffer == nullptr)
        {
            std::cerr<<"RingBuffer(): no enough space"; 
        }
    }

    ~RingBuffer()
    {
        if(buffer != nullptr)
        {
            for(Rank r = front; r != rear; r = (r  + 1) % capacity_)
            {
                buffer[r].~T();                 
            }
            delete [] buffer; 
        }

    }


    bool isEmpty() noexcept  
    {
        return front == rear; 
    }

    bool isFull() noexcept
    {
        return front == (rear + 1) % capacity_; 
    }

    void push_back(const T& value)
    {
        if(isFull()) return; 

        buffer[rear] = value; 
        rear= (rear + 1) % capacity_; 

    }

    void push_back(T&& value)
    {
        if(isFull()) return; 
        buffer[rear] = value; 
        rear = (rear + 1) % capacity_; 
    }

    T pop_front(void)
    {
        assert(isEmpty()); 
        Rank pos = front; 
        front  = (front + 1) % capacity_; 
        return buffer[pos]; 
    }

}; 








}






#endif // !_RINGBUFFER_HPP_