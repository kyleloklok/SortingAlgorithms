#include <iostream>
#include <stack> 
#include "Sort.h"

bool Sort::verifysort(int* arr, int size){
    for(int i = 1; i < size - 1; i++){
        if(arr[i - 1] > arr[i] || arr[i + 1] < arr[i]) return false; 
    }
    return true; 
}

void Sort::mergesort(int* arr, const int size){
    i_mergesort(arr, size); 
}

void Sort::i_mergesort(int* a, const int size){
    const int end = size - 1; 
    int *curr = a, *copy, b[size]; 
    for(int len = 1; len < size; len *= 2){
        copy = curr == a ? b : a; 
        for(int head = 0; head < size; head += 2 * len){
            if(head + len > end){
                for(int i = head; i < size; i++) copy[i] = curr[i]; 
                break; 
            }
            else{
                int next = head + len; 
                int tail1 = next - 1; 
                int tail2 = next + len > end ? end : next + len - 1; 
                for(int i = head, h_ptr = head, n_ptr = next; i <= tail2; i++){
                    if(h_ptr > tail1) copy[i] = curr[n_ptr++]; 
                    else if(n_ptr > tail2) copy[i] = curr[h_ptr++]; 
                    else copy[i] = curr[h_ptr] <= curr[n_ptr] ? curr[h_ptr++] : curr[n_ptr++]; 
                }
            }
        }
        curr = copy; 
    }
    if(curr == b){
        for(int i = 0; i < size; i++) a[i] = b[i]; 
    }
}

void Sort::mergesort2(int* arr, int* b, int start, int end){
    if(start < end){
        int mid = (start + end) / 2; 
        mergesort2(arr, b, start, mid); 
        mergesort2(arr, b, mid + 1, end); 
        for(int i = start; i <= mid; i++) b[i] = arr[i]; 
        for(int i = mid + 1; i <= end; i++) b[i] = arr[mid + 1 + end - i]; 
        for(int i = start, r = start, l = end; i <= end; i++){
            arr[i] = b[r] <= b[l] ? b[r++] : b[l--]; 
        }
    }
}

void Sort::heapsort(int* arr, int size){
    for(int i = size / 2; i > -1; i--){
        downheap(arr, i, size - 1); 
    }
    for(int i = size - 1; i > 0; i--){
        swap(arr, 0, i); 
        downheap(arr, 0, i - 1); 
    }
}

//RADIX SORTS
void Sort::straightradix(int* arr, int size, int max_bit){
    int b[size]; 
    straightradix(arr, b, max_bit, size); 
}

void Sort::straightradix(int* arr, int* b, const int max_bit, const int size){
    int count[2]; 
    for(int bit = max_bit; bit > 0; bit--){
        count[0] = 0;
        count[1] = 0; 
        for(int i = 0; i < size; i++) count[getbits(arr[i], bit, 1, max_bit)]++; 
        count[1] += count[0]; 
        for(int i = size - 1; i >= 0; i--) b[--count[getbits(arr[i], bit, 1, max_bit)]] = arr[i];      
        for(int i = 0; i < size; i++) arr[i] = b[i]; 
    }
}

void Sort::straightradix2(int* arr, int* b, const int max_bit, const int size){
    int count[max_bit]; 
    int m = max_bit / 4;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    for(int pass = max_bit; pass > 0; pass -= m){
        for(int i = 0; i < max_bit; i++) count[i] = 0; 
        for(int i = 0; i < size; i++) count[getbits(arr[i], pass, m, max_bit)]++; 
        for(int i = 1; i < max_bit; i++) count[i] += count[i - 1]; 
        for(int i = size - 1; i >= 0; i--) b[--count[getbits(arr[i], pass, m, max_bit)]] = arr[i]; 
        for(int i = 0; i < size; i++) arr[i] = b[i]; 
    }
}

void Sort::radixexchange(int* arr, int size, int max_bit){
    radixexchange(arr, 0, size - 1, max_bit, max_bit); 
}

void Sort::radixexchange(int* arr, int start, int end, int bit, const int max_bit){
    std::stack<int> stack; 
    for(;;){
        while(start < end && bit >= 0){
            int r = start;
            int l = end; 
            while(r < l){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
                while(!getbits(arr[r], max_bit - bit + 1, 1, max_bit) && r < l) r++; 
                while(getbits(arr[l], max_bit - bit + 1, 1, max_bit) && r < l) l--; 
                swap(arr, r, l); 
            }
            if(!getbits(arr[r], max_bit - bit + 1, 1, max_bit)) r++; 
            if(r - start > end - r){
                stack.push(r - 1); 
                stack.push(start); 
                stack.push(bit - 1); 
                start = r; 
            } else{
                stack.push(end);
                stack.push(r);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
                stack.push(bit - 1);
                end = r - 1;
            }
            bit--; 
        }
        if(stack.empty()) break; 
        bit = stack.top(); 
        stack.pop();
        start = stack.top();
        stack.pop(); 
        end = stack.top();
        stack.pop(); 
    }
}

