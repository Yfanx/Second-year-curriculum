#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

string postfixToInfix(const string& postfixExpression) {
    stack<string> stk;

    for (char token : postfixExpression) {
        string str(1, token);  // 将字符转换为字符串

        if (!isOperator(token)) {
            stk.push(str);
        } // 如果是操作数，直接入栈
        else {
            string operand2 = stk.top(); stk.pop();
            string operand1 = stk.top(); stk.pop();
            string infixExpression = "(" + operand1 + " " + str + " " + operand2 + ")";
            stk.push(infixExpression);
        } // 如果是操作符，弹出两个操作数，构造中缀表达式，再入栈
    }
    return stk.top();
}

int main() {
    cout << "请输入后缀表达式: " << endl;

    // 读取后缀表达式
    string postfixExpression;
    getline(cin,postfixExpression);       //输入后缀表达式

    string infixExpression = postfixToInfix(postfixExpression);

    cout << "后缀表达式: " << postfixExpression << endl;
    cout << "中缀表达式: " << infixExpression << endl;
//text
    return 0;
}