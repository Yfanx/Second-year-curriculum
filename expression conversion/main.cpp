#include <iostream>
#include <string>

using namespace std;

// 栈节点结构体定义
struct StackNode {
    string data;       // 节点存储的数据
    StackNode* next;   // 指向下一个节点的指针

    // 构造函数，初始化节点数据
    StackNode(string data) : data(data), next(nullptr) {}
};

// 自定义栈类
class Stack {
private:
    StackNode* top; // 指向栈顶的指针

public:
    // 构造函数，初始化栈为空
    Stack() : top(nullptr) {}

    // 判断栈是否为空
    bool isEmpty() const {
        return top == nullptr;
    }

    // 入栈操作
    void push(const string& str) {
        StackNode* node = new StackNode(str); // 创建新节点
        node->next = top;                     // 新节点指向当前栈顶节点
        top = node;                           // 更新栈顶指针为新节点
    }

    // 出栈操作
    string pop() {
        if (isEmpty()) {
            throw exception("Stack underflow"); // 栈为空时抛出异常
        }
        string data = top->data;             // 保存栈顶数据
        StackNode* temp = top;               // 临时保存栈顶节点
        top = top->next;                     // 更新栈顶为下一个节点
        delete temp;                         // 释放原栈顶节点内存
        return data;                         // 返回栈顶数据
    }

    // 获取栈顶元素
    string peek() const {
        if (isEmpty()) {
            throw exception("Stack is empty"); // 栈为空时抛出异常
        }
        return top->data; // 返回栈顶数据
    }

    // 析构函数，用于释放栈内存
    ~Stack() {
        while (!isEmpty()) {
            pop(); // 释放所有节点内存
        }
    }
};

// 判断字符是否为运算符
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isEmpty(char c){
    return (c == ' ');
}

// 判断字符是否为操作数
bool isOperand(char c) {
    return (c >= '0' && c <= '9'|| c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

// 后缀表达式转中缀表达式
string postfixToInfix(const string& postfixExpression) {
    Stack stk; // 创建栈对象
    for (char token : postfixExpression) {
        if (isEmpty(token)) {
            continue;
        } else if (isOperator(token)) {
            // 检查栈是否有足够的操作数
            if (stk.isEmpty()) {
                throw exception("Invalid postfix expression: insufficient operands");
            }
            string operand2 = stk.pop();
            if (stk.isEmpty()) {
                throw exception("Invalid postfix expression: insufficient operands");
            }
            string operand1 = stk.pop();
            stk.push("(" + operand1 + " " + token + " " + operand2 + ")");
        } else if (isOperand(token)) {
            stk.push(string(1, token));
        } else {
            throw runtime_error(string("Invalid character encountered: ") + token);
        }
    }

    // 现在栈中理论上只有一个元素，即最终的中缀表达式
    string result = stk.peek(); // 获取栈顶元素但不移除
    stk.pop();                  // 移除栈顶元素

    // 如果栈不为空，说明后缀表达式不合法
    if (!stk.isEmpty()) {
        throw runtime_error("Invalid postfix expression: too many operands");
    }
    return result;
}

// 删除最外层的括号
string removeOuterParentheses(const string& infixExpression) {
    return infixExpression.substr(1, infixExpression.length() - 2);
}

// 主函数
int main() {
    cout << "请输入后缀表达式: " << endl;
    string postfixExpression;
    getline(cin, postfixExpression); // 读取后缀表达式

    try {
        // 将后缀表达式转换为中缀表达式
        string infixExpression = postfixToInfix(postfixExpression);
        // 删除最外层括号
        infixExpression = removeOuterParentheses(infixExpression);
        // 输出结果
        cout << "后缀表达式: " << postfixExpression << endl;
        cout << "中缀表达式: " << infixExpression << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

