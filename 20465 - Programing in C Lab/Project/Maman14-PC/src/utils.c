/*
 * utils.c
 *
 *  Created on: Jul 26, 2017
 *      Author: alex
 */

#include "utils.h"


int structs_array_size;

String* allocate_mem_matrix(int size){
	String* matrix = (String*)malloc(sizeof( String*)*size);
	if (!matrix){
		fprintf(stderr,"Unable to allocate memory to the matrix.\nContinuing with no operanns\n");
		exit(0);
	}
	return matrix;
}


String allocate_mem_string (int size){
	String	str = (char*)malloc (size * sizeof(char));
	if (!str){
		fprintf(stderr,"---Unable to allocate memory\n");
	}

/*	fprintf(stderr,"---Memory allocated successfully, size: %d\n",size);*/
	return str;
}



bodyArray allocate_mem_struct (int size){
	bodyArray array=(bodyArray) malloc(sizeof(body)*size);

	if (!array){
		fprintf(stderr,"---Unable to allocate memory to structs-array");
		exit(0);

	}
	return array;

}

int increase_mem_struct (int size,bodyArray array){
	size=size*2;
	bodyArray tmp = (bodyArray)realloc(array,sizeof(body)*size);
	if (!tmp){
		fprintf(stderr,"unable to increase memory to structs-array");
		exit (0);
	}

	array=tmp;
	return size;

}




void print_structs(bodyArray array, int size){
	int i;
	char tmp[15];
	char null[]="null           ";

	i=0;
	printf("\n--------------------------------------------------------");
	printf("--------------------------------------------------------\n");
	printf("                       STRUCT PRINT:\n");
	printf("\n--------------------------------------------------------");
	printf("--------------------------------------------------------\n");

	printf("\n");
	printf("Line |");
	printf("LABEL        |");
	printf("INSTRUCTION  |");
	printf("OPERATION    |");
	printf("OPERAND1     |");
	printf("OPERAND2     |");
	printf("OPERAND3     |");
	printf("\n");


	for (i=0;i<size;i++){
		/*Line number*/
		printf("%d    ",array[i].line_number);

		/*label*/
		if ((strcmp(array[i].label,"\0") ) !=0){
			strcpy(tmp,array[i].label);
			add_spaces_print(tmp);
			printf("%s",tmp);

		}else printf("               ");




		if ((strcmp(array[i].instruction,"\0") ) !=0){

		}
		strcpy(tmp,array[i].instruction);
		add_spaces_print(tmp);
		printf("%s",tmp);

		if (strcmp(array[i].instruction,"data")==0 || strcmp(array[i].instruction,"mat")==0){
			print_mat(array[i].data_string_array,array[i].data_values_number);

		}else printf("               ");

			/*OPERATION*/
		if ((strcmp(array[i].operantion,"\0") ) !=0){
			strcpy(tmp,array[i].operantion);
			add_spaces_print(tmp);
			printf("%s",tmp);
		}else printf("               ");


		if (strcmp(array[i].instruction,"data")!=0){

			if ((strcmp(array[i].operand1,"\0") ) !=0)
			{
					strcpy(tmp,array[i].operand1);
					add_spaces_print(tmp);
					printf("%s",tmp);
			}else printf("               ");


			if ((strcmp(array[i].operand2,"\0")) !=0){
					strcpy(tmp,array[i].operand2);
					add_spaces_print(tmp);
					printf("%s",tmp);
				}else printf("               ");

			if ((strcmp(array[i].operand3,"\0")) !=0){
					strcpy(tmp,array[i].operand3);
					add_spaces_print(tmp);
					printf("%s",tmp);
				}else printf("               ");


		}
		printf("\n");
	}
	printf("\n--------------------------------------------------------");
	printf("--------------------------------------------------------\n");
}


void add_spaces_print (String  array){
	int length;
	int i=0;

	length=strlen(array);
	while (array[i] != ' '){
		i++;
	}

	i=length;
	for (i=length; i<14; i++){
		array[i]=' ';
	}

}


void print_line(body item){

	if (strcmp(item.instruction,"data")==0){
		printf("%d %s %s ",item.line_number,item.label,item.instruction);
		print_mat(item.data_string_array,item.data_values_number);
	}

	else {
		printf("<%d",item.line_number);
		if (strcmp(item.label,"\0")!=0){
			printf(" %s",item.label);
		}

		if (strcmp(item.instruction,"\0")!=0){
			printf(" %s",item.instruction);

		}
		if (strcmp(item.operantion,"\0")!=0){
			printf(" %s",item.operantion);

		}

		if (strcmp(item.operand1,"\0")!=0){
			printf(" %s",item.operand1);

		}

		if (strcmp(item.operand2,"\0")!=0){
			printf(" %s",item.operand2);

		}

		if (strcmp(item.operand3,"\0")!=0){
			printf(" %s",item.operand3);

		}
	}
	printf(">\n");
}

void print_mat (String* mat, int size){
	int i;

	for (i=0;i<size;i++){
		printf("%s ",*mat);
		mat++;
	}

	NORMALCOLOR

	printf("\n");

}


/*
 * Linked List
 */

void add_to_list(list_item_reference * head, String str){
	list_item_reference new_item,temp;

	if ((new_item = (list_item_reference)malloc( sizeof(list_item))) == NULL)
	{
		fprintf(stderr,"unable to allocate memory to a list item. Exiting the program\n");
		exit(0);
	}

	new_item->str=allocate_mem_string(strlen(str)+1);

	strcpy(new_item->str,str);
	new_item->next=NULL;

	if (*head == NULL){
		new_item->prev=NULL;
		*head=new_item;
	}
	else{
		temp=*head;

		while (temp->next != NULL){
			temp=temp->next;
		}

		temp->next=new_item;
		new_item->prev=temp;
	}

}

void print_list(list_item_reference head){

	if (head==NULL){
		printf("Empty list\n");
		return;
	}


	while (head != NULL){
		printf(KBLUE "%s",head->str);
		head=head->next;
	}
	printf("\n");
}

void free_list(list_item_reference *head){
	free(*head);
}


String covert_int_to_string (int number){
	int arraysize =12;
	String result;
	result = allocate_mem_string(arraysize);
	sprintf(result,"%d",number);
	return result;
}

void strncy_safe(String  dest, String  source, int size){
	strncpy(dest,source,size);
	dest[strlen(dest)]='\0';
}
