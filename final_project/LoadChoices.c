#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
struct node
{
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

void pushFront(struct node **head,char dest[200],char prob[200],char f_d[200],int pf_a,int if_a,int vf_a,char s_d[200],int ps_a,int is_a,int vs_a,short int p);

int countlines(char *filename)
{
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;

    if (fp == NULL)
        return 0;
    ch=fgetc(fp);
    while ((ch) != EOF)
    {
	if (ch == '\n')
    		lines++;
	ch=fgetc(fp);
    }
    fclose(fp);
    return lines;
}

struct node * make_nodes(int *nodes_count)
{
    struct node * head = NULL;
    char choices_file[100]="./CHOICES.txt";
    int c_lines = countlines(choices_file);
    FILE *choices_fp = fopen(choices_file,"r");
    for(int i=0;i<c_lines;i++)
    {
        char name[50],choice_file[100]="./";
        fgets(name,50,choices_fp);
        for(int i=0;i<50;i++)
            if(name[i]=='\n')
            {
                name[i]='\0';
                break;
            }
        strcat(choice_file,name);
        FILE *choice_fp = fopen(choice_file,"r");
        char prob[200];
        char f_d[200];
        int pf_a;
        int if_a;
        int vf_a;
        char s_d[200];
        int ps_a;
        int is_a;
        int vs_a;
        short int p=3;
        fgets(prob,200,choice_fp);
        fgets(f_d,200,choice_fp);
        fscanf(choice_fp,"%d %d %d",&pf_a,&if_a,&vf_a);
        fseek(choice_fp,2*sizeof(char),SEEK_CUR);
        fgets(s_d,200,choice_fp);
        fscanf(choice_fp,"%d %d %d",&ps_a,&is_a,&vs_a);
        pushFront(&head,choice_file,prob,f_d,pf_a,if_a,vf_a,s_d,ps_a,is_a,vs_a,p);
        (*nodes_count)++;
    }
    return head;
}


struct node * load_nodes(int *nodes_count,char destination[200],struct point * player)
{
    struct node * head = NULL;
    FILE *choices_fp = fopen(destination,"rb");
    fread(player, sizeof(struct point), 1, choices_fp);
    //printf("%s %d %d %d\n",player->name,player->people,player->imperial,player->vault);
    fread(nodes_count, sizeof(int), 1, choices_fp);
    //printf("%d",*nodes_count);
    for(int i=0;i<*nodes_count;i++)
    {
        char choice_file[200];
        short int p;
        fread(choice_file,200* sizeof(char), 1, choices_fp);
        fread(&p, sizeof(short int), 1, choices_fp);
        FILE *choice_fp = fopen(choice_file,"r");
        char prob[200];
        char f_d[200];
        int pf_a;
        int if_a;
        int vf_a;
        char s_d[200];
        int ps_a;
        int is_a;
        int vs_a;
        fgets(prob,200,choice_fp);
        fgets(f_d,200,choice_fp);
        fscanf(choice_fp,"%d %d %d",&pf_a,&if_a,&vf_a);
        fseek(choice_fp,2*sizeof(char),SEEK_CUR);
        fgets(s_d,200,choice_fp);
        fscanf(choice_fp,"%d %d %d",&ps_a,&is_a,&vs_a);
        pushFront(&head,choice_file,prob,f_d,pf_a,if_a,vf_a,s_d,ps_a,is_a,vs_a,p);
        fclose(choice_fp);
    }
    fclose(choices_fp);
    return head;
}

int compare (const void * a, const void * b)
{
    struct point *orderA = (struct point *)a;
    struct point *orderB = (struct point *)b;
    if( orderB->people - orderA->people ==0)
        if( orderB->imperial - orderA->imperial ==0)
            return ( orderB->vault - orderA->vault );
        else
            return ( orderB->imperial - orderA->imperial );
    else
        return ( orderB->people - orderA->people );
}



int ranking(struct point players[10])
{
    FILE * fp = fopen("./scores.bin","rb");
    int i;
    for(i=0;i<10;i++)
    {
        if(fread(&players[i], sizeof(struct point), 1, fp) < 1)
        {
            i--;
            break;
        }
    }
    qsort(players, i+1, sizeof(struct point), compare);
    fclose(fp);
    return i+1;
}
