/*
 * parser.c
 *
 *  Created on: Aug 3, 2017
 *      Author: alexz
 */



#include "parser.h"
#include "utils.h"
#define INITIAL_SARRAY_SIZE 8000
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


bodyArray  parse_file (FILE * file){
	String line;
	bodyArray result;
	int cell_counter;

	line=allocate_mem_string(MAXMEM);
	result=allocate_mem_struct(INITIAL_SARRAY_SIZE);

	cell_counter=0;

	fgets(line,MAXMEM,file);


	result[0] = parse_line(line);
	cell_counter = cell_counter +1;

	return result;

}

body  parse_line (String str){
	body result;
	int result_size;
	char * tmp;
	char line[MAXMEM];

	tmp=allocate_mem_string(MAXMEM);
	strcpy(line,str);
	printf("strcpy - %s\n",line);


	/*extract label*/
	strcpy(tmp,extract_label(str));
	result_size=strlen(tmp) +1;
	result.label=allocate_mem_string(result_size);
	strcpy(result.label,tmp);


	/*extract instruction*/
	strcpy(tmp,extract_instruction(str));
	result_size=strlen(tmp)+1;
	result.instruction=allocate_mem_string(result_size);
	strcpy(result.instruction,tmp);

	/*printf("%s\n",line);
	strcpy(result.instruction, extract_instruction(line));
*/
	return result;
}

String extract_label (String line){
	char * result;
	char * found_char;
	char * array_start;
	int size;

	fprintf(stderr,"---Extract_lable: started\n");

	found_char = strchr(line,':');
	if (!found_char){
		RETURN_NULL(result)
		return result;

	}
	array_start=line;
	size = (found_char-array_start) * sizeof(char);

	fprintf(stderr,"---label length: %d\n",size);
	result = allocate_mem_string(size+1);

	strncpy(result,line,size);
	printf(" in result:%s\n",result);
	fprintf(stderr,"---Extract_lable: Finished\n");
	return result;

}


char * extract_instruction(char * str){
	String result;
	String copy;
	char * found_char;
	char * array_start;
	char * inspection_start;
	char * inspection_end;
	int size;

	result=allocate_mem_string(strlen(str));
	copy=allocate_mem_string(strlen(str));

	array_start=str;

	fprintf(stderr,"---Extract_instruction: started\n");
	fprintf(stderr,"---Extracting: dot \n");

	found_char = strchr(str,'.');
	if (!found_char){
		RETURN_NULL(result)
		return result;
	}

	/*In which position the dot appears. 1 is added because we care about what's after the dot*/
	/*size = ((found_char - array_start) * sizeof(char))+1;*/
	size=CALCSIZE(array_start,found_char);
	size++;

	fprintf(stderr,"---Calculated dot position:%d\n",size);
	inspection_start=str+size;
	strcpy(copy,inspection_start); /*Now copy holds everything after the dot*/

	fprintf(stderr,"---Extracting: space \n");
	inspection_end = strchr(copy,' ');
	if (!inspection_end){
		size=strlen(copy);
		inspection_end=copy+size; /*point to the last cell of the array*/
	}

	size=CALCSIZE(copy, inspection_end);

	strncpy(result,copy,size);
	printf("in result: %s\n",result);

	fprintf(stderr,"---Extraction Completed.\n",size);

	return result;
}


