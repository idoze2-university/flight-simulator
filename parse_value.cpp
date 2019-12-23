#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include "parser.h"
using namespace std;
static unordered_map<string, double> map;

bool isVariable(string var)
{
    for (char c : var)
    {
        if (Lexer::isBadCharacter(c, 2))
        {
            return false;
        }
    }
    return true;
}

queue<string> shuntingYard(string s)
{
    queue<string> outputQueue;
    stack<string> stack;
    string tempName;
    for (long unsigned int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            stack.push(s.substr(i, 1));
            continue;
        }
        if (s[i] == ')')
        {
            while (stack.top() != "(")
            {
                string temp = "" + stack.top();
                outputQueue.push(temp);
                stack.pop();
            }
            if (!stack.empty() && stack.top() == "(")
            {
                stack.pop();
            }
            continue;
        }
        // if s[i] is number
        if (isdigit(s[i]) || (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/'))
        {
            if (isdigit(s[i]))
            {
                double num = 0;
                double fraction = 0;
                double deciFraction = 1;
                while (isdigit(s[i]))
                {
                    num *= 10;
                    num += stoi(s.substr(i, 1));
                    if (isdigit(s[i + 1]))
                    {
                        ++i;
                        continue;
                    }
                    break;
                }
                if (s[i + 1] == '.')
                {
                    i += 2;
                    while (isdigit(s[i]))
                    {
                        deciFraction /= 10;
                        fraction += stoi(s.substr(i, 1)) * deciFraction;
                        if (!isdigit(s[i + 1]))
                        {
                            break;
                        }
                    }
                }
                outputQueue.push(to_string(num + fraction));
                num = 0;
                deciFraction = 1;
                fraction = 0;
                continue;
            }
            do
            {
                tempName += s[i];
                i++;
            } while (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && i < s.size() && s[i] != ')' &&
                     s[i] != '(');
            i--;
            outputQueue.push(tempName);
            tempName = "";
            continue;
        }
        //if s[i] is operator
        else
        {
            if (s[i] == '-' && !stack.empty() && stack.top() == "-")
            {
                string temp = "" + stack.top();
                outputQueue.push(temp);
                stack.pop();
                stack.push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '-' && !stack.empty() && stack.top() == "+")
            {
                string temp = "" + stack.top();
                outputQueue.push(temp);
                stack.pop();
                stack.push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '+' && !stack.empty() && stack.top() == "-")
            {
                string temp = "" + stack.top();
                outputQueue.push(temp);
                stack.pop();
                stack.push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '/' && !stack.empty() && stack.top() == "/")
            {
                string temp = "" + stack.top();
                outputQueue.push(temp);
                stack.pop();
                stack.push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '/' && !stack.empty() && stack.top() == "*")
            {
                string temp = "" + stack.top();
                outputQueue.push(temp);
                stack.pop();
                stack.push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '*' && !stack.empty() && stack.top() == "/")
            {
                string temp = "" + stack.top();
                outputQueue.push(temp);
                stack.pop();
                stack.push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '*' && !stack.empty() && (stack.top() == "+" || stack.top() == "-"))
            {
                stack.push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '/' && !stack.empty() && (stack.top() == "+" || stack.top() == "-"))
            {
                stack.push(s.substr(i, 1));
                continue;
            }
            //stronger
            if (s[i] == '+' || s[i] == '-')
            {
                while (!stack.empty() && (stack.top() == "/" || stack.top() == "*") && stack.top() != "(")
                {
                    string temp = "" + stack.top();
                    outputQueue.push(temp);
                    stack.pop();
                }
                if (s[i] == '-' && !stack.empty() && stack.top() == "-")
                {
                    string temp = "" + stack.top();
                    outputQueue.push(temp);
                    stack.pop();
                    stack.push(s.substr(i, 1));
                    continue;
                }
                if (s[i] == '-' && !stack.empty() && stack.top() == "+")
                {
                    string temp = "" + stack.top();
                    outputQueue.push(temp);
                    stack.pop();
                    stack.push(s.substr(i, 1));
                    continue;
                }
                if (s[i] == '+' && !stack.empty() && stack.top() == "-")
                {
                    string temp = "" + stack.top();
                    outputQueue.push(temp);
                    stack.pop();
                    stack.push(s.substr(i, 1));
                    continue;
                }
            }
            stack.push(s.substr(i, 1));
            continue;
        }
    }
    while (!stack.empty())
    {
        string temp = "" + stack.top();
        outputQueue.push(temp);
        stack.pop();
    }
    return outputQueue;
}

void setVariables(queue<string> &q)
{
    for (long unsigned int i = 0; i < q.size(); i++)
    {
        double value;
        string token = q.front();
        if (isVariable(token))
        {
            try
            {
                value = DB::getInstance()->getSymbol(token);
            }
            catch (string e)
            {
                cout << e << endl;
            }
            string value_str = to_string(value);
            q.pop();
            q.push(value_str);
        }
        else
        {
            q.pop();
            q.push(token);
        }
    }
}

double calculateBin(double first, double second, char math)
{
    switch (math)
    {
    case '+':
        return first + second;
    case '-':
        return first - second;
    case '*':
        return first * second;
    case '/':
        return first / second;
    default:
        break;
    }
    return false;
}

double calculateAll(queue<string> q)
{
    stack<string> stack;
    string first, second;
    while (!q.empty())
    {
        string token = q.front();
        if (Lexer::isMathToken(token[0]))
        {
            second = stack.top();
            stack.pop();
            first = stack.top();
            stack.pop();
            stack.push(to_string(calculateBin(stod(first), stod(second), token[0])));
        }
        else
        {
            stack.push(token);
        }
        q.pop();
    }
    return stod(stack.top());
}

string fixBrackets(string s)
{
    int countLeft = 0, countRight = 0, bracetsToAdd;
    for (char i : s)
    {
        if (i == '(')
        {
            countLeft++;
        }
        if (i == ')')
        {
            countRight++;
        }
    }
    if (countLeft > countRight)
    {
        bracetsToAdd = countLeft - countRight;
    }
    else
    {
        bracetsToAdd = countRight - countLeft;
    }
    for (int i = 0; i < bracetsToAdd; i++)
    {
        s += ')';
    }
    return s;
}

string fixNeg(string s)
{
    string newS;
    newS = "";
    for (long unsigned int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0' && s[i + 1] == '-' && s[i + 2] == '0')
        {
        }
        if (s[i] == '(' && s[i + 1] == '-')
        {
            if (s[i + 2] != '(')
            {
                newS = newS + s[i] + "(" + "0" + "-";
                int skipper = i + 2;
                if (isdigit(s[skipper]))
                {
                    while (isdigit(s[skipper]) || s[skipper] == '.')
                    {
                        newS += s[skipper];
                        skipper++;
                    }
                    newS += ')';
                    i = skipper;
                    continue;
                }
                while (s[skipper] != '+' && s[skipper] != '-' && s[skipper] != '*' && s[skipper] != '/')
                {
                    newS += s[skipper];
                    skipper++;
                }
                newS += ')';
                i = skipper - 1;
                continue;
            }
            else if (s[i + 2] == '(')
            {
                newS = newS + '(' + '0' + '-';
                i++;
                continue;
            }
        }
        if ((s[i] == '+' && s[i + 1] == '-') || (s[i] == '-' && s[i + 1] == '+'))
        {
            newS = newS + "-";
            ++i;
            continue;
        }
        if (((s[i] == '-' && s[i + 1] == '-')) || ((s[i] == '+' && s[i + 1] == '+')))
        {
            newS = newS + "+";
            ++i;
            continue;
        }
        if ((s[i] == '*' || s[i] == '/') && s[i + 1] == '-')
        {
            newS = newS + s[i] + "(0-" + s[i + 2] + ')';
            i += 2;
            continue;
        }
        if (s[i] == '+')
        {
            if (s[i + 1] == ')')
            {
                continue;
            }
            if (i == 0)
            {
                continue;
            }
            if (s[i - 1] == '*' || s[i - 1] == '/')
            {
                continue;
            }
        }
        if (i == 0 && s[i] == '-')
        {
            newS = newS + "0-" + s[i + 1];
            i++;
            continue;
        }
        newS = newS + s[i];
    }
    try
    {
        string e = "Error";
        if (newS.size() > 100)
        {
            throw e;
        }
    }
    catch (string e)
    {
        cout << e << endl;
    }
    newS = fixBrackets(newS);
    return newS;
}
int checkCondition(double left, double right, string condition)
{
    if (condition == "!=")
    {
        return left != right;
    }
    else if (condition == "==")
    {
        return left == right;
    }
    else if (condition == ">=")
    {
        return left >= right;
    }
    else if (condition == "<=")
    {
        return left <= right;
    }
    else if (condition == "<")
    {
        return left < right;
    }
    else if (condition == ">")
    {
        return left > right;
    }
    return 0;
}
double Parser::parseValue(string var)
{
    while (var != fixNeg(var))
    {
        var = fixNeg(var);
    }
    queue<string> queue = shuntingYard(var);
    setVariables(queue);
    return calculateAll(queue);
}

int parseCondition(string s)
{
    string left_str, right_str, condition, e = s + ". Bad Condition Error";
    double left_v, right_v;
    int pos;
    try
    {
        if (s.find("==") != string::npos)
        {
            pos = s.find('=');
            condition = "==";
            left_str = s.substr(0, pos);
            right_str = s.substr(pos + 2, s.size());
        }
        else if (s.find("!=") != string::npos)
        {
            pos = s.find('!');
            condition = "!=";
            left_str = s.substr(0, pos);
            right_str = s.substr(pos + 2, s.size());
        }
        else if (s.find(">=") != string::npos)
        {
            pos = s.find('>');
            condition = ">=";
            left_str = s.substr(0, pos);
            right_str = s.substr(pos + 2, s.size());
        }
        else if (s.find("<=") != string::npos)
        {
            pos = s.find('<');
            condition = "<=";
            left_str = s.substr(0, pos);
            right_str = s.substr(pos + 2, s.size());
        }
        else if (s.find('>') != string::npos)
        {
            pos = s.find('>');
            condition = ">";
            left_str = s.substr(0, pos);
            right_str = s.substr(pos + 1, s.size());
        }
        else if (s.find('<') != string::npos)
        {
            pos = s.find('<');
            condition = "<";
            left_str = s.substr(0, pos);
            right_str = s.substr(pos + 1, s.size());
        }
        else
        {
            throw e;
        }
        left_v = Parser::parseValue(left_str);
        right_v = Parser::parseValue(right_str);
    }
    catch (string err)
    {
        cout << err << endl;
    }
    return checkCondition(left_v, right_v, condition);
}