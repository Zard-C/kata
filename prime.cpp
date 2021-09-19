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

// 因数分解: 试除法
using std::vector; 
vector<int> factorization(int n)
{
    vector<int> res; 

    for(int i = 2; i*i <= n; ++i)
    {
        while(n % i == 0)
        {
            res.push_back(i); 
            n /= i; 
        }
    }

    if( n != 1) res.push_back(n);
    return std::move(res); 
}




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

void test2(int n)
{
    using namespace std; 
    using namespace tt0; 
    
    vector<int> res = factorization(n); 

    cout << n << " contains: "; 
    for(const int & i : res)
    {
        cout << i <<" "; 
    }
    cout << endl; 
}


int main()
{
    test1(); 
    test2(65535);
    return 0; 
}