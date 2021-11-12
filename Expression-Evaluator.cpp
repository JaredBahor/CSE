//
// Created by jared on 6/23/2021.
//

#include <iostream>
#include <string>
#include <stack>
#include <queue>

#include "evalExp.h"

using std::string;
using std::stack;
using std::queue;
using std::cout;
using std::endl;
using std::min;
using std::max;


bool isValidExpression(const string &exp) {
    // Your code
    //char left = '(';
    //char right = (char) ")";
    stack<string> stack;
    char valueL = 40;// (
    char valueR = 41;// )
    for (int i = 0; i < exp.length(); i++){
        char exp1 = exp.at(i);
        if (exp1 == valueL){//pusht he first "(" to the stack
            string val;
            val += exp1;
            stack.push(val);//pushing "(" to the stack
        }else if (exp1 == valueR){
            string l = "(";
            string val;
            val += exp1;
            if (!stack.empty() && stack.top() == l){//check top of stack for "("
                stack.pop();
            }else{
                return false;
            }
        }
    }
    if (stack.empty()){
        return true;
    }else{
        return false;
    }
}

queue<string> parseExpression(const string &exp) {
    // Your code
    string opperand, letter, optor, etc;

    queue<string> queue;
    if (isValidExpression(exp)){// string is a valid expression
        for (int i = 0; i < exp.length(); i++){
            char exp1 = exp.at(i);
            if (exp1 >= '0' && exp1 <= '9'){// ascii values 48 - 57 that represent 0-9// if NUMBER ....
                opperand += exp1;
                if (exp.length() - i > 1){// prevent seg fault// need a check inside of the while loop
                    char exp2 = exp.at(i + 1);// char next to current char
                    if (exp2 >= '0' && exp2 <= '9'){// dont clear opperand
                        // meaning next element is a NUMBER// DONT CLEAR
                    }else{
                        queue.push(opperand);
                        opperand = "";
                        //queue.push("|");
                    }
                    //queue.push(opperand);
                    //opperand = "";
                }else {// end of string
                    queue.push(opperand);
                    opperand = "";
                }
            }else if (exp1 >= 'a' && exp1 <= 'z'){// ascii values 97 - 122 represent a - z// if LETTER ....
                char second = exp.at(i + 1);// i || a
                char third = exp.at(i + 2);// n || x
                letter += exp1;
                letter += second;
                letter += third;
                queue.push(letter);
                letter = "";
                if (exp.length() - i == 1){//end of string

                }else{
                    //queue.push("|");
                }
                i += 2;// could be 3 or 2.. will have to test to confirm
            }else if (exp1 == '*' || exp1 == '+' || exp1 == '-' || exp1 == '/'){// ascii values 42, 43, 45, 47 // if OPERATOR ....
                optor += exp1;
                queue.push(optor);
                optor = "";
                if (exp.length() - i == 1){//end of string

                }else{
                    //queue.push("|");
                }
            }else if (exp1 == '(' || exp1 == ')' || exp1 == ','){// these will be in the min || max functions when called
                etc += exp1;
                queue.push(etc);
                etc = "";
                if (exp.length() - i == 1){//end of string

                }else{
                    //queue.push("|");
                }
            }
            // | after each elemement except the last
            //queue.push("|");// should put in each if statement
        }
    }else{// string is not valid and returning and empty queue;
        return queue;// what should we return if it isnt valid ??
    }
    //queue<string> queue;
    return queue;
}



bool checkPrec(const string &opr1, const string &opr2) {
    /*
        Returns true if opr1 has higher or equal precedence as opr2.
        Returns false if opr1 has loWer precedence than opr2.
    */
    if ((opr1 == "(") or
        (opr1 == "+" and opr2 == "*") or
        (opr1 == "+" and opr2 == "/") or
        (opr1 == "-" and opr2 == "*") or
        (opr1 == "-" and opr2 == "/")) {
        return false;
    } else {
        return true;
    }
}



queue<string> inFixToPostFix(queue<string> &exp){
    // Your code
    queue<string> queue1;
    stack<string> opstack1;
    //string h = exp.front();
    //char e = h[0];

    while (!exp.empty()){
        string tmp = exp.front();
        char input = tmp[0];
        //isdigit(input);
        if (input >= '0' && input <= '9'){
            queue1.push(exp.front());
        }else if (input >= 'a' && input <= 'z'){
            opstack1.push(exp.front());
        }else if (input == '*' || input == '+' || input == '-' || input == '/'){
            while (!opstack1.empty() && checkPrec(opstack1.top(), exp.front())){ // if stack is empty do what?? how do we check to see i guess?? we dont>???
                queue1.push(opstack1.top());
                opstack1.pop();
            }
            opstack1.push(exp.front());// could be wrong idk
        }else if (input == ','){
            string tmp2 = opstack1.top();
            char stac = tmp2[0];
            while (stac != '(' && !opstack1.empty()){
                queue1.push(opstack1.top());
                opstack1.pop();
                tmp2 = opstack1.top();
                stac = tmp2[0];
            }
        }else if(input == '('){
            opstack1.push(exp.front());
        }else if(input == ')'){
            string tmp2 = opstack1.top();
            char stac = tmp2[0];
            while (stac != '(' &&  !opstack1.empty()){
                queue1.push(opstack1.top());
                opstack1.pop();
                tmp2 = opstack1.top();
                stac = tmp2[0];
            }
            opstack1.pop();// '(' popped from stack
            char stackinput;
            if (!opstack1.empty()){
                string tmp1 = opstack1.top();
                stackinput = tmp1[0];
                if (isalpha(stackinput)){// cheks to see if it is a function or not, true if is false otheriwse.
                    queue1.push(opstack1.top());
                    opstack1.pop();
                }
            }
        }
        exp.pop();
    }
    while (!opstack1.empty()){
        queue1.push(opstack1.top());
        opstack1.pop();
    }

    return queue1;
}



int EvalPostFixExp(queue<string> &exp) {
    // Your code

    stack<int> opperand;
    while(!exp.empty()){
        string tmp = exp.front();
        char input = tmp[0];
        if (input >= '0' && input <= '9'){
            int value = stoi(exp.front());
            opperand.push(value);
        }else if(input == '*' || input == '+' || input == '-' || input == '/' || isalpha(input)){
            int b = opperand.top();
            opperand.pop();
            int a = opperand.top();
            opperand.pop();
            if (input == '*'){// order doesnt matter
                int ans = a * b;
                opperand.push(ans);
            }else if (input == '+'){
                int ans = a + b;
                opperand.push(ans);
            }else if (input == '-'){// order matters
                int ans = a - b;
                opperand.push(ans);
            }else if (input == '/'){
                int ans = a / b;
                opperand.push(ans);
            }else {
                input = tmp[1];
                if (input == 'i'){// min
                    int ans = min(a,b);
                    opperand.push(ans);
                }else if (input == 'a'){// max
                    int ans = max(a,b);
                    opperand.push(ans);
                }
            }
        }
        exp.pop();
    }
    return opperand.top();
}



int EvalExp(const string &exp) {
    if (!isValidExpression(exp)) {
        return -1024;
    } else {
        queue<string> parsedExp = parseExpression(exp);
        queue<string> postFixExp = inFixToPostFix(parsedExp);
        int x = EvalPostFixExp(postFixExp);
        return x;
    }

}
