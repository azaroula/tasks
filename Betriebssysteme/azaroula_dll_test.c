#include <stdio.h>
#include <stdlib.h>
#include "azaroula_dll.h"

struct proc_info{
	struct list_head kopf;
  	int pid;
};    
 
struct list_head *anker,*tmp;

//------------------------------------------------------------------
void printlist(void){
 	struct list_head *temp;
	temp = anker;
 	temp = temp->next;
 	while(temp != anker){
 		printf("<--pid:%d--> ",((struct proc_info*)temp)->pid);
		temp = temp->next;
	 }	
	 printf("\n\n");   
}
//------------------------------------------------------------------

int main(void){
 	struct proc_info *prozess;
 	int i;
 
 	anker = malloc(sizeof(struct list_head));
 	list_init(anker);

	tmp=anker;
 
 	printf("Erstelle Liste\n");
 	for(i=0; i<4; i++){
 		prozess = malloc(sizeof(struct proc_info));
 		prozess->pid=i;
 		list_add(&prozess->kopf, tmp);
 		tmp = &prozess->kopf;
 	}
 	printlist();
  
 	prozess = malloc(sizeof(struct proc_info));
 	prozess->pid=4;
 	printf("list_add_tail von pid:%d\n",prozess->pid); 
 	list_add_tail(&prozess->kopf, tmp);
 	printlist();
 
 	list_del(tmp);
 	printf("gelöschtes Objekt: pid:%d\n",((struct proc_info*)tmp)->pid);
 	printlist();
 	free((struct proc_info*)tmp);
 	tmp = &prozess->kopf;

 	tmp = tmp->prev->prev;
 	printf("List_move mit entry=pid:%d und Head=pid:%d\n",((struct proc_info*)tmp)->pid,prozess->pid);
 	list_move(tmp, &prozess->kopf);
 	printlist();
 
 	tmp = tmp->next->next;
 	printf("List_move_tail mit entry=pid:%d und Head=pid:%d\n",((struct proc_info*)tmp)->pid,prozess->pid);
 	list_move_tail(tmp, &prozess->kopf);
 	printlist();
 
 	if (list_empty(anker)== TRUE)
 		printf("Liste ist leer\n");
 	else 
 		printf("Liste ist nicht leer\n");

	return 0;
}

