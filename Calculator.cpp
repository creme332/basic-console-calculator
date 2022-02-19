#include <string>
#include <iostream>
#include <regex>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

int precedence(char op) {
    switch (op) {
    case '-':return 2;
    case '+':return 2;
    case '/':return 3;
    case '*':return 3;
    case '^':return 4;
    case 'm': return 5; //unary minus
    case 'p': return 5; //unary plus
    }
    return -1;
}
char associativity(char op) {
    //L : left associativity R: right associativity
    switch (op) {
    case '-':return 'L';
    case '+':return 'L';
    case '/':return 'L';
    case '*':return 'L';
    case '^':return 'R';
    case 'm':return 'R'; //unary minus
    case 'p':return 'R'; //unary plus
    }
    return '.';
}

bool isoperator(char op) {
    //used to identify unary operators. A unary operator appears just after the following op.
    switch (op) {
    case '-':return 1;
    case '+':return 1;
    case '/':return 1;
    case '*':return 1;
    case '^':return 1;
    case '(':return 1;
    }
    //Note a minus/plus following ) is not a unary minus/plus
    return 0;
}
std::string modify(std::string s) {
    //Remove all spaces from s
    //Replace unary plus with p
    //Replace unary minus with m
    //add * before ( if there's no operator

    s = std::regex_replace(s, std::regex(" "), ""); //remove spaces

     //Replace unary plus with p
    //Replace unary minus with m
    for (long long i = 1;i < s.length();i++) {
        if (isoperator(s[i - 1]) && (s[i] == '-' || s[i] == 'm')) {
            s[i] = 'm';
        }
        if (isoperator(s[i - 1]) && (s[i] == '+' || s[i] == 'p')) {
            s[i] = 'p';
        }
    }
    if (s[0] == '-') { s[0] = 'm'; }
    if (s[0] == '+') { s[0] = 'p'; }

    //add * before ( if there's no operator
    std::string ans="";
    for (int i = 0;i < s.length()-1;i++) {
        if (s[i] >= '0' && s[i] <= '9' && s[i + 1] == '(') {
            ans += s[i]; ans+= '*';
        }
        else {
            ans += s[i];
        }
    }
    ans += s[s.length() - 1];
    return ans;
}

std::string to_postfix(std::string exp) {
    //Implementation of shunting yard algorithm.
    exp = modify(exp);
    std::vector <char> operators;
    std::string ans = "";
    std::string operand = "";
    char prevchar = '*';

    for (long long i = 0;i < exp.length();i++) {

        if (i > 0) { prevchar = exp[i - 1]; }
        char c = exp[i];

        if (isdigit(c) != 0 || c == '.') { // if c is a digit or a decimal point
            operand += c;
        }
        else {// c is an operator 

          //add operand to ans
            if (operand != "") {
                ans += operand + " ";
                operand = "";
            }
            if (operators.size() == 0 || c == '(') {
                operators.push_back(c);
            }
            else { //operator stack not empty
                char top = operators.back(); //operator at top of operator stack
                if (c == ')') {
                    while (top != '(') {
                        ans += top;ans += " ";
                        operators.pop_back();
                        top = operators.back();
                    }
                    operators.pop_back(); //pop the (
                }
                else {
                    if (top == '(' || (associativity(c) == 'R' && (precedence(c) >= precedence(top)))) {
                        operators.push_back(c);
                    }
                    else {
                        if (associativity(c) == 'L') {
                            while (precedence(c) <= precedence(top) && operators.size() != 0 && top != '(') {
                                ans += top; ans += " ";
                                operators.pop_back();
                                if (operators.size() == 0) { break; }
                                top = operators.back();
                            }
                            operators.push_back(c);
                        }
                    }
                }
            }

        }
    }

    if (operand != "") {
        ans += operand + " ";
    }
    if (operators.size() != 0) {
        for (int i = operators.size() - 1;i > -1;i--) {
            ans += operators[i]; ans += " ";
        }
    }

    return ans;
}

double result(double a, double b, std::string o) {
    //result(5.2, 1.1, "-") returns 4.1
    if (o == "+") { return a + b; }
    if (o == "-") { return a - b; }
    if (o == "*") { return a * b; }
    if (o == "/") { return a / b; }
    if (o == "^") { return pow(a, b); }
    return 0;
}
double EvaluateExpression(std::string exp) {
    std::string postfix = to_postfix(exp); //postfix has spaces but no ()
    std::cout<<"Postfix = "<< postfix<<"\n\n";
    std::regex regex(R"([\s]+)");
    std::vector<std::string> out( // save all space-separated operands and operators to out
        std::sregex_token_iterator(postfix.begin(), postfix.end(), regex, -1),
        std::sregex_token_iterator()
    );

    //Note : unary plus is always ignored
    std::vector <double> Operand;
    for (auto i : out) {
        if (i == "m") { //unary minus
            double a = Operand.back();
            Operand.pop_back();
            Operand.push_back(a * -1);
        }
        else {
            if (i == "*" || i == "/" || i == "+" || i == "-" || i == "^") {
                double b = Operand.back();
                Operand.pop_back();
                double a = Operand.back();
                Operand.pop_back();
                Operand.push_back(result(a, b, i));
            }
            else {
                Operand.push_back(stod(i));
            }
        }
    }
    return Operand.back();
}
int main() {
    std::string expression; int p;
    std::cout << "Enter your mathematical expression : ";
    std::cin >> expression;
    std::cout << "\n";
    std::cout << "Enter precision (number of decimal places): ";
    std::cin >> p;
    std::cout << "\n";
    double result = EvaluateExpression(expression);
    std::cout << "Answer = " << std::fixed << std::setprecision(p) << result << "\n\n";
    system("pause");
}