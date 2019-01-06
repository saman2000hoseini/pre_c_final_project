#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char dest[200];
    char problem[200];
    char first_decision[200];
    int pf_Affection;
    int if_Affection;
    int vf_Affection;
    char second_decision[200];
    int ps_Affection;
    int is_Affection;
    int vs_Affection;
    short int p;
    struct node *next;
};

struct point
{
    char name[100];
    short people;
    short imperial;
    short vault;
};

void pushFront(struct node **head,char dest[200],char prob[200],char f_d[200],int pf_a,int if_a,int vf_a,char s_d[200],int ps_a,int is_a,int vs_a,short int p)
{
    struct node * new_node=(struct node*)malloc(sizeof(struct node));
    new_node->next=*head;
    *head = new_node;
    strcpy(new_node->dest,dest);
    strcpy(new_node->problem,prob);
    strcpy(new_node->first_decision,f_d);
    new_node->pf_Affection=pf_a;
    new_node->if_Affection=if_a;
    new_node->vf_Affection=vf_a;
    strcpy(new_node->second_decision,s_d);
    new_node->ps_Affection=ps_a;
    new_node->is_Affection=is_a;
    new_node->vs_Affection=vs_a;
    new_node->p=p;
}

void pushBack(struct node *head,char dest[200],char prob[200],char f_d[200],int pf_a,int if_a,int vf_a,char s_d[200],int ps_a,int is_a,int vs_a,short int p)
{
    struct node * new_node = (struct node*)malloc(sizeof(struct node));
    struct node * temp = head;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=new_node;
    new_node->next=NULL;
    strcpy(new_node->dest,dest);
    strcpy(new_node->problem,prob);
    strcpy(new_node->first_decision,f_d);
    new_node->pf_Affection=pf_a;
    new_node->if_Affection=if_a;
    new_node->vf_Affection=vf_a;
    strcpy(new_node->second_decision,s_d);
    new_node->ps_Affection=ps_a;
    new_node->is_Affection=is_a;
    new_node->vs_Affection=vs_a;
    new_node->p=p;
}

void deleteZeroNodes (struct node ** head,int * nodes_count)
{
    struct node * current = *head;
    struct node * comin = current->next;
    if(current->p==0)
    {
        *head=comin;
        free(current);
    }
    else
    {
        while(comin!=NULL)
        {
            if(comin->p==0)
            {
                current->next=comin->next;
                free(comin);
                (*nodes_count)--;
            }
            current=comin;
            comin = current->next;
        }
    }
}

void deleteNode (struct node ** head,struct node * temp)
{
    struct node * current = *head;
    struct node * comin = current->next;
    if(current==temp)
    {
        *head=comin;
        free(current);
    }
    else
    {
        while(comin!=NULL && comin!=temp)
        {
            current=comin;
            comin = current->next;
        }
        current->next=comin->next;
        free(comin);
    }
}

struct node * print(struct node *head,int num)
{
    struct node * temp= head;
    for(int i=0;i<num;i++)
    {
        temp=temp->next;
    }
    printf("%s[1] %s[2] %s\n\n",temp->problem,temp->first_decision,temp->second_decision);
    return temp;
}

struct node * print_everything(struct node *head,int num)
{
    struct node * temp= head;
    for(int i=0;i<num;i++)
    {
        temp=temp->next;
    }
    printf("%s%s%d %d %d\n%s%d %d %d\n%d\n\n",temp->problem,temp->first_decision,temp->pf_Affection,temp->if_Affection,temp->vf_Affection,temp->second_decision,temp->ps_Affection,temp->is_Affection,temp->vs_Affection,temp->p);
    return temp;
}
