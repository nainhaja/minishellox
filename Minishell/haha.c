#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
#include "get_next_line.h"
#include <sys/wait.h>

char **split;
int g_start;
int    ft_checkQuotes(int *i,int *cpt,int *cpt2,char *s)
{
    if(s[*i] == '\'')
    {
        *cpt =1;
        *i = *i + 1;
    }
    else if(s[*i] == '"')
    {
        *cpt2 =1;
        *i = *i + 1;
    }
    return *i;
}
void    ft_storeData(char *s,char **str,int start,int i,char **env)
{
    char *test = ft_strjoin(*str,ft_substr(s,start,i-start));
    if(s[i] == '\'')
    {
        *str = ft_strjoin(*str,ft_substr(s,start,i-start));
    }   
    else
    {
        *str = ft_checkDollar(test,env);
    }        
}
char *ft_remove_spaces(char *haha, int *start, int *i)
{
    char *ptr;
    while((haha[*start] == ' ' || haha[*start] == '\t') && haha[*start] != '\0')
        *start = *start + 1;
    *i = *start;
    while(haha[*i] != ' ' && haha[*i] != '\t' && haha[*i] != '\0')
        *i = *i + 1;
    ptr =  ft_substr(haha,*start,*i - *start);
    *start = *i;
    return ptr;
}
char *ft_remove_quotes(char *buf, char **env)
{
    int i = 0;
    int cpt = 0;
    int startquotes,endquotes;
    int start_dquotes,end_dquotes;
    int start = 0,end;
    char *ptr = ft_strdup("");
    while(buf[i])
    {
        if(buf[i] == '\'')
        {
            if(cpt == 0)
            {
                cpt = 1;
                startquotes = i + 1;
                //printf("%s|\n",ft_substr(buf,start,i - start));
                ptr = ft_strjoin(ptr, ft_checkDollar(ft_substr(buf,start,i - start),env));
            }
            else if(cpt == 1)
            {
                start = i + 1;
                endquotes = i;
                cpt = 0;
                ptr = ft_strjoin(ptr, ft_substr(buf,startquotes,endquotes - startquotes));
            }
        }
        else if(buf[i] == '"')
        {
            if(cpt == 0)
            {
                cpt = 2;
                start_dquotes = i + 1;
                ptr = ft_strjoin(ptr, ft_checkDollar(ft_substr(buf,start,i - start),env));
                //printf("%d\n",startquotes);
            }
            else if(cpt == 2)
            {
                start = i + 1;
                end_dquotes = i;
                cpt = 0; 
                //printf("%d| %d|\n",start_dquotes,end_dquotes);
                ptr = ft_strjoin(ptr, ft_checkDollar(ft_substr(buf,start_dquotes,end_dquotes - start_dquotes),env));
                
            }
        }
        i++;
    }
    if (buf[start] != '\0')
        ptr = ft_strjoin(ptr, ft_checkDollar(ft_substr(buf,start,i),env));
    return ptr;
}

char *ft_checkCases(char *s,char **env)
{
    char *ret;
    char *plus;

    int length = strlen(s);
    ret = malloc(sizeof(char)*strlen(s));
    int i=0;
    int cpt = 0;
    int cpt2 = 0;
    int start = 0;
    int Fin=0,end=0;
    char *str;
    str = "";
    start = ft_checkQuotes(&i,&cpt,&cpt2,s);
    while(s[i])
    {
        if((s[i] == '\'' && cpt == 1 ) || (s[i] == '"' && cpt2 == 1 ))
        {
            ft_storeData(s,&str,start,i,env);
            if(s[i+1] == ' ')
                str = ft_AddSpace(str,1);
            cpt = 0;
            end = i+1;
            cpt2 = 0;
            Fin = i+1;
        }
        else if(s[i] == '\'' && cpt == 0 && cpt2 == 0)
        {
            if(i != 0 && s[i-1] == ' ')
               str = ft_strjoin(str,ft_RmSpace(ft_checkDollar(ft_substr(s,end,i-end),env),1));
            else
                str = ft_strjoin(str,ft_RmSpace(ft_checkDollar(ft_substr(s,end,i-end),env),0));
            cpt = 1;
            start = i+1;
        }
        else if(s[i] == '"' && cpt2 == 0 && cpt == 0 )
        {
            cpt2 = 1;
            start = i+1;
            if(i != 0 && s[i-1] == ' ')
                str = ft_strjoin(str,ft_RmSpace(ft_checkDollar(ft_substr(s,end,i-end),env),1));
            else
                str = ft_strjoin(str,ft_RmSpace(ft_checkDollar(ft_substr(s,end,i-end),env),0));
        }
        i++;
    }
    str = ft_strjoin(str,ft_checkDollar(ft_RmSpace(ft_substr(s,Fin,i-Fin),2),env));
    
    ret = str;
    return ret;
}


