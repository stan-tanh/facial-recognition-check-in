
/*
    解决QString 和String 的转换
QString s2q(const string &s)
{
return QString(QString::fromLocal8Bit(s.c_str()));
}
string q2s(const QString &s)
{
return string((const char *)s.toLocal8Bit());
}
    解决输入等待 flag_start_save
*/

#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <vector>

#include <dirent.h>

#include <QString>
#include <QList>
using namespace std;

extern void get_usrs(QList<QString> &usrs,QList<QString> &pwds);
extern void read_names(vector<string> &name,vector<int> &label);
extern bool save_samplename(char *name);
extern void get_namescsv();

extern string facesdir;
string mum_path = facesdir;
extern string names_file;
extern string listpath;
extern string usr_manege;

//str转qstr
QString str2qstr(string str){
    return QString::fromStdString(str);
}

/*
    返回名字、标签（根据"usr_manage.txt"）
*/
void get_usrs(QList<QString> &usrs,QList<QString> &pwds)
{
    fstream f;
    f.open(usr_manege,ifstream::in);
    char separator = ' ';
    string line, usr, pwd;
    //vector<string> lines;
    while (!f.eof())
    {
        getline(f, line);
        //cout << line <<endl;
        if(line.empty())
            break;
        //lines.push_back(line.c_str());
        stringstream lines(line);
        getline(lines, usr, separator);//获取样本名字
        getline(lines, pwd);			//获取标签
        usrs.push_back(str2qstr(usr.c_str()));
        pwds.push_back(str2qstr(pwd.c_str()));
    }
    f.close();
    //return lines;
}


void write_usrs(QString line){
    ofstream fo;                    	//写打开
    fo.open(usr_manege,ofstream::app);
    string strline = line.toStdString();
    fo<<strline<<endl;
    fo.close();
}

/*
    "names_file.txt"　文件中存储格式　　youjiang 0
    新样本，增加在后面
*/
bool save_samplename(string name){

    char separator = ' ';
    string line, old_name, classlabel;
    fstream f;
    f.open(names_file,ifstream::in);
    if(!f){
        ofstream fc(names_file,ofstream::out);
        fc.close();
        f.open(names_file,ifstream::in);
    }
    int last_label = -1;
    while (!f.eof())
    {
        getline(f, line);
        //cout << line << endl;
        stringstream lines(line);
        getline(lines, old_name, separator);//获取样本名字
        getline(lines, classlabel);	//获取标签
        if(name == old_name)
            return 0;
        if(!classlabel.empty())
            last_label = atoi(classlabel.c_str());
        else if(!old_name.empty())
            break;
    }
    f.close();

    ofstream fo;                    	//写打开
    fo.open(names_file,ofstream::app);
    last_label ++;
    fo<<name<<separator<<last_label<<endl;
    fo.close();
    return 1;
}

/*
    返回名字、标签（根据"names_file.txt"）

    使用方法：
        vector<string> m;
        read_names(m);
*/
void read_names(vector<string> &name,vector<int> &label)
{
    fstream f;
    f.open(names_file,ifstream::in);
    char separator = ' ';
    string line, old_name, classlabel;
    //vector<string> lines;
    while (!f.eof())
    {
        getline(f, line);
        //cout << line <<endl;
        if(line.empty())
            break;
        //lines.push_back(line.c_str());
        stringstream lines(line);
        getline(lines, old_name, separator);//获取样本名字
        getline(lines, classlabel);			//获取标签
        name.push_back(old_name.c_str());
        label.push_back(atoi(classlabel.c_str()));
    }
    //return lines;
}

/*
    得到文件夹的描述文件　csv
    这里主要是文件操作，流程为：
    １、读取我的ｔｘｔ文件里的名字列表，这些就是我需要遍历的子文件夹
    ２、子文件夹里遍历文件
    ３、记录遍历的文件
*/
void get_namescsv()
{
    DIR *dir;
    struct dirent * ptr;
    string rootdirPath = mum_path;
    string filename;
    //string first_file;
    //int num = 0;
    vector<string> m;
    vector<int> l;
    read_names(m,l);

    ofstream csv;
    csv.open(listpath,ofstream::out);
    for(int i = 0;i < m.size();i++){
        m[i] =  mum_path+"/"+ m[i];
        cout << m[i].c_str() << "  "<<l[i]<<endl;
        dir = opendir(m[i].c_str());
        while((ptr = readdir(dir)) != NULL) //循环读取目录数据 //（为什么这个遍历机制不会在扫描完成之前重复扫描）!!!很好用
        {
            filename = ptr->d_name; 		//输出文件名
            if(filename[0] == '.')			//过滤隐藏文件
                continue;
/*
            if(!num)
                first_file = filename;
            else if(filename == first_file){
                first_file = "  ";
                num = 0;
                //break;
                cout<<" sdsssssssss"	<<endl;
            }
            num ++;
*/
            //cout << filename <<endl;

            csv << m[i]+"/"+filename +" "<<l[i]<<endl;
        }
    }
    csv.close();
}


