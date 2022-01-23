#include"ibomarketing.h"
void push(node *ip,qu *qptr)
{
    if(qptr->siz==N)
    {
        printf("queue size full.\n");
    }
    else
    {
        if(qptr->f==-1)
        {
            qptr->f=0;
        }
        qptr->r=((qptr->r)+1)%N;
        qptr->arr[qptr->r]=ip;
        qptr->siz=qptr->siz+1;
    }
}
node *pop(qu *qptr)
{
    node *retval=NULL;
    if(qptr->siz==0)
    {
        printf("queue empty.DELETE failed\n");
    }
    else
    {
        retval=qptr->arr[qptr->f];
        if(qptr->siz==1)
        {
            qptr->f=-1;
            qptr->r=-1;
        }
        else
        {
            qptr->f=((qptr->f)+1)%N;
        }
        qptr->siz=qptr->siz-1;

    }
    return retval;
}
void initialise(qu *qptr)
{
    qptr->f=-1;
    qptr->r=-1;
    qptr->siz=0;
}
node *create(char *str,int score)
{

    node *ip;
    ip=(node*)malloc(sizeof(node));
    strcpy(ip->name,str);
    ip->id=(rand()%10000)+1;
    ip->lc=NULL;
    ip->mc=NULL;
    ip->mentorscore=0;
    ip->rc=NULL;
    ip->salescore=score;
    ip->siz=0;
    return ip;
}
int score(node *root)
{
    return((root->mentorscore)+(root->salescore));
}
int noc(node *root)
{
    int c=0;
    if(root->lc)
    {
        c++;
    }
    if(root->mc)
    {
        c++;
    }
    if(root->rc)
    {
        c++;
    }
    return c;
}
void preorder(node *root)
{
    if(root)
    {
        printf("%s--%d\n",root->name,root->id);
        preorder(root->lc);
        preorder(root->mc);
        preorder(root->rc);
    }
}
void preorderc(node *root)
{
    if(root)
    {
        printf("%s--%d--%d--%d--%d\n",root->name,root->id,root->mentorscore,root->salescore,root->siz);
        preorderc(root->lc);
        preorderc(root->mc);
        preorderc(root->rc);
    }
}
bool insertibo(node *ibo,int mentorid,node *root)
{
    if(!root)
    {
        return false;
    }
    if(root->id==mentorid)
    {
        if(!root->lc)
        {
            root->lc=ibo;
            root->mentorscore+=100;
            root->salescore+=percentage*(ibo->salescore);
            root->siz++;
            return true;
        }
        else if(!root->mc)
        {
            root->mc=ibo;
            root->mentorscore+=100;
            root->salescore+=(int)percentage*(ibo->salescore);
            root->siz++;
            return true;
        }
        else if(!root->rc)
        {
            root->rc=ibo;
            root->mentorscore+=200;
            root->salescore+=(int)percentage*(ibo->salescore);
            root->siz++;
            return true;
        }
        else
        {
            printf("No of children cannot exceed 3.Already 3 children exist for the current mentor\n");
            return false;
        }
    }
    if(insertibo(ibo,mentorid,root->lc)||insertibo(ibo,mentorid,root->mc)||insertibo(ibo,mentorid,root->rc))
    {
        root->mentorscore+=10;
        root->salescore+=(int)percentage*(ibo->salescore);
        root->siz++;
        return true;
    }
    return false;

}

void exceeds(node *root)
{
    if(root)
    {
        if(root->lc&&score(root->lc)>score(root))
        {
            printf("%s with id %d leads his mentor %s with id %d by %d points\n",root->lc->name,root->lc->id,root->name,root->id,(score(root->lc)-score(root)));
        }
        if(root->mc&&score(root->mc)>score(root))
        {
            printf("%s with id %d leads his mentor %s with id %d by %d points\n",root->mc->name,root->mc->id,root->name,root->id,(score(root->mc)-score(root)));
        }
        if(root->rc&&score(root->rc)>score(root))
        {
            printf("%s with id %d leads his mentor %s with id %d by %d points\n",root->rc->name,root->rc->id,root->name,root->id,(score(root->rc)-score(root)));
        }
        exceeds(root->lc);
        exceeds(root->mc);
        exceeds(root->rc);
    }
}
bool updatesalescore(int iboid,int score,node *root)
{
    if(!root)
    {
        return false;
    }
    if(root->id==iboid)
    {
        root->salescore+=score;
        return true;
    }
    if(updatesalescore(iboid,score,root->lc)||updatesalescore(iboid,score,root->mc)||updatesalescore(iboid,score,root->rc))
    {
        root->salescore+=percentage*score;
        return true;
    }
    return false;
}

