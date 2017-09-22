#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int getPrecedence(char optr)
{
	if (optr == '!')
	{
		return 3;
	}
	if (optr == '&')
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

bool doOperation(bool op1, bool op2, char optr)
{
	if (optr == '|')
	{
		return (op1 || op2);
	}
	else
	{
		return (op1 && op2);
	}
}

int getNum(char num)
{
	if (num == '0')
		return 0;
	if (num == '1')
		return 1;
	if (num == '2')
		return 2;
	if (num == '3')
		return 3;
	if (num == '4')
		return 4;
	if (num == '5')
		return 5;
	if (num == '6')
		return 6;
	if (num == '7')
		return 7;
	if (num == '8')
		return 8;
	if (num == '9')
		return 9;
	else
		return -1;
}

int evaluate(string infix, const bool values[], string& postfix, bool& result)
// Evaluates a boolean expression
// Postcondition: If infix is a syntactically valid infix boolean
//   expression, then postfix is set to the postfix form of that
//   expression, result is set to the value of the expression (where
//   in that expression, each digit k represents element k of the
//   values array), and the function returns zero.  If infix is not a
//   syntactically valid expression, the function returns 1.  (In that
//   case, postfix may or may not be changed, but result must be
//   unchanged.)

{
	//***determine if infix is syntactically valid***
	int infixSize = infix.size();
	int digitCount = 0;
	int leftPren = 0;
	int rightPren = 0;
	int operatorCount = 0;
	int binaryOpCount = 0;
	for (int i = 0; i < infixSize; i++)
	{
		if (!(infix[i] >= '0' && infix[i] <= '9') && infix[i] != '!' && infix[i] != '(' && infix[i] != ')' && infix[i] != '&' && infix[i] != '|' && infix[i] != ' ')
		{
			return 1;
		}
		if (infix[i] >= '0' && infix[i] <= '9')
		{
			if (i < infixSize - 1) 
			{
				if (infix[i + 1] >= '0' && infix[i + 1] <= '9')  //digits cant be followed by digits
				{
					return 1;
				}
				if (infix[i + 1] == '!' || infix[i + 1] == '(')  //no '(' or '!' after digits
				{
					return 1;
				}
			}
			digitCount++;
		}
		if (infix[i] == '(')
		{
			if (i < infixSize - 1)  //'(' must be followed by digits or '!' or space
			{
				if (infix[i + 1] == ')' || infix[i + 1] == '|' || infix[i + 1] == '&')
				{
					return 1;
				}
			}
			int digitCount1 = 0;
			int binaryOpCount1 = 0;
			for (int j = i; j < infixSize; j++) //if theres enough operators within a pair of parentheses
			{
				
				if (infix[j] == ')') {
					break;
				}
				if (infix[j] >= '0' && infix[j] <= '9')
				{
					digitCount1++;
				}
				if (infix[j] == '&' || infix[j] == '|')
				{
					binaryOpCount1++;
				}
			}
			if (digitCount1 == binaryOpCount1) //too many ops
			{
				return 1;
			}
			if (digitCount > 1 && operatorCount == 0)  //too few ops
			{
				return 1;
			}
			leftPren++;
		}
		if (infix[i] == ')')
		{
			if (i < infixSize - 1) 
			{
				if (infix[i + 1] >= '0' && infix[i + 1] <= '9') // cant have digits after ')'
				{
					return 1;
				}
				if (infix[i + 1] == '(' || infix[i + 1] == '!') //cant have '(' or '!' after ')'
				{
					return 1;
				}
			}
			rightPren++;
		}
		if (infix[i] == '!' || infix[i] == '&' || infix[i] == '|')
		{
			operatorCount++;
		}
		if (infix[i] == '&' || infix[i] == '|')
		{
			if (i > 0) //binary operators must have digits in front
			{
				if (infix[i - 1] < '0' && infix[i - 1] > '9')
				{
					return 1;
				}
			}
			if (i < infixSize - 1) //binary operators must have digits behind
			{
				if (infix[i + 1] == '&' || infix[i + 1] == '|')
				{
					return 1;
				}
				if (infix[i + 1] == ')')
				{
					return 1;
				}
			}
			binaryOpCount++;
		}
	}
	if (digitCount > 1 && operatorCount == 0) {
		return 1;
	}
	if (leftPren != rightPren) {
		return 1;
	}
	if (digitCount == 0) {
		return 1;
	}
	if (digitCount == binaryOpCount) {
		return 1;
	}

	//****converting to postfix***
	postfix = "";
	stack<char> operators;
	for (int i = 0; i < infixSize; i++)
	{
		if (infix[i] == ' ')  //skip to next char if current char is space
		{
			continue;
		}
		switch (infix[i]) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			postfix += infix[i];
			break;
		case '(':
			operators.push(infix[i]);
			break;
		case ')':
			// pop stack until matching '('
			while (operators.top() != '(') {
				postfix += operators.top();
				operators.pop();
			}
			operators.pop();
			break;
		case '!':
		case '&':
		case '|':
			int currentPre = getPrecedence(infix[i]);
			while (!(operators.empty()) && (operators.top() != '(') && currentPre <= getPrecedence(operators.top())) 
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.push(infix[i]);
			break;
		}
	}
	while (!operators.empty())
	{
		postfix += operators.top();
		operators.pop();
	}

	//cout << postfix << endl;  //DEBUG

	//***evaluating postfix***
	stack<bool> operands;
	int postfixSize = postfix.size();
	for (int i = 0; i < postfixSize; i++)
	{
		if (postfix[i] >= '0' && postfix[i] <= '9')  //when digit
		{
			int index = getNum(postfix[i]);
			operands.push(values[index]);
		}
		else if (postfix[i] == '!')  //turn current operand to the opposite of itself
		{
			bool operand = operands.top();   //save the top bool b4 popping it
			operands.pop();
			operands.push(!operand);  //push the opposite of operand back in the stack
		}
		else  //when binary operator: | or &
		{
			if (operands.size() < 2) //whenever an operator is read there should be at least 2 operands
			{
				return 1;
			}
			bool operand2 = operands.top();
			operands.pop();
			bool operand1 = operands.top();
			operands.pop();
			bool opResult = doOperation(operand1, operand2, postfix[i]);
			operands.push(opResult);
		}
	}
	if (operands.size() > 1) //when theres more than 1 operands left, b/c not enough operators
	{
		return 1;
	}
	result = operands.top();
	return 0;
}

int main()
{
	bool ba[10] = {
		//  0      1      2      3      4      5      6      7      8      9
		true,  true,  true,  false, false, false, true,  false, true,  false
	};
	string pf;
	bool answer;
	//evaluate("2| 3", ba, pf, answer);
	
	assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" &&  answer);
	assert(evaluate("8|", ba, pf, answer) == 1);
	assert(evaluate("4 5", ba, pf, answer) == 1);
	assert(evaluate("01", ba, pf, answer) == 1);
	assert(evaluate("()", ba, pf, answer) == 1);
	assert(evaluate("2(9|8)", ba, pf, answer) == 1);
	assert(evaluate("2(&8)", ba, pf, answer) == 1);
	assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
	assert(evaluate("", ba, pf, answer) == 1);
	assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
		&& pf == "43!03&&|" && !answer);
	assert(evaluate(" 9  ", ba, pf, answer) == 0 && pf == "9" && !answer);
	ba[2] = false;
	ba[9] = true;
	assert(evaluate("((9))", ba, pf, answer) == 0 && pf == "9"  &&  answer);
	assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" && !answer);
	cout << "Passed all tests" << endl;
}
