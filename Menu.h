
#ifndef MENU_H
#define MENU_H

#include <iostream> // for ostream
#include "Text.h"
using std::ostream;
using ElemType = Text;

class Menu 
    {
    private: // private data member representation
        int capacity;
        int count;
        Text top_message = " ";
        Text bottom_message = " ";
        ElemType * option_list{ nullptr }; // pointer to dynamic memory

    private:    // private facilitator method members representation
        void clear();  // resets count to zero, discarding all elements currently on the stack
        void deepCopy(const Menu & source); // deep copies source to *this
        void error(std::string msg) const;  // encapsulates our error handling policy
        void double_capacity();            // doubles the capacity of this stack

    public:
        Menu(); // default constructor
        // the "Big Three" ---------------------------------------------------
        Menu(const Menu & source); // copy constructor
        Menu & operator=(const Menu & source); // copy assignment
        virtual ~ Menu(); // destructor, don't leave objects on the heap without it!
        // -------------------------------------------------------------------
        explicit Menu(int size);

        void set_top_message(const ElemType&); // Set top messages
        Text get_top_message() const; // Set top messages
        void set_bottom_message(const ElemType&); // Set bottom messages
        Text get_bottom_message() const; // Get bottom messages
        void clear_top_message();
        void clear_bottom_message();
        int getCapacity(); // return the current capacity of the option_list
        int read_option_number(); // Displays menu and then reads and returns a valid option number
        ElemType toString() const; // return a string representation
        ElemType get(int k) const;

        // Implementation of stack ADT ---------------------------------------
        void push_back(ElemType e); // push_back a given element on the stack
        ElemType pop_back();        // remove stack top element and return a copy
        ElemType top() const;  // return the stack top element
        void insert(int index, const ElemType& inserted_txt); // inserts option at position index
        void remove(int index); // Removes an option from the list at given index

        // public facilitator member functions
        bool isEmpty() const; // Determines whether this menu’s option list is empty
        bool isFull() const;
        int size() const;

        void toStream(ostream& sout)const;  // writes option_list elements to a given output stream
    };

ostream& operator<<(std::ostream& sout, const Menu& ol);

#endif //MENU_H
