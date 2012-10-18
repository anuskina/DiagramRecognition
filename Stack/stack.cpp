#include    "stack.h"
#include    <iostream>

using namespace std;

Stack::Stack()
{
    mTop	=	0;
}
Stack::~Stack()
{
    while(mTop	!=	0)
    {
        Item	*oldTop	=	mTop;
        mTop	=	oldTop->next;
        delete	oldTop;
    }
}

Stack&	Stack::push(const int &element)
{
    Item	*item	=	new	Item;
    item->next	=	mTop;
    item->data	=	element;
    mTop	=	item;
    return	*this;
}

int Stack::pop()
{
    if(isEmpty())
    {
        cout    <<  "Stack is empty";
        throw	StackException();
    }
    Item	*oldTop	=	mTop;
    mTop	=	oldTop->next;
    int	data	=	oldTop->data;
    delete	oldTop;
    return	data;
}

int Stack::peek()
{
    if(isEmpty())
    {
        cout    <<  "Stack is empty"    <<  endl;
        throw	StackException();
    }
    return mTop->data;
}

bool Stack::isEmpty()	const
{
    return	mTop	==	0;
}

void Stack::print()	const
{
    if(isEmpty())
    {
        cout    <<  "Stack is empty"    <<  endl;
    }
    Item	*myTop	=	mTop;
    while(myTop	!=	0)
    {
        Item	*temp	=	myTop;
        myTop	=	temp->next;
        cout    <<  temp->data;
    }
    cout    <<  endl;
}
