#include <iostream> 
#include <vector> 
#include <ctime> 
#include <cstdlib> 

std::ostream& operator<<(std::ostream& os, std::vector<int>& vec)
{
    for( auto & v: vec)
    {
        os << v << " "; 
    }
    return os; 
}


namespace tt0
{

// bubble sort 
// selection sort
// insert_sort
// heapsort
// mergesort
// quicksort 
// shuffle 


using std::vector; 

// bubblesort 
void bubblesort(vector<int>& vec, int lo, int hi)
{
    bool  issorted = false; 

    for(int i = hi; i >lo; --i)
    {
        issorted = true; 
        for(int j = lo; j < hi - 1; ++j)
        {
            if(vec[j] > vec[j + 1])
            {
                std::swap(vec[j], vec[j + 1]); 
                issorted = false; 
            }
        }
        if(issorted) return; 
    }
}

// selectsort 
void selectsort(vector<int>& vec, int lo, int hi)
{
    for(int i = hi; i >lo; --i)
    {
        int index = lo; 
        for(int j = lo + 1; j < i; ++j)
        {
            if(vec[index] < vec[j])
            {
                index = j; 
            }
        }
        std::swap(vec[index], vec[i-1]); 
    }

}

// insert 将位于末尾oldpos处的元素插入到newpos 
void insert_helper(vector<int>& vec, int newpos, int oldpos) 
{
    if(newpos <0 || newpos >= oldpos) return; 
    int temp = vec[oldpos]; 
    // 向后移动
    for(int j = oldpos; j > newpos; --j)
    {
        vec[j] = vec[j-1]; 
    }

    vec[newpos] = temp; 
}

int findInsertPos(vector<int>& vec, int lo, int hi, int target)
{
    // find insertpos in [lo, hi)
    for(int i = lo; i < hi; ++i)
    {
        if(vec[i] > target) return i; 
    }
    return hi; 
}

// insertsort 
void insertsort(vector<int>& vec, int lo, int hi)
{
    for(int i = lo; i < hi; ++i)
    {
        int insertpos = findInsertPos(vec, lo, i + 1, vec[i]); 
        insert_helper(vec, insertpos, i); 
    }
}

// for quicksort 
int partition(vector<int>& vec, int lo, int hi)
{
    std::srand(static_cast<unsigned int> (time(nullptr))); 
    std::swap(vec[lo], vec[lo + rand() % (hi - lo + 1)]); 
    int pivot = vec[lo]; 

    while(lo < hi)
    {
        while(lo < hi && pivot <= vec[hi])
        {
            --hi; 
        }
        vec[lo] = vec[hi]; 
        while(lo < hi && pivot >= vec[lo])
        {
            ++lo; 
        }
        vec[hi] = vec[lo]; 
    }
    vec[lo] = pivot; 
    return lo; 
}

// quicksort 
void quicksort(vector<int>& vec, int lo, int hi)
{
    if(hi - lo < 2) return; 
    int mi = partition(vec, lo, hi - 1); 
    quicksort(vec, lo, mi); 
    quicksort(vec, mi + 1, hi); 
}

// find the rank/index of the proper parent 
int properParent(vector<int>& vec, int n, int i)
{
    // i, lc(i), rc(i) 中堪为父者
    int res = i; 
    res = 2*i + 1 < n ? vec[res] > vec[2*i + 1] ? res : 2*i + 1 : res;  
    res = 2*i + 2 < n ? vec[res] > vec[2*i + 2] ? res : 2*i + 2 : res; 

    return res; 
}


// perlocatedown for heapify
int perlocateDown(vector<int>& vec, int n, int i)
{
    int j = 0; 
    // if i isn't the proper parent, down to leaf node 
    while(i != (j = properParent(vec, n, i)))
    {
        std::swap(vec[i], vec[j]); i = j; 
    }
    return i; 
}

// O(n)
void heapify(vector<int>& vec)
{
    // for each nodes from the bottom to the top, do the perlocate down 
    for(int i = vec.size() - 1; i >= 0; --i)
    {
        perlocateDown(vec, vec.size(), i);
    }
}


// heapsort 
void heapsort(vector<int>& vec)
{ 
    heapify(vec);
    for(int i = vec.size(); i >=0; --i)
    {
        std::swap(vec[i -1], vec[0]);  
        perlocateDown(vec, i-1, 0); 
    }
}


// for mergesort 2-way merge 
void merge(vector<int>& vec, int lo, int mi, int hi)
{
    vector<int> temp (vec.begin() + lo, vec.begin() + mi); 
    int i =0; int len1 = mi - lo; 
    int j = mi; 
    int k = lo; 

    while(i < len1 || j < hi)
    {
        if(i < len1 && j < hi) 
        {
            if(temp[i] < vec[j]) { vec[k++] = temp[i++]; } 
            else { vec[k++] = vec[j++]; }
        }
        else if (i == len1)
        {
            vec[k++] = vec[j++]; 
        }
        else  
        {
            vec[k++] = temp[i++]; 
        }
    }
}

// mergesort 
void mergesort(vector<int>& vec, int lo, int hi)
{
    if(hi - lo  < 2) return;  
    int mi = lo + (hi - lo) / 2; 

    mergesort(vec, lo, mi); 
    mergesort(vec, mi, hi); 
    merge(vec, lo, mi, hi); 
}

// shuffle the vector 随机置乱算法
void shuffle(vector<int>& vec, int lo, int hi)
{
    typedef int rank; 
    while(hi > lo)
    {
        std::swap(vec[hi - 1], vec[lo + rand() % (hi - lo)]); 
        --hi; 
    }
}

void initvector(vector<int>& vec)
{
    srand(static_cast<unsigned int>(time(nullptr))); 

    for(int i = 0; i < vec.size(); ++i)
    {
        vec[i] = i; 
    }
}

}   // end of namespace 



void test() 
{
    using std::vector; 
    using std::cout; 
    using std::endl; 
    using namespace tt0; 
    vector<int> vec(10); 
    initvector(vec); 


    // bubblesort 
    cout << "bubble sort: " << endl;  
    shuffle(vec, 0, vec.size()); 
    cout << vec << endl; 
    bubblesort(vec, 0, vec.size());
    cout << vec << endl; 
    cout << endl;  

    // quicksort
    cout << "quicksort: " << endl;  
    shuffle(vec, 0, vec.size()); 
    cout << vec << endl;
    quicksort(vec, 0, vec.size()); 
    cout << vec << endl; 
    cout << endl; 

    // mergesort 
    cout <<"mergesort: " <<endl;  
    shuffle(vec, 0, vec.size());
    cout << vec << endl; 
    mergesort(vec, 0, vec.size());
    cout << vec << endl; 
    cout << endl; 

    // heapsort
    cout <<"heapsort: " <<endl;  
    shuffle(vec, 0, vec.size());
    cout << vec << endl; 
    heapsort(vec);
    cout << vec << endl; 
    cout << endl; 

    // selectsort 
    cout <<"selectsort: " <<endl;  
    shuffle(vec, 0, vec.size());
    cout << vec << endl; 
    selectsort(vec, 0, vec.size());
    cout << vec << endl; 
    cout << endl; 


    // insertsort 
    cout <<"insertsort: " <<endl;  
    shuffle(vec, 0, vec.size());
    cout << vec << endl; 
    insertsort(vec, 0, vec.size());
    cout << vec << endl; 
    cout << endl; 
}



int main()
{
    test(); 
    return 0; 
}