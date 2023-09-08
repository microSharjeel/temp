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
	  pop();	
	  scan_out--; 
	}
///////////////////////////////////////////
//	adj1 adj2	
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
 void pop()
  {
   ptrTray temp = (ptrTray) malloc(sizeof(trayType));
   temp=first_node;
   first_node=first_node->next;
   free(temp);   
  }
 void adjustment_1()
  {
   //from 12am to 4pm //add start of the day aswell
   if(first_node->hour<=16)
   {
	   while(first_node->next!=current_node)
	   {
	     if((current_node->hour-first_node->hour)==3) //think about it if all of the nodes were added at same time
	     //3hrs ago ? for this u need current timestamp no matter if the scan in is there or not!
	     {
	       
	     }
	   }
   }	   
   //from 4pm to 12am
  }
