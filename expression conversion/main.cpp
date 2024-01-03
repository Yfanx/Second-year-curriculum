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
            throw runtime_error("Stack is empty"); // 栈为空时抛出异常
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
            throw runtime_error("Stack is empty"); // 栈为空时抛出异常
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

// 后缀表达式转中缀表达式
string postfixToInfix(const string& postfixExpression) {
    Stack stk; // 创建栈对象

    for (char token : postfixExpression) {
        string str(1, token); // 将字符转换为字符串

        if (!isOperator(token)) {
            if(isEmpty(token)){
                continue;
            }
            stk.push(str); // 如果是操作数，直接入栈
        } else {
            // 如果是操作符，从栈中弹出两个操作数
            string operand2 = stk.pop();
            string operand1 = stk.pop();
            // 构造中缀表达式并将其入栈
            string infixExpression = "(" + operand1 + " " + str + " " + operand2 + ")";
            stk.push(infixExpression);
        }
    }
    return stk.peek(); // 返回栈顶元素，即最终的中缀表达式
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
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
