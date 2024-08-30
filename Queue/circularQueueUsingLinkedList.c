/*
    ModRed

    Implementing Circular Queue using  Circular Linked List.

    enqueue() -> inserts elemets at end
    dequeue() -> removes element from the front (FIFO)
    peek()    -> peeks at the element at the front.
    __________________________________________________________

    The Idea Here Is Quite Simple.

    starting mei both front and end point to NULL since queue is empty

    
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

void enqueue(node** front, node **end);
void dequeue(node** front, node **end);
void traversal(node* front, node *end);
void peek(node* front);

int main()
{
    int ch;
    node *front = NULL;
    node *end = NULL;

    do
    {   
        printf("\n1. Enqueue\n2. Dequeue\n3. Traverse\n4. Peek\n5. Exit\n\n");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
            enqueue(&front,&end);
            printf("\nModified Queue:\n");
            traversal(front,end);
            break;
            case 2:
            dequeue(&front,&end);
            printf("\nModified Queue:\n");
            traversal(front,end);
            break;
            case 3:
            traversal(front,end);
            break;
            case 4:
            peek(front);
            break;
            case 5:
            exit(0);
            break;
            default:
            printf("Wrong choice....");
            break;
        }
    } while(ch!=5);
    

    return 0;
}

void enqueue(node** front, node **end)
{   
    int data;
    printf("Enter Data: ");
    scanf("%d",&data);
    if(*front == NULL && *end == NULL) //queue is empty
    {   
        *end = (node*)malloc(sizeof(node));
        (*end)->data = data;
        (*end)->next = *end;
        *front = *end;
        return;
    } 
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    (*end)->next = newNode;
    newNode->next = *front;
    *end = newNode; //error was here, rectified now.
}
void dequeue(node** front, node **end)
{   
    if(*front == NULL && *end == NULL)
    {
        printf("Queue is empty....Underflow.");
        return;
    }

    if(*front == *end)
    {
        free(*front);
        *front = NULL;
        *end = NULL;
        return;
    }

    node* temp = (*front);
    *front = (*front)->next;
    (*end)->next = *front;
    free(temp);
    temp = NULL;
}
void traversal(node* front, node *end)
{   
    if(front == NULL && end == NULL)
    {
        printf("Empty Queue....");
        return;
    }
    node* temp = front;
    do
    {   
        printf("%d",temp->data);
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
    }while(temp != front);
}
void peek(node* front)
{
    if(front == NULL)
    {
        printf("Queue is empty!!");
        return;
    }
    printf("%d --> FRONT", front->data);
}