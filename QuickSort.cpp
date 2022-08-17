#include <stack>

inline int partition(int* arr, int start, int end){ //PARTITION
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
inline int medianofthree(int* arr, int start, int end){
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

void quicksort(int* arr, int start, int end){
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

void quicksort2(int* arr, int start, int end){
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

void quicksort3(int* arr, int start, int end){
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

void quickselect(int* arr, int start, int end, int k){
    while(start < end){
        int p = partition(arr, start, end); 
        if(p < k - 1) start = p + 1; 
        else if(p > k - 1) end = p - 1; 
        else break; 
    }
}

void quickselect2(int* arr, int start, int end, int k){
    if(start >= end) return; 
    int p = partition(arr, start, end); 
    if(p > start + k - 1) quickselect(arr, start, p - 1, k); 
    if(p < start + k - 1) quickselect(arr, p + 1, end, start + k - p - 1); 
}
