#include <vector>
#include "polNot.h"

enum Operation
{
	SUM,
	MULT,
	NOT,
};

enum State
{
	START,
	OPERATION,
	OPERAND,
	END,
	ERROR,
};

struct Node
{
	Operation operation = NOT;
	std::vector<Node*> operands;
	Node* parent = nullptr;
	int res = 0;
};

static void CalculateExpression(Node* current)
{
	if (current->operation == SUM)
		for (auto i : current->operands)
			current->res += i->res;
	else
	{
		current->res = 1;
		for (auto i : current->operands)
			current->res *= i->res;
	}
}

static void SetOperations(Node* current, char ch)
{
	if (ch == '+')
		current->operation = SUM;
	else if (ch == '*')
		current->operation = MULT;
}

static bool IsNewExpression(Node*& current, std::istream& input)
{
	Node* newNode = new Node();
	int operand{};
	if (input >> operand)
	{
		newNode->res = operand;
		newNode->parent = current;
		current->operands.push_back(newNode);
	}
	else
	{
		newNode->parent = current;
		current->operands.push_back(newNode);
		current = newNode;
		input.clear();
		return true;
	}
	return false;
}

int Calculate(std::istream& input)
{
	State state = START;
	Node* root = new Node();
	Node* current = root;
	char ch;

	while (input >> ch)
	{
		switch (state)
		{
		case START:
			if (ch == '(')
				state = OPERATION;
			else
				state = ERROR;
			break;
		case OPERAND:
			if (ch == ')')
			{
				state = END;
				break;
			}
			input.unget();
			if (IsNewExpression(current, input))
				state = START;
			break;
		case OPERATION:
			state = OPERAND;
			SetOperations(current, ch);
			if (current->operation == NOT)
				state = ERROR;
			break;
		case END:
			input.unget();
			CalculateExpression(current);
			current = current->parent;
			state = OPERAND;
			break;
		case ERROR:
			throw std::invalid_argument("ERROR! Incorrect input");
			break;
		}
	}
	CalculateExpression(current);
	return current->res;
}
