#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "task1.h"

typedef struct StackNode
{
	float data;
	struct StackNode* next;
} StackNode;

StackNode* CreateNode(float data) 
{
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) 
    {
        printf("Error.Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

bool isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

float PerformOperation(float operand1, float operand2, char operator)
{
    switch (operator)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    default:
        printf("Incorrect input: %c\n", operator);
        exit(EXIT_FAILURE);
    }
}
int GetPriority(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}
float EvaluateExpression(char* expression)
{
    StackNode* operandStack = NULL;
    StackNode* operatorStack = NULL;

    for (int i = 0; expression[i] != '\0'; i++) 
    {
        char ch = expression[i];

        if (isspace(ch)) 
        {
            continue;
        }
        else if (isdigit(ch)) 
        {
            StackNode* newNode = CreateNode(ch - '0');
            newNode->next = operandStack;
            operandStack = newNode;
        }
        else if (ch == '(')
        {
            StackNode* newNode = CreateNode(ch);
            newNode->next = operatorStack;
            operatorStack = newNode;
        }
        else if (ch == ')')
        {
            while (operatorStack != NULL && operatorStack->data != '(')
            {
                char operator = operatorStack->data;
                operatorStack = operatorStack->next;

                if (operandStack == NULL)
                {
                    printf("Incorrect expression\n");
                    exit(EXIT_FAILURE);
                }

                float operand2 = operandStack->data;
                operandStack = operandStack->next;

                if (operandStack == NULL) 
                {
                    printf("Incorrect expression\n");
                    exit(EXIT_FAILURE);
                }

                float operand1 = operandStack->data;
                operandStack = operandStack->next;

                float result = PerformOperation(operand1, operand2, operator);

                StackNode* resultNode = CreateNode(result);
                resultNode->next = operandStack;
                operandStack = resultNode;
            }

            if (operatorStack == NULL || operatorStack->data != '(') {
                printf("Incorrect expression\n");
                exit(EXIT_FAILURE);
            }

            StackNode* temp = operatorStack;
            operatorStack = operatorStack->next;
            free(temp);
        }
        else if (isOperator(ch))
        {
            while (operatorStack != NULL && isOperator(operatorStack->data) &&
                GetPriority(ch) <= GetPriority(operatorStack->data))
            {
                char operator = operatorStack->data;
                operatorStack = operatorStack->next;

                if (operandStack == NULL) 
                {
                    printf("Incorrect expression\n");
                    exit(EXIT_FAILURE);
                }

                float operand2 = operandStack->data;
                operandStack = operandStack->next;

                if (operandStack == NULL) 
                {
                    printf("Incorrect expression\n");
                    exit(EXIT_FAILURE);
                }

                float operand1 = operandStack->data;
                operandStack = operandStack->next;

                float result = PerformOperation(operand1, operand2, operator);

                StackNode* resultNode = CreateNode(result);
                resultNode->next = operandStack;
                operandStack = resultNode;
            }
            StackNode* newNode = CreateNode(ch);
            newNode->next = operatorStack;
            operatorStack = newNode;
        }
        else 
        {
            printf("Incorrect symbol: %c\n", ch);
            exit(EXIT_FAILURE);
        }
    }
    while (operatorStack != NULL && isOperator(operatorStack->data)) 
    {
        char operator = operatorStack->data;
        operatorStack = operatorStack->next;

        if (operandStack == NULL) 
        {
            printf("Incorrect expression\n");
            exit(EXIT_FAILURE);
        }

        float operand2 = operandStack->data;
        operandStack = operandStack->next;

        if (operandStack == NULL) 
        {
            printf("Incorrect expression\n");
            exit(EXIT_FAILURE);
        }

        float operand1 = operandStack->data;
        operandStack = operandStack->next;

        float result = PerformOperation(operand1, operand2, operator);

        StackNode* resultNode = CreateNode(result);
        resultNode->next = operandStack;
        operandStack = resultNode;
    }
    if (operandStack == NULL || operandStack->next != NULL) 
    {
        printf("Incorrect expression\n");
        exit(EXIT_FAILURE);
    }

    float result = operandStack->data;
    free(operandStack);
    return result;
}
void FirstTask()
{
	char buffer[256];
	printf("Enter the expression:");
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
	if (fgets(buffer, sizeof buffer, stdin))
	{
		size_t length = strlen(buffer);
		if (length > 0 && buffer[length - 1] == '\n')
		{
			buffer[length - 1] = '\0';
		}
		else
		{
			printf("Buffer overflow\n");
			exit(-1);
		}
        float result = EvaluateExpression(buffer);
		printf("Result: %.2f\n", result);
	}
}