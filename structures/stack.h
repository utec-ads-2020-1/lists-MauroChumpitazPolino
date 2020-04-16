#ifndef STACK_H
#define STACK_H

using namespace std;

#define MAX 1000

// TODO: Implement all methods
template <typename T>
class stack {
	T* data;
	int itop;
	int capacity;

public:
	stack(int size = MAX){
		data = new T[size];
		itop = -1;
	}
	~stack(){
		delete data;
	}   		

	void push(T value){
		if (itop == (capacity - 1)){
			cout << "Overflow instruction" << endl;
		}
		else{
			itop++;
			data[itop] = value;
		}
	}

	int pop(){
		if(itop < 0){
			cout << "Underflow instruction" << endl;
			return 0;
		}
		else{
			itop = itop - 1;
			return data[itop+1];
		}
	}

	int top(){
		if(itop < 0){
			cout << "No hay top, stack vacío" << endl;
			return 0;
		}
		else{
			return data[itop];
		}	
	}

	int size(){
		return (itop+1);
	}

	bool empty(){
		if(itop < 0){
			return true;
		}
		else{
			return false;
		}
	}

};

#endif