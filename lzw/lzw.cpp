#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
#define MAXSIZE 255
struct dictionary
{
    /* data */
    vector<string> str; //编码表
    int size;           //当前编码表大小
};
/*插入编码*/
void insert(dictionary *dict, string seq)
{
    dict->str.push_back(seq);
    dict->size++;
};
/*初始化编码表*/
void init(dictionary *dict)
{
    dict->size = 0;
    /*初始化编码表*/
    char seq = 0;
    insert(dict, " ");
    insert(dict, "\n");
    for (int i = 33; i < 127; i++)
        insert(dict, string(1, seq + i));
};
/*显示编码表*/
void displayDict(dictionary *dict)
{
    cout << "-------编码表-------\n";
    cout << "编号\t |     字符串\n";
    cout << "————————————————————\n";
    for (int i = 0; i < dict->size; i++)
        cout << i << "\t |\t" << dict->str[i] << "\n";
};
/*查询是否存在编码*/
int inquire(dictionary *dict, string seq)
{
    for (int i = 0; i < dict->size; i++)
        if (dict->str[i] == seq)
            return i;
    return -1;
};
/*编码*/
vector<int> encode(dictionary *dict, string code)
{
    vector<int> res;
    for (int i = 0; i < code.size(); i++)
    {
        string seq = "";
        for (int j = i; j < code.size(); j++)
        {

            if (code[j] == ' ')
            {
                if (seq != "")
                    res.push_back(inquire(dict, seq));
                res.push_back(0);
                i = j;
                break;
            }
            string s(1, code[j]);
            if (inquire(dict, s) == -1)
            {
                if (seq != "")
                    res.push_back(inquire(dict, seq));
                res.push_back(1);
                i = j + 1;
                break;
            }
            seq = seq + code[j];
            if (inquire(dict, seq) == -1)
            {
                insert(dict, seq);
                if (seq.size() == 1)
                    res.push_back(inquire(dict, seq));
                else
                    res.push_back(inquire(dict, seq.substr(0, seq.size() - 1)));
                i = j - 1;
                break;
            }
            if (code.size() == j + 1)
            {
                res.push_back(inquire(dict, seq));
                i = j + 1;
            }
        }
    }
    return res;
};
/*解码*/
string decode(dictionary *dict, vector<int> code, int codeLength)
{
    string seq = "";
    string prev, current;
    for (int i = 0; i < codeLength; i++)
    {
        if (code[i] == 0)
        {
            seq.append(" ");
            current = "";
            continue;
        }
        if (code[i] == 1)
        {
            seq.append("\n");
            current = "";
            continue;
        }
        prev = current;
        current = dict->str[code[i]];
        seq.append(current);
        if (inquire(dict, prev + current[0]) == -1)
            insert(dict, prev + current[0]);
    }
    return seq;
};

/*菜单功能选择*/
char menuSelect()
{
    char value;
    do
    {
        cout << "Don't Use Chinese Please!!!";
        cout << "选择使用的功能\n1-压缩\n2-解压\n0-退出\n";
        cin >> value;
        if (value == '0')
            exit(1);
    } while (value != '1' && value != '2');
    return value;
}
/*文件地址获取*/
string getFilePath()
{
    string path;
    cout << "请输入要读写的文件绝对地址 : ";
    cin >> path;
    return path;
}
/*读取原文*/
string readOriginal()
{
    ifstream infile;
    infile.open(getFilePath(), ios::in | ios::binary);
    if (infile.is_open() == false)
    {
        cout << "Open file fail!" << endl;
        exit(1);
    }
    istreambuf_iterator<char> beg(infile), end;
    string data(beg, end);
    return data;
}
/*写入译文*/
void saveTranslation(vector<int> res)
{
    ofstream outfile;
    outfile.open(getFilePath(), ios::out | ios::binary);
    if (outfile.is_open() == false)
    {
        cout << "Open file fail!" << endl;
        exit(1);
    }
    int length = res.size();
    outfile.write((char *)&length, sizeof(int));
    outfile.write((char *)&res[0], res.size() * sizeof(int));
    outfile.close();
}
/*读取译文*/
vector<int> readTranslation()
{
    ifstream infile;
    infile.open(getFilePath(), ios::in | ios::binary);
    if (infile.is_open() == false)
    {
        cout << "Open file fail!" << endl;
        exit(1);
    }
    int length;
    infile.read((char *)&length, sizeof(int));
    vector<int> res(length);
    infile.read((char *)&res[0], res.size() * sizeof(int));
    infile.close();
    return res;
}
/*保存原文*/
void saveOriginal(string data)
{
    ofstream outfile;
    outfile.open(getFilePath(), ios::out);
    if (outfile.is_open() == false)
    {
        cout << "Open file fail!" << endl;
        exit(1);
    }
    outfile << data;
    outfile.close();
}
int main()
{
    int value;
    char choice;
    dictionary dict;
    init(&dict); //初始化字典
    while (true)
    {
        /* code */
        switch (menuSelect())
        {
        case '1':
        {
            vector<int> res;
            string data = readOriginal();
            cout << "原文:" << data << endl;
            res = encode(&dict, data);
            cout << "编码后:";
            for (auto x : res)
                cout << x << " ";
            cout << "\n是否保存为二进制文件(Y/N)" << endl;
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
                saveTranslation(res);
            break;
        }
        case '2':
        {
            vector<int> res = readTranslation();
            for (auto x : res)
                cout << x << " ";
            string data = decode(&dict, res, res.size());
            cout << "\n"
                 << data << endl;
            cout << "是否保存解码结果？(Y/N)" << endl;
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
                saveOriginal(data);
            break;
        }
        default:
            break;
        }
        cout << "是否查看编码表(Y/N)" << endl;
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
            displayDict(&dict);
    }
    return 0;
}
