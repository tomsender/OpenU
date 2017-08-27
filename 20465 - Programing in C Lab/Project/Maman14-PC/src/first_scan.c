/*
 * label_finder.c
 *
 *  Created on: Aug 25, 2017
 *      Author: alexz
 */

#include "first_scan.h"







/*
 * Searches and returns a symbol for a given key (a label in a list of labels)
 */
symbol_ptr search_symbol (String key, symbol_ptr list){
	symbol_ptr current_pointer=list;

	while ((current_pointer->next)!=NULL){
		if (strcasecmp(key,current_pointer->name) == 0){
			return current_pointer;

		}
		current_pointer=current_pointer->next;
	}

	return NULL;
}


void first_scan(bodyArray items, int bodyarray_size){
	int IC,DC;
	int item_counter;
	body current;
	symbol_ptr symbols_list_head=NULL;
	char error[MAXERRORSIZE];
	symbol_ptr current_symbol;
	list_item_reference errors_list=NULL;
	Bool error_found=FALSE;


	IC=DC=0;

	for (item_counter=0;item_counter<bodyarray_size;item_counter++){
		current=items[item_counter];

		/*Label exists*/
		if (strlen(current.label) != 0){
			/*check if it already exists*/

			if (search_symbol(current.label,symbols_list_head) != NULL){
				sprintf(error,"label %s is a duplicate.\n",current.label);
				add_to_list(&errors_list,error);
				error_found=TRUE;
			}
		}

			/*New label, needs to be added*/
		current_symbol=create_symbol(current,IC,DC); /*create new symbol*/
		add_symbol_to_list(current_symbol,&symbols_list_head);/*adds to list of symbols*/


		IC+=calc_new_ic();/*advance ic*/
		DC+=calc_new_dc();/*advance dc*/


	}

	print_symbol_list(symbols_list_head);

}


symbol_ptr create_symbol(body item,int ic, int dc){
	symbol_ptr sym;


	/*copy label*/
	sym=(symbol_ptr)allocate_mem_general(1,sizeof(sym));
	sym->name=(String)allocate_mem_general(strlen(item.label),sizeof(char));
	strcpy(sym->name,item.label);



	/*Address*/
	if (strlen(item.operantion)==0){ /*is operation was not received*/
		/*instructions*/
		if (strcmp(item.operantion,"data")==0 ||
			strcmp(item.instruction,"mat")==0||
			strcmp(item.instruction,"string")==0){
			sym->address=dc;
			sym->declaration_type=internal;
			sym->command_type=instructional;
		}

		if (strcmp(item.instruction,"extern")==0){
			sym->name=item.OPERAND1;
			sym->address=0;
			sym->declaration_type=external;
			sym->command_type=unknown;
		}
	}
	else{
		/*Operational Command*/
		sym->address=ic;
		sym->declaration_type=internal;
		sym->command_type=operational;

	}



	printf("finished with the symbol creation\n");
	return sym;

}



void add_symbol_to_list(symbol_ptr current,symbol_ptr* list){
	symbol_ptr p;

	if (!*list){
		printf("list is empty\n");

		/*list=(symbol_ptr)allocate_mem_general(1,sizeof(symbol_ptr));*/
		(*list)=current;
		(*list)->next=NULL;
		return;
	}

	printf("list is not empty\n");
	p=*list;
	while (p->next != NULL){
		p=p->next;
	}

	p->next=current;
	p->next->next=NULL;

}

int calc_new_ic(){
	return 0;
}

int calc_new_dc(){
	return 0;
}
