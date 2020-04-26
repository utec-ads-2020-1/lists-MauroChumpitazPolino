#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

// TODO: Implement all methods
template <typename T>
class CircularLinkedList : public List<T> {
    private:
        Node<T>* sentinel;
    public:
        CircularLinkedList() : List<T>() {
            sentinel = new Node<T>;
            sentinel->data = 0;
            sentinel->next = nullptr;
            sentinel->prev = nullptr;
        }
        ~CircularLinkedList() {
            if(this->head != nullptr){
                this->head = this->head->prev;
                this->head->next = nullptr;
                while(this->nodes - 1 > 0){
                    this->head = this->head->prev;
                    this->nodes--;
                }
            }
            delete sentinel;
        }

        T front(){
            if(this->head == nullptr){
                throw out_of_range("Circular list is empty, no front element.");
            }
            return this->head->data;
        }

        T back(){
            if(this->head == nullptr){
                throw out_of_range("Circular list is empty, no back element.");
            }
            return this->head->prev->data;
        }

        void push_front(T newElement){
            int counter = this->nodes;
            auto newNode = new Node<T>;
            newNode->data = newElement;

            if(this->head == nullptr){
                this->head = newNode;
                this->head->next = this->head;
                this->head->prev = this->head;
            }
            else{
                this->head->prev = newNode;
                newNode-> next = this->head;
                this->head = newNode;
                
                while (counter > 0){
                    newNode = newNode->next;
                    counter--;
                }
                newNode->next = this->head;
                this->head->prev = newNode;
            }
            this->nodes++;
        }

        void push_back(T newElement){
            int counter = this->nodes - 1;
            auto tailNode = new Node<T>;

            if(this->head == nullptr){
                this->head = tailNode;
                this->head->data = newElement;
                this->head->next = this->head;
                this->head->prev = this->head;
            }
            else{
                tailNode = this->head;
                while (counter > 0){
                    tailNode = tailNode->next;
                    counter--;
                }
                auto backElement = new Node<T>;
                backElement->data = newElement;
                backElement->next = this->head;
                backElement->prev = tailNode;
                tailNode->next = backElement;
                this->head->prev = backElement;
            }
            this->nodes++;
        }

        void pop_front(){
            if( empty() ){
                cout << "Underflow instruction, Circular list is alredy empty" << endl;
                return;
            }
            auto popNode = new Node<T>;

            if(this->head->next == this->head){
                popNode = this->head;
                this->head = nullptr;
                this->nodes = 0;
                popNode->killSelf();
                cout << "Circular List is empty now" << endl;
            }
            
            else{
                auto tailNode = new Node<T>;
                tailNode = this->head->prev;
                this->head = this->head->next;
                this->head->prev = tailNode;
                popNode = tailNode->next;
                tailNode->next = this->head;
                popNode->next = nullptr;
                popNode->prev = nullptr;
                popNode->killSelf();
                this->nodes--;
            }            
        }

        void pop_back(){
            if( empty() ){
                cout << "Underflow instruction, Circular list is alredy empty." << endl;
                return;
            }
            auto popNode = new Node<T>;
            popNode = this->head;

            if(this->head->next == this->head){
                this->head = nullptr;
                this->nodes = 0;
                popNode->killSelf();
                cout << "Circular List is empty now" << endl;
            }

            else{
                int counter = this->nodes - 1;
                while (counter > 0){
                    popNode = popNode->next;
                    counter--;
                }
                popNode->next = nullptr;
                popNode = popNode->prev;
                this->head->prev = popNode;
                popNode->next->killSelf();
                popNode->next = this->head;
                this->nodes--;
            }
        }

        T operator[](int position){
            if(position >= this->nodes){
                throw out_of_range("Invalid element position.");
            }
            auto tempPos = new Node<T>;
            if (position == 0 || position == this->nodes-1){
                (position == 0)? tempPos=this->head : tempPos=this->head->prev;                
            }
            else if (position <= this->nodes / 2){
                tempPos = this->head;
                while(position > 0){
                    tempPos = tempPos->next;
                    position--;
                }
            }
            else{
                tempPos = this->head->prev;
                while(position < this->nodes-1){
                    tempPos = tempPos->prev;
                    position++;
                }
            }
            return tempPos->data;
        }

        bool empty(){
            return (this->nodes > 0)? false : true;
        }

        int size(){
            return this->nodes;
        }

        void clear(){
            auto clearNode = new Node<T>;
            clearNode = this->head->prev;
            clearNode->next = nullptr;
            clearNode = this->head;
            clearNode->killSelf(); 
            
            this->head = nullptr;
            this->nodes = 0;
        }

        // Swap Function - Used in SORT FUNCTION
        void swap(Node<T> *a, Node<T> *b){
            T swapTemp;
            swapTemp = a->data;
            a->data = b->data;
            b->data = swapTemp;
        }

        // Sort the elements using Bubble sorting
        void sort(){
            if(this->head == nullptr){
                return;
            }
            else{
                auto tempSort = new Node<T>;
                bool swapped;
                
                do{
                    swapped = false;
                    tempSort = this->head;
                    
                    while(tempSort->next != this->head){
                        if(tempSort->data > tempSort->next->data){
                            swap(tempSort, tempSort->next);
                            swapped = true;
                        }
                        tempSort = tempSort->next;
                    }
                } while(swapped);
            }
        }

        void reverse(){
            auto tempHead = new Node<T>;
            for (int i = (this->nodes - 1); i > 0; i--){
                tempHead = this->head;
                for (int j = i; j > 0; j--){
                    swap(tempHead, tempHead->next);
                    tempHead = tempHead->next;
                }
            }     
        }

        BidirectionalIterator<T> begin(){
            if(this->head == nullptr){
                throw out_of_range("Circular List is not initialized.");
            }
            return BidirectionalIterator<T>(this->head);
        }

	    BidirectionalIterator<T> end(){
            if(this->head == nullptr){
                throw out_of_range("Circular List is not initialized.");
            }
            sentinel->next = this->head;
            sentinel->prev = this->head->prev;
            return BidirectionalIterator<T>(sentinel); 
        }

        string name() {
            return "Circular Linked List";
        }

        void merge(CircularLinkedList<T>& mergeList){
            if ( empty() ){
                this->head = mergeList.head;
                this->nodes = mergeList.nodes;
            }
            else if( mergeList.empty() ){
                cout << "Circular List to merge was already empty" << endl;
            }
            else{
                auto mergeNode = new Node<T>;
                mergeNode = this->head;
                while(mergeNode->next != this->head){
                    mergeNode = mergeNode->next;
                }
                mergeNode->next = mergeList.head;
                mergeList.head->prev = mergeNode;
                this->nodes = this->nodes + mergeList.nodes;
                for (int i = 0; i < mergeList.nodes; i++){
                    mergeNode = mergeNode->next;
                }
                mergeNode->next = this->head;
                this->head->prev = mergeNode;
            }
            mergeList.head = nullptr;
            mergeList.nodes = 0;
        }
};

#endif