#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
char pop(std::string &str) {
	char item = str.back();
	str.pop_back();
	if (item == '(' || item == ')') 
		return NULL;
	return item;
}
int priority(char c) {
	if (c == '$' || c == '^')
		return 3;
	else if (c== '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return 0;
}
bool check_valid(char c) {
	return ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123)) ? true : false;
//if alphabet or number return true otherwise return false;
}
void delete_space(std::string &input) {
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
}
void convert_operator(std::string &input) {
	//this function convert input when have -+  operator to - or when - - to +
	int i = 0;
	int j = 0;
	std::string new_input;
	while (i<input.size()) {
		if ((input[i] == '+') && input[i + 1] == '-' || (input[i] == '-'&&input[i + 1] == '+')) {
			new_input.push_back('-');
			i += 2;
		}
		else if ((input[i] == '-') && (input[i + 1] == '-')) {
			new_input.push_back('+');
			i += 2;
		}
		else {
			new_input.push_back(input[i]);
			i++;
		}
	}
	input = new_input;
}
bool push_power(std::string &stack,char e) {
	if ((stack.back() == '$' || stack.back() == '^') && ((e == '$') || (e == '^'))) {
		return true;
	}
	else
		return false;
}
void infix_to_postfix(std::string & infix, std::string &  n_element) {
	std::string stack;
	delete_space(infix);
	//convert_operator(infix);
	for (int i = 0; i < infix.size(); i++) {
		int c = 0;
		if (check_valid(infix[i])) {
			n_element.push_back(' ');
			int j = 0;
			while (check_valid(infix[i])) {
				n_element.push_back(infix[i]);
				i++;
				 //x *= -1;

			}
			i--;
		}
		else if (infix[i] == '(') {
			stack.push_back(infix[i]);
		}
		else if (!(check_valid(infix[i]))) {
			int timer = 0;
			if ((!stack.empty())&&(stack.back() == '$'||stack.back()=='^')&&(infix[i] == '$'||infix[i]=='^')){
				stack.push_back(infix[i]);
			}
			else
			do { 
				timer = 0;
				if (stack.empty()) {
					stack.push_back(infix[i]);
					timer = 1;
				}
				else if (stack.back() == '(') {
					if (c) {
						n_element.push_back(' ');
						pop(stack);
						timer = 1;
						break;
					}
					timer = 1;
					stack.push_back(infix[i]);
				}
				else if (priority(infix[i]) > priority(stack.back())) {
					stack.push_back(infix[i]);
					timer = 1;
				}
				else {
					if (infix[i]== ')') 
						c = 1;
				n_element.push_back(' ');
				n_element.push_back(pop(stack));
						
					
				}
			} while (!timer);
		}
		else {
			while (stack.back() != '(') {
				n_element.push_back(' ');
				n_element.push_back(pop(stack));
			}
			n_element.push_back(' ');
			pop(stack);
		}

	}
	if (!stack.empty()) {
		while (!stack.empty()) {
			n_element.push_back(pop(stack));
		}

	}
	//n_element.push_back(pop(stack));
}
int pop_digit(std::vector<int>&digits) {
	if (digits.empty())
		exit(1);
	else
	{
		int item = digits.back();
		digits.pop_back();
		return item;
	}

}
int postfix_evoluation(std::string input) {
	std::string n_element;
	std::vector<int>digits;
	convert_operator(input);
	infix_to_postfix(input, n_element);

	for (auto i=0;i<n_element.size();i++){
		if (n_element[i] == ' ')
			continue;
		else if (n_element[i] == '\n')
			continue;
		else if (isdigit(n_element[i])) {
			int number = 0;
			while (isdigit(n_element[i])) {
				number = number * 10 + (int)n_element[i]- '0';//this one for multiple number;
				i++;
			
			}
			i--;
			digits.push_back(number);

		}
		else {
			int value1 = pop_digit(digits);
			int value2 = pop_digit(digits);
			switch (n_element[i]) {
			case '+':
				digits.push_back(value1 + value2);
				break;
			case '-':
				digits.push_back(value2 - value1);
				break;

			case '$':
				digits.push_back(pow(value2,value1));
				break;
			case '*':
				digits.push_back(value2*value1);
				break;
			case '/':
				digits.push_back(value2 / value1);
				break;
			}
			
		}

	}
	auto value = digits.back();

	return value;

}
int main() {
	std::string n_element;
	std::string input;
	
	std::cout << "enter your  infix expression : ";
	std::cin >> input;
	infix_to_postfix(input, n_element);
	postfix_evoluation(input);
	std::cout << std::endl << n_element << std::endl;
	std::cout << postfix_evoluation(input) << std::endl;


	system("pause");
	return 0;

}