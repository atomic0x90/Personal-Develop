#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

string input_string;	//Save input values
stack <char> temp_stack;
vector <char> temp_char;	//Save input by letter
vector <char> formula;	//Save formula using a postfix notation


/*
 * cin infix notation
*/
void Input_screen()
{
	cout<<"----------------------------------------------------------"<<endl;
	cout<<"\t"<<"\t"<<"-------------------------"<<endl;
	cout<<"\t"<<"\t"<<"     Stack Calculator"<<endl;
	cout<<"\t"<<"\t"<<"-------------------------"<<"\n"<<endl;
	cout<<"\t"<<"   Please enter expression to calculator"<<endl;
	cout<<"\t"<<"     --Please enter Infix Notation--"<<endl;
	cout<<"----------------------------------------------------------"<<endl;

	getline(cin,input_string);

	return;
}


/*
 * Divide a string into char
*/
void split()
{
	for(int i = 0; i < input_string.size(); i++)
		temp_char.push_back(input_string.at(i));
	
	return;
}


/*
 * Check list
 *
 * Parentheses paired -> ((1+2)*3
 * Duplicated operator -> 1 +/ 3
 * Using four aritimetical operations or number
*/
int valid_formula_check()
{
	int num = 0, check_duplicate_symbol = 0;	
/*
  If 'check_duplicate_symbol >= 2' -> error 

   Example duplicate symbol -> 1 + * 2,  1 / - 2, etc.
*/
	for(int i = 0; i < temp_char.size(); i++)
	{
		if(temp_char[i] == '(')
		{
			num++;
			if(check_duplicate_symbol == 1)		//Example -> 3 + (-4)
				check_duplicate_symbol--;
		}
		else if(temp_char[i] == ')')
		{
			num--;
			if(check_duplicate_symbol == 1)
				return 0;
		}
		
		else if((temp_char[i] >= 48 && temp_char[i] <= 57) || temp_char[i] == ' ')
		{	//A blank space and number(ASCII code)
			if(temp_char[i] >= 48 && temp_char[i] <= 57 && check_duplicate_symbol == 1)
				check_duplicate_symbol--;

			continue;
		}

		else if(temp_char[i] == '+' || temp_char[i] == '-' || temp_char[i] == '/' || temp_char[i] == '*')
		{	//Four arithmetical operations
			check_duplicate_symbol++;

			if(check_duplicate_symbol == 2)
				return 0;
		}

		else	//Not the four aritimetical operations or number
			return 0;
	}

	if(num == 0)	//Parentheses are paired
		return 1;
	if(num != 0)	//Parentheses are not paired
		return 0;
}


/*
 * 1. If number, push postfix notation
 * 
 * 2. If left parenthesis, stack push
 * 
 * 3. If right parenthesis, stack pop until left parenthesis comes out
 *  -> Push back the stack pop to the postfix notation
 * 
 * 4. If four aritimetical operator, stack pop until this is a higher priority than top of stack
 *  -> Push back the stack pop to the postfix notation
 *
 * 5. Once you have read the entire input formula, push the operator remaining in the stack to postfix notation
 *
 *
 * Priority
 * '(' < '+','-' < '*','/'
*/
void infix_notation_change_to_postfix_notaion()
{
	for(int i = 0; i < temp_char.size(); i++)
	{
		if(temp_char[i] == ' ')	//Ignore space
			continue;
		else if(temp_char[i] == '(')	//(2) Push into stack if left parenthesis
		{
			temp_stack.push(temp_char[i]);
		}
		else if(temp_char[i] == ')')	//(3) Pop stack until the left parenthesis comes out
		{
			while(1)
			{
				if(temp_stack.top() == '(')
				{
					temp_stack.pop();
					break;
				}
				formula.push_back(temp_stack.top());
	
				temp_stack.pop();
			}
		}
		else if(temp_char[i] == '+' || temp_char[i] == '-')	//(4)
		{
			formula.push_back(' ');
			/*
			 * Blank push to distinguish the number of digits
			*/
			if(temp_stack.top() == '(' || temp_stack.top() == 'b')
				temp_stack.push(temp_char[i]);
			else
			{
				while(!(temp_stack.top() == '(' || temp_stack.top() == 'b'))
				{
					formula.push_back(temp_stack.top());
					temp_stack.pop();
				}
				temp_stack.push(temp_char[i]);
			}
		}
		else if(temp_char[i] == '*' || temp_char[i] == '/')	//(4)
		{
			formula.push_back(' ');
			/*
			 * Blank push to distinguish the number of digits
			*/
			if(temp_stack.top() == '+' || temp_stack.top() == '-')
				temp_stack.push(temp_char[i]);
			else
			{
				while(temp_stack.top() == '*' || temp_stack.top() == '/')
				{
					formula.push_back(temp_stack.top());
					temp_stack.pop();
				}
				temp_stack.push(temp_char[i]);
			}
		}
		else
		{	//(0) Number(ASCII code)
			formula.push_back(temp_char[i]);
		}
	}

	while(temp_stack.top() != 'b')		//(5)
	{
		formula.push_back(temp_stack.top());
		temp_stack.pop();
	}

	for(int i = 0; i < formula.size(); i++)
	{
		cout<<formula[i];
	}
	cout<<endl;

	return;
}

int main()
{
	int num;
	temp_stack.push('b');
/*
 * Why push 'b' into the stack?
 *  -> Express the bottom of a stack
*/

	while(1)
	{
		Input_screen();

		split();

		num = valid_formula_check();

		if(num == 1)
			infix_notation_change_to_postfix_notaion();
		else if(num == 0)
			printf("Parentheses do not match or are not math formula\n");

		break;
	}

	return 0;
}
