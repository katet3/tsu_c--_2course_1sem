#include<iostream>
#include "route.h"
//#define CORRECT 0
//#define ERR_NOT_PTR 403

using error_code_t = int;

//Первый конструктор с кол-вом эл
Route::Route(int _number)
{
    cityes = _number;
    route = new int[_number];

    for(int i = 0; i < _number; i++)
    {
        route[i] = i + 1;///заполняем массив числами от 1 до n
    };
};

//Второй конструктор с сущ
Route::Route(const Route &_argument)
{
    cityes = _argument.cityes;
    route = new int[cityes];

    for(int i = 0; i < cityes; i++)
    {
        route[i] =  _argument.route[i];
    };
};


//Операторы
Route& Route::operator=(const Route& _arg)
{
    if(this == &_arg)
    {
        return *this;
    };

    delete(route);
    cityes = _arg.cityes; //присваеваем длину маршрута
    route = new int [cityes];

    for(int i = 0; i < cityes; i++)
    {
        route[i]=_arg.route[i];
    }
    
    return *this;
};

std::ostream& operator<< (std::ostream &out, const Route & _route)
{
    for(int i = 0; i < _route.cityes; i++)
    {
        out << _route.route[i] << ' ';
    }
 
    return out;
}

//подсчёт матрицы стоимости
int Route::routePrice(int** _matrix)
{
    int sum = 0;
    int next;

    for(int i = 0; i < cityes-1;i++)
    {
        //второй город
        next = route[i+1];               
        //заносим стоимость пути i в второй            
        sum += _matrix[route[i]-1][next-1];          
    };
    
    next = route[0];
    // путь из последнего в первый для цикла
    sum += _matrix[route[cityes-1]-1][next-1];    
    
    return sum;
};

bool Route::nextRoute()
{
    int i;
    int j;
    bool flag = false;
    for(i = cityes-2; i>-1; i--)
    {
        if(route[i]<route[i+1])
        {
            flag = true;
            break;
        }
    }///поиск i

    if(flag){
        for(j = cityes-1; j>i; j--)
        {
            if(route[i]<route[j])
            {
                break;
            }
        }///поиск j

        int c;
        c=route[i];
        route[i]=route[j];
        route[j]=c;


        if(i<cityes-2){
            int left = i+1;
            int right = cityes-1;
            while(left<right){
                c=route[left];
                route[left]=route[right];
                route[right]=c;
                left++;
                right--;
            }
        }///инвертирование хвоста
        if(route[0]!=1){
            flag = false;///так как все пути не равные 1 можем не расматривать, так как пути цикличны
        }
        return flag;
    }
    else{
        return flag;
    }
};












