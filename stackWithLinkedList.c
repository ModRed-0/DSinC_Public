//ModRed
/*
Implementing Queue using Linked List:

ok so the way i've implemented a stack is like follows:

initially there are no elements in stack so top is NULL;
_________________________________________________________________________-
then when pushed, a node is created lets say with value 5.
so now our stack looks like : 

top
 |
 V
 5 -> NULL; 
_________________________________________________________________________-
now the traversal() and peek() functions will be pretty clear to anyone who knows basic Linked List,
so won't be elaborating here.
_________________________________________________________________________-
push() -> after the inital push() of inserting first element, 
push() will work the same as insertion at the beginning of a Linked List.
so suppose we wanna insert an element with value 10, our stack with Linked List implementation will look like:

top
 |
 V
 10 -> 5 -> NULL; 

 and so on.....
_________________________________________________________________________-
pop() -> is basically Linked List's delete from start ka implementation.
so after a pop() our stack will look like:

top
 |
 V
 5 -> NULL; 

 another pop will give;

top
 |
 V
 NULL; 

 another pop() will now show the underflow message.
__________________________________________________________________________-

The two major issues I faced while implementing this was the assignment of:
*top = newNode; i did newNode = *top instead lol;  
in the push() function.
yeah, yeah, ik ik. stupid error. my bad.

another error i made was 
while(temp->next != NULL) instead of the correct while(temp != NULL) in the traverse() function

yeah that's it ig.

*/
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node* next;
}node;

void pop(node** top); //pops the top element
void push(node **top);
int peek(node *top);
void traverse(node** top);

int main()
{   
    int ch = 0;
    node *top = NULL;
    do
    {
        printf("1: Push\n2: Pop\n3. Peek\n4. View Stack\n5. Exit\n\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            push(&top);
            printf("\n");
            break;
            case 2:
            pop(&top);
            printf("\n");
            break;
            case 3:
            peek(top);
            printf("\n");
            break;
            case 4:
            traverse(&top);
            printf("\n");
            break;
            case 5:
            exit(0);
            break;
            default:
            printf("Wrong input!!");
            printf("\n");
        }
    }while(ch!=5);

    return 0;
}

void pop(node** top)
{
    //underflow
    if((*top) == NULL)
    {
        printf("Stack is already empty!! Underflow.");
        return;
    }
    //delete linked list node from the beginning of the list.
    node* temp = *top;
    *top = (*top)->next;
    free(temp);
    printf("\n");
}
void push(node **top)
{   
    int data;
    printf("Enter Data: ");
    scanf("%d",&data);
    //this case is to handle the insertion of the first element in the stack
    //since starting mei we pointed top to NULL in main()
    //we need to assign memory to the node and handle the rest.
    //this will also handle cases where the stack is empty after consecutive pop()'s and the stack is empty.
    if((*top) == NULL)
    {   
        *top = (node*) malloc(sizeof(node));
        (*top)->data = data; 
        (*top)->next = NULL;
    }
    else
    {   
        //if stack is not empty 
        node* newNode = (node*) malloc(sizeof(node));
        newNode->data = data;
        newNode->next = (*top);
        *top = newNode; //error Prone area lol
    }
    printf("\n");
}
int peek(node *top)
{
    printf("%d --> TOP\n",top->data);
    printf("\n");
}
void traverse(node** top)
{   
    node *temp = *top;
    if(temp == NULL)
    {
        printf("Stack is empty!!");
        return;
    }
    while(temp != NULL)
    {   
        if(temp == *top)
        {
            printf("%d --> TOP\n",(*top)->data);
        }
        else
        {
            printf("%d\n",temp->data);
        }
        temp = temp->next;
    }
    printf("\n");
}