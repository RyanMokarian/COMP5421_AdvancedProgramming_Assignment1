// To Do:
// Change string to cstring in error method

#include <iostream> // for ostream
#include <cstdlib>
#include <cstring>
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

#include "Menu.h"
#include "Text.h"

 // Default constructor.
 // Initializes top/bottom messages to empty strings,
 // the options list to dynamic array of capacity 1, and count to 0.

 Menu::Menu()
{
    this->capacity = 1;
    this->count = 0;
    option_list = new ElemType[getCapacity()+1]; // first, allocate memory,
    // including one extra byte for the null byte
    for (int i = 0; i < getCapacity(); i++) {
        option_list[i] = ElemType();
    }
}

// the "Big Three" ---------------------------------------------------
// copy constructor
Menu::Menu(const Menu & source)
{
    deepCopy(source);
}
// copy assignment
Menu & Menu::operator=(const Menu & source)
{
    if( this != &source)
    {
        delete[] this -> option_list; // release memory currently in use by lhs operand
        deepCopy(source); // deep copy source to *this
    }
    return *this;
}
// destructor, release objects on the heap
Menu::~ Menu(){ delete[] option_list;}
// End of the "Big Three"---------------------------------------------

Menu::Menu(int size) : count{0}, capacity{size}, option_list{new ElemType[size]}{}

// Implementation of stack ADT ---------------------------------------
// push_back a given element on the stack
void Menu::push_back(ElemType e)
{
    if(full()) double_capacity();
    option_list[count] = e;
    count++;
}
// remove stack top element and return a copy
ElemType Menu::pop_back()
{
    if(this->empty()) this->error("Stack underflow");
    ElemType temp = option_list[--count];
    return temp;
}
// return the stack top element
ElemType Menu::top() const
{
    if(this->empty()) this->error("Stack underflow");
    return this->option_list[this->count-1];
}
// public facilitator member functions
bool Menu::empty() const { return count == 0;}
bool Menu::full() const { return count == capacity;}
int Menu::size() const { return this->count;}
// End of implementation of stack ADT----------------------------------

// Set and get opening message
void Menu::set_top_message(const Text& m) {this->top_message = m;}
Text Menu::get_top_message() const {return top_message;}
// Set and get closing message
void Menu::set_bottom_message(const Text& m) {this->bottom_message = m; }
Text Menu::get_bottom_message() const {return bottom_message;}
// get capacity
int Menu::getCapacity() {return capacity;}
// Displays this menu and then reads and returns a valid option number
int Menu::read_option_number()
{
    int choice;
    cout <<*this << "  ";
    cin >> choice;
    while (choice<1 || choice > this->count) {
        cout << "Invalid choice " << choice << ". It must be in the range [1, " << this->count << "]\n";
        cout << *this << "  ";
        cin >> choice;
    }
    return choice;
}
// Inserts option at position index, shifting all options at or past index over to the right by one position.
void Menu::insert(int index, const char* inserted_txt)
{
    ElemType * temp_stack = new ElemType[index]; // index-1

    for (int i = 0; i<index; i++)
    {
        temp_stack[i] = this->option_list[count-1]; // this->top();
        this->pop_back();
    }
    this->push_back(inserted_txt);
    for (int j = 0; j<index; j++)
    {
        this->push_back(temp_stack[index-j-1]);
    }
    delete[] temp_stack;
    cout << "Option inserted successfully!\n";
}
// write option_list elements to a given output stream
void Menu::toStream(ostream& sout)const
{
   const char * tpMsg = get_top_message().getCstring();
   if (strcmp (tpMsg," ") != 0 ) sout << "\n" << get_top_message();
   else sout << "\n";
    for(int k=0; k < count; ++k)
   {
       sout << "\n   " << k+1 << ": " << option_list[k];
   }
    const char * bmMsg = get_bottom_message().getCstring();
    if (strcmp (bmMsg," ") != 0 ) sout << "\n" << get_bottom_message() << "\n";
   sout << "??";
}
// private method members representation -------------------------------------
// clear
void Menu::clear() {count = 0;}
// deep copy
void Menu::deepCopy(const Menu & source)
{
    this->capacity = source.capacity;
    this->count = source.count;
    option_list = new ElemType[source.capacity];
    for(int k =0; k < source.capacity; k++)
    {
        option_list[k] = source.option_list[k];
    }
}
// error
void Menu::error(std::string msg)const
{
    std::cerr << msg << "\n";
    exit(EXIT_FAILURE);
}
// Double the option_list capacity
void Menu::double_capacity()
{
    int twice_cap = 2 * this->getCapacity();  // new desired capacity
    Text * temp = new Text[twice_cap];         // allocate space twice the current capacity

    for (std::size_t i = 0; i < this->getCapacity(); i++) // assign current option list to temp, element by element
    {
        temp[i] = this->option_list[i];   // Text's operator= performs the assignment
    }
    delete[] this->option_list;         // release current storage
    this->option_list = temp;          // point at new storage
    this->capacity = twice_cap;     // adjust capacity
}
// End of private method methods representation -------------------------------
// End of public and private methods representation ---------------------------

// a free function for sout
ostream& operator<<(std::ostream& sout, const Menu& optLst)
{
    optLst.toStream(sout);
    return sout;
}