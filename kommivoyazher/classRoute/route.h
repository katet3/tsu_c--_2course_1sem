#pragma once
class Route
{
    int* route;
    int cityes;

    public:
        Route(int _number);
        Route(const Route &_argument);
        ~Route(){if(route) delete(route); route == NULL;};

        Route& operator=(const Route&); // операция присваивания
        //friend std::ostream& operator<<(std::ostream&, const Route&); // вывод маршрута
        void print(const int route, const int cityes);
        friend std::ostream& operator<< (std::ostream &out, const Route & _route);

        int routePrice(int** ); // вычисляет стоимость маршрута по матрице стоимости
        bool nextRoute(); // вычисляет следующий маршрут, используя алгоритм Дейкстры
};