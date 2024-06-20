//Conversion Infix Expression into Postfix
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
// get weight of operators as per precedence
// higher weight given to operators with higher precedence // for non operators, return 0
int getPriority(char ch) {
    switch (ch) {
        case '/':
        case '*': return 2;
        case '+':
        case '-': return 1;
        default : return 0;
    }
}
// convert infix expression to postfix using a stack
void infix2postfix(char infix[], char postfix[], int size) { stack<char> s;
    int priority;
    int i = 0;
    int k = 0;
    char ch;
    // iterate over the infix expression
    while (i < size) {
        ch = infix[i];
        if (ch == '(') {
            // simply push the opening parenthesis
            s.push(ch);
            i++;
            continue;
        }
        if (ch == ')')
            {
                // if we see a closing parenthesis,
                // pop of all the elements and append it to
                // the postfix expression till we encounter
                // a opening parenthesis
                while (!s.empty() && s.top() != '(') {
                    postfix[k++] = s.top();
                    s.pop();
                }
                // pop off the opening parenthesis also
                if (!s.empty()) {
                    s.pop(); }
                i++;
                continue; }
        priority = getPriority(ch);
        if (priority == 0) {
            // we saw an operand
            // simply append it to postfix expression
            postfix[k++] = ch;
        }
        else {
            // we saw an operator
            if (s.empty()) {
                // simply push the operator onto stack if
                // stack is empty
                s.push(ch);
            }
            else {
                // pop of all the operators from the stack and
                // append it to the postfix expression till we
                // see an operator with a lower precedence that
                // the current operator
                while (!s.empty() && s.top() != '(' && priority <=
                       getPriority(s.top())) {
                    postfix[k++] = s.top();
                    s.pop(); }
                // push the current operator onto stack
                s.push(ch);
            }
        }
        i++; }
    // pop of the remaining operators present in the stack // and append it to postfix expression
    while (!s.empty()) {
        postfix[k++] = s.top();
        s.pop(); }
    postfix[k] = '\0'; // null terminate the postfix expression
}
    void Eval(char postfix[40]) //123+*
    {
        stack<int> s;
        int op1, op2;
        char token;
        int i, result;
        for(i=0;i<strlen(postfix);i++)
        {   token=postfix[i];
            if(getPriority(token)==0)
            {
                //operand found push on stack
                s.push(token-48); //atoi
            }
            else
            {
                op2=s.top();
                s.pop();
                cout<<"1:"<<op2;
                op1=s.top();
                cout<<"2:"<<op1;
                s.pop();
                switch(token)
                {
                    case '+':  result=op1+op2; break;
                    case '-':  result=op1-op2; break;
                    case '*':  result=op1*op2; break;
                    case '/':  result=op1/op2; break;
                }
                s.push(result);
            }
        }
        cout<<"\n Postfix expression:"<<postfix; cout<<"\n Evaluation result is:"<<s.top();
    }
    // main
    int main()
{
        char infix[40];
        int ch,size;
        char postfix[40];
        while(1)
        {
            cout<<"\nMenu: \n1. Read infix expression \n2.Infix to Postfix\n3. Evaluation \n4.Exit";
            cout<<"\nEnter Choice:";
            cin>>ch;
            switch(ch)
            {
                case 1:
                    cout<<"Enter String/line:";
                    cin>>infix;
                    size = strlen(infix);
                    break;
                case 2:
                    infix2postfix(infix,postfix,size);
                    cout<<"\nInfix Expression :: "<<infix;
                    cout<<"\nPostfix Expression :: "<<postfix;
                    break;
                case 3:
                    cout<<"\nEnter postfix expression (operands will be only one digit):";
                    cin>>postfix;
                    Eval(postfix);
                    break;
                case 4:
                    exit(0);
            }
            
        }
        return 0;
}

