#include "p_queue.h"
#include <iostream>

p_queue::p_queue(){
    heap_size = 10; 
    heap = new int[heap_size]; 
    pos = -1; 
}

p_queue::~p_queue(){
    delete[] heap; 
}

p_queue::p_queue(const p_queue& p_queue){
    this->pos = p_queue.size() - 1; 
    this->heap = new int[pos + 1]; 
    this->heap_size = p_queue.heap_size; 
    for(int i = 0; i <= pos; i++){
        this->heap[i] = p_queue.heap[i]; 
    }
}

p_queue& p_queue::operator= (const p_queue& p_queue){
    delete[] this->heap; 
    this->pos = p_queue.size() - 1; 
    this->heap = new int[pos + 1]; 
    this->heap_size = p_queue.heap_size; 
    for(int i = 0; i <= pos; i++){
        this->heap[i] = p_queue.heap[i]; 
    }
    return *this; 
}

int p_queue::size() const{
    return pos + 1; 
}

bool p_queue::empty() const{
    return pos == -1; 
}

void p_queue::checksize(){
    if(size() == heap_size){
        heap_size *= 2; 
        int* arr = new int[heap_size]; 
        for(int i = 0; i < size(); i++){
            arr[i] = heap[i]; 
        }
        delete[] heap;
        heap = arr; 
    }
    else if(size() == heap_size / 4){
        heap_size *= 2; 
        int* arr = new int[heap_size]; 
        for(int i = 0; i < size(); i++){
            arr[i] = heap[i]; 
        }
        delete[] heap;
        heap = arr; 
    }
}

void p_queue::insert(const int n){
    checksize(); 
    heap[++pos] = n;
    upheap(pos); 
} 

int p_queue::remove(){
    checksize(); 
    int key = heap[0]; 
    heap[0] = heap[pos--]; 
    downheap(0); 
    return key; 
}

void p_queue::replace(const int n){
    heap[0] = n;
    downheap(0); 
}