void levelorderqueries(node *root)
{
    node *tmp,*sco,*desc;
    int maxdesc=0;
    int maxsco=0;
    int level=0;
    qu q;
    initialise(&q);
    push(root,&q);
    int flag=q.siz;
    while(q.siz!=0)
    {
        while(flag)
        {
            tmp=pop(&q);
            flag--;
            if(tmp->siz>maxdesc)
            {
                maxdesc=tmp->siz;
                desc=tmp;
            }
            if(score(tmp)>maxsco)
            {
                maxsco=score(tmp);
                sco=tmp;
            }
            if(tmp->lc)
            {
                push(tmp->lc,&q);
            }
            if(tmp->mc)
            {
                push(tmp->mc,&q);
            }
            if(tmp->rc)
            {
                push(tmp->rc,&q);
            }

        }
        printf("At level %d :\n",level);
        printf("%s with id %d has the highest score with %d points\n",sco->name,sco->id,maxsco);
        if(maxdesc)
        {
            printf("%s with id %d has highest number of descendants(%d)\n",desc->name,desc->id,maxdesc);
            printf("\n");
        }
        else
            printf("Leaf level reached,all ibos have equal descendants(0) at this level\n");
        flag=q.siz;
        level++;
        maxdesc=0;
        maxsco=0;
    }

}

void adjust(node *a,node *b,node *c,node *d)
{
    a->rc=c;

    if(!b->lc)
    {
        b->lc=d;
        b->mentorscore+=100;
    }
    else if(!b->mc)
    {
        b->mc=d;
        b->mentorscore+=100;
    }
    else if(!b->rc)
    {
        b->rc=d;
        b->mentorscore+=200;
    }
    b->siz+=d->siz+1;
    b->mentorscore+=(d->siz*10);
}
void adjustmi(node *a,node *b)
{
    if(!a->lc)
    {
        a->lc=b;
        a->mentorscore+=100;
    }
    else if(!a->mc)
    {
        a->mc=b;
        a->mentorscore+=100;
    }
    else if(!a->rc)
    {
        a->rc=b;
        a->mentorscore+=200;
    }
    a->siz+=b->siz+1;
    a->mentorscore+=(b->siz*10);
}

