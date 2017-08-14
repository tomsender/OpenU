/*
 * parser.c
 *
 *  Created on: Aug 3, 2017
 *      Author: alexz
 */



#include "parser.h"
#include "utils.h"

#define INITIAL_SARRAY_SIZE 8000
#define ADDEDSIZE 1
/*
 * This macro helps calculating which parts of the array need to be copied
 */
#define CALCSIZE(array_start, index)\
	(index-array_start)*sizeof(char);

/*
 * This macro is used when I want to reresent a string as empty.
 * It allocates 1 memory and inserts \0 as the string value.
 *
 */
#define RETURN_NULL(result) \
	result=allocate_mem_string(1); \
	strcpy(result,"\0");

/*
 * Frees the extract_value that receives from the function
 * Allocates new memory
 */
#define REALLOCATE_EXTRACTED_VALUE\
	free(extracted_value);\
	extracted_value=allocate_mem_string(strlen(current_pointer));


bodyArray  parse_file (FILE * file, int* parsed_size, int * n_lines){
	String line;
	bodyArray parsed_file;
	int cell_counter;


	line=allocate_mem_string(MAXMEM);
	parsed_file=allocate_mem_struct(INITIAL_SARRAY_SIZE);

	cell_counter=0;


	while (  (fgets(line,MAXMEM,file)) != NULL){
		*n_lines+=1;

		if (check_empty_line(line)==FALSE && line[0]!=';'){
			printf("______________________________________________\n");
			printf("Working on line: [%s\n",line);

			parsed_file[cell_counter] = parse_line(line,*n_lines);
			cell_counter++;
		}
	}

	if (cell_counter>0){
		*parsed_size=cell_counter;
	}else{
		*parsed_size=0;
	}

	printf("\n---Finished parsing file---\n");
	return parsed_file;
}

