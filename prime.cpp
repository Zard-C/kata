#include <iostream> 
#include <vector> 

namespace tt0
{

// is prime 判断质数
bool isPrime(int n)
{
    if(n < 3) return false;  
    for(int i = 2; i*i <=n ; ++i)
    {
        if(n % i == 0) return false; 
    }
    return true; 
}

// 因数分解 
using std::vector; 




} // end of namespace 


void test1()
{
    using namespace tt0; 
    for(int i = 0; i < 100; ++i)
    {
        if( isPrime(i)) std::cout << i << " "; 
    }
    std::cout << '\n'; 
}



int main()
{
    test1(); 
    return 0; 
}