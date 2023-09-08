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
static ptrTray current_node=NULL;
static ptrTray first_node=NULL;
static unsigned short grand_total;

int main(int argc,char**argv)
{
  index=0;
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
	  //printf("%s\n",str);
	  token = strtok(str,",");
	  //puts(token);
	  sub_str[index++]=token;
	  while(token!=NULL)
	  {
	   	token = strtok(NULL,",");
	        
	        if(token!=NULL)
	        {
	    //    	puts(token);
	        	sub_str[index]=token;
	        }
	        index++;
	  }
	index=0;
	scan_in=atoi(sub_str[2]);
	scan_out=atoi(sub_str[3]);
	token = strtok(sub_str[1],":");
	//puts(token);
        time[index]=atoi(token);
	 while(token!=NULL)
	 {
	   	token = strtok(NULL,":");
	        if(token!=NULL)
	        {
	  //      	puts(token);
	        	time[++index]=atoi(token);
	        }
	 }
	//Push scanned in trays 
	while(scan_in)
	{
	  push();
	  scan_in--;
	}
	//pop scanned out trays
	while(scan_out) 
	{
	  pop();	
	  scan_out--; 
	}
	//pop all trays if 12am is the time e.g., scanned in at 11:00 and 12:00 am is the time	
	//apply adjustment 1
	adjustment_1();
	//apply adjustment 2
	adjustment_2();
      }
  }
  fclose(infile);
  printf ("Accumulated number of trays on sushi train %d\n",grandTotal);
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
   ptrTray temp = (ptrTray) malloc(sizeof(trayType));
   temp=first_node;
   first_node=first_node->next;
   grand_total--;
   free(temp);   
}
void adjustment_1(void)
{
   //from 12am to 4pm
   if(time[0]>=3) && (time[0]<=16))
   {
     ptrTray ptrTemp=first_node;
     while(ptrTemp!=NULL)
     {
       ptrTemp=ptrTemp->next;
       if((time[0]-first_node->hour)==3)
	 pop();
     }
   }
   //from 4pm to 12am 
   else if(time[0]>16 && time[0]<24)	   
   {
     ptrTray ptrTemp=first_node;
     while(ptrTemp!=NULL)
     {
       ptrTemp=ptrTemp->next;
       if((time[0]-first_node->hour)==1.5)
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

