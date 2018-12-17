#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <ctime>
using namespace std;



//Gathers input and checks for errors in the input.
template<typename T>
void GetInput(T &target, string prompt, string errorMessage){
	cout << prompt;
	while (not(cin >> target)){
		cout << errorMessage;
		cin.clear();
		cin.ignore(1024, '\n');
	}
}

//generates two integers to be used as operands for arithmetic.
void ProblemGenerator(int &operand1, int &operand2){
	operand1 = rand();
	operand2 = rand();
}

//returns an random operand as an integer.
int GenerateOperand(int digitCount){
	int randomDigit = rand();
	randomDigit = randomDigit % 100;
	vector <string> randomDigitVect = {to_string(randomDigit)};

//while loop counts the number of digits in randomDigit (assigned to 
//randomDigitVect)
	int currentDigit{0};
	while (randomDigitVect[0][currentDigit]){
		++currentDigit;
	}
	float randomDigitLen = currentDigit;
	
	float removedDigits = randomDigitLen - digitCount;
//division cancels the unwanted digits.
	int operand = (randomDigit / ((pow(10.0, removedDigits))));
	return operand;
}

//returns a string containing the problem and its prompt.
string DisplayProblem(string prompt, int operand1, int operand2, \
					char operator1){
	string problemStatement = prompt + to_string(operand1) + " " \
									+ operator1 + " " + to_string(operand2) \
									+ '\n';
	return problemStatement;
}

int main(){
    cout << "This is a program for training your arithmetic skills. The problems will get harder " \
    "as you progress. The problems will get harder when you get a series of questions right " \
    "and easier when you get consecutive problems wrong." << endl;
	srand(time(NULL));
    //defining the lengths of the operands in the problem.
	int operand1Size = 1;
	int operand2Size = 1;
    //defining the operands of the arithmetic question.
	int operand1 = GenerateOperand(operand1Size);
	int operand2 = GenerateOperand(operand2Size);
	vector <string> operandVect;
	operandVect.push_back(to_string(operand1) + to_string(operand2));
    
	//stores the values that correspond to a operation for intuitive access.
	enum operations{plus = 1, minus, multiply, divide};
	int randomNum{0};
	randomNum = rand();
    
    //used as a flag for looping through the procedure
    //that determines the operation for the question.
	bool randomCheck{false};
    
    //result will hold the correct answer to the problem.
	int result{0};
    
	char operator1{' '};
    
    //sentinel for the main loop.
	char playAgain;
	string playAgainPrompt = "q)uit, anything to continue: ";
    string genericErrorMsg = "Invalid Option";
    
    //Asking the user whether they want to quit or play.
	GetInput(playAgain, playAgainPrompt, genericErrorMsg);
    
    //counts the number of problems worked over the lifecycle of the program. No persistence.
    int incrementCheck{0};
    
    //Counters for false and correct answers, respectively.
    int falseAnswers{0};
    int correctAnswers{0};
    
	while (playAgain != 'q'){
		do{
			if ((randomNum % 2) == 0){
				result = operand1 + operand2;
				operator1 = '+';
				randomCheck = false;
			}
			else if ((randomNum % 2) != 0){
				result = operand1 - operand2;
				operator1 = '-';
				randomCheck = false;
			}
			else if ((randomNum % 3) == 0){
				result = operand1 * operand2;
				operator1 = '*';
				randomCheck = false;
	
			}
			else if ((randomNum % 5) == 0){
				result = operand1 / operand2;
				operator1 = '/';
				randomCheck = false;
	
			}
			else{
				randomCheck = true;
			}
		} while(randomCheck);
        

		string prompt = "Enter the answer: ";
		cout << DisplayProblem(prompt, operand1, operand2, operator1) << endl;
        
        //user inputs their guess into resultInput
		int resultInput{0};
		string inputPrompt = "Enter the result: ";
		string inputErrorMsg = "Invalid result.";
        
        //starting time
		int solveTimeInit = time(NULL);
        
        //Gathering input. ie. Getting the user's answer.
		GetInput(resultInput, inputPrompt, inputErrorMsg);
        
        //ending time
		int solveTimeFinal = time(NULL);
		int timeDifference = solveTimeFinal - solveTimeInit;
		bool answerCorrect{false};
        

        ++incrementCheck;
        //Do this if the answer's correct and answered within the time limit.
		if ((result == resultInput) and (timeDifference <= 5)){
			answerCorrect = true;
            
            //resets the answer streak.
			falseAnswers = 0;
			++correctAnswers;
			cout << "Correct Answer" << endl;
		}
        
        //Do this if the answer's wrong.
		else{
			answerCorrect = false;
            
            //resets the answer streak
			correctAnswers = 0;
			++falseAnswers;
			if (timeDifference > 5){
				cout << "Timed Out. ";
			}
			if (result != resultInput){
				cout << "Incorrect Answer. ";
			}
			cout << "No Credit. " << endl;
		}

		
		//After three false answers and adequately sized operands, do this.
		if ((falseAnswers == 3) and (operand1Size > 1) and (operand2Size > 1)){
			--operand1Size;
			--operand2Size;
            falseAnswers = 0;
		}
		
        //Do this if the user has entered two correct answers in a row and incrementCheck is even.
		if ((correctAnswers == 2) and ((incrementCheck % 2) == 0)){
			++operand1Size;
            correctAnswers = 0;
		}
        //Do this after two correct answers and if incrementCheck mod 2 is not zero. ie. it's odd.
		else if ((correctAnswers == 2) and ((incrementCheck % 2) != 0)){
			++operand2Size;
            correctAnswers = 0;
		}
        
        //Asking the user to play again.
		GetInput(playAgain, playAgainPrompt, "Invalid Option");

        //Generating new operands.
        operand1 = GenerateOperand(operand1Size);
		operand2 = GenerateOperand(operand2Size);
	}
    cout << "Program Ending." << endl;
	return 0;
}