void deleteasal(node **root)
{
    node *maxnode,*tmp,*l,*m,*r;
    l=(*root)->lc;
    m=(*root)->mc;
    r=(*root)->rc;
    int max=0;
    tmp=*root;
    if(l&&score(l)>max)
    {
        max=score(l);
        maxnode=l;
    }
    if(m&&score(m)>max)
    {
        max=score(m);
        maxnode=m;
    }
    if(r&&score(r)>max)
    {
        max=score(r);
        maxnode=r;
    }
    if(maxnode==l)
    {
        *root=l;

        if(l->mc)
        {

            if(!m)
            {
                (*root)->mc=l->mc;
            }
            else if(m)
            { node *ip=l->mc;


                (*root)->mc=m;

                m->siz+=ip->siz+1;
                m->mentorscore+=((ip->siz+1)*10);
                while(m->mc!=NULL)
                {
                   m=m->mc;
                   m->siz+=ip->siz+1;
                   m->mentorscore+=((ip->siz+1)*10);
                }

                m->mc=ip;

                m->mentorscore+=90;


            }
        }
        else if(!l->mc)
        {
            if(m)
            {
              (*root)->mentorscore+=100;
            }
            (*root)->mc=m;
        }
        if(l->rc)
        {
            if(!r)
            {
                (*root)->rc=l->rc;
            }
            else if(r)
            {  node *ip1=l->rc;
                (*root)->rc=r;
                r->siz+=ip1->siz+1;
                r->mentorscore+=((ip1->siz+1)*10);
                while(r->rc!=NULL)
                {
                   r=r->rc;
                   r->siz+=ip1->siz+1;
                   r->mentorscore+=((ip1->siz+1)*10);
                }
                r->rc=ip1;
                r->mentorscore+=190;

            }
        }
        else if(!l->rc)
        {
            if(r)
            {
              (*root)->mentorscore+=200;
            }
            (*root)->rc=r;
        }
    }
    else if(maxnode==m)
    {

        *root=m;
        if(m->lc)
        {
            if(!l)
            {
                (*root)->lc=m->lc;
            }
            else if(l)
            {
                node *ip2=m->lc;
                (*root)->lc=l;
                l->siz+=ip2->siz+1;
                l->mentorscore+=((ip2->siz+1)*10);
                while(l->lc!=NULL)
                {
                   l=l->lc;
                   l->siz+=ip2->siz+1;
                   l->mentorscore+=((ip2->siz+1)*10);
                }
                l->lc=ip2;
                l->mentorscore+=90;
            }
        }
        else if(!m->lc)
        {
            if(l)
            {
              (*root)->mentorscore+=100;
            }
            (*root)->lc=l;
        }

        if(m->rc)
        {
            if(!r)
            {
                (*root)->rc=m->rc;
            }
            else if(r)
            {
                node *ip3=m->rc;
                (*root)->rc=r;
                r->siz+=ip3->siz+1;
                r->mentorscore+=((ip3->siz+1)*10);
                while(r->rc!=NULL)
                {
                   r=r->rc;
                   r->siz+=ip3->siz+1;
                   r->mentorscore+=((ip3->siz+1)*10);
                }
                r->rc=ip3;
                r->mentorscore+=190;
            }
        }
        else if(!m->rc)
        {
            if(r)
            {
              (*root)->mentorscore+=200;
            }
            (*root)->rc=r;
        }
    }
    else if(maxnode==r)
    {
        *root=r;
        if(r->lc)
        {
            if(!l)
            {
                (*root)->lc=r->lc;
            }
            else if(l)
            {
                node *ip4=r->lc;
                (*root)->lc=l;
                l->siz+=ip4->siz+1;
                l->mentorscore+=((ip4->siz+1)*10);
                while(l->lc!=NULL)
                {
                   l=l->lc;
                   l->siz+=ip4->siz+1;
                   l->mentorscore+=((ip4->siz+1)*10);
                }
                l->lc=ip4;
                l->mentorscore+=90;
            }
        }
        else if(!r->lc)
        {
            if(l)
            {
              (*root)->mentorscore+=100;
            }
            (*root)->lc=l;
        }
        if(r->mc)
        {
            if(!m)
            {
                (*root)->mc=r->mc;
            }
            else if(m)
            {
                node *ip5=r->mc;
                (*root)->mc=m;
                m->siz+=ip5->siz+1;
                m->mentorscore+=((ip5->siz+1)*10);
                while(m->mc!=NULL)
                {
                   m=m->mc;
                   m->siz+=ip5->siz+1;
                   m->mentorscore+=((ip5->siz+1)*10);
                }
                m->mc=ip5;
                m->mentorscore+=90;
            }
        }
        else if(!r->mc)
        {
            if(m)
            {
              (*root)->mentorscore+=100;
            }
            (*root)->mc=m;
        }
    }
    (*root)->siz=0;
    if((*root)->lc)
    {
        (*root)->siz+=(*root)->lc->siz+1;
    }
    if((*root)->mc)
    {
        (*root)->siz+=(*root)->mc->siz+1;
    }
    if((*root)->rc)
    {
        (*root)->siz+=(*root)->rc->siz+1;
    }
    free(tmp);

}

