/*
    ModRed

    1. insertionAtHead() − add an element at the beginning of the list.
    2. deletionAtHead() − delete an element at the beginning of the list.
    3. insertAtLast() - add an element in the end of the list.
    4. deleteAtLast() − delete an element from the end of the list.
    5. insertAfter() − add an element after an item of the list.
    6. traverse() − Traverse and display the complete list in forward manner.
    7. search() − search an element using given key / data item.
    8. delete() − delete an element using given key / data item.

*/
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node* next; 
}node;
void insertionAtHead(node** head);
void deletionAtHead(node** head);
void insertionAtLast(node** head);
void deletionAtLast(node** head);
void insertAfter(node** head);
void traverse(node* head);
void search(node* head);
void delete(node** head);

int main()
{   
    int ch;
    node *head = NULL;
    do
    {
        printf("\n1. insertionAtHead()\n2. deletionAtHead()\n3. insertAtLast()\n4. deleteAtLast()\n5. insertAfter()\n6. traverse()\n7. search() \n8. delete()\n9. exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            insertionAtHead(&head);
            printf("Modified LL: \n");
            traverse(head);
            break;
            case 2:
            deletionAtHead(&head);
            printf("Modified LL: \n");
            traverse(head);
            break;
            case 3:
            insertionAtLast(&head);
            printf("Modified LL: \n");
            traverse(head);
            break;
            case 4:
            deletionAtLast(&head);
            printf("Modified LL: \n");
            traverse(head);
            break;
            case 5:
            insertAfter(&head);
            printf("Modified LL: \n");
            traverse(head);
            break;
            case 6:
            traverse(head);
            break;
            case 7:
            search(head);
            break;
            case 8:
            delete(&head);
            printf("Modified LL: \n");
            traverse(head);
            break;
            case 9:
            exit(0);
            break;
            default:
            printf("Wrong choice");
            break;
        }
        printf("\n");
    }
    while(ch!=9);
    return 0;
}

void insertionAtHead(node** head)
{   
    node* NewNode = (node*)malloc(sizeof(node));
    int data;
    printf("Enter Data: ");
    scanf("%d",&data);
    NewNode->data = data;

    if(*head == NULL)
    {
        *head = NewNode;
        NewNode->next = NULL;
        return;
    }
    NewNode->next = *head;
    *head = NewNode;

    printf("\n");

}
void deletionAtHead(node** head)
{
    if(*head == NULL)
    {
        printf("Linked List is empty....");
        return;
    }
    node* temp = *head;
    *head = (*head)->next;
    free(temp);
    temp = NULL;

    printf("\n");
}
void insertionAtLast(node** head)
{
    node* newNode =(node*)malloc(sizeof(node));
    int data;
    printf("Enter Data: ");
    scanf("%d",&data);
    newNode->data = data;

    if(*head == NULL)
    {
        *head = newNode;
        (*head)->next = NULL;
        return;
    }
    node *temp = *head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = NULL; 
    printf("\n");
}
void deletionAtLast(node** head)
{

    if(*head == NULL)
    {
        printf("Empty Linked List....");
        return;
    }

    if((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
        return;
    }
    node* temp = *head;

    while((temp->next)->next != NULL)
    {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
    printf("\n");
}
void insertAfter(node** head)
{   
    int position;
    printf("Enter the Position you wish to insert your node at: ");
    scanf("%d",&position);

    if(position == 1)
    {
        insertionAtHead(head);
        return;
    }
    
    int i = 1;
    node *newNode = (node*)malloc(sizeof(node));
    printf("Enter Data: ");
    scanf("%d", &newNode->data);
    node* temp = *head;
    while(i != position-1)
    {
        temp = temp->next;
        i++;
        if(temp == NULL)
        {
            printf("Position out of bound...\n");
            return;
        }
    }
    newNode->next = temp->next;
    temp->next = newNode;
}
void traverse(node* head)
{   
    if(head == NULL)
    {
        printf("Linked List is empty\n");
        return;
    }
    
    node* temp = head;
    printf("HEAD --> %d ", temp->data);
    temp = temp->next;

    while(temp != NULL)
    {   
        printf("--> %d ", temp->data);
        temp = temp->next;
    }
    printf("--> NULL");
    printf("\n");
}

void search(node* head)
{
    int key;
    printf("Enter the element you wish to search for: ");
    scanf("%d",&key);

    node *temp = head;
    int i = 1,flag = 0;
    while(temp != NULL)
    {   
        if(temp->data == key)
        {   
            if(flag == 0) printf("Element Found At Node: ");
            printf("%d ",i);
            flag = 1;
        }
        temp = temp->next;
        i++;
    }
    if(flag == 0)
    {
        printf("Element Not Found...");
    }
    printf("\n");
}
void delete(node** head)
{
    int position;
    printf("Enter the Position of the node you wish to delete: ");
    scanf("%d",&position);

    if(position == 1)
    {
        deletionAtHead(head);
        return;
    }
    
    int i = 1;
    node* temp = *head;
    while(i != position-1)
    {
        temp = temp->next;
        i++;

        if(temp == NULL || temp->next == NULL)
        {
            printf("Position out of bound...\n");
            return;
        }
    }
    node* delNode = temp->next;
    temp->next = (temp->next)->next;
    free(delNode);
    delNode = NULL;
}
