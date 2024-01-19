#include<iostream>
#include"./classRoute/route.h"
#include"./classRoute/route.cpp"


Route task(int num)
{///решение задачи коммивояжера
    int**matrix = new int* [num];///выделяем память

    for (int i = 0; i < num; i++) 
        matrix[i] = new int [num];

    for(int i = 0; i < num; i++){///заполняем матрицу
        for(int j = 0; j < num; j++){
            std::cout << "(" << i << ", " << j << ")" << std::endl; 
            std::cin >> matrix[i][j];
        };
    };

    Route r(num);///начальный путь по возрастанию
    Route final_r = r;///создание конечного значения

    int sum = r.routePrice(matrix);///стоймость начального пути
    std::cout << r << " : " << sum << std::endl;///вывод начального пути и его стоимость

    while(r.nextRoute()){
        int newSum = r.routePrice(matrix);///стоимость следующего пути

        std::cout<< r << " : " << newSum << std::endl;///вывод следующего пути и его стоимость

        if(sum > newSum && newSum > 0){///если путь дешевле выбираем его
            sum = newSum;
            final_r = r;
        };
    };

    return final_r;///возвращаем лучший путь
};


int main()
{
    int n = 4;

    std::cout << task(n) << std::endl;

    return 0;
}