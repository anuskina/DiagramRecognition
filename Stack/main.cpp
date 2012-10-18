#include    <iostream>
#include    <stack.h>

using namespace std;

int main()
{
    Stack   *stack  =   new Stack;
    cout    <<  "1 - add an item to the stack"  <<  endl;
    cout    <<  "2 - remove an item from the stack" <<  endl;
    cout    <<  "3 - show top of the stack" <<  endl;
    cout    <<  "4 - print stack items" <<  endl;
    cout    <<  "5 - stack is empty?"   <<  endl;
    cout    <<  "6 - exit"  <<  endl;
    int menuItem    =   0;
    int item    =   0;
    while(menuItem  !=  6)
    {
        cout    <<  "Enter the item of menu"    <<  endl;
        cin >>  menuItem;
        switch(menuItem)
        {
        case    1:
            cout    <<  "Please, enter item you wish to add to the stack"   <<  endl;
            cin >>  item;
            stack->push(item);
            break;

        case    2:
            cout    <<  stack->pop()    <<  ' ' <<  "this item is removed from the stack"   <<  endl;
            break;
        case    3:
            cout    <<  stack->peek()    <<  ' ' <<  "this item on the top of stack"   <<  endl;
            break;
        case    4:
            stack->print();
            break;
        case    5:
            if(stack->isEmpty())
            {
                cout    <<  "Stack is empty"    <<  endl;
            }
            else
            {
                cout    <<  "Stack is not empty"    <<  endl;
            }
            break;
        case    6:
            return  0;
        }
    }
    stack->~Stack();
    return  0;
}

