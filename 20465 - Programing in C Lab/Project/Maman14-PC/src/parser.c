/*
 * parser.c
 *
 *  Created on: Aug 3, 2017
 *      Author: alexz
 */

#include "parser.h"
#include "utils.h"
#define INITIAL_SARRAY_SIZE 8000

bodyArray  parse_file (FILE * file){
	String line;
	bodyArray result;
	int cell_counter;

	cell_counter=0;

	line=allocate_mem_string(MAXMEM);
	result=allocate_mem_struct(INITIAL_SARRAY_SIZE);

	fgets(line,MAXMEM,file);
	printf("fgets- %s\n",line);


	result[0] = parse_line(line);
	printf("stas- %s\n",result[0].label);
	cell_counter = cell_counter +1;

	return result;

}

body  parse_line (String str){
	body result;
	char line[MAXMEM];


	strcpy(line,str);
	printf("strcpy - %s\n",line);


	/*extract label*/
	strcpy(result.label,get_label(line));



	return result;
}

char * get_label (char * line){
	char * token;
	char copy[MAXMEM];

	strcpy(copy,line);
		token = strtok(copy,":");

		printf("token- %s\n",token);

		if (!token){
			return NULL;
		}

		return token;
}

