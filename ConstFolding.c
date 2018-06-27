/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2017                                *
 *  Author: Uli                              *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head)
	{
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	/* Implementation - Start */
	Instruction *curr = head;
	while (curr != NULL)
	{
		if (curr->opcode == LOADI)
		{
			if (curr->next->opcode == LOADI)
			{
				OpCode OP = curr->next->next->opcode;
				if ((OP == ADD || OP == SUB || OP == MUL) && (curr->field2 == curr->next->next->field1) && (curr->next->field2 == curr->next->next->field2))
				{
					int a = curr->field1;
					int b = curr->next->field1;
					int reg = curr->next->next->field3;
					int result = 0;

					switch (OP)
					{
					case ADD:
						result = a + b;
						break;
					case SUB:
						result = a - b;
						break;
					case MUL:
						result = a * b;
						break;
					default:
						break;
					}

					Instruction *newInstr = (Instruction *)calloc(1, sizeof(Instruction));
					newInstr->prev = curr->prev;
					newInstr->next = curr->next->next->next;
					newInstr->opcode = LOADI;
					newInstr->field1 = result;
					newInstr->field2 = reg;

					if (curr->prev != NULL)
					{
						curr->prev->next = newInstr;
					}
					curr->next->next->next->prev = newInstr;

					free(curr->next->next);
					free(curr->next);
					if (curr == head)
					{
						free(head);
						head = newInstr;
					}
					else
					{
						free(curr);
					}
					curr = newInstr;
				}
				else if (OP == LOADI)
				{
					curr = curr->next;
				}
				else
				{
					curr = curr->next->next->next;
				}
			}
			else
			{
				curr = curr->next->next;
			}
		}
		else
		{
			curr = curr->next;
		}
	}
	/* Implementation - End */

	if (head)
		PrintInstructionList(stdout, head);

	return EXIT_SUCCESS;
}
