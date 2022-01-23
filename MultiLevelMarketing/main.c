#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include"ibomarketing.h"

int main()
{
    node *head,*ip;int choose=0;
    char p[20]="qwerty";
    char str[20];int ss,iid;
    head=create(p,100);
    FILE* fp;
    fp=fopen("init.txt","r");
    if(fp==NULL)
    {
        printf("unable to open the init file\n");

    }
    else
    {
        int ins;
        fscanf(fp,"%d",&ins);
        while(ins)
        {

            fscanf(fp,"%s %d %d",str,&ss,&iid);
            ip=create(str,ss);
            if(!insertibo(ip,iid,head))
                printf("insert unsuccessful\n");
            ins--;

        }
    }
    printf("choose the corresponding number for the corresponding operation\n");
    while(choose!=6)
    {
        printf("1.insert ibo 2.update sale score 3.delete ibo 4.print ibotree 5.otherqueries 6.exit\n");
        scanf("%d",&choose);
        if(choose==1)
        {
            printf("preexisting members are as follows\n");
            preorder(head);
            printf("enter the name of ibo\n");
            scanf("%s",str);
            printf("enter the sale score of ibo\n");
            scanf("%d",&ss);
            printf("enter the id of mentor under whom ibo is to be inserted\n");
            scanf("%d",&iid);
            ip=create(str,ss);
            if(insertibo(ip,iid,head))
            {
                printf("insert successful and id assigned to ibo is %d\n",ip->id);
            }
        }
        else if(choose==2)
        {
            FILE* fpp;char fname[20];
            printf("enter the name of the file containing sale details\n");
            scanf("%s",fname);
            fpp=fopen(fname,"r");
            if(fpp==NULL)
            {
                printf("UNABLE TO OPEN THE SALES FILE.\n");

            }
            else
            {
                int sfc;fscanf(fpp,"%d",&sfc);
                while(sfc)
                {
                    fscanf(fpp,"%d %d",&iid,&ss);
                    updatesalescore(iid,ss,head);
                    sfc--;
                }
                printf("sale scores updated successfully\n");
            }
        }
        else if(choose==3)
        {
            printf("enter the id of ibo to be deleted\n");
            scanf("%d",&iid);
            if(head->id==iid)
            {
                deleteasal(&head);
                printf("ibo deleted successfully\n");
                if(head)
                    printf("new head of system is %s with id %d\n",head->name,head->id);

            }
            else
            {
                if(deleteutil(iid,head))
                {
                    printf("ibo deleted successfully\n");
                }
            }
        }
        else if(choose==4)
        {
            printf("name--id--mentorscore--salescore--descendants(format)\n");
            preorderc(head);
        }
        else if(choose==5)
        {
             levelorderqueries(head);
             printf("\n");
             exceeds(head);
        }

    }
    return 0;
}






