#include <iostream>
#include <fstream> //for file reading
#include <time.h>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList
{
private:
    struct Customer
    {
        // fields of customer
        string name;

        Customer *prev;
        Customer *next;

        // constructor
        Customer(string s, Customer *p = nullptr, Customer *n = nullptr)
        {
            name = s; // take in string name as parameter
            prev = p;
            next = n;

            cout << '\t' << name << " joined the line\n";
        }

        // default constructor
        Customer()
        {
            ifstream in("names.txt"); // open names.txt file
            if (!in.good())
            {
                cout << "ERROR opening text file to read names in.";
            }
            else
            {
                int randName = (rand() % 99); // generate random 0-98 int number to ignore in txt file
                for (int i = 0; i < randName; i++)
                    in.ignore(100, '\n');
                getline(in, name); // get string name after random ignore, assign directly to Customer
            }

            prev = nullptr;
            next = nullptr;

            cout << name << " joined the line";
        }
    };

    Customer *head;
    Customer *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void insert_after(string s, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Customer *newCustomer = new Customer(s);
        if (!head)
        {
            head = tail = newCustomer;
            return;
        }

        Customer *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp)
        {
            cout << "Position exceeds list size. Customer not inserted.\n";
            delete newCustomer;
            return;
        }

        newCustomer->next = temp->next;
        newCustomer->prev = temp;
        if (temp->next)
            temp->next->prev = newCustomer;
        else
            tail = newCustomer;
        temp->next = newCustomer;
    }

    void delete_name(string n)
    {
        if (!head)
            return;

        Customer *temp = head;

        while (temp && temp->name != n)
            temp = temp->next;

        if (!temp)
            return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1)
        {
            pop_front();
            return;
        }

        Customer *temp = head;

        for (int i = 1; i < pos; i++)
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next)
        {
            pop_back();
            return;
        }

        Customer *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string s)
    {
        Customer *newCustomer = new Customer(s); // make customer with string for name
        if (!tail)
            head = tail = newCustomer;
        else
        {
            tail->next = newCustomer;
            newCustomer->prev = tail;
            tail = newCustomer;
        }
        cout << s << " joined the line"; 
    }

    void push_front(string s)
    {
        Customer *newCustomer = new Customer(s);
        if (!head)
            head = tail = newCustomer;
        else
        {
            newCustomer->next = head;
            head->prev = newCustomer;
            head = newCustomer;
        }
    }

    void pop_front()
    {

        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        Customer *temp = head;

        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        cout << temp->name << " is served"; 
        delete temp;
    }

    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Customer *temp = tail;

        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            Customer *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print()
    {
        Customer *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << '\t' << current->name << '\n'; // print out all names of people in line, seperated by newlines
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() // if needed
    {
        Customer *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << '\t' << current->name << '\n';
            current = current->prev;
        }
        cout << endl;
    }
};

// prototypes
void simLoop(DoublyLinkedList);
void simulateMinute(DoublyLinkedList);
string getName();

// main***********************************
int main()
{
    srand(time(0));
    DoublyLinkedList list; // intialize doubly-linked list

    simLoop(list);

    return 0;
}

void simLoop(DoublyLinkedList list)
{
    const int MINUTES = 20, INITIAL_CUSTOMERS = 5; // 20 loops "minutes"

    cout << "Store opens: \n"; // begin application

    for (int i = 0; i < INITIAL_CUSTOMERS; i++) // when starting, fill with 5 initial customers
        list.push_back(getName());

    cout << "Resulting line: \n";
    list.print();

    for (int i = 0; i < MINUTES; i++)
    {
        cout << "Time step #" << i+2 << ": \n"; //start at time step 2
        simulateMinute(list);
    }
}

void simulateMinute(DoublyLinkedList list) // simulates one "minute run"
{
    //variables representing situations: 

    int a = rand()%100 + 1, b = rand()%100 + 1, c = rand()%100 + 1, d = rand()%100 + 1, e = rand()%100 + 1; //probabilities for each minute should are independent. 
    // A customer being helped at the beginning of the line and ordering their coffee is 40%
    if(a <= 40)
        list.pop_front(); //help first customer

    // A new customer joining the end of the line is 60%
    if(b <= 60) //new customer joins
        list.push_back(getName()); 

    // The customer at the end of the line deciding they don't want to wait and leaving is 20%
    if(c <= 20)
        

    // Any particular customer can decide they don't want to wait and leave the line: 10%


    // A VIP (very important person) customer with a Coffee House Gold Card gets to skip the line and go straight to the counter and order: 10%


}

string getName() // gets a random name from the txt file
{
    string buf;
    ifstream in("names.txt"); // open names.txt file
    if (!in.good())
    {
        cout << "ERROR opening text file to read names in.";
    }
    else
    {
        int randName = (rand() % 99); // generate random 0-98 int number to ignore in txt file
        for (int i = 0; i < randName; i++)
            in.ignore(100, '\n');
        getline(in, buf); // get string name after random ignore, assign directly to Customer
    }
    return (buf);
}