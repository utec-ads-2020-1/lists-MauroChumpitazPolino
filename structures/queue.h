#ifndef QUEUE_H
#define QUEUE_H

#include <cstring>
#include <stdexcept>
using namespace std;

#define MAX 10

// TODO: Implement all methods
template <typename T>
class queue {
	T* data;
	int top;
	int capacity;

public:
	queue(int size = MAX){
		data = new T[size];
		top = -1;
		capacity = size;
	}
	~queue(){
		delete[] data;
	}	

	// Resize the Queue to enable push() function
	void resize(){
		size_t newSize = capacity * 2;
		T* newData = new T[newSize];

		memcpy(newData, data, capacity * sizeof(data[0]) );
		capacity = newSize;
		delete[] data; 
		data = newData;
	}

	// Shift all elements one position to right
	void pushShift(){
		for(int i = top; i >= 0; i--){
			data[i+1] = data[i];
		}
	}

	// Push an element into the Queue
	void push(T newValue){
		if (top >= (capacity - 1) ){
			resize();
		}
		pushShift();
		data[0] = newValue;
		top++;
	}

	// Pop an element from Queue or send messages if needed
	void pop(){
		if (top < 0){
			cout << "Underflow instruction" << endl;
		}
		else if (top == 0){
			cout << "Queue is empty now" << endl;
			top = -1;
		}
		else{
			top = top - 1;
		}
	}

	// Returns the front element or throw an error if empty
	T front(){
		if (top < 0)
		{
			throw out_of_range("Queue is empty, front is null.");
		}
		return data[top];	
	}

	// Returns the back element or throw an error if empty
    T back(){
		if (top < 0)
		{
			throw out_of_range("Queue is empty, back is null.");
		}
		return data[0];
	}

	// Returns the Queue size
	int size(){
		return (top+1);
	}

	// Return true if Queue is empty
	bool empty(){
		return (top < 0)? true : false;
	}

};

#endif