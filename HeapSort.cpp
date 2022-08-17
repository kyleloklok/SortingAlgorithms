inline void downheap(int* arr, int n, const int stop){
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

void heapsort(int* arr, int size){
    for(int i = size / 2; i > -1; i--){
        downheap(arr, i, size - 1); 
    }
    for(int i = size - 1; i > 0; i--){
        swap(arr, 0, i); 
        downheap(arr, 0, i - 1); 
    }
}