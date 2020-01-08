#include <stdio.h>
#include <stdlib.h>

typedef int STACK_DATA;

typedef enum errorCodes_2
{
	FAILURE_2,
	SUCCESS_2

}errorCode_2;

typedef enum YES_NO_2
{
	NO_2,
	YES_2
}YES_NO_2;


typedef struct Stack {

	int Head;
	int Size;
	STACK_DATA* Data;


} Stack ;


Stack CreateStack(int size);
errorCode_2 push(Stack* s_ptr, STACK_DATA x);
errorCode_2 pop(Stack* s_ptr, STACK_DATA* returnValue);
YES_NO_2 Stack_isEmpty(Stack* s_ptr);
YES_NO_2 Stack_isFull(Stack* s_ptr);
STACK_DATA* stackToArray(Stack* s_ptr, int* sizeToReturn);
