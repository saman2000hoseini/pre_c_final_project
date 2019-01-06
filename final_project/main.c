#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include<stdbool.h>

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


struct node * make_nodes(int *nodes_count);

struct node * load_nodes(int *nodes_count,char destination[200],struct point * player);

void deleteNode (struct node ** head,struct node * temp);

int ranking(struct point players[10]);

struct node * print(struct node *head,int num);

void print_rankning()
{
    struct point players[10];
    int players_count = ranking(players);
    if(players_count>0)
        printf("name\t\tpeople\t\tcourt\t\ttreasury\n");
    for(int i=0;i<players_count;i++)
        printf("%s:\t\t%d\t\t%d\t\t%d\n",players[i].name,players[i].people,players[i].imperial,players[i].vault);
}

void save_file(int *nodes_count,struct node * head,struct point * player,char destination[200],int state)
{
    FILE *tmp_save = fopen(destination,"wb");
    fwrite(player,sizeof(struct point),1,tmp_save);
    fwrite(nodes_count, sizeof(int),1,tmp_save);
    struct node * temp = head;
    for(int i=0;i<*nodes_count;i++)
    {
        fwrite(&temp->dest,200*sizeof(char),1,tmp_save);
        fwrite(&temp->p, sizeof(short int),1,tmp_save);
        temp=temp->next;
    }
    fwrite(&state, sizeof(int),1,tmp_save);
    fclose(tmp_save);
    if(state>0)
    {
        FILE *scores = fopen("./scores.bin","rb");
        if(scores==NULL)
        {
            scores = fopen("./scores.bin","wb");
            fwrite(player,sizeof(struct point),1,scores);
            fclose(scores);
        }
        else
        {
            struct point myrecord;
            FILE * fp_temp = fopen("./temp_scores.bin","wb");
            bool exists = false;
            while(1)
            {
                if(fread(&myrecord, sizeof(struct point), 1, scores) < 1)
                    break;
                else if(strcmp(myrecord.name,player->name)==0)
                {
                    exists=true;
                    fwrite(player,sizeof(struct point),1,fp_temp);
                }
                else
                {
                    fwrite(&myrecord, sizeof(struct point), 1, fp_temp);
                }
            }
            fclose(scores);
            remove("scores.bin");
            if(!exists)
            {
                fwrite(player,sizeof(struct point),1,fp_temp);
            }
            fclose(fp_temp);
            rename("temp_scores.bin", "scores.bin");
        }
    }
}


void next_round(int *nodes_count,struct node * head,struct point * player,char destination[200])
{
    int rnd = rand();
    rnd%=*nodes_count;
    struct node * temp= print(head,rnd);
    int t;
    scanf("%d",&t);
    if(t==1)
    {
        player->people+=temp->pf_Affection;
        player->imperial+=temp->if_Affection;
        player->vault+=temp->vf_Affection;
    }
    else
    {
        player->people+=temp->ps_Affection;
        player->imperial+=temp->is_Affection;
        player->vault+=temp->vs_Affection;
    }
    system("CLS");
    printf("People: %d Imperial Court: %d Treasury: %d\n",player->people,player->imperial,player->vault);
    temp->p--;
    if(temp->p==0)
    {
        deleteNode(&head,temp);
        (*nodes_count)--;
    }
    save_file(nodes_count,head,player,destination,0);
}

void continueOrExit(int *nodes_count,struct node * head,struct point * player,char destination[200],char last[200])
{
    char command;
    scanf("%c",&command);
    scanf("%c",&command);
    if(command=='0')
    {
        printf("[1] SAVE & EXIT\t\t[2] RANKING & EXIT\t\t[3] EXIT\n");
        int st;
        scanf("%d",&st);
        if(st==1)
        {
            remove(last);
            save_file(nodes_count,head,player,destination,1);
            exit(0);
        }
        else if(st==2)
        {
            print_rankning();
            Sleep(5000);
            exit(0);
        }
        else
            exit(0);
    }
}

int main()
{
    print_rankning();
    srand(time(0));
    struct node * head;
    struct point player;
    char destination1[200]="./temp/",destination2[200]="./save/";
    int nodes_count=0,x=0;
    bool flag = true;
    while(x==0)
    {
        char name[100];
        printf("Enter your username: ");
        fflush(stdin);
        gets(name);
        strcpy(player.name,name);
        strcat(destination1,player.name);
        strcat(destination1,".bin");
        strcat(destination2,player.name);
        strcat(destination2,".bin");
        FILE *crashed = fopen(destination1,"rb");
        if(crashed!=NULL)
        {
            printf("You have a game in progress do you want to continue?(y/n) ");
            char tmp;
            scanf("%c",&tmp);
            if(tmp=='y' || tmp=='Y')
            {
                flag=false;
                x=1;
                head = load_nodes(&nodes_count,destination1,&player);
            }
            fclose(crashed);
        }
        if(flag)
        {
            FILE * saved_file = fopen(destination2,"rb");
            if(saved_file!=NULL)
            {
                char tmp;
                printf("You have a saved game do you want to continue?(y/n) ");
                fflush(stdin);
                scanf("%c",&tmp);
                if(tmp=='y' || tmp=='Y')
                {
                    flag=false;
                    x=1;
                    head = load_nodes(&nodes_count,destination2,&player);
                }
            }
            else
            {
                x=1;
            }
        }
        system("CLS");
    }
    if(flag)
    {
            player.imperial=50;
            player.people=50;
            player.vault=50;
            head = make_nodes(&nodes_count);
    }
    printf("People: %d Imperial Court: %d Treasury: %d\n",player.people,player.imperial,player.vault);
    while(nodes_count!=0 && player.imperial>0 && player.people>0 && player.vault>0 && ((player.imperial+player.people+player.vault)/3)>10)
    {
        next_round(&nodes_count,head,&player,destination1);
        continueOrExit(&nodes_count,head,&player,destination2,destination1);
    }
    if(nodes_count==0)
    {
        printf("You have finished the game !!! wait for next updates :)) ");
        save_file(&nodes_count,head,&player,destination2,2);
    }
    else
    {
        printf("You have lost the game !! try again :((");
        save_file(&nodes_count,head,&player,destination2,3);
    }
    Sleep(4000);
    return 0;
}
