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
        if(!this){
            return;
        }
        if(next != nullptr && next != this){
            next->killSelf();
        }

        delete this;
    }
};

#endif //NODE_H