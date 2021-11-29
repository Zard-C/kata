#include <iostream> 
#include <vector> 
#include <cstdlib>
#include <ctime> 

std::ostream& operator << (std::ostream& os, const std::vector<int>& vec)
{
    for(auto &val : vec)
    {
        os << val << " "; 
    }

    return os; 
}


int partition(std::vector<int>& vec, int lo, int hi)
{
    srand(time(nullptr)); 
    std::swap(vec[lo], vec[lo + rand() % (hi - lo)]);
    int pivot = vec[lo]; 

    while(lo < hi)
    {
        while(lo < hi && pivot <= vec[hi]) --hi; 
        vec[lo] = vec[hi]; 
        while(lo < hi && pivot >= vec[lo]) ++lo; 
        vec[hi] = vec[lo];
    }

    vec[lo] = pivot; 

    return lo; 
}

void quicksort(std::vector<int>& vec, int lo, int hi)
{
    if(hi - lo < 2) return; 
    int mi = partition(vec, lo, hi - 1); 
    quicksort(vec, lo, mi); 
    quicksort(vec, mi + 1, hi); 
}


void shuffle(std::vector<int>& vec)
{
    srand(time(nullptr)); 
    for(int len = vec.size(); len > 0; --len)
    {
        std::swap(vec[len - 1], vec[rand() % len]); 
    }
}


void test(void)
{
    std::vector<int> vec(20); 

    for(int i = 0; i < vec.size(); ++i)
    {
        vec[i] = i; 
    }

    std::cout << vec << std::endl; 

    shuffle(vec); 
    std::cout << vec << std::endl; 

    quicksort(vec, 0, vec.size()); 
    std::cout << vec << std::endl; 
    shuffle(vec); 
    std::cout << vec << std::endl; 
}

int main(int argc, char** argv)
{
    test();
    return 0; 
}





