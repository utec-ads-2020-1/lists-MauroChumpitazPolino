#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "../node.h"

// TODO: Implement all methods
template <typename T> 
class BidirectionalIterator {
    private:
        Node<T> *current;
        bool inLimit;

    public:
        BidirectionalIterator(){
            this->current = nullptr;
            inLimit = false;
        }
        BidirectionalIterator(Node<T>* listNode){
            this->current = listNode;
            inLimit = false;
        }

        BidirectionalIterator<T> operator=(BidirectionalIterator<T> eqItr){
            if(this->current != eqItr.current){
                this->current = eqItr.current; 
            }
            // Creas nuevos iteradores
            return this->current;
        }

        bool operator!=(BidirectionalIterator<T> neqItr){
            if (this->current == nullptr){
                throw out_of_range("BidirectionalIterator is not initialized.");
            }

            if (neqItr.current != nullptr){
                if(inLimit == true){
                    inLimit = false;
                    return false;
                }
                else if(neqItr.current->prev == this->current){
                    inLimit = true;
                }
            }
            
            return this->current != neqItr.current;
        }

        BidirectionalIterator<T> operator++(){
            if(this->current == nullptr){
                throw out_of_range("BidirectionalIterator is not initialized.");
            }
            else{
                this->current = this->current->next;
                // Creas nuevos iteradores
                return this->current;
            }
        }

        BidirectionalIterator<T> operator--(){
            if(this->current == nullptr){
                throw out_of_range("BidirectionalIterator is not initialized.");
            }
            else{
                this->current = this->current->prev;
                 // Creas nuevos iteradores
                return this->current;
            }
        }

        T operator*(){
            if(this->current == nullptr){
                throw out_of_range("BidirectionalIterator is not initialized.");
            }
            return this->current->data;
        }
};

#endif