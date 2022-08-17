inline int* merge(int* a, int a_size, int* b, int b_size){
    int a1 = 0, b1 = 0;
    int* arr = new int[a_size + b_size]; 
    for(int i = 0; i < a_size + b_size; i++){
        if(a1 >= a_size) arr[i] = b[b1++]; 
        else if(b1 >= b_size) arr[i] = a[a1++]; 
        else arr[i] = a[a1] <= b[b1] ? a[a1++] : b[b1++];  
    }
    return arr; 
}

void mergesort(int* a, const int size){
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

void mergesort2(int* arr, int* b, int start, int end){
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
