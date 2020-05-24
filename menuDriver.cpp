#include <iostream> // for cout and cin
#include "Text.h" // for Text class
#include "Menu.h" // for Menu class

// using-declarations
using std::cout;
using std::endl;

void demoText(); // demonstrates Text objects
void demoMenu(); // demonstrates Menu objects

int main()
{
//    demoText();
    demoMenu();
    return 0;
}

void demoText()
{ Text t1; // defalt constructor
Text t2("quick brown fox"); // conversion constructor
Text t3{ t2 }; // copy constructor
cout << "t1: " << t1 << endl; // operator<< overload
cout << "t2: " << t2 << endl;
cout << "t3: " << t3 << endl;

t1.append("The "); // append a given C-string to t1’s C-string
cout << "t1: " << t1 << endl;
t1.append(t2); // append t2’s C-string to t1’s C-string
cout << "t1: " << t1 << endl;

t2 = Text(" jumps over "); // assignment operator overload
cout << "t2: " << t2 << endl;

t3.assign("a lazy dog"); // assign a given C-string to t3’s C-string
cout << "t3: " << t3 << endl;

t1.append(t2); // assign t2’s C-string to t1’s C-string
cout << "t1: " << t1 << endl;
t1.append(t3); // append t3’s C-string to t1’s C-string
cout << "t1: " << t1 << endl;
return;
}

void demoMenu()
{
    int choice;
    Menu menu;
    menu.set_top_message("Choose your thirst crusher");
    menu.set_bottom_message("Enter a drink number");
    menu.push_back("Pepsi");
    menu.push_back("Apple juice");
    menu.push_back("Root beer");
    menu.push_back("Orange juice");
    menu.pop_back(); // remove the last option
    menu.insert(2, "Iced tea with lemon"); // this will be option 2
    choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;
    // WIP menu.remove(1);
}