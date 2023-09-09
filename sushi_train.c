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
unsigned short time[3];
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
//	scan_in=scan_array[0];
//	scan_out=scan_array[1];
//////////////////////////////////////////////
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
	adjustment_1();
	//apply adjustment 2
	adjustment_2();
	//pop scanned out trays
	while(scan_out) //just in case if no tray was there then what
	{
	  //if(grand_total)
	  pop();	
	  scan_out--; 
	}
	//pop all trays if 12am is the time e.g., scanned in at 11:00 and 12:00 am is the time	
	//apply adjustment 1
	
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
	   current_node->next=ptr;
	   current_node=current_node->next;
	}
	else
	{    
	   current_node=ptr;
	   first_node=current_node;
	}
}

void pop(void)
{
   if(first_node!=NULL){
   ptrTray temp = (ptrTray) malloc(sizeof(trayType));
   temp=first_node;
   first_node=first_node->next;
   grand_total--;
   free(temp); }  
}
void adjustment_1(void)/////////////////////????????? seconds ???????????
{
   //from 12am to 4pm
   if((time[0]>=3) && (time[0]<16))
   {
     ptrTray ptrTemp=first_node;
     while(ptrTemp!=NULL)
     {
       ptrTemp=ptrTemp->next;
       if ( (time[0]-first_node->hour)>=3 && ((time[1]-first_node->min) ==0 ) ) 
	 pop();
     }
   }
   //from 4pm to 12am 
   else if(time[0]>=16 && time[0]<24)	   
   {
     ptrTray ptrTemp=first_node;
     while(ptrTemp!=NULL)
     {
       ptrTemp=ptrTemp->next;
 //      if((time[0]-first_node->hour)>=1.5)
       if ( (time[0]-first_node->hour)>=1.5 && ((time[1]-first_node->min) ==0 ) ) 
	 pop();
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
 while(first_node!=NULL)
 {  
  temp=first_node;
  first_node=first_node->next;
  free(temp);
 } 
}