bool deleteutil(int delid,node *root)
{
  if(!root)
  {
      return false;
  }
  if(root->lc&&root->lc->id==delid)
  {
      int p=noc(root);
      int c=noc(root->lc);
      if(p==3&&c==3)
      {
          printf("relaxation allowed for this special case\n");
          return false;
      }
      else if(p==3&&c==2)
      {
          if(noc(root->lc->lc)==3&&noc(root->lc->mc)==3)
          {
              printf("relaxation allowed for this special case\n");
              return false;
          }
          else
          {
              root->siz-=1;
              delchesei(root,&(root->lc));
              return true;
          }
      }
      else if(p==2&&c==3)
      {
          if(noc(root->lc->lc)==3&&noc(root->lc->mc)==3&&noc(root->lc->rc)==3)
          {
              printf("relaxation allowed for this special case\n");
              return false;
          }
          else
          {
              root->siz-=1;
              delchesei(root,&(root->lc));
              return true;
          }
      }
      else
      {
          root->siz-=1;
          delchesei(root,&(root->lc));

          return true;
      }

  }
  if(root->mc&&root->mc->id==delid)
  {
      int p=noc(root);
      int c=noc(root->mc);
      if(p==3&&c==3)
      {
          printf("relaxation allowed for this special case\n");
          return false;
      }
      else if(p==3&&c==2)
      {
          if(noc(root->mc->lc)==3&&noc(root->mc->mc)==3)
          {
              printf("relaxation allowed for this special case\n");
              return false;
          }
          else
          {
              root->siz-=1;
              delchesei(root,&(root->mc));
              return true;
          }
      }
      else if(p==2&&c==3)
      {
          if(noc(root->mc->lc)==3&&noc(root->mc->mc)==3&&noc(root->mc->rc)==3)
          {
              printf("relaxation allowed for this special case\n");
              return false;
          }
          else
          {
              root->siz-=1;
              delchesei(root,&(root->mc));
              return true;
          }
      }
      else
      {

          root->siz-=1;
          delchesei(root,&(root->mc));

          return true;
      }

  }
  if(root->rc&&root->rc->id==delid)
  {
      int p=noc(root);
      int c=noc(root->rc);
      if(p==3&&c==3)
      {
          printf("relaxation allowed for this special case\n");
          return false;
      }
      else if(p==3&&c==2)
      {
          if(noc(root->rc->lc)==3&&noc(root->rc->mc)==3)
          {
              printf("relaxation allowed for this special case\n");
              return false;
          }
          else
          {
              root->siz-=1;
              delchesei(root,&(root->rc));
              return true;
          }
      }
      else if(p==2&&c==3)
      {
          if(noc(root->rc->lc)==3&&noc(root->rc->mc)==3&&noc(root->rc->rc)==3)
          {
              printf("relaxation allowed for this special case\n");
              return false;
          }
          else
          {
              root->siz-=1;
              delchesei(root,&(root->rc));

              return true;
          }
      }
      else
      {
          root->siz-=1;
          delchesei(root,&(root->rc));

          return true;
      }

  }
  if(deleteutil(delid,root->lc)||deleteutil(delid,root->mc)||deleteutil(delid,root->rc))
  {
      if(root)
        root->siz-=1;
      return true;
  }
  return false;
}
void delchesei(node *p,node **c)
{
   int p1=noc(p);
   int c1=noc(*c);
   node *tmp;
   tmp=*c;
   p->mentorscore+=tmp->mentorscore;
   p->salescore+=tmp->salescore;
   if(p1==1&&c1==3)
   {
       p->lc=tmp->lc;
       p->mc=tmp->mc;
       p->rc=tmp->rc;
   }
   else if(p1==3&&c1==2)
   {
       if(noc(tmp->lc)==3)
       {
           *c=tmp->mc;
           adjustmi(*c,tmp->lc);
       }
       else if(noc(tmp->mc)==3)
       {
           *c=tmp->lc;
           adjustmi(*c,tmp->mc);
       }
       else
       {
           if(score(tmp->lc)>=score(tmp->mc))
           {
               *c=tmp->lc;
               adjustmi(*c,tmp->mc);
           }
           else if(score(tmp->lc)<score(tmp->mc))
           {
               *c=tmp->mc;
               adjustmi(*c,tmp->lc);
           }
       }
   }
   else if(p1==2&&c1==3)
   {
       int a1=noc(tmp->lc);
       int b1=noc(tmp->mc);
       int c1=noc(tmp->rc);
       if(a1!=3)
       {
           *c=tmp->lc;
           if(score(tmp->mc)>score(tmp->rc))
           {
               adjust(p,*c,tmp->mc,tmp->rc);
           }
           else
           {
               adjust(p,*c,tmp->rc,tmp->mc);
           }
       }
       else if(b1!=3)
       {
           *c=tmp->mc;
           if(score(tmp->lc)>score(tmp->rc))
           {
               adjust(p,*c,tmp->lc,tmp->rc);
           }
           else
           {
               adjust(p,*c,tmp->rc,tmp->lc);
           }
       }
       else if(c1!=3)
       {
           *c=tmp->rc;
           if(score(tmp->mc)>score(tmp->lc))
           {
               adjust(p,*c,tmp->mc,tmp->lc);
           }
           else
           {
               adjust(p,*c,tmp->lc,tmp->mc);
           }
       }
   }
   else
   {
       *c=tmp->lc;
       if(!p->lc)
       {
           p->lc=tmp->mc;
       }
       if(!p->mc)
       {
           p->mc=tmp->mc;
       }
       if(!p->rc)
       {
           p->rc=tmp->mc;
       }
   }
   free(tmp);
}
