#include <iostream>
#include <stdio.h>
using namespace std;

#include <stdlib.h>

typedef struct rec rec;
typedef struct node node;
typedef struct LinkedList LinkedList;

struct rec
{
    int arrivalTime;
    int servTime;
    int startServ;
    int departureTime;
    int waiTime;
    int order;
    int teller;
};

struct node
{
    rec data;
    node* next;
    node* prev;
};

struct LinkedList
{
    node* pfirst;
    node* plast;
};
/////////////////////////////////////////////////////////////////
///****************** Initialize a list **********************///
////////////////////////////////////////////////////////////////
void initList(LinkedList* l)
{
    l->pfirst=NULL;
    l->plast=NULL;
}
/////////////////////////////////////////////////////////////////
///******************* Create a node *************************///
////////////////////////////////////////////////////////////////
node* createRecord(){
    node* newNode  =(node*)malloc(sizeof(node));
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

/////////////////////////////////////////////////////////////////
///******************** Add a node ***************************///
////////////////////////////////////////////////////////////////

void addRecord(LinkedList* L, node* newNode)
{
    if (L->pfirst==NULL) //empty list
    {
        L->pfirst=newNode;
        L->plast=newNode;
    }
    else
    {
        newNode->prev=L->plast;
        L->plast->next=newNode;
        L->plast=newNode;
        L->plast->next=NULL;
    }
}
/////////////////////////////////////////////////////////////////
///****************** Remove a Node *************************///
////////////////////////////////////////////////////////////////
node* removeNode (LinkedList* L, node * pRemove)
{
    if (pRemove == L->pfirst )
    {
        if (pRemove == L->plast)
        {
            L->pfirst=L->plast=NULL ;
        }
        else
        {
           L->pfirst = pRemove->next ;
           L->pfirst ->prev=0 ;
        }
    }

    else if (pRemove == L->plast)
    {
        L->plast = L->plast->prev;
        L->plast ->next=0;
    }
    else
    {
        pRemove -> next -> prev = pRemove -> prev ;
        pRemove -> prev-> next = pRemove -> next ;
    }
    return pRemove;
}

/////////////////////////////////////////////////////////////////
///******************* Insert After **************************///
////////////////////////////////////////////////////////////////
void insertAfter (LinkedList* L, node *pafter , node* pnewnode)
{
        if (pafter == L->plast)
        {
            addRecord(L, pnewnode);
        }
        else
        {
            pnewnode -> prev = pafter ;
            pnewnode -> next = pafter->next;
            pafter -> next -> prev= pnewnode ;
            pafter-> next = pnewnode;
        }
}
/////////////////////////////////////////////////////////////////
///******************* Insert Before ************************///
////////////////////////////////////////////////////////////////
void insertBefore (LinkedList* L, node *pbefore , node*pnewnode)
{
        if (pbefore == L->pfirst)
        {
            pnewnode -> next = L->pfirst ;
            L->pfirst -> prev = pnewnode ;
            L->pfirst=pnewnode ;
        }
        else
        {
            pnewnode ->prev = pbefore ->prev ;
            pnewnode ->next = pbefore ;
            pbefore -> prev ->next = pnewnode ;
            pbefore -> prev =pnewnode ;
        }
}

/////////////////////////////////////////////////////////////////
///******************* Bubble Sort ***************************///
////////////////////////////////////////////////////////////////

void swaping(LinkedList* L, node* node1, node* node2)
{
    if(node2->next==NULL)
    {
        node* p_inserted=removeNode(L, node2);
        insertBefore(L, node1, p_inserted);
        L->plast=node1;
    }
    else
    {
        node* p_inserted=removeNode(L, node1);
        insertAfter(L, node2, p_inserted);
    }
}

void bubbleSort(LinkedList* L)
{
    int sorted=0;
    node* pTraverse=L->pfirst;

    do
    {
        sorted=1;
        pTraverse = L->pfirst;
        while(pTraverse->next!=NULL)
        {

            if(pTraverse->data.arrivalTime > pTraverse->next->data.arrivalTime)
            {
                swaping(L, pTraverse, pTraverse->next);
                sorted=0;
            }
            else
            {
                pTraverse=pTraverse->next;
            }
        }
    }
    while(!sorted);
}
