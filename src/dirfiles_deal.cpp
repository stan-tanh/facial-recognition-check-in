
/*
     Resolves QString and String conversions
QString s2q(const string &s)
{
return QString(QString::fromLocal8Bit(s.c_str()));
}
string q2s(const QString &s)
{
return string((const char *)s.toLocal8Bit());
}
    Resolve input wait for FLAG_STARt_save
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

//Turn the str to qstr
QString str2qstr(string str){
    return QString::fromStdString(str);
}

/*
    Return name, label (according to "usr_manage.txt")
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
        getline(lines, usr, separator);//Get sample name
        getline(lines, pwd);			//The label
        usrs.push_back(str2qstr(usr.c_str()));
        pwds.push_back(str2qstr(pwd.c_str()));
    }
    f.close();
    //return lines;
}


void write_usrs(QString line){
    ofstream fo;                    	//Write to open
    fo.open(usr_manege,ofstream::app);
    string strline = line.toStdString();
    fo<<strline<<endl;
    fo.close();
}

/*
   The "namesfile. TXT" file is stored in format youjiang 0
New samples, added later
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
        getline(lines, old_name, separator);//Get sample name
        getline(lines, classlabel);	//The label
        if(name == old_name)
            return 0;
        if(!classlabel.empty())
            last_label = atoi(classlabel.c_str());
        else if(!old_name.empty())
            break;
    }
    f.close();

    ofstream fo;                    	//Write to open
    fo.open(names_file,ofstream::app);
    last_label ++;
    fo<<name<<separator<<last_label<<endl;
    fo.close();
    return 1;
}

/*
    Return name, label (according to "namesfile.txt")

    Usage:
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
        getline(lines, old_name, separator);//Get sample name
        getline(lines, classlabel);			//The label
        name.push_back(old_name.c_str());
        label.push_back(atoi(classlabel.c_str()));
    }
    //return lines;
}

/*
    Get the folder description file CSV
    Here is mainly file operation, and the process is as follows:
   1, read the list of names in my TXT file, these are the subfolders I need to traverse
   2, traversal files in subfolders
   3，Document traversal
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
        while((ptr = readdir(dir)) != NULL) //Cyclic reading of directory data //
        {
            filename = ptr->d_name; 		//Output file name
            if(filename[0] == '.')			//Filtering hidden files
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


