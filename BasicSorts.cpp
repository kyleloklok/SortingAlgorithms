inline void swap(int* arr, int a, int b){
    int save = arr[a]; 
    arr[a] = arr[b]; 
    arr[b] = save; 
}

void shellsort(int* arr, int size){
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

void selectionsort(int* arr, int size){
    for(int i = 0; i < size - 1; i++){
        int minInd = i; 
        for(int j = i + 1; j < size; j++){
            if(arr[j] < arr[minInd]) minInd = j;
        }
        swap(arr, i, minInd); 
    }
}

void insertionsort(int* arr, int size){
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

void bubblesort(int* arr, int size){
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

void countsort(int* arr, int size, int max){
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
