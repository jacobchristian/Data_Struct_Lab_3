#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

//function prototype
int postfixOperation(const std::string&);
int operandSwitchEvaluation(const char&, const int&, const int&);
bool isOperator(const char&);

//main driver
int main() {

    //variable for user input
    std::string userInput;

    std::cout << "Postfix Operation (press Enter by itself to quit): ";
    std::getline(std::cin, userInput);
    
	while (!userInput.empty()) {
		try{
			int result = postfixOperation(userInput);	//Return result if successful
        		std::cout << "Result for " << userInput << " = " << result << '\n';
		}
        catch (std::string e) {						//If the postfix operation was invalid
        	std::cout << e << '\n';
		}
		//Ask again to loop through user (allows enter to be pressed in beginning)
        std::cout << "Postfix Operation (press Enter by itself to quit): ";
    	std::getline(std::cin, userInput);
	}
    return 0;
}

/* Iterates through a string. When it runs into a operator, it checks to see if there
   are at least two operands in the stack, and if not, then it skips. Otherwise, it will
   pop two operands (can be more than 2 in stack) at once and finds the result based on 
   the current operand found in the string. Then, it pushes that result into the stack */
int postfixOperation(const std::string& userInput) {
    std::stack<int> operandStack;  					//create stack object
    int result = 0;                					//Initialize result to return

    for(auto chr : userInput) {						//Iterate through the string
        bool atLeastTwoOperands = operandStack.size() > 1;		//Confirm that two operands are in the stack
        if(0 <= (chr-'0') && (chr-'0' <= 9)) {				//If the character is 0-9, push onto stack
            operandStack.push(chr - '0');				
        }

        else if ( isOperator(chr) && atLeastTwoOperands) {		//If we find that current char is operator and there
            								//are at least two operands on the stack
			int operand2 = operandStack.top();		//Assign operand 2 and pop	
            operandStack.pop();								
            int operand1 = operandStack.top();				//Assign operand 1 and pop
            operandStack.pop();
            int resultant= operandSwitchEvaluation(chr, operand1, operand2);
			operandStack.push(resultant);			//Evaluate result and pop onto stack
        }
    }
    //If the stack is empty or has more than one number left, postfix expression is incorrect, throw exception
    if (operandStack.size() != 1){
    	throw std::string("Error in postfix expression, please try again.\n");
	}
	
	result = operandStack.top();					//Pop the result out of the stack and return
	operandStack.pop();
	return result;			
}

/* switch case function that takes in two operands and peforms a result based on the operand passed in.
   Since only one of four can be passed based on a true result from isOperator(), the default is not needed.
   Semantically included it for convention. */
int operandSwitchEvaluation (const char& op, const int& a, const int& b){
    int result = 0; //Initialize value to return

    switch(op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        default:
            //default not needed, function won't be called unless
            //character is one of four operators
            break;
    }
    return result;
}

/* returns true if one of four operands that are allowed */
bool isOperator(const char& character) {
    return character == '+' || character == '-' ||
           character == '*' || character == '/' ;
} 	
