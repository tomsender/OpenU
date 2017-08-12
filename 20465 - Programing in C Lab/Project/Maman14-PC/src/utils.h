/*
 * utils.h
 *
 *  Created on: Jul 26, 2017
 *      Author: alex
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NORMAL  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGREEN  "\x1B[32m"
#define KYELLOW  "\x1B[33m"
#define KBLUE  "\x1B[34m"
#define KMAGENTA  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHITE  "\x1B[37m"

#define NORMALCOLOR printf(NORMAL "");


#define MAXMEM 81

#define COMPARE(a,b) strcmp(a,"b")





typedef char* String;

typedef enum {
	FALSE = 0,
	TRUE = 1
} Bool;

typedef enum {
	ACTION =0,
	INSTRUCTION=1,
	UNKNOWN=3
}line_type;



/*
 * Parser  related
 */
typedef struct parsed_line {
	int line_number;
	int data_values_number;
	String label;
	String instruction;
	String operantion;
	String operand1;
	String operand2;
	String operand3; /*This exists to hold additional operands (for validation)*/
	String* data_string_array;
	int * data_int_values;
	Bool valid;
	/*decide on how to deal with .data*/


} body;

typedef  body * bodyArray;



/*
 * Linked List
 */

typedef struct node* list_item_reference;
typedef struct node {
	String str;
	list_item_reference next;
	list_item_reference prev;
}list_item;



/**********************************/
/***********FUNCTIONS**************/
/**********************************/


bodyArray allocate_mem_struct (int); /*dynamically allocates memory for a struct array*/

/*A function that receives a string length and allocates the required memory */
String* allocate_mem_matrix(int size);
String  allocate_mem_string(int);


/**
 * For linked list
 */

void add_to_list(list_item_reference*,String);

void print_list(list_item_reference);

void free_list(list_item_reference*);




/*for testing*/
void print_structs(bodyArray, int size);

void add_spaces_print (String array);

void print_line(body);
void print_mat (String*, int);

#endif /* UTILS_H_ */
