/*
    ModRed

    Implementing Circular Queue using  Circular Linked List.

    enqueue() -> inserts elemets at end
    dequeue() -> removes element from the front (FIFO)
    peek()    -> peeks at the element at the front.
    __________________________________________________________

    The Idea Here Is Quite Simple.

    starting mei both front and end point to NULL since queue is empty

    {NOTE: not the literal function arguement here, just for simpler illustration}
    enqueue(5) will result in;

    (f)5(e)
    ^    |
    |____|

    front and end both are at 5 only.

    wow, that was hard to make. yeah, im !not making more diagrams.

    enqueue(10); front is 5 and end is 10
    (f)5 --> (e)10
    ^            |
    |____________|

    enqueue(15);
    (f)5 --> 10 --> 15(e)
    ^                |
    |________________|

    dequeue();
    (f)10 --> 15(e)
    ^            |
    |____________|

    dequeue();
    (f)15(e)
    ^     |
    |_____|

    and so on.......
    

    peek() and traversal() mere hisab se is very intuitive and need not be explained.
    __________________________________________________________________________________

    Problems I faced implementing this? 
    since i directly jumped to circular LL without studying the theory first
    took me some time to figure things out by trial and error, but overall no issues tbh.

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

void enqueue(node** front, node **end); //inserts element from end
void dequeue(node** front, node **end); //deletes element from start
void traversal(node* front, node *end); //traverses the queue
void peek(node* front); //front element that will be dequeued if needed.

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
        //if queue is empty then end node will point to itself
        (*end)->next = *end;
        //front will point to end since 1 node he hai queue mei
        *front = *end;
        return;
    } 
    //making a new node here below
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    //yaha pe removing the circular property of end-->front and putting end --> newNode connection below
    (*end)->next = newNode;
    //yaha pe reintroducing the circular property below newNode will now point to front
    newNode->next = *front;
    *end = newNode; //error was here, rectified now. update end to newNode
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
        //dequeueing when only 1 element there.
        free(*front);
        *front = NULL;
        *end = NULL;
        return;
    }
    //temp to free the node and delete it
    node* temp = (*front);
    //updating front to the next node
    *front = (*front)->next;
    //end->next should point to the new front since the circular LL was updated (1st node deleted)
    (*end)->next = *front;
    //temp delete kar diya and dangling pointer handle kar diya
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
    //took some time to decide on do..while instead of just while, did weird shit with while() loop
    //but nhi hua while se bas. i think the flag method would work, but kaun karega ab? try kar lo khud se
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
