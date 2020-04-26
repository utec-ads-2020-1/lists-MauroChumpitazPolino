#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"
using namespace std;

// TODO: Implement all methods
template <typename T>
class LinkedList : public List<T> {
    public:
        LinkedList() : List<T>() {}

        T front(){
             if(this->head == nullptr){
                throw out_of_range("LinkedList is empty, no front element.");
            }
            return this->head->data;
        }

        T back(){
            if(this->head == nullptr){
                throw out_of_range("LinkedList is empty, no back element.");
            }
            return this->tail->data;
        }

        void push_front(T newElement){
            auto newNode = new Node<T>;
            newNode->data = newElement;

            if(this->head == nullptr){
                newNode->next = nullptr;
                this->head = newNode;
                this->tail = newNode;
            }
            else{
                newNode->next = this->head;
                this->head->prev = newNode;
                this->head = newNode;
            }
            this->nodes++;
        }

        void push_back(T newElement){
            auto newNode = new Node<T>;
            newNode->data = newElement;

            if(this->tail == nullptr){
                newNode->next = nullptr;
                this->head = newNode;
                this->tail= newNode;
            }
            else{
                this->tail->next = newNode;
                newNode->prev = this->tail;
                newNode->next = nullptr;
                this->tail = newNode;
            }
            this->nodes++;
        }

        void pop_front(){
            if( empty() ){
                cout << "Underflow instruction, List is alredy empty" << endl;
            }
            else{
                auto popNode = new Node<T>;
                popNode = this->head;

                if(this->head->next == nullptr){
                    this->head = nullptr;
                    this->tail = nullptr;
                    this->nodes = 0;
                    popNode->killSelf();
                    cout << "LinkedList is empty now" << endl;
                }
                else{
                    this->head = this->head->next;
                    popNode->next = nullptr;
                    popNode->killSelf();
                    this->head->prev = nullptr;
                    this->nodes--;
                }
            }
        }

        void pop_back(){
            if( empty() ){
                cout << "Underflow instruction, LinkedList is alredy empty." << endl;
            }
            else{
                auto popNode = new Node<T>;
                popNode = this->tail;

                if(this->head->next == nullptr){
                    this->head = nullptr;
                    this->tail = nullptr;
                    this->nodes = 0;
                    popNode->killSelf();
                    cout << "LinkedList is empty now" << endl;
                }
                else{
                    this->tail = this->tail->prev;
                    this->tail->next = nullptr;
                    popNode->killSelf();
                    this->nodes --;
                }
            }
        }

        T operator[](int position){
            if(position >= this->nodes){
                throw out_of_range("Invalid element position.");
            }
            auto tempPos = new Node<T>;
            if (position == 0 || position == this->nodes-1){
                (position == 0)? tempPos=this->head : tempPos=this->tail;                
            }
            else if (position <= this->nodes / 2){
                tempPos = this->head;
                while(position > 0){
                    tempPos = tempPos->next;
                    position--;
                }
            }
            else{
                tempPos = this->tail;
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
            clearNode = this->head;
            clearNode->killSelf(); 
            
            this->head = nullptr;
            this->tail = nullptr;
            this->nodes = 0;
        }

        // Swap Function - Used in SORT FUNCTION
        void swap(Node<T> *a, Node<T> *b){
            T swapTemp;
            swapTemp = a->data;
            a->data = b->data;
            b->data = swapTemp;
        }

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
                    
                    while(tempSort->next != nullptr){
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
            BidirectionalIterator<T> begItr(this->head);
            return begItr; 
        }
	    BidirectionalIterator<T> end(){
            BidirectionalIterator<T> endItr(this->tail->next);
            return endItr; 
        }

        string name() {
            return "Linked List";
        }

        void merge(LinkedList<T>& mergeList){
            if ( empty() ){
                this->head = mergeList.head;
                this->tail = mergeList.tail;
                this->nodes = mergeList.nodes;
            }
            else if( mergeList.empty() ){
                cout << "List to merge was already empty" << endl;
            }
            else{
                this->tail->next = mergeList.head;
                mergeList.head->prev = this->tail;
                this->tail = mergeList.tail;
                this->nodes = this->nodes + mergeList.nodes;
            }
            mergeList.head = nullptr;
            mergeList.tail = nullptr;
            mergeList.nodes = 0;
        }
};

#endif