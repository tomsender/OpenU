#include "utils.h"
#include <ctype.h>
#include "validator.h"


#define MAXLABELSIZE 3
#define MAXERRORSIZE 200



/*Macro that adds a log*/
#define INVALIDINPUT fprintf(stderr, "Invalid input: ");

void validate_file(bodyArray parsed, int array_size){
	int i;
	body item;
	list_item_reference error_list_head;

	printf(KYELLOW"------------------------------\n");
    printf("      VALIDATION STAGE:        \n");
	printf("------------------------------\n");


	NORMALCOLOR

	i=0;
	item=parsed[i];
	error_list_head=NULL;


	if(strcmp(item.label,"\0") != 0){
		/*VALIDATE LABEL*/
		validate_label(&item,&error_list_head);

		printf("finished validating file\n");
		if (item.valid==TRUE){
			printf(KGREEN "Label <%s> is valid\n",item.label);
		} else {
			printf(KRED "Label <%s> is invalid\n",item.label);
		}



	}

/*	if(strcmp(item.instruction,"\0") != 0){
		printf("instruction exists\n");
		validate_instruction(item.instruction);
		validate_ins_oprands(item);
	}

	if(strcmp(item.operantion,"\0") != 0){
		printf("operation exists\n");
		validate_operation(item.operantion);
		validate_oper_operands(item);
	}

	if(strcmp(item.label,"\0") != 0){

	}*/





	/*
	for (i=0;i<array_size; i++){
		item=parsed[i];
		printf("current_struct:\n");


*/

	printf(KYELLOW"------------------------------\n");
    printf("      ERROS:        \n");
	printf("------------------------------\n");

	print_list(error_list_head);
	NORMALCOLOR

	free(error_list_head);

}



void validate_label (body* item, list_item_reference*  head){
	String label;
	int line_number;
	char error[MAXERRORSIZE];
	int length;
	int size;
	int i;
	char c;
	Bool valid_letter;
	Bool is_a_num;


	label=item->label;
	line_number=item->line_number;


	/*validating label length*/
	length=strlen(label);
	if (length > MAXLABELSIZE){
		sprintf(error,"1. Error in line %d: Label <%s> is too long.\n",line_number,label);
		add_to_list(head,error);
		item->valid=FALSE;

	}


	/*validate the first char*/
	i=0;
	c=label[i];
	valid_letter=is_valid_letter(c);

	if (valid_letter==FALSE){
		item->valid=FALSE;
		sprintf(error,"2. Error in line %d: Label <%s> doesn't start with a letter (%c).\n",line_number,label,c);
		add_to_list(head,error);
	}
	i++;


	/*validating each char in the string, starting from cell #1:*/

	size=strlen(label);
	while (i<size){
		c=label[i];
		valid_letter=is_valid_letter(c);
		if (valid_letter==FALSE){
			/*not a letter*/
			is_a_num=is_valid_number(c);

			if (is_a_num==FALSE){
				item->valid=FALSE;

				printf("weird character\n");
				sprintf(error,"3. Error found in line %d: invalid char <%c> found in label <%s>.\n",line_number,c,label);
				printf("%s\n",error);
				add_to_list(head,error);
			}

		}

		i++;
	}

}

void validate_instruction(String inst){

}

void validate_operation(String operation){

}

void validate_ins_oprands (body item){

}

void validate_oper_operands (body item){

}



Bool is_valid_letter(char c){

	if ( ('a'<=c && c<= 'z') || ('A'<=c && c<= 'Z')){
		return TRUE;
	}

	return FALSE;


}

Bool is_valid_number (char c){
	if(isdigit(c)){
		return TRUE;
	}

	return FALSE;
}
