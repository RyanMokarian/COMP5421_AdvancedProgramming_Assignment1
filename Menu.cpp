
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
    option_list = new ElemType[getCapacity()]; // allocate memory
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
        this->deepCopy(source); // deep copy source to *this
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
    if(this->isFull()) double_capacity();
    option_list[count] = e;
    count++;
}
// remove stack top element and return a copy
ElemType Menu::pop_back()
{
    if(this->isEmpty()) this->error("Stack underflow");
    ElemType temp = option_list[--count];
    return temp;
}
// return the stack top element
ElemType Menu::top() const
{
    if(this->isEmpty()) this->error("Stack underflow");
    return this->option_list[this->count-1];
}
// public facilitator member functions
bool Menu::isEmpty() const { return this->size() == 0;}
bool Menu::isFull() const { return this->size() == this->capacity;}
int Menu::size() const { return this->count;}
// End of implementation of stack ADT----------------------------------

// Set and get opening message
void Menu::set_top_message(const Text& m) {this->top_message = m;}
Text Menu::get_top_message() const {return top_message;}
// Set and get closing message
void Menu::set_bottom_message(const Text& m) {this->bottom_message = m; }
Text Menu::get_bottom_message() const {return bottom_message;}
// clearing messages
void Menu::clear_top_message() { this->top_message = "";}
void Menu::clear_bottom_message() { this->bottom_message = "";}

// get capacity
int Menu::getCapacity() {return capacity;}

// Displays this menu and then reads and returns a valid option number
int Menu::read_option_number()
{
    int choice;
    cout <<*this << "  ";
    cin >> choice;
    if (this->count == 0)
    {
        return choice;
    }
    else
    {
        while (choice < 1 || choice > this->count) {
            cout << "Invalid choice " << choice << ". It must be in the range [1, " << this->count << "]\n";
            cout << *this << "  ";
            cin >> choice;
        }
        return choice;
    }
}

// Returns a Text object storing a string representation of this menu
ElemType Menu::toString() const
{
    ElemType strRep;
    strRep.append("\n");

    const char * tpMsg = get_top_message().getCstring();
    if (strcmp (tpMsg," ") != 0 )
    {
        strRep.append(top_message);
        strRep.append("\n");
    }
    for (int k = 0; k < this->count; ++k)
    {
        strRep.append("  ");
        strRep.append(std::to_string(k + 1).c_str());
        strRep.append(": ");
        strRep.append(option_list[k]);
        strRep.append("\n");
    }
    const char * bmMsg = get_bottom_message().getCstring();
    if (strcmp (bmMsg," ") != 0 )
    {
        strRep.append(bottom_message);
        strRep.append("\n");
    }
    strRep.append("??");

    return strRep;
}

// get option_list
ElemType Menu::get(int k) const { return this->option_list[k];}

// Inserts option at position index, shifting all options at or past index over to the right by one position.
void Menu::insert(int index, const ElemType & inserted_txt)
{
    // increase the capacity if the option goes to the end
    if(this->isFull()) double_capacity();

    // check if the option will be in the range
    while (index < 1 || index > (this->count) + 1)
    {
        cout << "Invalid menu position " << index <<
        ". It must be in the range [1, " << (this->count) << "]\n";
        cout << "Enter a valid menu position\n  ";
        cin >> index;
    }

    // shifting all options at or past index over to the right by one position
    for (int i = this->count; i >= index; i--)
    {
        this->option_list[i] = this->option_list[i - 1];
    }
    // inserting element at position index
    this->option_list[index - 1] = inserted_txt;

    this->count++;
    cout << "Option inserted successfully!\n";
}

// Removes an option from the list at given index
void Menu::remove(int index)
{
    // check if the option will be in the range
    while (index < 1 || index > (this->count))
    {
        cout << "Invalid menu position " << index <<
             ". It must be in the range [1, " << (this->count) << "]\n";
        cout << "Enter a valid menu position\n  ";
        cin >> index;
    }

    // shifts all options to the right of index left by one position.
    for (int i = index; i < count; i++)
    {
        this->option_list[i-1] = this->option_list[i];
    }
    this->count--;
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
    if (strcmp (bmMsg," ") != 0 ) sout << "\n" << get_bottom_message();
   sout << "\n??";
}

// private method members representation -------------------------------------
// clear
void Menu::clear() {count = 0;}
// deep copy
void Menu::deepCopy(const Menu & source)
{
    this->capacity = source.capacity;
    this->count = source.size();
    this->top_message = source.get_top_message();
    this->bottom_message = source.get_bottom_message();
    option_list = new ElemType[source.capacity];
    for(int k =0; k < source.count; k++)
    {
        this->option_list[k] = source.get(k);
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
ostream& operator<<(ostream& sout, const Menu& optLst)
{
    optLst.toStream(sout);
    return sout;
}