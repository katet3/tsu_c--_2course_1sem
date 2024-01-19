#include<iostream>

#define MAX_SIZE_LOGIN 32
#define MAX_SIZE_PASS 32

#define error_code_t int32_t
#define str std::string

class User
{
    private:
        str login;
        str password;
        char key;

    public:
        User(str _login, str _password);
    
    public:
        bool setLogin(str _login);
        bool setPassword(str _password);
        bool getPassword();
        bool getLogin();

    private:
        str encryptPassword(str _text);
};

User::User(str _login, str _password)
{
    if((_login.length() <= MAX_SIZE_LOGIN) && (_login.length() <= MAX_SIZE_PASS))
    {
        setLogin(_login);
        setPassword(_password);
    }
    else{
        this->login = "";
        this->password = "";
    };
    
};

bool User::setLogin(str _login)
{
    login = _login;
    return true;
}

bool User::setPassword(str _password)
{
    //this->password = _password;
    password = encryptPassword(_password);
    return true;
};

str User::encryptPassword(str _text)
{


    char key = '~';
    this->key = key;


    for(int i = 0; i < _text.length(); i++)
    {
        _text[i] ^= key;
    };

    this->key = key;

    return _text;
}

bool User::getPassword()
{
    std::cout << password << std::endl;
    return true;
};

bool User::getLogin()
{
    std::cout << login << std::endl;
    return true;
};


int main()
{
    using namespace std;

    User test("123", "55555");
    test.getLogin();
    test.getPassword();    

/*
    str test = "112";
    char t = '~';

    test[0] ^= t;

    cout << test << endl; 
*/
    return 0;
}
