#ifndef FORWARD_H
#define FORWARD_H

#include <stdlib.h>
#include "list.h"
#include "iterators/forward_iterator.h"
using namespace std;

// TODO: Implement all methods
template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList() : List<T>() {}

        // Returns the front element
        T front(){
            if(this->head == nullptr){
                throw out_of_range("Forward list is empty, no front element.");
            }
            return this->head->data;
        }

        // Returns the back element
        T back(){
            if(this->head == nullptr){
                throw out_of_range("Forward list is empty, no back element.");
            }
            // Por qué creas un Nodo? 
            auto backNode = new Node<T>;
            backNode = this->head;
            while(backNode->next != nullptr){
                backNode = backNode->next;
            }
            return backNode->data;
        }

        // Push an element to the front
        void push_front(T newElement){
            auto newNode = new Node<T>;
            newNode->data = newElement;

            if(this->head == nullptr){
                newNode->next = nullptr;
                this->head = newNode;
            }
            else{
                newNode->next = this->head;
                this->head = newNode;
            }
            this->nodes++;
        }

        // Push an element to the back 
        void push_back(T newElement){
            auto newNode = new Node<T>;

            if(this->head == nullptr){
                newNode->next = nullptr;
                newNode->data = newElement;
                this->head = newNode;
            }
            else{
                newNode = this->head;
                while (newNode->next != nullptr){
                    newNode = newNode->next;
                }
                auto backElement = new Node<T>;
                backElement->data = newElement;
                backElement->next = nullptr;
                newNode->next = backElement;
            }
            this->nodes++;
        }

        // Removes the front element and updates the head
        void pop_front(){
            if( empty() ){
                cout << "Underflow instruction, Forward list is alredy empty" << endl;
                return;
            }
            auto popNode = new Node<T>;
            popNode = this->head;

            if(this->head->next == nullptr){
                this->head = nullptr;
                this->nodes = 0;
                popNode->killSelf(); // No es la mejor forma
                cout << "Forward List is empty now" << endl;
            }
            else{
                this->head = this->head->next;
                popNode->next = nullptr;
                popNode->killSelf(); // Por qué no delete simplemente?
                this->nodes--;
            }
        }

        // Removes the back element
        void pop_back(){
            if( empty() ){
                cout << "Underflow instruction, Forward list is alredy empty." << endl;
                return;
            }
            auto popNode = new Node<T>;
            popNode = this->head;

            if(this->head->next == nullptr){
                this->head = nullptr;
                this->nodes = 0;
                popNode->killSelf();
                cout << "Forward List is empty now" << endl;
            }
            else{
                for(int i = 0; i < this->nodes - 2; i++){
                    popNode = popNode->next;
                }
                popNode->next->killSelf();
                popNode->next = nullptr;
                this->nodes--;
            }
        }

        // Returns an element in a certain position
        T operator[](int position){
            if(position >= this->nodes){
                throw out_of_range("Invalid element position.");
            }
            auto tempPos = new Node<T>;
            tempPos = this->head;

            while(position > 0){
                tempPos = tempPos->next;
                position--;
            }
            return tempPos->data;
        }

        // Returns a 'true' if is empty
        bool empty(){
            return !(this->nodes);
        }

        // Returns the current count of elements
        int size(){
            return this->nodes;
        }

        // Removes all the elements
        void clear(){
            auto clearNode = new Node<T>;
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

        // Reverts the elements of the structure
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

        ForwardIterator<T> begin(){
            ForwardIterator<T> begItr(this->head);
            return begItr; 
        }

	    ForwardIterator<T> end(){
            // Creas un nuevo nodo cada vez
            auto iterNode = new Node<T>;
            iterNode = this->head;
            while(iterNode->next != nullptr){
                iterNode = iterNode->next;
            }
            ForwardIterator<T> endItr(iterNode->next);
            return endItr;
        }

        string name() {
            return "Forward List";
        }

        void merge(ForwardList<T>& mergeList){
            if ( empty() ){
                this->head = mergeList.head;
                this->nodes = mergeList.nodes;
            }
            else if( mergeList.empty() ){
                cout << "Forward List to merge was already empty" << endl;
            }
            else{
                auto mergeNode = new Node<T>;
                mergeNode = this->head;
                while(mergeNode->next != nullptr){
                    mergeNode = mergeNode->next;
                }
                mergeNode->next = mergeList.head;
                this->nodes = this->nodes + mergeList.nodes;
            }
            mergeList.head = nullptr;
            mergeList.nodes = 0;
        }
};

#endif