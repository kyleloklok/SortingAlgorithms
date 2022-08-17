#ifndef SORTING_ALGORITHMS_P_QUEUE
#define SORTING_ALGORITHMS_P_QUEUE
#include <iostream>
#include <cmath>

class p_queue{
    public:
        void print() const{
            for(int i = 0; i <= pos; i++) printf("%d ", heap[i]); 
            std::cout << std::endl; 
        }
        p_queue(); 
        ~p_queue(); 
        p_queue(const p_queue& p_queue); 
        p_queue& operator= (const p_queue& p_queue); 
        int size() const; 
        bool empty() const; 
        void insert(const int n); 
        int remove(); 
        void replace(const int n); 
    private:
        int* heap; 
        int pos, heap_size; 
        void checksize(); 
        inline void upheap(int n){
            int save = heap[n]; 
            while(save > heap[(n - 1) / 2] && n != 0){
                heap[n] = heap[(n - 1) / 2]; 
                n = (n - 1) / 2;
            }
            heap[n] = save; 
        }
        inline void downheap(int n){
            int save = heap[n]; 
            while(n <= (pos + 1) / 2){
                int dir = 2 * n + 1; 
                if(dir <= pos && dir + 1 <= pos && heap[dir] < heap[dir + 1]) dir++; 
                if(dir > pos || save >= heap[dir]) break; 
                heap[n] = heap[dir];
                n = dir; 
            }
            heap[n] = save; 
        }
};

#endif