body  parse_line (String str, int line_number){
	body result;
	int i;
	int result_size;
	char * extracted_value;
	char * current_pointer;
	int size;
	int n_skipped_spaces;
	int data_array_size=0;
	int str_length;

	printf(KYELLOW "------------------------------\n");
    printf("      PARSING LINE:        \n");
	printf("------------------------------\n");
	NORMALCOLOR


	/*puts \0 instead of \n*/
	str_length=strlen(str);
	str[str_length-1]='\0';

	result.line_number=line_number;
	n_skipped_spaces=count_spaces(str);
	str+=n_skipped_spaces;
	current_pointer=str;
	result.valid=TRUE;



	/*extract label*/
	extracted_value=extract_label(current_pointer);

	result_size=strlen(extracted_value)+1;

	result.label=allocate_mem_string(result_size);
	strcpy(result.label,extracted_value);

	if ((strcmp(extracted_value,"\0")) != 0){
		current_pointer+=result_size; /*Advance current_pointer to point to after ':'*/
	}
	printf(KBLUE "---Extracted label: [%s]\n",result.label);
	NORMALCOLOR
	REALLOCATE_EXTRACTED_VALUE;


	/*extract instruction*/
	n_skipped_spaces=count_spaces(current_pointer);
	current_pointer+=n_skipped_spaces;

	printf(KGREEN "--counted spaces: %d\n",n_skipped_spaces);
	printf(KGREEN "--current pointer: <%s>\n",current_pointer);

	extracted_value=extract_instruction(current_pointer);

	result_size=strlen(extracted_value)+1;
	result.instruction=allocate_mem_string(result_size);
	strcpy(result.instruction,extracted_value);




	/*
	 * Instruction exists:
	 * result.Instruction should be updated
	 * current pointer should be advanced
	 * operation should be updated with null
	 *
	 */
	if ((strcmp(extracted_value,"\0")) != 0){ /*instruction exists*/
		printf(KBLUE "---Extracted instruction: [%s]\n",extracted_value);
		NORMALCOLOR

		/*advance the pointer*/
		current_pointer+=result_size;
		printf(KCYN "---Current pointer: [%s]\n",current_pointer);
		NORMALCOLOR

		REALLOCATE_EXTRACTED_VALUE;

		/*Update operation=null*/
		result.operantion=allocate_mem_string(1);
		strcpy(result.operantion,"\0");

	}
	/*
	 * Instruction doesn't exist:
	 * operation should be extracted
	 *
	 */

	else {
		printf(KGREEN "extracting operation:\n");

		/*EXTRACT THE OPERATION*/
		extracted_value=extract_operation(current_pointer);
		result_size=strlen(extracted_value)+1;
		result.operantion=allocate_mem_string(result_size);
		strcpy(result.operantion,extracted_value);
/*
		if (strcmp(extracted_value,"\0") == 0 ){
			current_pointer+=result_size-1;
		}*/

		current_pointer+=result_size;
/*
		if ( strcmp(extracted_value,"\0") != 0 ){
			current_pointer+=result_size-1;
		}
*/

		n_skipped_spaces=count_spaces(current_pointer);
		current_pointer+=n_skipped_spaces;
		printf(KRED"skipped_spaces: %d\n",n_skipped_spaces);
		NORMALCOLOR

	}

		REALLOCATE_EXTRACTED_VALUE;

		printf(KBLUE "---!Extracted operation: [%s]\n",result.operantion);
		printf(KCYN "---sCurrent pointer: [%s]\n",current_pointer);
		NORMALCOLOR

	/*PARSING OPERANDS*/
	/*
	 * In case of .data, we invoke a specific method that breaks the string by ','
	 */

		printf(KGREEN "Extracting Operands:\n");

	if ((strcmp(result.instruction,"data") == 0)){
		/*Count number of operands*/
		i=0;
		printf(KGREEN "--parsing for: .data\n");
		NORMALCOLOR
		while(current_pointer[i]!='\0'){
			if(current_pointer[i]==','){
				data_array_size++;
			}
			i++;
		}

		data_array_size++;
		result.data_values_number=data_array_size;

		/*allocate memory*/
		result.data_string_array = (String*)malloc(sizeof(String)*data_array_size);

		if (result.data_string_array != NULL){
			result.data_string_array=extract_data_strings(current_pointer,data_array_size);
		}else {
			fprintf(stderr,"Unable to allocate memory to a matrix\nMoving on..\n");
		}

	}
	/*
	 * instruction is not .data, so we need to populate operands1-3 fields
	 */
	else {
		printf(KGREEN "--parsing for non data \n");
		NORMALCOLOR

		printf(KCYN "---Current pointer: [%s]\n",current_pointer);

/*		n_skipped_spaces=count_spaces(current_pointer);
		current_pointer+=n_skipped_spaces;*/

		printf(KGREEN "OPERAND#1: \n");
		NORMALCOLOR
		extracted_value=extract_operand(current_pointer);
		result_size=strlen(extracted_value)+1;
		result.operand1=allocate_mem_string(result_size);
		strcpy(result.operand1,extracted_value);
		NORMALCOLOR

		current_pointer+=result_size+1;
		REALLOCATE_EXTRACTED_VALUE

		printf(KBLUE "---Extracted operand1: [%s]\n",result.operand1);
		printf(KCYN "---Current pointer: [%s]\n",current_pointer);


		printf(KGREEN "OPERAND#2: \n");
		NORMALCOLOR
		n_skipped_spaces=count_spaces(current_pointer);
		current_pointer+=n_skipped_spaces;

		strcpy(extracted_value,extract_operand(current_pointer));
		result_size=strlen(extracted_value)+1;
		result.operand2=allocate_mem_string(result_size);
		strcpy(result.operand2,extracted_value);
		current_pointer+=result_size+1;

		printf(KBLUE "---Extracted operand2: [%s]\n",result.operand2);
		printf(KCYN "---Current pointer: [%s]\n",current_pointer);


		/*For non .data we expect to receive 2 operands. if more are received,
		 * They are stored as junk to be validated by a different module, at a later stage
		 * */
		printf(KGREEN "OPERAND#3(Leftovers): \n");
		NORMALCOLOR

		if (current_pointer[0] != '\n'){
			printf(KGREEN"--extracting leftovers\n");
			extracted_value=extract_operand(current_pointer);
			result_size=strlen(extracted_value);
			result.operand3=allocate_mem_string(result_size+ADDEDSIZE);
			strcpy(result.operand3,extracted_value);

			printf(KBLUE "---Extracted operand3: [%s]\n",result.operand3);
			printf(KCYN "---Current pointer: [%s]\n",current_pointer);
		} else {
			/*Reached \n */{
				result.operand3=allocate_mem_string(1);
				strcpy(result.operand3,"\0");
			}
		}

	}

	NORMALCOLOR
	free(extracted_value);


	print_line(result);
	return result;

}

/*
 * Recieves a substrings
 * Counts how many operands there are by counting ','
 * move with a pointer - count each operand, allocate memory in required size and split
 */
String extract_operand (String str){
	int operand_size;
	int count=0;
	int i;
	int n_spaces;
	String ptr;
	String result;

	printf(KMAGENTA);

	n_spaces=count_spaces(str);
	str+=n_spaces;
	ptr=strchr(str,',');
	i=0;
	if (!ptr){
		/*we are the last operand*/
		while (str[i] != '\0'){
			count++;
			i++;
		}

		ptr=str+i;
		printf("counted %d chars\n",count);
	}

	operand_size=CALCSIZE(str,ptr);
	n_spaces=reverse_count_spaces(str,ptr);
	operand_size=operand_size-n_spaces;

	result=allocate_mem_string(operand_size+ADDEDSIZE);
	strncpy(result,str,operand_size);
	printf("operand size:%d\nstr: [%sresult: [%s\n",operand_size,str,result);
	NORMALCOLOR
	return result;

}




