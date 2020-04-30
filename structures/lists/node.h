#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){
        next = nullptr;
        prev = nullptr;
    }

    void killSelf(){
        if(!this){ //warning: 'this' pointer cannot be null in well-defined C++ code; pointer may be assumed to always convert to true
            return;
        }
        if(next != nullptr && next != this){
            next->killSelf();
        }

        delete this;
    }
};

#endif //NODE_H