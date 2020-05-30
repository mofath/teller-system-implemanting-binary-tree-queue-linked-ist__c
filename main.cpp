#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

using namespace std;

#include "queue.h"
#include "menu.h"
#include "linkedList.h"

int timer=0;
int order=0;
int loop =1;
int isQuEmpty1 =0, isQuEmpty2=0, isQuEmpty3=0;
void print_res(LinkedList* l, int num, float avg1, float avg2, float avg3);

void calcData(node* pNode, int* endServ);


/////////////////////////////////////////////////////////////////
///************************ Main ****************************///
////////////////////////////////////////////////////////////////
int main()
{
    Queue tel1, tel2, tel3;
    initQueue(&tel1);
    initQueue(&tel2);
    initQueue(&tel3);

    Node* pClient;

    LinkedList records;
    initList(&records);

    LinkedList* pRec=&records;
    node* pTraverse;

    char yn;
    int rowId=1;
    char key;

    int endServ1=0,  tel1_counter=0;
    int endServ2=0,  tel2_counter=0;
    int endServ3=0,  tel3_counter=0;
    float avgWait1=0.0, avgWait2=0.0, avgWait3=0.0;
    float totWait1=0.0, totWait2=0.0, totWait3=0.0;
    int sysTime=0;


    system("cls");
    char option[3][30]={"Inserting new client",
                        "Printing data",
                        "Exit"    };

    while(loop)
    {
        system("cls");
        for(int counter=1; counter<=3; counter++)
        {
            gotoxy(15,5*counter);
            if(rowId==counter) SetColor(yellow);
            else SetColor(white);
            printf("%s", option[counter-1]);
        }

        key=getch();
        if(key==isExtended)
        {
            key=getch();
            switch(key)
            {
                case up:
                    rowId--;
                    if(rowId==0) rowId=3;
                    break;
                case down:
                    rowId++;
                    if(rowId==4) rowId=1;
                    break;
            }
        }
        else if(key==enter)
        {
            if(rowId==1)
            {
                system("cls");
                    do
                    {
                        system("cls");
                        order++;
                        pTraverse=createRecord();

                        gotoxy(30,2);
                        SetColor(green);
                        printf("Client %d ", order);

                        gotoxy(2,6);
                        SetColor(yellow);
                        printf("Insert the arrival time of client %d :", order);
                        gotoxy(2,9);
                        printf("Insert the service time of client %d :", order);
                        SetColor(white);
                        gotoxy(43,6);
                        scanf("%d", &pTraverse->data.arrivalTime);
                        gotoxy(43,9);
                        scanf("%d", &pTraverse->data.servTime);

                        addRecord(&records, pTraverse);

                        gotoxy(2,13);
                        SetColor(cyan);
                        printf("Would you like to add a new client? (Y/N):  ");
                        SetColor(white);
                        scanf(" %c", &yn);
                    } while((yn == 'Y' || yn == 'y') && (yn != 'N' || yn != 'n'));

                bubbleSort(pRec);
                for(int i=1; i<=order; i++)
                {
                    pTraverse=pRec->pfirst;
                    pTraverse->data.order=i;
                    pTraverse=pTraverse->next;
                }

                sysTime=pRec->plast->data.startServ + pRec->plast->data.servTime;
                pTraverse=pRec->pfirst;
                for(; timer<=sysTime; timer++)
                {
                    while(pTraverse != NULL)
                    {
                            if (isQuEmpty1 !=0 && tel1.fron->data.departureTime==timer) {dequeue(&tel1); isQuEmpty1--;}
                            if (isQuEmpty2 !=0 &&tel2.fron->data.departureTime==timer) {dequeue(&tel2); isQuEmpty2--;}
                            if (isQuEmpty3 !=0 &&tel3.fron->data.departureTime==timer) {dequeue(&tel3); isQuEmpty3--;}

                        //assign the client to a certain teller
                        if(endServ1 <= endServ2 && endServ1 <= endServ3)
                        {
                            tel1_counter++;
                            pTraverse->data.teller=1;

                            calcData(pTraverse, &endServ1);

                            totWait1 += pTraverse->data.waiTime;
                            avgWait1 = totWait1/tel1_counter;

                            pClient=create(pTraverse->data.order, pTraverse->data.startServ, pTraverse->data.departureTime);
                            enqueue(&tel1, pClient);
                            isQuEmpty1++;
                        }

                        else if (endServ2 <= endServ1 && endServ2 <= endServ3)
                        {
                            tel2_counter++;
                            pTraverse->data.teller=2;

                            calcData(pTraverse, &endServ2);

                            totWait2+=pTraverse->data.waiTime;
                            avgWait2=totWait2/tel2_counter;
                            pClient=create(pTraverse->data.order, pTraverse->data.startServ, pTraverse->data.departureTime);
                            enqueue(&tel2, pClient);
                            isQuEmpty2++;
                        }
                        else
                        {
                            tel3_counter++;
                            pTraverse->data.teller=3;

                            calcData(pTraverse, &endServ3);

                            totWait3+=pTraverse->data.waiTime;
                            avgWait3=totWait3/tel3_counter;
                            pClient=create(pTraverse->data.order, pTraverse->data.startServ, pTraverse->data.departureTime);
                            enqueue(&tel3, pClient);
                            isQuEmpty3++;
                        }


                        pTraverse=pTraverse->next;
                    }
                }
                getch();
            }
            else if (rowId==2)
            {
                system("cls");
                gotoxy(35,10);
                print_res(&records, order, avgWait1, avgWait2, avgWait3);
                getch();
            }
            else if (rowId==3)
            {
                system("cls");
                loop=0;
                system("cls");
            }
        }
   }
    return 0;
}

