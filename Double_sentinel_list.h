
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
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"


template <typename Type>
class Double_sentinel_list {
	private:
		Double_node<Type> *list_head;
		Double_node<Type> *list_tail;
		int list_size;

	public:
		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node<Type> *head() const;
		Double_node<Type> *tail() const;

		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();
		Type pop_back();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list() {
    list_size = 0;
    list_head = new Double_node<Type>;
    list_tail = new Double_node<Type>;
    
    list_head->previous_node=nullptr;
    list_head->next_node=list_tail;
    list_tail->previous_node=list_head;
    list_tail->next_node=nullptr;
    
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ), 
list_tail( nullptr ),
list_size( 0 ) {
	// enter your implementation here
    Double_node<Type> *phead = new Double_node<Type>;
    Double_node<Type> *ptail = new Double_node<Type>;
    list_size=0;
    
    list_head=phead;
    list_tail=ptail;
    
    list_head->next_node=list_tail;
    list_tail->previous_node=list_head;
    list_head->previous_node=0;
    list_tail->next_node=0;
    
    Double_node<Type> *ptr=list.head()->next();
    while (ptr->element != NULL)
    {
        push_back(ptr->retrieve());
        ptr=ptr->next_node;
        
    }
    
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    //enter your implementation here
    while ( !empty() )
    {
        pop_back();
    }
    
    delete list_head;
    delete list_tail;

}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	// enter your implementation here
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// enter your implementation here
	return list_size==0;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// enter your implementation here
    if (list_size>0)
        return list_head->next()->retrieve();
    else
        throw underflow();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// enter your implementation here
    if (list_size>0)
        return list_tail->previous()->retrieve();
    else
        throw underflow();
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {
	// enter your implementation here
	return list_head;
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {
	// enter your implementation here
	return list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// enter your implementation here
    int count=0;
    for (Double_node<Type> *ptr = list_head; ptr != 0; ptr = ptr->next())
    {
        if((ptr->retrieve())==(obj))
            count++;
    }
	return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> const &rhs ) {
	Double_sentinel_list<Type> copy( rhs );

	swap( copy );
	
	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	// enter your implementation here
    
    Double_node<Type> *pNew;
    pNew = new Double_node<Type>;
    
    pNew->element=obj;
    pNew->next_node=list_head->next_node;
    pNew->previous_node=list_head;
    pNew->next_node->previous_node=pNew;
    list_head->next_node=pNew;
    list_size++;
}


template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// enter your implementation here
    
    Double_node<Type> *pNew;
    pNew = new Double_node<Type>;
    
    pNew->element=obj;
    pNew->previous_node=list_tail->previous_node;
    pNew->next_node=list_tail;
    pNew->previous_node->next_node=pNew;
    list_tail->previous_node=pNew;
    list_size++;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_front() {
	// enter your implementation here
    if ( empty() ) {
        throw underflow();
    }
    
    
    Double_node <Type> e = front();
    Double_node <Type> *ptr = list_head->next_node;
    list_head->next_node = list_head->next_node->next_node;
    list_head->next_node->previous_node=list_head;
    delete ptr;
    list_size--;
    return e.retrieve();
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {
	// enter your implementation here
    if ( empty() ) {
        throw underflow();
    }
    
    
    Double_node <Type> e = back();
    Double_node <Type> *ptr =list_tail->previous_node;
    list_tail->previous_node=list_tail->previous_node->previous_node;
    list_tail->previous_node->next_node=list_tail;
    delete ptr;
    list_size--;
    return e.retrieve();
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// enter your implementation here
    for (Double_node<Type> *ptr = list_head; ptr != 0; ptr = ptr->next())
    {
        if((ptr->element)==(obj))
        {
            Double_node <Type> *temp;
            temp=ptr;
            ptr->next_node->previous_node=ptr->previous_node;
            ptr->previous_node->next_node=ptr->next_node;
            delete temp;
            list_size--;
            return 1;
        }
    }
	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.head() || ptr == list.tail() ) {
			out << "->S";
		} else {
			out << "->" << ptr->retrieve();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.head() || ptr == list.tail() ) {
			out << "->S";
		} else {
			out << "->" << ptr->retrieve();
		}
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
