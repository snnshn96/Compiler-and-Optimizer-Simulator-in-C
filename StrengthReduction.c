/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2017                                *
 *  Author: Uli / Sinan Sahin                *
 *  Student Version                          *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
			OpCode OP = curr->next->opcode;
			if ((OP == DIV || OP == MUL) && (curr->field2 == curr->next->field2))
			{
				// Check if power of two
				int n = curr->field1;
				if (n < 2)
				{
					curr = curr->next->next;
				}
				else
				{
					int isTwos = 1;
					int count = 0;
					while (n != 1)
					{
						if (n % 2 != 0)
						{
							isTwos = 0;
							break;
						}
						n = n / 2;
						count++;
					}
					if (isTwos < 1)
					{
						curr = curr->next->next;
					}
					else
					{
						Instruction *newInstr = (Instruction *)calloc(1, sizeof(Instruction));
						newInstr->prev = curr->prev;
						newInstr->next = curr->next->next;
						newInstr->field1 = curr->next->field1;
						newInstr->field2 = count;
						newInstr->field3 = curr->next->field3;

						switch (OP)
						{
						case DIV:
							newInstr->opcode = RSHIFTI;
							break;
						case MUL:
							newInstr->opcode = LSHIFTI;
							break;
						default:
							break;
						}

						if (curr->prev != NULL)
						{
							curr->prev->next = newInstr;
						}
						curr->next->next->prev = newInstr;

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
				}
			}
			else
			{
				curr = curr->next;
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
