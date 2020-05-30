#include <iostream>
#include <stdio.h>
using namespace std;

#include <stdlib.h>

typedef struct Node Node;
typedef struct Queue Queue;
typedef struct client client;

struct client
{
    int id;
    int startServ;
    int departureTime;

};

struct Node
{
    client data ;
    Node * prev;
};

struct Queue
{
    Node* fron;
    Node* rear;
};

void initQueue(Queue* q)
{
    q->fron=NULL;
    q->rear=NULL;
}

Node* create (int _id, int _startServ, int _departureTime)
{
    Node * newNode = (Node *)malloc (sizeof (Node));
    newNode->data.id=_id;
    newNode->data.startServ=_startServ;
    newNode->data.departureTime=_departureTime;

    newNode ->prev = NULL;
    return newNode;
}

void enqueue (Queue* q, Node *newNode )
{
    if (q->fron == NULL)
    {
        q->fron = q->rear = newNode ;
    }
    else
    {
        q->rear ->prev = newNode ;
        q->rear = newNode ;
    }
}

void dequeue(Queue* q)
{
    Node * pnode;
    pnode = q->fron ;
    q->fron = q->fron ->prev ;
    pnode->prev= NULL;
}
