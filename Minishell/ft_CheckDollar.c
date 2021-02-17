
#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
#include "get_next_line.h"
#include <sys/wait.h>


char *ft_BeforeEq(char *k)
{
    int i=0;
    char *str;
    str = malloc(sizeof(char)*strlen(k));
    while(k[i])
    {
        if(k[i] == '=')
        {
            str[i] = 0;
            break;
        }
        str[i] = k[i];
        i++;
    }
    return str;
}
char *ft_AfterEq(char *k)
{
    int i=0;
    char *str;
    str = malloc(sizeof(char)*strlen(k));
    if(strstr(k,"PATH") != NULL)
    {
        path = strstr(k,"PATH");
        path2 = ft_split(&path[5],':');
    }
    while(k[i])
    {
        if(k[i] == '=')
        {
            i++;
            break;
        }
        i++;
    }
    str = k+i;
    return str;

}
void ft_check_redirecitions(char *ptr)
{
    int i = 0;
    while(ptr[i])
    {
        if(ptr[i] == ';')
        {
            g_red = i;
            break;
        }  
    }
}
void    ft_CheckVariables(char *str,char **env,char **stock,int *j)
{
    int i=0,p=0;
    char *s;
    node_t *temp = head; 
    
    while(temp!=NULL)
     {
         if(strcmp(temp->BeforeEq,str) == 0)
         {
            s = temp->AfterEq;
            while(s[p])
            {
                stock[0][*j] = s[p];
                p++;
                *j = *j + 1;
            }
             break;
         }         
        temp=temp->next;
     }
}
char *ft_checkDollar(char *str,char **env)
{
    int p=0;
    int j=0;
    int start,end;
    int cpt =0;
    char *stock = malloc(sizeof(char) * 100);
    while(str[p])
    {
        if(str[p] == '$' && str[p+1] != '/')
        {
            cpt = 1;
            p++;
            start = p;
            while(str[p] != '$' && str[p] != ' ' && str[p] != '\0' && str[p] != '\'' && str[p] != '"')
                p++;
            ft_CheckVariables(ft_substr(str,start,p-start),env,&stock,&j);
        }
        else
        {
            stock[j] = str[p];
            j++;
            p++;
        }
    }
        if(cpt == 1)
            return stock;
        else
            return str;
        
    
}