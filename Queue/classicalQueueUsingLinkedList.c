/*
    ModRed

    Implementing Classical Queue using Linked List.

    enqueue() -> inserts elemets at end
    dequeue() -> removes element from the front (FIFO)
    peek()    -> peeks at the element at the front.
    __________________________________________________________

    The Idea Here Is Quite Simple.

    starting mei both front and end point to NULL since queue is empty

    then after enqueue(5) , note here that the function call parameters is just an example, not the actual parameter implemented in my program.

        FRONT 
        ^
        |
        5 -> NULL
        |
        V
        END
    
    then after enqueue(10)

        FRONT 
        ^
        |
        5 ->  10 -> NULL
               |
               V
              END
    
    and so on....

    dequeue() will just remove the first element and update the front node's addr
    
        FRONT 
        ^
        |
        10 -> NULL
        |
        V
        END
    
    peek() and traverse() mere hisab se is very intuitive and need not be explained.
    __________________________________________________________________________________

    Problems I faced implementing this? 
    None tbh. Quite easy to implement if you are comfy with Single Linked List.

    Improvements can be done by listing elements that have been dequeued or enqueued, 
    also better documentations maybe? lol.

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
}node;

void enqueue(node **front, node** end); //inserts element after the end node and updates end node
void dequeue(node **front, node** end); //deletes the front node and updates front node
void traverse(node*front,node*end); //traversal, simple enough
void peek(node *front); //top element peek i.e. the front element that will be dequeued 

int main()
{
    node* front = NULL;
    node* end = NULL;
    int ch;
    do
    {   
        printf("\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Traverse\n5. Exit\n\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            enqueue(&front,&end);
            printf("\nModified Queue:\n");
            traverse(front,end);
            break;
            case 2:
            dequeue(&front,&end);
            printf("\nModified Queue:\n");
            traverse(front,end);
            break;
            case 3:
            peek(front);
            break;
            case 4:
            traverse(front,end);
            break;
            case 5:
            exit(0);
            break;
            default:
            printf("Wrong Choice...");
            break;
        }
    }
    while(ch != 5);
    
    return 1;
}

void enqueue(node **front, node** end)
{   
    int data;
    printf("Enter Data: ");
    scanf("%d",&data);
    if(*front == NULL && *end == NULL)
    {
        //empty stack
        *end = (node*)malloc(sizeof(node));
        (*end)->data = data;
        (*end)->next = NULL;
        *front = *end;
    }
    else
    {
        node* newNode = (node*)malloc(sizeof(node));
        newNode->data = data;

        //updates the end pointer ka next to have the new element node
        (*end)->next = newNode;
        //since insert at last hai toh NULL toh karwana he padega na bhai.
        newNode->next = NULL;
        //updates the end pointer to newNode
        *end = newNode;
    }
}
void dequeue(node **front, node** end)
{
    if(*front == NULL && *end == NULL)
    {
        printf("Underflow, Stack is already empty");
        return;
    }

    node *temp = *front;
    (*front) = (*front)->next;
    free(temp);
    temp = NULL;
    if (*front == NULL)
    {
        *end = NULL; //after dequeueing the last elemtent dangling pointers avoid karne ke liye
    }
}
void traverse(node*front,node *end)
{
    node* temp = front;

    if(front == NULL && end == NULL)
    {
        printf("Queue is Empty...");
        return;
    }

    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        if(temp == front)
        {
            printf(" --> FRONT\n");
        }
        else if(temp == end)
        {
            printf(" --> END\n");
        }
        else
        {
            printf("\n");
        }
        temp = temp->next;
    }
}
void peek(node *front)
{
    if(front==NULL)
    {
        printf("Empty Queue");
    }
    else
    {
        printf("%d -> FRONT TOP",front->data);
    }
    printf("\n");
}