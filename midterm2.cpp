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
        //fields of customer
        int data;

        Customer *prev;
        Customer *next;

        //constructor
        Customer(int val, Customer *p = nullptr, Customer *n = nullptr)
        {
            data = val;
            prev = p;
            next = n;
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

    void insert_after(int value, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Customer *newCustomer = new Customer(value);
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

    void delete_val(int value)
    {
        if (!head)
            return;

        Customer *temp = head;

        while (temp && temp->data != value)
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

    void push_back(int v)
    {
        Customer *newCustomer = new Customer(v);
        if (!tail)
            head = tail = newCustomer;
        else
        {
            tail->next = newCustomer;
            newCustomer->prev = tail;
            tail = newCustomer;
        }
    }

    void push_front(int v)
    {
        Customer *newCustomer = new Customer(v);
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
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse()
    {
        Customer *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

//prototypes
void simulateMinute(DoublyLinkedList);


int main()
{
    //my code
    const int MINUTES = 20; //20 loops "minutes"
    srand(time(0));

    DoublyLinkedList list; //intialize doubly-linked list
    list.push_front(3); //value for customer

    for(int i = 0; i < MINUTES; i++)
    {
        simulateMinute(list);
    }


    return 0;
}

void simulateMinute(DoublyLinkedList list) //simulates one "minute run"
{
    list.print(); //test
}