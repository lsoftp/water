#ifndef FORMULA_H
#define FORMULA_H

#include<iostream>
#include<vector>
#include<cstdio>
#include<map>
#include<cstring>
#include<string>
//#include<set>
using namespace std;

typedef map<string, double> MSD;
//表达式类
class Expression
{
public:
    virtual double Evaluate(MSD vars){ return 0; }
    virtual ~Expression(){cout<<"~Expression"<<endl;}
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
        cout<<"const:"<<value<<endl;
        return value;
    }
    virtual ~Constant(){cout<<"~Constant "<<"const:"<<value<<endl;}
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
        cout<<"variable " <<name<<" "<<value<<endl;
        return value;
    }
    virtual ~VariableReference(){cout<<"~VariableReference  "<<"variable " <<name<<" "<<endl;}
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
        double x ,y;
        //递归计算
        if(left)
        {
             x = left->Evaluate(vars);
        }
        else
        return -99999;
        if(right)
        {
             y = right->Evaluate(vars);
        }
        else
        return -99999;
             //运算
                cout<<x<<op<<y<<endl;

        switch (op)
        {
        case '+':return x + y;
        case '-':return x - y;
        case '*':return x*y;
        case '/':return x / y;
        }

    }

     virtual ~Operation(){
        cout<<"~Operation"<<op<<endl;

    }
};
//将字符串转换为树
//s起始位置，t结束位置

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

class Formula
{
public:
    string str;
    Expression *e;
    MSD itemmap;
    bool isvalid;
    Formula(string s);
    ~Formula();
    double value(MSD vs)
    {
        if(e!=NULL)
        return e->Evaluate(vs);
        else
            return -999999;
    }

    void formuleDestroy(Expression *e)
    {
        //Expression  l=*left,r=*right;
        if(Operation* p=dynamic_cast<Operation*>(e))
        {

            formuleDestroy(p->left);
            formuleDestroy(p->right);
            delete p;
            cout<<"delet p"<<endl;
            return;
        }
        if(Constant* p1=dynamic_cast<Constant*>(e))
        {
            delete p1;
            return;
        }
        if(VariableReference* p2=dynamic_cast<VariableReference*>(e))
        {
            delete p2;
            return;
        }

    }

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
                if ((str[i] >= 'a'&&str[i] <= 'z') || (str[i] >= 'A'&&str[i] <= 'Z')||str[i]=='_')
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
        if (findChar == false){
            itemmap[str.substr(s, t - s + 1)]=0;
            return new VariableReference(str.substr(s, t - s + 1));
        }

        //从s到t是个运算
        //没有加减就用乘除
        if (lastPS == -1)
            lastPS = lastMD;
        if(lastPS<1)
        {
            isvalid=false;
            return NULL;
        }
        else
        {
            cout<<"last ps :"<<lastPS<<"lastMD "<<lastMD<<endl;
            cout<<"*************"<<str.substr(s, lastPS-s)<<'|'<< str[lastPS]<<'|'<<str.substr( lastPS + 1, t-lastPS)<<endl;
            return new Operation(strToTree(str, s, lastPS - 1), str[lastPS], strToTree(str, lastPS + 1, t));
        }
}
    int count() {return itemmap.size();}

};

void test_formula1();

#endif // FORMULA_H