void Sort::radixexchange2(int* arr, int start, int end, int bit, const int max_bit){
    if(start < end && bit > 0){
        int r = start;
        int l = end; 
        while(r < l){
            while(!getbits(arr[r], max_bit - bit + 1, 1, max_bit) && r < l) r++; 
            while(getbits(arr[l], max_bit - bit + 1, 1, max_bit) && r < l) l--; 
            swap(arr, r, l); 
        }
        if(!getbits(arr[r], max_bit - bit + 1, 1, max_bit)) r++; 
        radixexchange2(arr, start, r - 1, bit - 1, max_bit); 
        radixexchange2(arr, r, end, bit - 1, max_bit); 
    }
}

//QUICKSORT
void Sort::quicksort(int* arr, int size){
    quicksort(arr, 0, size - 1); 
}
void Sort::quicksort(int* arr, int start, int end){
    std::stack<int> stack; 
    for(;;){
        while(start < end){
            int med = medianofthree(arr, start, end);
            swap(arr, med, end - 1);  
            int p = partition(arr, start, end - 1); 
            if(p - start > end - p){
                stack.push(start);
                stack.push(p - 1); 
                start = p + 1; 
            }
            else{
                stack.push(p + 1); 
                stack.push(end); 
                end = p - 1; 
            }
        }
        if(stack.empty()) break; 
        end = stack.top();
        stack.pop(); 
        start = stack.top();
        stack.pop();          
    }
}

void Sort::quicksort2(int* arr, int start, int end){
    std::stack<int> stack;
    stack.push(start);
    stack.push(end); 
    for(;;){
        if(stack.empty()) break; 
        int r = stack.top(); 
        stack.pop();
        int l = stack.top();
        stack.pop(); 
        if(l < r){
            int p = partition(arr, l, r); 
            stack.push(p + 1);
            stack.push(r); 
            stack.push(l); 
            stack.push(p - 1); 
        }
    } 
}

void Sort::quicksort3(int* arr, int start, int end){
    if(start >= end) return; 
    int r = start - 1; 
    int l = end; 
    swap(arr, end, rand() % (start - end) + start);
    int pivot = arr[end]; 
    int count = 0; 
    for(;;){
        while(arr[++r] < pivot); 
        while(arr[--l] > pivot);
        if(r >= l){
            if(l == r){
                if(l <= end) swap(arr, l + 1, end); 
                quicksort3(arr, start, l - 1);
                quicksort3(arr, l + 2, end); 
                return;  
            }
            break; 
        } 
        swap(arr, r, l); 
    }
    swap(arr, r, end); 
    quicksort3(arr, start, r - 1); 
    quicksort3(arr, r + 1, end); 
}

void Sort::quickselect(int* arr, int size, int k){
    if(k < 1 || k > size){
        printf("%s\n", "Invalid input number");
        return; 
    }
    quickselect(arr, 0, size - 1, k); 
}

void Sort::quickselect(int* arr, int start, int end, int k){
    int p;
    while(start < end){
        p = partition(arr, start, end); 
        if(p < k - 1) start = p + 1; 
        else if(p > k - 1) end = p - 1; 
        else break; 
    }
}

void Sort::quickselect2(int* arr, int start, int end, int k){
    if(start >= end) return; 
    int p = partition(arr, start, end); 
    if(p > start + k - 1) quickselect(arr, start, p - 1, k); 
    if(p < start + k - 1) quickselect(arr, p + 1, end, start + k - p - 1); 
}

void Sort::countsort(int* arr, int size, int max){
    int count[max + 1], b[size]; 
    for(int i = 0; i <= max; i++){
        count[i] = 0; 
    }
    for(int i = 0; i < size; i++){
        count[arr[i]]++; 
    }
    for(int i = 1; i <= max; i++){
        count[i] += count[i - 1]; 
    }
    for(int i = size - 1; i >= 0; i--){
        b[--count[arr[i]]] = arr[i]; 
    }
    for(int i = 0; i < size; i++){
        arr[i] = b[i]; 
    }
}

//SHELLSORT
void Sort::shellsort(int* arr, int size){
    int gap; 
    for(gap = 1; 3 * gap + 1 < size; gap = 3 * gap + 1); 
    for(; gap > 0; gap /= 3){
        for(int i = gap; i < size; i++){
            int n = i;
            int save = arr[n];  
            while(n >= gap && save < arr[n - gap]){
                arr[n] = arr[n - gap]; 
                n-= gap; 
            }
            arr[n] = save; 
        }
    }
}

//BASIC SORTING METHODS
void Sort::selectionsort(int* arr, int size){
    for(int i = 0; i < size - 1; i++){
        int minInd = i; 
        for(int j = i + 1; j < size; j++){
            if(arr[j] < arr[minInd]) minInd = j;
        }
        swap(arr, i, minInd); 
    }
}

void Sort::insertionsort(int* arr, int size){
    for(int i = 1; i < size; i++){
        int save = arr[i]; 
        int n = i - 1; 
        while(n > 0 && save < arr[n]){
            arr[n + 1] = arr[n];
            n--;  
        }
        arr[n - 1] = save; 
    }
}

void Sort::bubblesort(int* arr, int size){
    bool swapped; 
    for(int i = 0; i < size - 1; i++){
        swapped = false; 
        for(int j = 0; j < size - 1 - i; j++){
            if(arr[j] > arr[j + 1]){
                swap(arr, j, j + 1); 
                swapped = true; 
            }
        }
        if(!swapped) return; 
    }
}



