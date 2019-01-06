#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char exit[]="exit";
    while(1)
    {
        char prob[200];
        char f_d[200];
        int pf_a;
        int if_a;
        int vf_a;
        char s_d[200];
        int ps_a;
        int is_a;
        int vs_a;
        printf("Enter the problem: ");
        gets(prob);
        if(strcmp(prob,exit)==0)
            break;
        printf("Enter the first decision: ");
        gets(f_d);
        printf("Enter the Affection on people, imperial and vault: ");
        scanf("%d %d %d",&pf_a,&if_a,&vf_a);
        printf("Enter the second decision: ");
        gets(s_d);
        gets(s_d);
        printf("Enter the Affection on people, imperial and vault: ");
        scanf("%d %d %d",&ps_a,&is_a,&vs_a);
        char name[50],destination[100]="./";
        printf("Enter the File Name: ");
        gets(name);
        gets(name);
        FILE *fpc=fopen("./CHOICES.txt","a");
        fputs(name,fpc);
        fprintf(fpc,"\n");
        fclose(fpc);
        strcat(destination,name);
        FILE *fp=fopen(destination,"w");
        fprintf(fp,"%s\n%s\n%d\n%d\n%d\n%s\n%d\n%d\n%d",prob,f_d,pf_a,if_a,vf_a,s_d,ps_a,is_a,vs_a);
        fclose(fp);
        system("CLS");
    }
    return 0;
}
