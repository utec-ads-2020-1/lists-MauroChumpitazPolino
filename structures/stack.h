#ifndef STACK_H
#define STACK_H

using namespace std;

#define MAX 1000

// TODO: Implement all methods
template <typename T>
class stack {
	T* data;
	int itop;
	int top;
	int capacity;

public:
	stack(int size = MAX){
		data = new T[size];
		top = -1;
		capacity = size;
	}
	~stack(){
		delete data;
	}   		

	void push(T newValue){
		// If stack is full, show 'overflow' message.
		if (top >= (capacity - 1)){
			cout << "Overflow instruction" << endl;
		}
		// Else, top goes to next position and add the new value.
		else{
			top++;
			data[top] = newValue;
		}
	}

	void pop(){
		// If stack is empty, show 'underflow' message.
		if(top < 0){
			cout << "Underflow instruction" << endl;
		}
		// Else, top goes to previous position.
		else{
			top = top - 1;
		}
	}

	T peak(){
		// If stack is empty, show 'no peak element' message.
		if(top < 0){
			cout << "No peak element, empty stack" << endl;
			return 0;
		}
		// Else, return the peak element.
		else{
			return data[top];
		}	
	}

	int size(){
		// Because first stack element starts in 'top = 0', the stack size is (top + 1).
		return (top+1);
	}

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