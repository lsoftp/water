#ifndef FORMULA_H
#define FORMULA_H

#include<iostream>
#include<vector>
#include<cstdio>
#include<map>
#include<cstring>
#include<string>
using namespace std;

typedef map<string, double> MSD;
//表达式类
class Expression
{
public:
    virtual double Evaluate(MSD vars){ return 0; }

};
//常数类
class Constant :public Expression
{
public:
    double value;
    Constant(double value)
    {
        this->value = value;
    }
    double Evaluate(MSD vars)
    {
        return value;
    }
};
//未知数类
class VariableReference :public Expression
{
public:
    string name;
    VariableReference(string name)
    {
        this->name = name;
    }
    double Evaluate(MSD vars)
    {
        double value = vars[name];
        return value;
    }
};
//运算类
class Operation :public Expression
{
public:
    //左边的表达式
    Expression *left;
    //当前运算
    char op;
    //右边的表达式
    Expression *right;
    Operation(Expression *left, char op, Expression *right)
    {
        this->left = left;
        this->op = op;
        this->right = right;
    }
    //计算值
    double Evaluate(MSD vars)
    {
        //递归计算
        double x = left->Evaluate(vars);
        double y = right->Evaluate(vars);
        //运算
        switch (op)
        {
        case '+':return x + y;
        case '-':return x - y;
        case '*':return x*y;
        case '/':return x / y;
        }
    }
};
//将字符串转换为树
//s起始位置，t结束位置
Expression *strToTree(string str, int s, int t)
{
    //去除包含整个当前表达式的括号
    while (s <= t&&str[s] == '('&&str[t] == ')')s++, t--;
    if (s > t)
        return new Constant(0);
    //findLetter找到字母，用以判断是否为未知数
    //findChar找到字符，用以判断是否存在运算符
    bool findLetter = false, findChar = false;
    //括号标记
    int brackets = 0;
    //lastPS最后的加减法
    //lastMD最后的乘除
    int lastPS = -1, lastMD = -1;

    for (int i = s; i <= t; i++)
    {
        //当前位置不是常数
        if (str[i] != '.' && (str[i]<'0' || str[i]>'9'))
        {
            //如果是字母的话
            if ((str[i] >= 'a'&&str[i] <= 'z') || (str[i] >= 'A'&&str[i] <= 'Z'))
                findLetter = true;
            else
            {
                //不是常数，不是字母，就是运算符
                findChar = true;
                switch (str[i])
                {
                case '(':brackets++; break;
                case ')':brackets--; break;
                    //更新最后加减法的位置
                case '+':
                case '-':if (!brackets)lastPS = i; break;
                    //更新最后乘除法的位置
                case '*':
                case '/':if (!brackets)lastMD = i; break;
                }
            }
        }
    }
    //从s到t都是常数
    if (findLetter == false && findChar == false)
        return new Constant(stod(str.substr(s, t - s + 1)));
    //从s到t是未知数
    if (findChar == false)
        return new VariableReference(str.substr(s, t - s + 1));
    //从s到t是个运算
    //没有加减就用乘除
    if (lastPS == -1)
        lastPS = lastMD;
    return new Operation(strToTree(str, s, lastPS - 1), str[lastPS], strToTree(str, lastPS + 1, t));
}

//int main()
//{
//	MSD vars;
//	//这里设置未知数
//	vars["x"] = 123;
//	vars["y"] = 100;
//	//输入字符串
//	string str;
//	cin >> str;
//	//转换为树
//	Expression *exp = strToTree(str, 0, str.length() - 1);
//	//输出值
//	cout << exp->Evaluate(vars) << endl;
//	return 0;
//}


#endif // FORMULA_H
