#include <iostream>
#include <time.h>
#include <algorithm>
#include <thread>
#include <chrono>
#include <utility>
#include<stdlib.h>

class Array
{ 
    private:
        int* array;
        int size;

    public:
    // конструктор 1
    // len – число элементов в массиве
    // t = 1 – неупорядоченный массив
    // t = 2 – массив, упорядоченный по возрастанию
    // t = 3 – массив, упорядоченный по убыванию
    // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
        Array(int _len = 1, int _t = 1, int _d = 10);
        Array(int* _array, size_t _size); // конструктор 2: по массиву
        Array(Array& );
        ~Array(){delete(array);};

    public:
        Array& operator=(Array& );
        int& operator[](size_t );
        bool Test(); //проверка на упорядоченность по неубыванию
        bool operator==(Array); // равенство элементов массивов (но не порядка)
        void Shell_sort();
        void Heapsort();

        void sift(int _index);
        void toHeap();
        inline void swap(int i, int j);

        void Hoar_sort();
        //void Hoar_sort(int low, int high);
        void Hoar_sort(int _first, int _last);

        void sort()
        {
            std::sort(array, array+size);
        };


        friend std::istream& operator>>(std::istream& _cin, Array& _inputArray);
        friend std::ostream& operator<<(std::ostream& _out, Array& _inputArray);

        int getSize(){return size;};
};

auto get_time()
{
  return std::chrono::high_resolution_clock::now();
}

void print_difference(std::chrono::high_resolution_clock::time_point t1,
                      std::chrono::high_resolution_clock::time_point t2)
{
  unsigned nano  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  unsigned micro = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  unsigned sec = std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();

  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << sec   << " seconds" << std::endl;
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << micro << " microseconds" << std::endl;
  std::cout << nano  << " nanoseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
}



int minInt(
    int* _array,
    size_t _size,
    int _d
    )
{
    int newElement = rand() % _d;
    int tmp = newElement;

    _array[0] = rand();
    for (int ix = 1; ix < _size; ix++)
    {
        _array[ix] = _array[ix-1] - (rand() % _d);
        
    };
    
    
    return 0;
};

int hightInt(
    int* _array,
    size_t _size,
    int _d
    )
{
    _array[0] = rand() % _d;
    for (int ix = 1; ix < _size; ix++)
    {
        _array[ix] = (rand() % _d) + _array[ix-1];
        
    };
    
    return 0;
};


int randomInt(
    int* _array,
    size_t _size,
    int _d
    )
{
    for (int ix = 0; ix < _size; ix++)
    {
        _array[ix] = (rand() % _d);
    }
    
    return 0;
};

//i+tmp
Array::Array(int _len, int _t, int _d)
{
    array = new int[_len];
    size = _len;

    switch (_t)
    {
        case 1:
            randomInt(array, size, _d);
            break;

        case 2:
            hightInt(array, size, _d);           
            break;

        case 3:
            minInt(array, size, _d);
            break;

        default:
            break;
            
    };
    
};

Array::Array(int* _array, size_t _size)
{
    size = _size;
    array = new int[size];

    for(int i = 0; i < size; i++)
    {
        array[i] = _array[i];
    };
};

Array::Array(Array& _other)
{
    size = _other.size;
    array = new int[size];

    for(int i = 0; i < size; i++)
    {
        array[i] = _other.array[i];
    };
};


int& Array::operator[](size_t _index)
{
    if(_index < size)
        return array[_index];

    return array[0];
};

Array& Array::operator=(Array& _other)
{   
    if(this == &_other)
    {
        return *this;
    };

    delete(array);
    size = _other.size;
    array = new int[size];

    for(int i = 0; i < size; i++)
    {
        array[i] = _other.array[i];
    };
    return *this;
};

bool Array::Test()
{
    if(size <= 1)
    {
        return true;
    };

    for(int i = 1;i < size; i++)
    {
        if (array[i] < array[i-1])
        {
            return false;
        };
    };

    return true;
};


//Сортировка
bool Array::operator==(Array _other)
{
    if(this == &_other)
        return true;

    if(size == _other.size)
    {
        sort();
        _other.sort();

        for(int i = 0; i < size; i++)
        {
            if (array[i] != _other.array[i])
            {
                std::cout << i << std::endl;
                return false;
            };
        };

        return true;
    }

    else
        return false;
};
//Память
std::istream& operator>>(std::istream& _in, Array& _inputArray)
{
    int N = 0;
    std::cin >> N;

    delete [](_inputArray.array);
    _inputArray.size = N;
    _inputArray.array = new int [N];

    for(int i = 0; i < N; i++)
    {
        _in >> _inputArray.array[i];
    };

    return _in;
};

