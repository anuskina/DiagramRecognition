#ifndef STACK_H
#define STACK_H

struct	Item
{
    int	data;
    Item	*next;
};

class Stack
{
public:
    Stack();
    ~Stack();
    Stack	&push(const	int	&item);
    int pop();
    int	peek();
    bool    isEmpty()	const;
    void	print()	const;
private:
    Item	*mTop;
};

class	StackException{
};
#endif // STACK_H
