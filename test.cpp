#include <iostream>
#include <vector> 


std::ostream& operator<< (std::ostream& os, const std::vector<int>& vec)
{
    for(auto & val : vec)
    {
        os << val <<" "; 
    }
    return os; 
}


int partition(std::vector<int>& vec, int lo, int hi)
{
    srand(time(nullptr)); 
    std::swap(vec[lo], vec[lo + rand() % (hi - lo + 1)]); 
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
    if(hi - lo < 2) return ; 
    int mi = partition(vec, lo, hi - 1); 
    quicksort(vec, lo, mi); 
    quicksort(vec, mi + 1, hi); 
}

void shuffle(std::vector<int>& vec)
{
    srand(time(nullptr)); 
    int size = vec.size(); 
    for(; size > 0; --size)
    {
        std::swap(vec[size - 1], vec[rand() % size]);
    }
}

int uniqify(std::vector<int>& vec)
{
    if(vec.size() < 2) return vec.size(); 
    int i = 0;
    for(int j = 1; j < vec.size(); ++j)
    {
        if(vec[i] != vec[j])
        {
            vec[++i] = vec[j]; 
        }
    }
    return i + 1; 
}



void test(void)
{
    std::vector<int> vec(32, 0); 

    srand(time(nullptr)); 
    for(auto & val : vec)
    {
        val = rand() % 10; 
    }
    std::cout << vec << std::endl; 

    quicksort(vec, 0, vec.size()); 
    std::cout << vec << std::endl; 

    int size = uniqify(vec); 

    for(int i = 0; i < size; ++i)
    {
        std::cout << vec[i] << " "; 
    } 
    std::cout << std::endl; 

    shuffle(vec); 
    std::cout << vec << std::endl; 
}

int binSearch(std::vector<int>& vec, int target)
{
    int lo = 0;

    return 0; 
}


int main(int argc, char** argv)
{
    test();
    return 0; 
}








