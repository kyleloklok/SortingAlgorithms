#include <stack> 

inline int getbits(int n, const int digit, const int bits_wanted, const int max_bit){
    int mask; 
    if(bits_wanted == sizeof(int) * 8) mask = ~0; 
    else mask = ~(~0 << bits_wanted); 
    return (n >> (max_bit - digit)) & mask; 
}

void radixexchange(int* arr, int start, int end, int bit, const int max_bit){
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

void radixexchange2(int* arr, int start, int end, int bit, const int max_bit){
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

void straightradix(int* arr, int* b, const int max_bit, const int size){
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

void straightradix2(int* arr, int* b, const int max_bit, const int size){
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