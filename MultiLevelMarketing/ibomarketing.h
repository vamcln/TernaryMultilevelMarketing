#ifndef IBOMARKETING_H_INCLUDED
#define IBOMARKETING_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define percentage 0.1
#define N 1000
typedef struct node
{
    char name[100];
    int id;
    int mentorscore;
    int salescore;
    struct node *lc;
    struct node *mc;
    struct node *rc;

}node;
typedef struct qu
{
    int f;
    int r;
    int siz;
    node* arr[N];

}qu;
void push(node *ip,qu *qptr);
void initialise(qu *qptr);
node *pop(qu *qptr);
void levelorderqueries(node *root);
bool insertibo(node *ibo,int mentorid,node *root);
bool updatesalescore(int iboid,int score,node *root);
void deleteasal(node **root);
node *create(char *str,int score);
void adjust(node *a,node *b,node *c,node *d);
void adjustmi(node *a,node *b);
bool deleteutil(int delid,node *root);
void delchesei(node *p,node **c);
int score(node *root);
int noc(node *root);
void preorder(node *root);
void preorderc(node *root);
void exceeds(node *root);

#endif // IBOMARKETING_H_INCLUDED
