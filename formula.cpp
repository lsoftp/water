#include "formula.h"

Formula::Formula(string s)
{
    str=s;
    isvalid=true;
    e=strToTree(s, 0, s.length() - 1);
}

Formula::~Formula()
{
    if(e!=NULL) formuleDestroy(e);
}

void test_formula1()
{
    MSD vars;
    //这里设置未知数
    vars["AA_A1"] = 123;
    vars["BBB1"] = 100;
    vars["CCC"]=100;
    vars["C"]=1;
    vars["a"]=2;
    cout<<"vars size"<<vars.size()<<endl;


    {   //输入字符串
        Formula f("AA_A1+C+2/5.1*(BBB1+CCC)");
        //cin >> str;
        //转换为树

        //输出值
        if(f.isvalid)
        {
            if (f.itemmap.find("C")==f.itemmap.end())
                cout<<"not find as"<<endl;
            cout <<"value"<< f.value(vars) << endl;
            //formuleDestroy(exp);
            map<string,double>::iterator ttt;
            for(ttt=f.itemmap.begin();ttt!=f.itemmap.end();ttt++)
                cout<<ttt->first<< "  "<<ttt->second<<endl;
        }
    }exit(0);
}
