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

int Calculate(std::istream& input)
{
	State state = START;
	Node* root = new Node();
	Node* current = root;
	Node* newNode = nullptr;
	int operand{};
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
			newNode = new Node();
			if (input >> operand)
				newNode->res = operand;
			else
				; // 
			;
			break;
		case OPERATION:
			state = OPERAND;
			if (ch == '+')
				current->operation = SUM;
			else if (ch == '*')
				current->operation = MULT;
			else
				state = ERROR;
			break;
		case END:

			break;
		default:
			throw std::invalid_argument("ERROR! Incorrect input");
			break;
		}
	}
}












bool IsNum(char ch)
{
	return ch >= '0' && ch <= '9';
}

std::stack<std::string> Parse1(const std::string& str)
{
	std::stack<char> operationsStack;
	std::stack<std::string> operandsStack;
	std::string hold;
	int count{};

	for (size_t i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '(':
			operandsStack.push("(");
			count++;
			break;
		case ')':
			hold.clear();
			hold.push_back(operationsStack.top());
			operandsStack.push(hold);
			operationsStack.pop();
			operandsStack.push(")");
			count--;
			break;
		case '+':
		case '*':
			operationsStack.push(str[i]);
			break;
		default:
			hold.clear();
			while (i < str.length() && (IsNum(str[i]) || str[i] == '-'))
			{
				hold.push_back(str[i]);
				i++;
			}
			i--;
			if (!hold.length())
				throw std::invalid_argument("ERROR! Incorrect input");
			operandsStack.push(hold);
			break;
		}
	}

	if (count)
		throw std::invalid_argument("ERROR! Incorrect input");

	return operandsStack;
}

int Calculate1(std::stack<std::string>& backPoland)
{
	std::stack<int> operand;
	std::stack<Operation> operation;
	State state = READY;


	while (backPoland.size())
	{
		std::string item = backPoland.top();
		backPoland.pop();
		switch (state)
		{
		case READY:
			if (item == ")")
				state = OPERATION;
			else
				throw std::invalid_argument("ERROR! Incorrect input");
			break;
		case OPERATION:

			break;
		case OPERAND:
			break;
		default:
			break;
		}
	}
}