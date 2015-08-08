

/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -Alex Lui, Tewoldebrhan Hagos, Khachatur Mirijanyan
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

/**********************************************************
 * YOU MUST MODIFY THIS FUNCTION IF YOU DID NOT IMPLEMENT
 * Single_list.h IN PROJECT 1.  THIS REQUIRES YOU TO:
 *   1.  Change which header file is is included.
 *   2.  Change the type of the member variable 'list'.
 *   3.  Update the ostream<< operator so that it prints
 *       out the entries in your implementation.
 **********************************************************/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_sentinel_list.h"
//#include "Single_list.h"
#include "Exception.h"
#include <iostream>

template <typename Type>
class Linked_stack {
	private:
		static int const ARRAY_CAPACITY = 8;

		Double_sentinel_list<Type *> list;
        //Single_list<Type *> list;
		int itop;
		int stack_size;

	public:
		Linked_stack();
		Linked_stack( Linked_stack const & );
		~Linked_stack();

		bool empty() const;
		int size() const;
		int list_size() const;

		Type top() const;

		void swap( Linked_stack & );
		Linked_stack &operator=( Linked_stack );
		void push( Type const &obj );
		Type pop();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Linked_stack<T> const & );
};

template <typename Type>
Linked_stack<Type>::Linked_stack():
stack_size( 0 ), itop(0) {
	// Empty constructor
}

template <typename Type>
Linked_stack<Type>::Linked_stack( Linked_stack const &stack )
//itop( stack.itop ),
//stack_size( stack.stack_size )
{
	// enter your implementation here
    itop=0;
    stack_size=0;
    
    Double_node<Type*> *traverser=stack.list.tail()->previous();
    int breaker=0;
    while (traverser->previous()!=list.head())
    {
        for (int i=0; i<ARRAY_CAPACITY; ++i)
        {
            if (breaker==stack.stack_size)
                break;
            push(*(traverser->retrieve()+i));
            breaker++;
            
        }
        if (breaker==stack.stack_size)
            break;
        traverser=traverser->previous();
    }
    itop=stack.itop;
    stack_size=stack.stack_size;
//
}

template <typename Type>
Linked_stack<Type>::~Linked_stack() {
	
    while (!empty())
    {
        this->pop();
    }
}

template <typename Type>
bool Linked_stack<Type>::empty() const {
	// enter your implementation here
	return stack_size==0;
}

template <typename Type>
int Linked_stack<Type>::size() const {
	// enter your implementation here
	return stack_size;
}

// Do not change this implementation

template <typename Type>
int Linked_stack<Type>::list_size() const {
	return list.size();
}

template <typename Type>
Type Linked_stack<Type>::top() const {
	// enter your implementation here
    if (stack_size==0)
        throw underflow();
    return *(list.front()+itop);
}

template <typename Type>
void Linked_stack<Type>::swap( Linked_stack<Type> &stack ) {
	std::swap( list, stack.list );
	std::swap( stack_size, stack.stack_size );
	std::swap( itop, stack.itop );
}

template <typename Type>
Linked_stack<Type> &Linked_stack<Type>::operator=( Linked_stack<Type> rhs ) {
	swap( rhs );

	return *this;
}

template <typename Type>
void Linked_stack<Type>::push( Type const &obj ) {
	// enter your implementation here

    if(stack_size == 0)
    {
        Type *array;
        array=new Type [ARRAY_CAPACITY];
        list.push_front(array);
        *(list.front()+itop)=obj;
        
        ++stack_size;
        return;
    }
    
    if (itop==ARRAY_CAPACITY-1)
    {
        //allocate new array
        itop=0;
        Type *array;
        array=new Type [ARRAY_CAPACITY];
        list.push_front(array);
        *(list.front()+itop)=obj;
        stack_size++;
        return;
    }
    
    itop++;
    *(list.front()+itop)=obj;
    
    stack_size++;
}

template <typename Type>
Type Linked_stack<Type>::pop() {
	// enter your implementation here

    
    if (stack_size==0)
    {
        throw underflow();
    }
    
    if(itop ==0)
    {
        Type temp = *(list.front() +itop);
        list.pop_front();
        itop=ARRAY_CAPACITY-1;
        --stack_size;
        return temp;
    }
    else
    {
    
        Type temp = *(list.front() +itop);
        stack_size--;
        itop--;
        return temp;
    
    }
}

// You will be required to modify this function in order to accomodate
// your implementation of a singly linked list in Project 1.

template <typename T>
std::ostream &operator<<( std::ostream &out, Linked_stack<T> const &stack ) {
	if ( stack.list.size() == 0 ) {
		out << "->0";
	} else if ( stack.list.size() == 1 ) {
		out << "->[ ";

		for ( int i = 0; i <= stack.itop; ++i ) {
			out << stack.list.front()[i] << " ";
		}

		out << "]->0";
	} else {
		out << "->";

		//for ( Single_node<T *> *ptr = stack.list.head(); ptr != nullptr; ptr = ptr->next() ) {
        for ( Double_node<T *> *ptr = stack.list.head(); ptr != nullptr; ptr = ptr->next() ) {

			out << "[ ";

			if ( ptr == stack.list.head() ) {
				for ( int i = 0; i <= stack.itop; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			} else {
				for ( int i = 0; i <= Linked_stack<T>::ARRAY_CAPACITY - 1; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			}

			out << "]->";
		}

		out << "0";
	}

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