void copy(char **t,int n)                        
{
    node_t *temp = malloc(sizeof(node_t));
    temp->BeforeEq= ft_BeforeEq(t[0]);
    temp->AfterEq = ft_AfterEq(t[0]);
    temp->next=NULL;
    head = temp;
    int i=1;
    while(i<n)
    {
        node_t *temp2= malloc(sizeof(node_t));
        temp->next= temp2;
        temp2->BeforeEq= ft_BeforeEq(t[i]);
        temp2->AfterEq = ft_AfterEq(t[i]);
        temp2->next = NULL;
        temp=temp2;
        i++;
     }  
}
void printlist() {
    node_t *temp = head;

    while(temp!=NULL)
    {
      printf("%s=",temp->BeforeEq);
      printf("%s \n",temp->AfterEq);
      temp=temp->next;

    }
    //printf("%s ",temp->BeforeEq);
}
void DeleteNode( char *t)
{
    
    node_t *tempp = head;
    while(tempp->next !=NULL)
    {
        if(strcmp(tempp->next->BeforeEq,t) == 0)
        {
            node_t *next = tempp->next->next;
            tempp->next = next;
            break ;
        }
            
        tempp=tempp->next;
    }

}
int     search_lastRed(char *str)
{
    int i=0;
    int cpt=0;
    while(str[i])
    {
        if(str[i] == '>')
            cpt = i;
        i++;
    }
    return cpt;
}
void AddNode(char *beforeEq, char *AfterEq)
{
    node_t *temp =(node_t*) malloc(sizeof(node_t));
    node_t *tempp = head;
    
    temp->BeforeEq = ft_strdup(beforeEq);
    temp->AfterEq = ft_strdup(AfterEq);
    // printf("%s|\n",AfterEq);
    temp->next=NULL;
    while(tempp->next!=NULL)
    {
        //if(strcmp(temp2->BeforeEq,beforeEq) == 0)
          //  break;
        tempp=tempp->next;
    }
    
    tempp->next = temp;
}
// void AddNode(char *beforeEq, char *AfterEq)
// {
//     node_t *temp =(node_t*) malloc(sizeof(node_t)*3);
//     node_t *tempp = head;
    
//     temp->BeforeEq = beforeEq;
//     //temp->AfterEq = AfterEq;
//     //printf("%s|\n",temp->AfterEq);
//     temp->next=NULL;
//     while(tempp->next!=NULL)
//     {
//         //if(strcmp(temp2->BeforeEq,beforeEq) == 0)
//           //  break;
//         tempp=tempp->next;
//     }
//     temp->AfterEq = AfterEq;
//     tempp->next = temp;
// }
char * SearchNode(char *t)
{
    char *afterEq;
    node_t *tempp = head;
    while(tempp->next !=NULL)
    {
        if(strcmp(tempp->next->BeforeEq,t) == 0)
        {
           return tempp->next->AfterEq;
        
        }
        tempp=tempp->next;
    }
    return 0;
}
int ft_strrlen(char **v)
{
    int i=0;
    while(v[i])
    {
        i++;
    }
    return i;
}
void ft_putstr(char *str)
{
    int i = 0;
    while(str[i])
    {
        write(1,&str[i],1);
        i++;
    }
}

void ft_check_split(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '\'')
        {
            i++;
            while(str[i] != '\'')
                i++;
            i++;
        }
        if(str[i] == '"')
        {
            i++;
            while(str[i] != '"')
                i++;
            i++;
        }
        if(str[i] == ';')
        {
            //printf("lqina \n");
            g_red++;
            //exit(0);
        }
        i++;
    }
    //printf("num is %d\n",g_red);
    //exit(0);
}

