#include <cstdlib>
#include <iostream>
#include <string>

template<typename T>
struct Node{
	T data;
	Node* next;
};

class StackException{
	public:
	StackException(std::string msg){
		std::cout << msg << std::endl;
	}
};

template<typename T>
class Stackplus{
	private:
		Node<T>* _head = new Node<T>;
		long _size = 0;
	
	public:
		Stackplus(){
			_head->next = NULL;
		}
		
		Node<T>* get_head(){
			return _head;
		}
		
		long size(){ // O(1)
			return _size;
		}
		
		bool is_empty(){ // O(1)
			return (this->size() == 0);
		}
		
		void push(T elem){	//O(1)
			Node<T>* temp = new Node<T>;
			temp->data = elem;	
			temp->next = _head->next;	
			_head->next = temp;
			_size++;
		}
		
		T pop(){ // O(1)
			if (this->is_empty()){
				throw StackException("Unable to pop - stack is empty");
			}
			
			Node<T>* temp = _head->next;
			T elem;
			_head->next = temp->next;
			temp->next = NULL;
			elem = temp->data;
			delete temp;
			_size--;
			return elem;
		}
		
		T peek(){ // O(1)
			if (this->is_empty()){
				throw StackException("Unable to peek - stack is empty");
			}		
			return _head->next->data;
		}
		
		void reverse(){ // O(3*n)
			Stackplus<T> aux;
			Stackplus<T> aux2;
			while(!this->is_empty()){
				aux.push(this->pop());
			}

			while(!aux.is_empty()){
				aux2.push(aux.pop());
			}
			
			while(!aux2.is_empty()){
				this->push(aux2.pop());
			}
		}
		
		void print(){ // O(2*n)
			Stackplus<T> aux;
			
			while(!this->is_empty()){
				aux.push(this->pop());
			}
			
			while(!aux.is_empty()){
				std::cout << aux.peek() << std::endl;
				this->push(aux.pop());
			}
			std::cout << std::endl;
		}
		
		void rprint(){ // O(2*n)
			Stackplus<T> aux;
			
			while(!this->is_empty()){
				std::cout << this->peek() << std::endl;
				aux.push(this->pop());
			}
			
			while(!aux.is_empty()){
				this->push(aux.pop());
			}
			std::cout << std::endl;
		}
		
		void StackSort(){ // O(2*(n^2) + n) , stable
			Stackplus<T> aux;
			Stackplus<T> aux2;
			long length = _size;
			T highest;
					
			for (long i = 0; i < length; i++){
				highest = this->peek();
				
				while (!this->is_empty()){
					if (this->peek() > highest){
						highest = this->peek();
					}
					aux.push(this->pop());
				}
				
				while(!aux.is_empty()){
					if (aux.peek() == highest){
						aux2.push(aux.pop());
					}
					
					else{
						this->push(aux.pop());
					}
				}
			}
			
			while(!aux2.is_empty()){
				this->push(aux2.pop());
			}
		}
};

int main(void){
	using namespace std;
	Stackplus<int> s;
	s.push(3);
	s.push(2);
	s.push(1);
	s.push(4);
	s.push(5);
	s.print();
	s.StackSort();
	s.print();
}