String extract_label (String line){
	char * result;
	char * found_char;
	char * array_start;
	int size;

/*	fprintf(stderr,"---Extract_lable: started\n");*/

	found_char = strchr(line,':');
	if (!found_char){
		RETURN_NULL(result)
		return result;

	}
	array_start=line;
	/*size = (found_char-array_start) * sizeof(char);*/
	size = CALCSIZE(array_start,found_char);
/*	fprintf(stderr,"---label length: %d\n",size);*/
	result = allocate_mem_string(size+ADDEDSIZE);

	strncpy(result,line,size);
/*	printf(" in result:%s\n",result);*/
/*	fprintf(stderr,"---Extract_lable: Finished\n");*/
	memset(result+size,'\0',1);
	return result;

}


char * extract_instruction(char * str){
	String result;
	char * found_char;
	char * array_start;
	char * inspection_start;
	char * inspection_end;
	int counted_non_spaces;
	int size;

	result=allocate_mem_string(strlen(str)+ADDEDSIZE);
	array_start=str;

	found_char = strchr(str,'.');
	if (!found_char){
		RETURN_NULL(result)
		return result;
	}

	/*In which position the dot appears. 1 is added because we care about what's after the dot*/
	size=CALCSIZE(array_start,found_char);
	size++;

	inspection_start=str+size;
	inspection_end = str+(count_non_spaces(str));


/*	if (!inspection_end){
		size=strlen(inspection_start);
		inspection_end=inspection_start+size; point to the last cell of the array
	}*/

	size=CALCSIZE(inspection_start, inspection_end);
	strncy_safe(result,inspection_start,size);

	return result;
}



/*This function runs from the first cell until the first non-blank char and removes the blanks*/
String remove_first_spaces(String str){
	int new_size;
	int counter=0;
	int i=0;
	String result;


	while ( str[i]=='\t' ||  str[i]==' '){
		counter++;
		i++;
	}

	if (counter == 0){
		return str;
	}
	new_size=(strlen(str))-counter;
	result=allocate_mem_string(new_size);
	strcpy(result,str+counter);

	return result;

}

/*counts how many blank chars there are for advancing the pointer*/
int count_spaces (String str){
	int n=0;
	int i=0;

	while ( str[i]=='\t' ||  str[i]==' '){
		n++;
		i++;
	}

	return n;
}


int reverse_count_spaces (String start, String end){
	int size,i,n;
	i=0;
	size=CALCSIZE(start,end);

	while (i<size && start[i]!=' ' && start[i]!='\t'){
		i++;
	}

	n=size-i;

/*	printf("size:%d, i:%d, calculated n: %d\n",size,i,n);*/
	return n;
}

String extract_operation(String str){
	int n_spaces;
	int size=0;
	String result;
	int i;
	char c;

	n_spaces= count_spaces(str);
	str +=n_spaces;

/*	printf(KMAGENTA "STR: [%s\n",str);*/

	i=0;
	c=str[i];
	while (c != ' ' && c!='\t' && c!='\n'){
		size++;
		i++;
		c=str[i];
	}

	result=allocate_mem_string(size+ADDEDSIZE);

	strncpy(result,str,size);

/*	printf(KMAGENTA "STR: [%s\n",str);*/

	NORMALCOLOR
	return result;
}

Bool check_empty_line(String str){
	int i;
	int size;
	Bool empty = TRUE;
	size=strlen(str);

	i=0;
	while (i<size && empty==TRUE){
		if (str[i]!='\t' && str[i]!='\n' && str[i]!=' '){
			empty=FALSE;

		}
		i++;
	}

	return empty;
}

/*
 * This function extracts the parameters received for data.
 * It creates a seperated string for each section devided by ','
 * Input: a pointer to a string, which holds all the parametes as one chunk
 * Output: an array of char*, where each parameter stored in a seperated cell
 */
String* extract_data_strings(char* str, int array_size){
	String* final_array;
	char* pointer;
	int size;
	int i;
	int cell=0;
	int n_spaces;

	final_array=allocate_mem_matrix(array_size);

	printf("------------------------------\n");
	printf(" Extracting strings for data\n");
	printf("------------------------------\n");

	for (i=0;i<array_size; i++){
			/*skip spaces at the start of str*/
			n_spaces=count_spaces(str);
			str+=n_spaces;

			/*find ','*/
			pointer=strchr(str,',');

		if (pointer != NULL){
			size=CALCSIZE(str,pointer);
			n_spaces=reverse_count_spaces(str,pointer);
			size-=n_spaces;

			final_array[cell]=allocate_mem_string(size);
			strncpy(final_array[cell],str,size);
			str=pointer+1;
/*			printf("in cell %d: [%s]\n",cell,final_array[cell]);*/
			cell++;
		} else {
			n_spaces=count_spaces(str);
			str+=n_spaces;
			size=strlen(str);
			str[size-1]='\0';
			final_array[cell]=allocate_mem_string(size);
			final_array[cell]=str;
/*			printf("String in cell %d: [%s]\n",cell, final_array[cell]);*/
		}

	}

	return final_array;
}

int count_non_spaces(String str){
	int i;
	char c;
	Bool found_space=FALSE;

	i=0;
	while (i<strlen(str) && found_space==FALSE){
		c=str[i];

		if (c!=' ' && c!='\t'){
			i++;

		}else{
			found_space=TRUE;
		}

	}

	return i;

}
