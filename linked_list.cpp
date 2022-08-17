#include "linked_list.h"
#include <random> 
#include <iostream>

linked_list::linked_list(){
    head = new node(); 
    tail = new node(); 
    head->next = tail; 
    tail->next = tail; 
    size = 0; 
}

linked_list::~linked_list(){
    node* curr = head; 
    while(curr != tail){
        node* save = curr->next; 
        delete curr; 
        curr = save; 
    }
    delete tail; 
}

linked_list::linked_list(const linked_list& list){
    this->size = list.size; 
    this->head = new node();  
    this->tail = new node();    
    node* copy = this->head; 
    node* curr = list.head; 
    while(curr->next != list.tail){
        copy->next = new node(curr->next->key); 
        curr = curr->next; 
        copy = copy->next; 
    }
    copy->next = tail; 
    tail->next = tail; 
}

linked_list& linked_list::operator=(const linked_list& list){
    node* copy = this->head; 
    node* curr = list.head; 
    for(int i = 0; i < this->size && copy->next != this->tail; i++, curr = curr->next, copy = copy->next){
        copy->next->key = curr->next->key; 
    }
    while(curr->next != list.tail){
        copy->next = new node(curr->next->key); 
        copy = copy->next;
        curr = curr->next; 
    }
    copy->next = this->tail; 
    this->tail->next = this->tail; 
    this->size = list.size; 
    return *this; 
}

int linked_list::get_size() const{
    return size; 
}

bool linked_list::empty() const{
    return size == 0; 
}

void linked_list::print() const{
    node* curr = head->next; 
    while(curr != tail){
        printf("%d ", curr->key); 
        curr = curr->next; 
    }
    printf("\n"); 
}

void linked_list::add(const int key){
    tail->key = key; 
    tail->next = new node(); 
    tail->next->next = tail->next; 
    tail = tail->next; 
    size++; 
}

void linked_list::add(const int ind, const int key){
    node* curr = head; 
    for(int i = -1; i < ind - 1 && curr; i++) curr = curr->next; 
    if(!curr) return; 
    node* save = curr->next;
    curr->next = new node(key); 
    curr->next->next = save;
    size++; 
}

int linked_list::remove(){
    if(empty()) return rand(); 
    int key = head->next->key; 
    node* save = head->next; 
    head->next = head->next->next; 
    delete save; 
    size--; 
    return key; 
}

int linked_list::remove(const int ind){
    if(empty()) return rand(); 
    node* curr = head; 
    for(int i = -1; i < ind - 1 && curr; i++) curr = curr->next; 
    if(!curr) return rand(); 
    node* save = curr->next; 
    curr->next = curr->next->next; 
    int key = save->key; 
    delete save;
    size--;  
    return key; 
}

void linked_list::sort(){
    head->next = mergesort(head->next); 
}

linked_list::node* linked_list::mergesort(linked_list::node* c){
    node dummy; 
    dummy.next = c; 
    for(int len = 1; len < size; len *= 2){
        node* todo = dummy.next;
        node* h = &dummy; 
        while(todo != tail){
            node* first = todo; 
            node* tail1 = todo; 
            for(int i = 1; i < len && tail1->next != tail; i++) tail1 = tail1->next; 
            node* second = tail1->next; 
            tail1->next = tail; 
            if(second == tail){
                h->next = first;
                break; 
            } 
            else{
                node* tail2 = second;
                for(int i = 1; i < len; i++) tail2 = tail2->next; 
                todo = tail2->next; 
                tail2->next = tail; 
                h->next = merge(first, second); 
                while(h->next != tail) h = h->next; 
            }
        }
    }
    return dummy.next; 
}

linked_list::node* linked_list::mergesort(linked_list::node* c, const int size){
    if(c->next != tail){
        node* save = c; 
        for(int i = 0; i < size / 2 - 1; i++) c = c->next; 
        node* mid = c->next; 
        c->next = tail; 
        return merge(mergesort(save, size / 2), mergesort(mid, size / 2)); 
    }
    return c; 
}