void ft_stock_split(char *str, int *i,int cpt)
{
    while(str[*i])
    {
        if(str[*i] == '\'')
        {
            *i = *i +1;
            while(str[*i] != '\'')
                *i = *i +1;
            *i = *i +1;
        }
        if(str[*i] == '"')
        {
            *i = *i +1;
            while(str[*i] != '"')
                *i = *i +1;
            *i = *i +1;
        }
        if(str[*i] == ';')
        {
            split[cpt] = ft_substr(str,g_start,*i - g_start);
            //printf("ok -- > %d|\n",g_start);
            g_start = *i + 1;
            
            *i = *i +1;
            
            break;
        }
        *i = *i +1;
    }
    
}
char *ft_check_redr(char *str,int cpt)
{
    int i = 0;
    int start = 0;
    int end=0;
    char *ptr=ft_strdup("");
    g_red_buff = ft_strdup("");
    while(str[i])
    {
        if(str[i] == '\'')
        {
            i = i +1;
            while(str[i] != '\'')
                i = i +1;
            i = i +1;
        }
        if(str[i] == '"')
        {
            i = i +1;
            while(str[i] != '"')
                i = i +1;
            i = i +1;
        }
        if(str[i] == '>' && str[i+1] == '>')
        {
            ptr =ft_strjoin(ptr,ft_substr(str,start,i - start));
            i = i + 2;
            while(str[i] == ' ' && str[i])
                i++;
            g_red_start = i;
            while(str[i] != ' ' && str[i])
                i++;
            g_red_buff = ft_substr(str,g_red_start,i-g_red_start);
            g_fd = open(g_red_buff,O_APPEND | O_RDONLY | O_WRONLY | O_CREAT,0777);
            start = i;
            //split[cpt] = ft_substr(str,g_start,i - start);
            //printf("ok -- > %d|\n",g_start);
            //g_start = i + 1;
            //i = i +1;
            //break;
        }
        i = i +1;
    }
    ptr =ft_strjoin(ptr,ft_substr(str,start,i - start));
    free(split[cpt]);
    split[cpt] = ft_strdup(ptr);
    
    // exit(0);
    return ptr;
}
int main(int argc,char **argv,char **env)
{
    char *haha;
    int i;
    int start = 0;
    g_fd = 1;
    copy(env,ft_strrlen(env));
     char *buff;
     char *ptr;
     int n= 0;
     int startt,j;
     //g_red = 0;
     g_start = 0;
     int awdi=0;
     int split_cpt=0;
        while(path2[i])
        {
            printf("%s\n",path2[i]);
            i++;
        }

    while(1)
    {
         write(1,"$> ",3);
        get_next_line(0,&haha);
        i = 0;
        //printf("awdi |%c|\n",haha[ft_strlen(haha)]);
        //exit(0);
        if(haha[ft_strlen(haha) - 1] != ';')
            haha = ft_strjoin(haha,";");
        
        ft_check_split(haha);
        split = malloc(sizeof(char*)*(g_red));
       //
       
        while (g_red > split_cpt)
        {
            //printf("aha %d|%d|%s\n",awdi,split_cpt,haha);
            ft_stock_split(haha,&awdi,split_cpt);
            split_cpt++;
        }
        
        split_cpt = 0;
        
        while(split_cpt < g_red)
        {
            
            buff = ft_remove_quotes(ft_remove_spaces(ft_check_redr(split[split_cpt],split_cpt), &start, &i),env);
            //buff = ft_remove_quotes(ft_remove_spaces(split[split_cpt], &start, &i),env);
            //printf("buff -->|%s|\n",split[split_cpt]);
            startt = start;

            j = i;
            //i=0;
            if(strcmp(buff,"echo") == 0)
            {
                //printf("buff -->|%s|\n",buff);
                if(strcmp(ft_remove_quotes(ft_remove_spaces(split[split_cpt], &startt, &j),env),"-n") == 0)
                    ft_putstr(ft_checkCases(split[split_cpt]+j+1,env));
                else
                {
                    //printf("string fd>> %d|%s|\n",g_fd,g_red_buff);

                    //printf("res -->|%s|\n",split[split_cpt]+i+1);
                    //ft_putstr_fd("lala sidi ",g_fd);
                    //printf("%d\n",g_fd);
                    //ft_putstr_fd(ft_remove_quotes(split[split_cpt]+i+1,env),1);
                    ft_putstr_fd(ft_remove_quotes(split[split_cpt]+i+1,env),g_fd);

                    write(g_fd,"\n",1);
                }  
            } 
            
            else if(strcmp(buff,"env") == 0)
            {
                printlist();
                
            }
            else if(strcmp(buff,"export") == 0)
            {
                //printf("%s|\n%s|\n",ft_BeforeEq(split[split_cpt]+i+1),ft_AfterEq(split[split_cpt]+i+1));
                AddNode(ft_BeforeEq(split[split_cpt]+i+1),ft_AfterEq(split[split_cpt]+i+1));
            }
            else if(strcmp(buff,"unset") == 0)
            {
                DeleteNode(split[split_cpt]+i+1);
            }
            else
            {
                int c = 0;
                char *str;
                int fdd;
                int id=fork();
                if(id == 0)
                {
                    char *argvv[]={buff,NULL};
                    char *envv[]={NULL};
                    while(path2[c])
                    {
                        printf("%s\n",path2[c]);
                        c++;
                    }
                    c = 0;
                    while(path2[c])
                    {
                        str = ft_strjoin(path2[c],"/");
                        str = ft_strjoin(str,buff);
                        //printf("|%s|\n",str);
                        fdd = open(str, O_RDWR);
                        //printf("|%d|\n",fdd);
                        if (fdd)
                        {
                             execve(str, argvv, envv);
                             exit(0);
                        }
                        c++;
                    }
                }
                wait(NULL);
                //parent kitsna child imot bach ikmel khdimto
            }
            i = 0;
            start = 0;
            split_cpt++;
        }
        start = 0;
        
        
        split_cpt = 0;
        while(split_cpt < g_red)
        {
            free(split[split_cpt]);
            split_cpt++;
        }
        //free(split[split_cpt]);
        //free(split);
        split_cpt = 0;
        g_red = 0;
        i = 0;
        awdi = 0;
        g_start = 0;
     //printf("%s\n",ft_checkDollar(ayoub,env));
    }
   
}


