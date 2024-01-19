#include<iostream>

using namespace std;

class String
{ 
    private:
        char* str = NULL;
        int len = 0;

    public:
        String(int _len = 0);
        String(const char* _arrayChar);
        String(String& _str);
        ~String() {if(str) delete []str; str = NULL;};

    public:
        int Len();
        String& operator=(const String& _str);
        char& operator[](int _number);
        bool operator==(String& _str);
        bool operator!=(String& _str);
        String operator+(const String& _str);
        String& operator+=(const String& _str);
        friend istream& operator>>(istream& _in, String& _str);
        friend ostream& operator<<(ostream& _out, String& _str);
        int BMH_search(String& _str);
};

//Первый конструктор
String::String(int _len)
{
    len = _len;
    str = new char[len];
};

//Второй конструктор
String::String(const char* _arrayChar)
{
    len = 0;

    for(int i = 0; _arrayChar[i]; i++)
    {
        len++;
    };

    str = new char[len];

    for(int i = 0; i < len; i++)
    {
        str[i] = _arrayChar[i];
    };
};

String::String(String& _str)
{
    len = _str.len;
    str = new char[len];

    for(int i = 0; i < len; i++)
    {
        str[i] = _str.str[i];
    };
};

int String::Len()
{
    return len;
};

String& String::operator=(const String& _str)
{
    if(&(_str) == this)
    {
        return *this;
    };

    delete []str;
    len = _str.len;
    str = new char[len];

    for(int i = 0; i < len; i++)
    {
        str[i] = _str.str[i];
    };

    return *this;
};

char& String::operator[](int _number)
{
    //Индекс
    return str[_number];
};

bool String::operator==(String& _str)
{
    if(len != _str.len)
    {
        return false;
    };

    for(int i = 0; i < len; i++)
    {
        if(str[i] != _str[i])
        {
            return false;
        };
    };
    return true;
};

bool String::operator!=(String& _str)
{
    if(len != _str.len)
    {
        return true;
    };

    for(int i = 0; i < len; i++)
    {
        if(str[i] != _str[i])
        {
            return true;
        };
    };
    return false;
};

String String::operator+(const String& _str)
{
    String result(len + _str.len); // 
    
    for(int i = 0; i < len; i++)
    {
        result.str[i] = str[i];
    };

    for(int i = 0; i + len < result.len; i++)
    {
        result.str[i + len] = _str.str[i];
    };

    return result;
};

String& String::operator+=(const String& _str)
{
    int lenOld = len;
    len += _str.len;
    char* newStr = new char[len];

    for(int i = 0; i < lenOld; i++)
    {
        newStr[i] = str[i];
    };

    for(int i = 0; i + lenOld < len; i++)
    {
        newStr[i + lenOld] = _str.str[i];
    };

    delete []str;
    this->str = newStr;

    return *this;
};

istream& operator>>(istream& _in, String& _str)
{
    //Любая длина
    for(int i = 0; i < _str.len; i++)
    {
        _in >> _str.str[i];
    };
    return _in;
};  

ostream& operator<<(ostream& _out, String& _str)
{
    for(int i = 0; i < _str.len; i++)
    {
        _out << _str.str[i];
    };
    return _out;
};
    

int String::BMH_search(String& _str)
{
    int i = 0;
    int tab[256] = {_str.len};
    int lenText = len;
    int lenStr = _str.len;

    //acaabb
    //ab
    //Нет \0
    while(i < lenStr)
    {
        tab[_str.str[i]] = lenStr - (i - 1);
        i++;
    };

    //-1 так как мы работаем с массивом и индексация идет с 0
    i = lenStr - 1;
    int j = lenStr - 1;
    
    while((i < lenText - 1))
    {
        int k = i;
        j = lenStr - 1;

        while(j >= 0)
        {
            if(str[k] == _str.str[j])
            {
                j--;
                k--;
            }
            else 
                break; 
        };
        if(j==-1)
            break;

        //i = i + tab[_str.str[j]] - 1;
        i = i + tab[str[i]] - 1;
        j = lenStr - 1;
    };

//aabbc
//abb

    if(j >= 0)
    {
        return -1;
    }
    else 
        return i-_str.len + 1 + 1; //так как без +1 возращается просто индекс в массиве str
};



int main()
{
    int size = 31; //кол-во символов без \0
    char tmpArray[] = "Hello, world! I am a program!!!";
    
    //Конструкторы
//---------------------------------//
//1
    String firstStr(size);
    cout << firstStr.Len() << endl;

//2
    cout << "tmpArray: " << tmpArray <<endl;
    String secondStr(tmpArray);
    cout << "secondArray Constr - str: ";
    for(char i = 0; i < secondStr.Len(); i++)
    {   
        cout << secondStr[i]; 
    };
    cout << "\nsecondArray Constr - len: " << secondStr.Len() << endl << "\n";

//3
    String resultStr(secondStr);
    cout << "resultStr Constr - str: ";
    for(char i = 0; i < resultStr.Len(); i++)
    {   
        cout << resultStr[i]; 
    };
    cout << "\nresultStr Constr - len: " << secondStr.Len() << endl << "\n";

//---------------------------------//
//operator=
    firstStr = resultStr;
    cout << "firstStr Constr - str: ";
    for(char i = 0; i < firstStr.Len(); i++)
    {   
        cout << firstStr[i]; 
    };
    cout << "\nfirstStr Constr - len: " << secondStr.Len() << endl  << "\n";

//operator[]
cout << "firstStr[0] - " << firstStr[0] << endl << "\n";

secondStr = firstStr + resultStr;
cout << "secondArray = first + result - str: ";
    for(char i = 0; i < secondStr.Len(); i++)
    {   
        cout << secondStr[i]; 
    };
    cout << "\nsecondArray Constr - len: " << secondStr.Len() << endl << "\n";

    firstStr += resultStr;
    cout << "firstStr += resultStr - str: ";
    for(int i = 0; i < firstStr.Len(); i++)
    {   
        cout << firstStr[i]; 
    };
    cout << "\nfirstStr += resultStr - len: " << firstStr.Len() << endl << "\n";


    String a(3);
    cout << a << "\n";
    cin >> a;
    cout << a << "\n";

    firstStr = "aabbc";
    resultStr = "abb";

    int pos = firstStr.BMH_search(resultStr);
    cout << "BM: " << pos << endl;
    return 0;
};









