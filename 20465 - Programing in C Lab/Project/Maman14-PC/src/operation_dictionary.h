/*
 * operation_dictionary.h
 *
 *  Created on: Aug 23, 2017
 *      Author: alexz
 */

#include "utils.h"

#ifndef OPERATION_DICTIONARY_H_
#define OPERATION_DICTIONARY_H_

#define OPERANDS_NUMBER 16



typedef struct operation_info{
	String name;
	int num_of_operands;
	Bool op1_intermid_allowed;
	Bool op1_label_allowed;
	Bool op1_matrix_allowed;
	Bool op1_register_allowed;
	Bool op2_intermid_allowed;
	Bool op2_label_allowed;
	Bool op2_matrix_allowed;
	Bool op2_register_allowed;
}operation_info;






void create_operation_info_array();

operation_info get_operation_info(String);


Bool is_operand1_allowed(operation_info,String,Operand_type);
Bool is_operand2_allowed(operation_info,String,Operand_type);
Operand_type get_operand_type (String operand);


#endif /* OPERATION_DICTIONARY_H_ */
