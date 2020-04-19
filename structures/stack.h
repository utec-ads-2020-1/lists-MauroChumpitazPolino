#ifndef STACK_H
#define STACK_H

using namespace std;

#define MAX 1000

// TODO: Implement all methods
template <typename T>
class stack {
	T* data;
	int top;
	int capacity;

public:
	stack(int size = MAX){
		data = new T[size];
		top = -1;
		capacity = size;
	}
	~stack(){
		delete []data;
	}   		

	// Resize the Stack to enable push() function
	void resize(){
		size_t newSize = capacity * 2;
		T* newData = new T[newSize];

		memcpy(newData, data, capacity * sizeof(data[0]) );
		capacity = newSize;
		delete[] data; 
		data = newData;
	}

	//Push one value into the Stack
	void push(T newValue){
		if (top >= (capacity - 1)){
			resize();
		}
		top++;
		data[top] = newValue;
	}

	// Pop one value from Stack or send messages if needed
	void pop(){
		if (top < 0){
			cout << "Underflow instruction" << endl;
		}
		else if (top == 0){
			cout << "Stack is empty now" << endl;
			top = -1;
		}
		else{
			top = top - 1;
		}
	}

	// Returns the peak value if Stack is not empty, else return a null
	T peak(){
		if(top < 0){
			cout << "Null peak, stack is empty" << endl;
			return 0;
		}
		else{
			return data[top];
		}	
	}

	// Returns the Queue size, zero if it is empty
	int size(){
		return (top+1);
	}

	// Return true if Queue is empty
	bool empty(){
		if(top < 0){
			return true;
		}
		else{
			return false;
		}
	}

};

#endif