/////////////////////////////////////////////////////////////////
///******************** Printing Results ********************///
////////////////////////////////////////////////////////////////
void print_res(LinkedList* l, int num, float avg1, float avg2, float avg3)
{
    node* pdisplay = l->pfirst;
    gotoxy(1,2); SetColor(lightgreen);
    printf("Results\n");
    gotoxy(1,3);
    printf("‹‹‹‹‹‹‹‹");
    gotoxy(1,5); SetColor(darkgray);
    printf("‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹");
    gotoxy(2,6); SetColor(green); printf("ID"); gotoxy(5,6); SetColor(darkgray); printf("«");
    gotoxy(7,6); SetColor(lightmagenta); printf("Teller"); gotoxy(14,6); SetColor(darkgray); printf("«");
    gotoxy(16,6); SetColor(lightmagenta); printf("Ariv. Time"); gotoxy(27,6); SetColor(darkgray); printf("«");
    gotoxy(29,6); SetColor(lightmagenta); printf("Waiting"); gotoxy(37,6); SetColor(darkgray); printf("«");
    gotoxy(39,6); SetColor(lightmagenta); printf("Start Serv."); gotoxy(51,6); SetColor(darkgray); printf("«");
    gotoxy(53,6); SetColor(lightmagenta); printf("Service Time"); gotoxy(66,6); SetColor(darkgray); printf("«");
    gotoxy(68,6); SetColor(lightmagenta); printf("Dep. Time"); gotoxy(78,6); SetColor(darkgray); printf("«");
    gotoxy(1,7);
    printf("‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹");

    if (num==0)
    {
        gotoxy(30,8); SetColor(green);
        printf("NO Entry Yet");
        gotoxy(1,9); SetColor(lightgray);
        printf("______________________________________________________________________________");
    }
    else
    {
        for(int i=2;i<=2*num;i+=2)
        {
            gotoxy(2,7+i); SetColor(lightblue); printf("%d",i/2); gotoxy(5,7+i); SetColor(white); printf("«");
            gotoxy(10,7+i); SetColor(lightgreen); printf("%d", pdisplay->data.teller); gotoxy(14,7+i); SetColor(white); printf("«");
            gotoxy(21,7+i); SetColor(lightgreen); printf("%d",pdisplay->data.arrivalTime); gotoxy(27,7+i);SetColor(white); printf("«");
            gotoxy(32,7+i); SetColor(lightgreen); printf("%d",pdisplay->data.waiTime); gotoxy(37,7+i); SetColor(white); printf("«");
            gotoxy(45,7+i); SetColor(lightgreen); printf("%d",pdisplay->data.startServ); gotoxy(51,7+i); SetColor(white); printf("«");
            gotoxy(59,7+i); SetColor(lightgreen); printf("%d",pdisplay->data.servTime); gotoxy(66,7+i); SetColor(white); printf("«");
            gotoxy(72,7+i); SetColor(lightgreen); printf("%d",pdisplay->data.departureTime); gotoxy(78,7+i); SetColor(white); printf("«");
            gotoxy(1,8+i);
            printf("______________________________________________________________________________");

            pdisplay=pdisplay->next;
        }

        gotoxy(1,(num*2)+12); SetColor(brown);
        printf("______________________________________________________________________________");
        gotoxy(2,(num*2)+13); SetColor(cyan); printf("Average waiting time at teller 1");
        gotoxy(35,(num*2)+13); SetColor(brown); printf("«");
        gotoxy(53,(num*2)+13); SetColor(lightgreen); printf("%0.2f", avg1);
        gotoxy(1,(num*2)+14); SetColor(brown);
        printf("______________________________________________________________________________");
        gotoxy(2,(num*2)+15); SetColor(cyan); printf("Average waiting time at teller 2");
        gotoxy(35,(num*2)+15); SetColor(brown); printf("«");
        gotoxy(53,(num*2)+15); SetColor(lightgreen); printf("%0.2f", avg2);
        gotoxy(1,(num*2)+16); SetColor(brown);
        printf("______________________________________________________________________________");
        gotoxy(2,(num*2)+17); SetColor(cyan); printf("Average waiting time at teller 3");
        gotoxy(35,(num*2)+17); SetColor(brown); printf("«");
        gotoxy(53,(num*2)+17); SetColor(lightgreen); printf("%0.2f", avg3);
        gotoxy(1,(num*2)+18); SetColor(brown);
        printf("______________________________________________________________________________");
    }
}

/////////////////////////////////////////////////////////////////
///********************* Calculate Data *********************///
////////////////////////////////////////////////////////////////
void calcData(node* pNode, int* endServ)
{
    if (pNode->data.arrivalTime < *endServ)
    {
        pNode->data.startServ=*endServ;
    }
    else
    {
        pNode->data.startServ=pNode->data.arrivalTime;
    }

    pNode->data.waiTime = pNode->data.startServ - pNode->data.arrivalTime;
    pNode->data.departureTime = pNode->data.startServ + pNode->data.servTime;

    *endServ = pNode->data.departureTime;
}