std::ostream& operator<<(std::ostream& _out, Array& _inputArray)
{
    for(int i = 0; i < _inputArray.size; i++)
    {
        _out << _inputArray.array[i] << " ";
    };

    return _out;
};

void Array::Shell_sort()
{
    for(int s = size/2; s > 0; s /= 2)
    {
        for(int i = s; i < size; i++)
        {
            int j = i;
            int el = array[i];

            while(j >= s && el < array[j-s])
            {
                array[j] = array[j-s];
                j -= s;
            };

            array[j] = el;
        };    
    };
};

void Array::toHeap(){

	for (int i = size/2; i >= 0; i--) 
    {
		sift(i);
	};
};

void Array::sift(int _root) 
{
	int currHead = _root;
	int tmp = array[_root];
	int child = 2 * currHead + 1;

	while (child < size) 
    {
		if ((child + 1 < size) && (array[child] < array[child + 1])) 
        {
			child++;
		};

		if (array[child] < tmp) 
        {
			break;
		};

		array[currHead] = array[child];
		currHead = child;
		child = 2 * currHead + 1;
	};

	array[currHead] = tmp;
};

inline void Array::swap(int i, int j) 
{
	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
};

void Array::Heapsort() {
	toHeap();
	
    int tmp = size;
	int j = size - 1;

	for(; j > 0; j--) 
    {
		swap(j, 0);
		size--;
		sift(0);
	};

	size = tmp;
};

void Array::Hoar_sort() 
{
	int low = 0;
	int high = size - 1;
	Hoar_sort(low, high);
};

void Array::Hoar_sort(int _first, int _last)
{
    int i = _first, j = _last, x = array[(_first + _last) / 2];
  
    do 
    {
        while (array[i] < x) i++;
        while (array[j] > x) j--;
  
        if(i <= j) 
        {
            swap(i, j);
            i++;
            j--;
        }
    } while (i <= j);
  
    if (i < _last)
        Hoar_sort(i, _last);

    if (_first < j)
        Hoar_sort(_first, j);
};

int main()
{
    using namespace std;

    srand((unsigned int) time(NULL));

    int size = 10;
    Array test(size, 1, 5);
    Array test2(size, 1, 5);

    cout << test << endl; 
    cout << test2 << endl; 

    bool a = test == test2;
    cout << a << endl;

    cout << test << endl; 
    cout << test2 << endl; 

    for(int i = 0; i < size; i++)
    {
        int result = test[i];
        std::cout << result;
    };
    std::cout << std::endl;

    Array copy(test);
    int* testCopyArray = new int[size];
    for(int i = 0; i < size; i++)
    {
        int result = copy[i];
        testCopyArray[i] = copy[i];
        std::cout << result;
    };
    std::cout << std::endl;

    Array fromArray(testCopyArray, size);
    for(int i = 0; i < size; i++)
    {
        int result = fromArray[i];
        std::cout << result;
    };
    std::cout << std::endl;
    std::cout << std::endl;


    Array time(1000000, 3, 100000);
    {
        fromArray = time;
        cout << "SHELL:" << endl;

        auto t1 = get_time();
        fromArray.Shell_sort();
        auto t2 = get_time();

        bool flag = fromArray.Test();
        if(!flag)
        {
            cout << "NO" << endl;
            return -1;
        }

        print_difference(t1, t2);
    
        bool bools = (fromArray == time);
    cout <<"\n" << bools << endl;
    }

    //cin >> fromArray;
    {
        fromArray = time;
        cout << "Heap:" << endl;
        auto t1 = get_time();
        fromArray.Heapsort();
        auto t2 = get_time();

        bool flag = fromArray.Test();
        if(!flag)
        {
            cout << "NO" << endl;
            return -1;
        }
        print_difference(t1, t2);
    
        bool bools = (fromArray == time);
    cout <<"\n" << bools << endl;
    }
    //cout << fromArray << endl;


    //cin >> fromArray;

    {
        fromArray = time;
        cout << "Hoar:" << endl;
        auto t1 = get_time();
        fromArray.Hoar_sort();
        auto t2 = get_time();

        bool flag = fromArray.Test();
        if(!flag)
        {
            cout << "NO" << endl;
            return -1;
        }
        print_difference(t1, t2);

        bool bools = (fromArray == time);
    cout <<"\n" << bools << endl;
    }

    //cout << fromArray << endl;
    cin >> fromArray;
    fromArray.sort();
    cout << fromArray << endl;


};