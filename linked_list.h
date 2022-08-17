#ifndef SORTING_ALGORITHMS_LINKED_LIST_H
#define SORTING_ALGORITHMS_LINKED_LIST_H
class linked_list{
    public:
        linked_list();
        ~linked_list(); 
        linked_list(const linked_list& list); 
        linked_list& operator=(const linked_list& list); 
        void sort();
        void add(const int key); 
        void add(const int ind, const int key); 
        int remove(); 
        int remove(const int ind); 
        int get_size() const; 
        bool empty() const; 
        bool is_sorted() const; 
        void print() const; 
    private:
        int size; 
        struct node{
            int key; 
            node* next;
            node(){
                this->key = 0;
                this->next = 0; 
            }
            node(int key){
                this->key = key; 
                this->next = 0; 
            }
            node(const node* node){
                this->key = node->key; 
                this->next = 0; 
            }
        };
        node *head, *tail;  
        inline node* merge(node* a, node* b){
            node* save; 
            if(a->key <= b->key){
                save = a;
                a = a->next; 
            } else{
                save = b; 
                b = b->next; 
            }
            node* curr = save; 
            for(;;){
                if(a->next == a && b->next == b) break; 
                else if(a->next == a){
                    curr->next = b; 
                    curr = curr->next;
                    b = b->next; 
                }
                else if(b->next == b){
                    curr->next = a; 
                    curr = curr->next;
                    a = a->next; 
                } 
                else if(b->key <= a->key){
                    curr->next = b; 
                    curr = curr->next;
                    b = b->next; 
                }
                else{
                    curr->next = a; 
                    curr = curr->next;
                    a = a->next; 
                }
            }
            curr->next = tail; 
            return save; 
        } 
        node* mergesort(node* c); 
        node* mergesort2(node* c);
        node* mergesort3(node* c, const int size); 
};
#endif