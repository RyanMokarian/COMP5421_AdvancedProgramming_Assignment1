#include <iostream> // for cout and cin
#include "Text.h" // for Text class
#include "Menu.h" // for Menu class

// using-declarations
using std::cout;
using std::cin;
using std::endl;

void demoText(); // demonstrates Text objects
void demoMenu(); // demonstrates Menu objects

int main()
{
    cout << "\ndemoMenu is presented:\n" << endl;
    demoMenu();
    cout << endl;

    cout << "\ndemoText is presented:\n" << endl;
    demoText();
    cout << endl;

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
}

void demoMenu()
{
    int choice;
//1. Create an empty menu
    Menu menu;

//2. Print an empty menu:
    cout << menu << endl;

//3. Display the menu and read user's input:
    choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;

//4. Add an option to our menu:
    menu.push_back("Pepsi");
    cout << menu << endl;

//5. Let's add couple of more options to our menu:
    menu.push_back("Apple juice");
    menu.push_back("Root beer");
    choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;

//6. Let's setup the top and bottom message:
    menu.set_top_message("Choose your thirst crusher");
    menu.set_bottom_message("Enter a drink number");
    cout << menu << endl;

//7. Let's remove the last option and then insert a new option at number 2:
    menu.pop_back(); // remove the last option
    menu.insert(2, "Iced tea with lemon"); // this will be option 2
    choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;

//8. The menu object let's you remove an option by option number:
    menu.pop_back();
    menu.remove(1); // remove the last option
    cout << menu << endl; // remove the first option

//9. The following code segment removes the only remaining option, leaving the menu with an empty option list:
    menu.pop_back();
    cout << menu << endl;

//10. Here is our final example:
    menu.clear_bottom_message();
    menu.set_top_message("Who Says You Can't Buy Happiness?\n"
                         "Just Consider Our Seriously Delicious Ice Cream Flavors");
    menu.set_bottom_message("Enter the number of your happiness! ");
    menu.push_back("Bacon ice cream!");
    menu.push_back("Strawberry ice cream");
    menu.push_back("Vanilla ice cream");
    menu.push_back("Chocolate chip cookie dough ice cream");
    // cout << menu.toString(); // to test the toString method
    choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;
}