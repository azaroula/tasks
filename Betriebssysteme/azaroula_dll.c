#include "azaroula_dll.h"


//-----------------------------------------------------------
 /* initialize "shortcut links" for empty list */
void
list_init(struct list_head *head){

 	head->next = head;
 	head->prev = head;
}

//-----------------------------------------------------------
 /* insert new entry after the specified head */
void
list_add(struct list_head *new, struct list_head *head){
 
 	head->next->prev = new;
 	new->prev = head;
 	new->next = head->next;
 	head->next = new;
}

//-----------------------------------------------------------
 /* insert new entry before the specified head */
void
list_add_tail(struct list_head *new, struct list_head *head){

 	new->next = head;
 	head->prev->next= new;
 	new->prev = head->prev;
 	head->prev = new;
}

//----------------------------------------------------------- 
 /* deletes entry from list, reinitializes it (next = prev = 0),
 and returns pointer to entry */
struct list_head*
list_del(struct list_head *entry){

 	entry->prev->next= entry->next; 
 	entry->next->prev= entry->prev;
 
 	entry->next= 0; 
 	entry->prev= 0;

 	return entry;
}

//-----------------------------------------------------------
 /* delete entry from one list and insert after the specified head */
void
list_move(struct list_head *entry, struct list_head *head){

 	entry->prev->next= entry->next; 
 	entry->next->prev= entry->prev;

 	head->next->prev = entry;
 	entry->prev = head;
 	entry->next = head->next;
 	head->next = entry;
} 

//-----------------------------------------------------------
 /* delete entry from one list and insert before the specified head */
void
list_move_tail(struct list_head *entry, struct list_head *head){

 	entry->prev->next= entry->next; 
 	entry->next->prev= entry->prev;
 
 	entry->next = head;
 	head->prev->next= entry;
 	entry->prev = head->prev;
 	head->prev = entry;
}

//-----------------------------------------------------------
 /* tests whether a list is empty */
int
list_empty(struct list_head *head){

 	if (head->next == head && head->prev == head)
 		return TRUE; 
 
 	else return FALSE;
}
