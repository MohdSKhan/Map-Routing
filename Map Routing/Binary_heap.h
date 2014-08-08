#ifndef HEAP_H 
#define HEAP_H 
#include <cassert> 
template<class Type> 
class priority_queue
{  
private: 
    int maxSize; 
    int n; 
    Type* q; 
    int parentIndex(int n) const
	{ 
        return ((n == 1)?(-1):((int)n/2)); 
    } 
    int childIndex(int n) const
	{ 
        return 2 * n; 
    } 
    void bubble_up(int p)
	{ 
        if(parentIndex(p) == -1) 
			return; 
        if(q[parentIndex(p)] > q[p])
		{ 
            swap(q[parentIndex(p)], q[p]); 
            bubble_up(parentIndex(p)); 
        } 
    } 
    void bubble_down(int p)
	{  
        int child = childIndex(p); 
        int min_index = p; 
        for(int i = 0; i <= 1; ++i)
		{          
            if((child + i) <= n)
			{ 
                if(q[min_index] > q[child + i]) min_index = child + i; 
            } 
        }        
        if(min_index != p)
		{ 
            swap(q[min_index], q[p]); 
            bubble_down(min_index); 
        } 
    } 
public: 
    priority_queue(int _maxSize) : maxSize(_maxSize + 1), n(0)
	{ 
        q = new Type[maxSize]; 
    } 
	~priority_queue()
	{ 
		delete[] q; 
    } 
    void push(const Type& item)
	{ 
        assert(n < maxSize); 
        n++; 
        q[n] = item; 
        bubble_up(n); 
    } 
    void pop()
	{ 
        assert(n > 0); 
        Type min = q[1];  
        q[1] = q[n]; 
        n--; 
        bubble_down(1); 
    } 
    Type top() const
	{ 
        return q[1]; 
    } 
    int size() const
	{  
        return n;  
    } 
    bool empty() const
	{ 
        return (n == 0); 
    } 
}; 
  
#endif 