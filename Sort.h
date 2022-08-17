#ifndef SORTING_ALGORITHMS_SORT_H
#define SORTING_ALGORITHMS_SORT_H
#include <iostream>
#include <bitset>
class Sort{
    public:
        static bool verifysort(int* arr, int size);
        static void mergesort(int* arr, const int size); 
        static void heapsort(int* arr, int size); 
        static void straightradix(int* arr, int size, int max_bit); 
        static void radixexchange(int* arr, int size, int max_bit); 
        static void quicksort(int* arr, int size);
        static void quickselect(int* arr, int size, int k);          
        static void countsort(int* arr, int size, int max);                                                                                                                                               
        static void shellsort(int* arr, int size);
        static void selectionsort(int* arr, int size);
        static void insertionsort(int* arr, int size);
        static void bubblesort(int* arr, int size);
        static inline int* merge(int* a, int a_size, int* b, int b_size){
            int a1 = 0, b1 = 0;
            int* arr = new int[a_size + b_size]; 
            for(int i = 0; i < a_size + b_size; i++){
                if(a1 >= a_size) arr[i] = b[b1++]; 
                else if(b1 >= b_size) arr[i] = a[a1++]; 
                else arr[i] = a[a1] <= b[b1] ? a[a1++] : b[b1++];  
            }
            return arr; 
        }
    private:
        static const int int_size = sizeof(int) * 8; 
        inline static void swap(int* arr, int a, int b){
            int save = arr[a]; 
            arr[a] = arr[b]; 
            arr[b] = save; 
        }
        inline static int getbits(int n, const int digit, const int bits_wanted, const int max_bit){
            int mask; 
            if(bits_wanted == int_size) mask = ~0; 
            else mask = ~(~0 << bits_wanted); 
            return (n >> (max_bit - digit)) & mask; 
        }
        //QUICKSORT ALGORITHMS
        inline static int partition(int* arr, int start, int end){ //PARTITION
            int r = start - 1; 
            int l = end; 
            int pivot = arr[end]; 
            for(;;){
                while(arr[++r] < pivot);
                while(arr[--l] > pivot);
                if(r > l) break; 
                swap(arr, r, l); 
            }
            swap(arr, r, end); 
            return r;
        }   
        inline static int medianofthree(int* arr, int start, int end){
            int mid = (start + end) / 2; 
            int l = mid - start;
            int r = end - mid; 
            int n, gap; 
            for(int i = mid; i <= end; i += r){
                if(i > mid){
                    n = mid;
                    gap = r; 
                }
                else{
                    n = start;
                    gap = l; 
                }
                while(arr[n] > arr[n + gap] && n > start - 1){
                    swap(arr, n, n + gap);
                    n -= l; 
                    gap = l; 
                }
            }
            return mid; 
        }
        static void quicksort(int* arr, int start, int end); //ITERATIVE 1
        static void quicksort2(int* arr, int start, int end); //ITERATIVE 2
        static void quicksort3(int* arr, int start, int end); //RECURSIVE
        static void quickselect(int* arr, int start, int end, int k); //FIND kTH SMALLEST ELEMENT IN ARRAY
        static void quickselect2(int* arr, int start, int end, int k); //FIND kTH SMALLEST ELEMENT IN ARRAY
        static void radixexchange(int* arr, int start, int end, int bit, const int max_bit); 
        static void radixexchange2(int* arr, int start, int end, int bit, const int max_bit); 
        static void straightradix(int* arr, int* b, const int max_bit, const int size); 
        static void straightradix2(int*arr, int* b, const int max_bit, const int size); 
        static inline void downheap(int* arr, int n, const int stop){
            int save = arr[n]; 
            while(n <= stop){
                int dir = 2 * n + 1; 
                if(dir <= stop && dir + 1 <= stop && arr[dir] < arr[dir + 1]) dir++; 
                if(dir > stop || save >= arr[dir]) break; 
                arr[n] = arr[dir];
                n = dir; 
            }
            arr[n] = save; 
        }
        static void i_mergesort(int* arr, const int size); 
        static void mergesort2(int* arr, int* b, int start, int end); 
        static void print(int* arr, int size){
            for(int i = 0; i < size; i++){
                printf("%i ", arr[i]); 
            }
            printf("\n"); 
        }
}; 
#endif 