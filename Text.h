#ifndef TEXT_H
#define TEXT_H

#include <iostream> // for ostream
using std::ostream;

 class Text
 {
 private:
    char* pStore{ nullptr }; // pointer to dynamic memory
 public:
     Text(); // default constructor
     Text(const char*); // a conversion constructor

 // the "Big Three" ---------------------------------------------------
     Text(const Text&); // copy constructor
     virtual ~Text(); // destructor
     const Text& operator=(const Text&); // assignment operator overload
 // -------------------------------------------------------------------

     const char * getCstring() const; // returns pStore as a const pointer

     void setCstring(char * str); // to change the string

     void append(const char*); // Appends a C-string to this object, extending its contents

     void append(const Text&); // Appends txt’s text to this object, extending its contents

     void assign(char*); // Assigns a C-string to this object, replacing its current contents

 // this facilitator method writes to the supplied output stream sout
    void write(ostream& sout) const; // const means that write cannot modify *this
 };

 ostream& operator<<( ostream &, const Text& ); // no param names required here
 #endif