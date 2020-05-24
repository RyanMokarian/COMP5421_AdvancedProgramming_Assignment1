// Provides definitions for the declarations made in Text.h
#include <iostream>
#include <cstring>
#include "Text.h"

// using-declarations
using std::cout;
using std::endl;
using std::strcpy;

 // conversion constructor
 Text::Text(const char *pCstr)
 {
 pStore = new char[strlen(pCstr) + 1]; // first, allocate memory,
 // including one extra byte for the null byte
 strcpy(pStore, pCstr); // next, copy
 }

 // default constructor
 Text::Text() : Text("") // delegating to the conversion constructor above
 {
 }

 // copy constructor; also delegating to our conversion constructor above
 Text::Text(const Text& txt) : Text(txt.pStore)
 {
 }

 // destructor
 Text::~Text()
 {
 delete[] pStore; // release memory
 this->pStore = nullptr; // defensive programming
 }

 // assignment operator overload
 const Text& Text::operator=(const Text &txt)
 {
 // handle self-assignment (this == &m)
 if (this != &txt) // do nothing on self-assignment
     {
     // release dynamic storage,
     // currently used by the left-hand side operand
     delete[] this->pStore;

     // now allocate storage of appropriate size
     this->pStore = new char[strlen(txt.pStore) + 1];
     strcpy(this->pStore, txt.pStore); // copy
     }
 return *this; // apart from making the compiler happy,
 // what’s the purpose of returning *this?
 }

 // returns pStore as a const pointer
 const char * Text::getCstring() const {return pStore;}

 // Setter
 void Text::setCstring(char * str)
{
    this->pStore =  str;
}

// Appends a C-string to this object, extending its contents
 void Text::append(const char* pCstr)
{
    const char* strg1{ getCstring() };
    const char* strg2{ pCstr };
    char* strgsConcat{ new char[strlen(strg1) + strlen(strg2) + 1] };
    strgsConcat = strcpy(strgsConcat, strg1);
    strgsConcat = strcat(strgsConcat, strg2);
    setCstring (strgsConcat);
}

// Appends txt’s text to this object, extending its contents
 void Text::append(const Text& txt)
 {
     const char* strg1{ getCstring() };
     const char* strg2{ txt.getCstring() };
     char* strgsConcat{ new char[strlen(strg1) + strlen(strg2) + 1] };
     strgsConcat = strcpy(strgsConcat, strg1);
     strgsConcat = strcat(strgsConcat, strg2);
     setCstring (strgsConcat);
 }

// Assigns a C-string to this object, replacing its current contents
 void Text::assign(char* pCstr)
 {
     setCstring (pCstr);
 }

 // sout
 void Text::write(ostream& sout) const // const means that write cannot modify *this
 {
 sout << this->pStore << endl;
 }

 // here we are overloading operator<< as a free (or top-level) function
 ostream& operator<<(ostream & sout, const Text& txt)
 {
     sout << txt.getCstring();
 return sout;
 }
