#include "utils.h"
#include <ctype.h>
#include "validator.h"


#define MAXLABELSIZE 30
#define MAXERRORSIZE 200
#define NOMATCH "none"


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


		printf("After label validation:\nFile is: ");

		if (item.valid==TRUE){
			printf(KGREEN "valid\n");
		} else {
			printf(KRED "invalid\n");
		}

		NORMALCOLOR
	}

	if(strcmp(item.instruction,"\0") != 0){
		/*VALIDATE INSTRUCTION*/
		printf("instruction exists\n");
		validate_instruction(&item,&error_list_head);;


		printf("After instruction validation:\nFile is: ");

		if (item.valid==TRUE){
			printf(KGREEN "valid\n");
		} else {
			printf(KRED "invalid\n");
		}

		NORMALCOLOR



		validate_ins_data(&item, &error_list_head);

		NORMALCOLOR

		printf("After instruction -Operands validation:\nFile is: ");

		if (item.valid==TRUE){
			printf(KGREEN "valid\n");
		} else {
			printf(KRED "invalid\n");
		}

		NORMALCOLOR
		printf("finished validating file\n");
	}
/*
	if(strcmp(item.operantion,"\0") != 0){
		printf("operation exists\n");
		validate_operation(item.operantion);
		validate_oper_operands(item);
	}

	if(strcmp(item.label,"\0") != 0){

	}
*/




	/*
	for (i=0;i<array_size; i++){
		item=parsed[i];
		printf("current_struct:\n");


*/

	printf(KYELLOW"------------------------------\n");
    printf("      ERRORS:        \n");
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
				add_to_list(head,error);
			}

		}

		i++;
	}

	/*validating that the label is not a saved word*/
	printf("label is a special word: %s\n",find_command_name(label));

	if (strcmp("none",find_command_name(label)) != 0){
		item->valid=FALSE;
		sprintf(error,"4. Error found in line %d: label <%s> is a preserved word.\n",line_number,label);
		add_to_list(head,error);
	}

}

void validate_instruction(body* item, list_item_reference*  head){
	int line=item->line_number;
	String inst_value= item->instruction;
	char error[MAXERRORSIZE];

	/*Check if instruction is all lower case*/
	if (is_string_lowercase(inst_value)==FALSE){
		item->valid=FALSE;
		sprintf(error,"5. Error in line %d: Instruction value <%s> has non-lowecase chars.\n",line,inst_value);
		add_to_list(head,error);
	}

	/*check if instruction is a valid command*/

	if (strcmp(NOMATCH,find_command_name(item->instruction))==0){
		item->valid=FALSE;
		sprintf(error,"6. Error in line %d: Instruction value <%s> is unrecognized.\n",line,inst_value);
		add_to_list(head,error);
	}

}

void validate_operation(body* item, list_item_reference*  head){

}

/*This function validates that the operands are valid numbers*/
void validate_ins_data (body* item, list_item_reference*  head){
	int num_of_operands;
	int line;
	Bool invalid_char_found=FALSE;
	int counter;
	String current;
	char c;
	int str_length;
	int i;
	char error[MAXERRORSIZE];

	num_of_operands=item->data_values_number;
	line=item->line_number;


	/*check if each string has valid numbers*/
	for(counter=0;counter<num_of_operands;counter++){
		printf(KMAGENTA "working on: %s\n",item->data_string_array[counter]);

		current=item->data_string_array[counter];
		str_length=strlen(current);

	/*first char is a symbol - or +*/
		i=0;
		if (current[i]=='-' || current[i]=='+'){
			i++;
		}



		while (i<str_length){
			c=current[i];
			if(is_valid_number(c) ==FALSE){
				invalid_char_found=TRUE;
			}
			i++;
		}


		if (invalid_char_found==TRUE){
			item->valid=FALSE;
			sprintf(error,"7. Error in line %d: non-numbers received in %s, for command %s.\n",line,current,item->instruction);
			add_to_list(head,error);
			return;
		}

		/*If we reached here, it means that we have valid numbers*/
		if((item->data_int_values=(int*)malloc(sizeof(int)*num_of_operands)) == NULL){
			fprintf(stderr,"Unable to allocate memory to data_int_values. Continuing\n");
		}


		for (counter=0;counter<num_of_operands;counter++){
			item->data_int_values[counter]=atoi(item->data_string_array[counter]);
			printf("current cell: %s, extracted number: %d\n",item->data_string_array[counter],item->data_int_values[counter]);
		}

		free(item->data_string_array);

	}


void validate_ins_string (body* item, list_item_reference*  head){

}

void validate_ins_mat(body* item, list_item_reference*  head){

}

void validate_ins_entry(body* item, list_item_reference*  head){

}

void validate_ins_extern(body* item, list_item_reference*  head){

}





}

void validate_oper_operands (body* item, list_item_reference*  head){

}


Bool is_valid_letter(char c){

	if ( ('a'<=c && c<= 'z') || ('A'<=c && c<= 'Z')){
		return TRUE;
	}

	return FALSE;


}

Bool is_lowcase(char c){
	if ('a'<=c && c<='z'){
			return TRUE;
	}

	return FALSE;
}

Bool is_string_lowercase(String str){
	int length = strlen(str);
	Bool lowercase=TRUE;
	int i;
	char c;
	i=0;

	c=str[i];
	while(i<length && lowercase==TRUE){
		if(is_lowcase(c)==FALSE){
			lowercase=FALSE;

		}

		i++;
		c=str[i];
	}

	return lowercase;
}


Bool is_valid_number (char c){
	if(isdigit(c)){
		return TRUE;
	}

	return FALSE;
}




























String find_command_name(String key){
	String data="data";
	String str="string";
	String mat="mat";
	String entry="entry";
	String none=NOMATCH;
	String external="external";

	String mov="mov";
	String cmp="cmp";
	String add="add";
	String sub="sub";
	String lea="lea";

	String not="not";
	String clr="clr";
	String inc="inc";
	String dec="dec";
	String jmp="jmp";
	String bne="bne";
	String red="red";
	String prn="prn";
	String jsr="jsr";

	String rts="rts";
	String stop="stop";

	if (strcmp(key,data)==0){
		return data;
	}
	if (strcmp(key,str)==0){
		return str;
	}
	if (strcmp(key,mat)==0){
		return mat;
	}
	if (strcmp(key,entry)==0){
		return entry;
	}
	if (strcmp(key,external)==0){
		return external;
	}



	if (strcmp(key,mov)==0){
		return mov;
	}

	if (strcmp(key,cmp)==0){
		return cmp;
	}

	if (strcmp(key,add)==0){
		return add;
	}

	if (strcmp(key,sub)==0){
		return sub;
	}

	if (strcmp(key,lea)==0){
		return lea;
	}


	if (strcmp(key,not)==0){
		return not;
	}
	if (strcmp(key,clr)==0){
		return clr;
	}

	if (strcmp(key,inc)==0){
		return inc;
	}

	if (strcmp(key,dec)==0){
		return dec;
	}

	if (strcmp(key,jmp)==0){
		return jmp;
	}

	if (strcmp(key,bne)==0){
		return bne;
	}

	if (strcmp(key,red)==0){
		return red;
	}

	if (strcmp(key,prn)==0){
		return prn;
	}

	if (strcmp(key,jsr)==0){
		return jsr;

	}

	if (strcmp(key,rts)==0){
		return rts;
	}

	if (strcmp(key,stop)==0){
		return stop;
	}

	return none;


}