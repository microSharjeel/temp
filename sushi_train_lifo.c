#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sushi_train.h"
#define MAX_LEN 100
FILE* infile;
const char* file_path;
char str[MAX_LEN+1];
char* token;
char* sub_str[4];
//unsigned short scan_array[2];
unsigned short indx;
unsigned short scan_in,scan_out;
static unsigned short time[3];
static ptrTray current_node=NULL;
static ptrTray first_node=NULL;
static unsigned short grand_total;

int main(int argc,char**argv)
{
  //indx=0;
  file_path=argv[1];
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
	  indx=0;
	  token = strtok(str,",");
	  sub_str[indx++]=token;
	  while(token!=NULL)
	  {
	   	token = strtok(NULL,",");
	        if(token!=NULL)
	        {
	          sub_str[indx]=token;//atoi here just like time below
	     	//  scan_array[indx]=atoi(token);	
	        }
	        indx++;
	  }
	indx=0;
	scan_in=atoi(sub_str[2]);//put value in scan in directly 
	scan_out=atoi(sub_str[3]);
	token = strtok(sub_str[1],":");
        time[indx]=atoi(token);
	 while(token!=NULL)
	 {
	   	token = strtok(NULL,":");
	        if(token!=NULL)
	        {
	        	time[++indx]=atoi(token);
	        }
	 }
	
	while(scan_in)
	{
	  push();
	  scan_in--;
	}

	//pop scanned out trays
	while(scan_out) //just in case if no tray was there then what
	{
	  pop();	
	  scan_out--; 
	}
	//apply adjustment 1
	adjustment_1();
	//apply adjustment 2
	adjustment_2();	
	//Push scanned in trays 
      }
  }
  fclose(infile);
  printf ("Accumulated number of trays on sushi train %d\n",grand_total);
  deleteFIFO();
  return 0;
}

void push(void)
{
	ptrTray ptr= (ptrTray) malloc(sizeof(trayType));
	ptr->hour=time[0];
	ptr->min=time[1];
	ptr->sec=time[2];
	ptr->next=NULL;
	grand_total++;
	//nodes are pushed into a FIFO 
	if(current_node!=NULL)
	{
	   ptr->next=current_node;
	   current_node=ptr;
	}
	else
	{    
	   current_node=ptr;
	   first_node=current_node;
	}
}

void pop(void)
{
   //Nodes are popped from FIFO	
   if(current_node!=NULL){
   ptrTray temp = (ptrTray) malloc(sizeof(trayType));
   temp=current_node;
   current_node=current_node->next;
   grand_total--;
   //printf("popped");
   free(temp); }  
}
void adjustment_1(void)
{
   //from 12am to 4pm
   if((time[0]>=3) && (time[0]<16))
   {
     ptrTray ptrTemp=first_node;
     while(ptrTemp!=NULL)
     {
       ptrTemp=ptrTemp->next;
       if ( ((time[0]-first_node->hour)==3) && ((time[1]-first_node->min) ==0 ) && (time[2]-first_node->sec ==0 ) ) 
       {
	 pop();
	 printf("here");
       } 
     }
   }
   //from 4pm to 12am 
   if(time[0]>=16 && time[0]<24)	   
   {
     ptrTray ptrTemp=first_node;
     while(ptrTemp!=NULL)
     {
       ptrTemp=ptrTemp->next;
     //  printf("outer\n");
       if ( (time[0]-first_node->hour==1) && (time[1]-first_node->min ==0) && (time[2]-first_node->sec ==0 ) ) 
       {
	 pop();
	 printf("there\n");
	} 
       else
       { 
         unsigned short t = 60-first_node->min;
	 if( (time[0]-first_node->hour > 1) &&  ( (time[1]+t) ==30) )
	 {
	    pop();
	    printf("here2\n");
	 }
	 if( (time[0]-first_node->hour > 1) && time[1]==0 )  
	 {
	   pop();
	 }
	}
     }
   }  
}
void adjustment_2()
{
 if(grand_total<0)
   grand_total=0;
}
void deleteFIFO(void)
{
 ptrTray temp;
 while(current_node!=NULL)
 {  
  temp=current_node;
  current_node=current_node->next;
  free(temp);
 } 
}

