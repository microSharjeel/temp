#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sushi_train.h>

FILE* infile;
const char* file_path;
char str[MAX_LEN+1];
char* token;
char* sub_str[4];
unsigned short index;
unsigned short scan_in,scan_out;
unsigned short time[3];
/////////////////////////////// change it 
static ptrTray current_node=NULL;
static ptrTray first_node=NULL;
///////////////////////////////
int main(int argc,char**argv)
{
  index=0;
  file_path=argv[1];
/////////////////////////////////////////////////////////////////// in one function
  infile=fopen(file_path,"r");
  if(infile==NULL)
  {
  	printf("\n failed to open file\n %s\n",file_path);
  	exit(1);
  }
  else
  {
  	printf("\nfile opened\n");
  	while(fscanf(infile,"%s",str)!=EOF)
	{
	  printf("%s\n",str);
	  token = strtok(str,",");
	  puts(token);
	  sub_str[index++]=token;
	  while(token!=NULL)
	  {
	   	token = strtok(NULL,",");
	        
	        if(token!=NULL)
	        {
	        	puts(token);
	        	sub_str[index]=token;
	        }
	        index++;
	  }
	  index=0;
	scan_in=atoi(sub_str[2]);
	scan_out=atoi(sub_str[3]);
	/////////////////////////////
	while(scan_in)
	{
	   index=0;
	   token = strtok(sub_str[1],":");
	   puts(token);
           time[index]=atoi(token);
	  while(token!=NULL)
	  {
	   	token = strtok(NULL,":");
	        if(token!=NULL)
	        {
	        	puts(token);
	        	time[++index]=atoi(token);
	        }
	  }
	  scan_in--;
	  if(current_node!=NULL)
	  {
	   current_node->next=push();
	   current_node=current_node->next;
	  }
	  else
          current_node=push();
	  if(first_node==NULL)
	  	first_node=current_node;
	}
	/////////////////////////////
	while(scan_out) 
	{
	  first_node=first_node->next;
	  //pop()	add here	
	  scan_out--; 
	}
      }
  }
  fclose(infile);	
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
 ptrTray push()
  {
	ptrTray ptr= (ptrTray) malloc(sizeof(trayType));//&newTray;
	ptr->hour=time[0];
	ptr->min=time[1];
	ptr->sec=time[2];
	ptr->next=NULL;
	return ptr;
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
#include<stdio.h>
#include<stdlib.h>
typedef struct node_type
{
  int value;
  struct node_type* ptr_node;
}*nptr,node;

static nptr current_node=NULL;
static nptr first_node=NULL;
//static unsigned int count;
nptr add_node(int val)
{
  nptr nd = (nptr)malloc (sizeof(node));
  nd -> value=val;
  nd -> ptr_node=NULL;
  if(current_node==NULL)
    current_node=nd;
  else
    current_node->ptr_node=nd;
 
  return nd;
}
void traverse_add(nptr nd,int count)
{  
  while(nd->ptr_node!=NULL)
    {
      count+=nd->value;
      printf("value=%d\n",nd->value);
      nd = nd->ptr_node;
    }
  count+=nd->value;
  printf("value=%d\n",nd->value);
 
}
void add_position(int val,nptr nd)
{
  if(nd->ptr_node!=NULL)
    {
      while(nd->value!=val)
       {
         nd=nd->ptr_node;
       }
      nptr nod = (nptr) malloc(sizeof(node));
      nod->value = val;
      nod->ptr_node = nd->ptr_node;
      nd->ptr_node=nod;
    }  
}
int main()
{
  int count=0;
  for(int i=0;i<5;i++)
    {
     if(current_node==NULL)
      first_node=add_node(i);
     else
       current_node=add_node(i);
    }
  traverse_add(first_node,count);
  printf("count=%d\n",count);
  //  std::cout<< count<<std::endl;
  add_position(2,first_node);
  count=0;
  traverse_add(first_node,count);
  printf("count=%d\n",count);
  //  std::cout<< count <<std::endl;
  //std::cin.get();
  return 0;
}*/
