#include <iostream>

class BoolV
{
private:
    unsigned int *v;
    int nbit, m; // nbit – количество бит вектора, m – количество элементов массива v

public:
    BoolV(int nn = 1);           // формируется булев вектор из nn бит; все биты со значениями 0
    BoolV(const char *, size_t); // формируется булев вектор по строке из нулей и единиц
    BoolV(const BoolV &);
    ~BoolV() { delete[] (v); };

public:
    int Set1(int); // устанавливает указанный бит в 1
    int Set0(int); // устанавливает указанный бит в 0
    int operator[](int);
    BoolV operator=(const BoolV &);
    bool operator==(const BoolV &); // равенство векторов
    BoolV operator|(const BoolV &);
    BoolV operator&(const BoolV &);
    BoolV operator~();
    friend std::ostream &operator<<(std::ostream &, const BoolV &);
    friend std::istream &operator>>(std::istream &, BoolV &);

};

class BoolM
{
private:
    BoolV *bm;
    int m, n; // m – количество строк, n – количество столбцов

public:
    BoolM(int _n = 1, int _m = 1); // формируется нулевая булева матрица размера kl
    BoolM(const BoolM &);
    ~BoolM(){delete [](bm);}

public:
    BoolV& operator[](int);
    BoolM operator=(const BoolM& _other);
    friend std::ostream& operator<<(std::ostream &, BoolM &);
};


BoolV::BoolV(int nn)
{
    m = (nn / 32)+1;
    v = new unsigned int[m];
    nbit = nn;

    for(int i = 0; i < m; i++)
    {
        v[i] &= 0;
    };
};

BoolV::BoolV(const char* _string, size_t _size)
{
    nbit = (_size * 8);
    m = (_size / 4) + 1;
    v = new unsigned int[m];

    size_t n_cel;
    size_t n_bit;
    int i, j;

    for(i = 0, j = m * 32 - 1; i < nbit && _string[i]; i++, j--)
    {
        n_cel = i / 32;
        n_bit = j % 32;
        
        if (_string[i] == '1')
        {
            v[n_cel] = v[n_cel] | (1 << (n_bit));
        };
    };

    nbit = i;

};

BoolV::BoolV(const BoolV& _other)
{
    m = _other.m;
    nbit = _other.nbit;

    v = new unsigned int[m];
    for(int i = 0; i < m; i++)
    {
        v[i] = _other.v[i];
    };
    
}

int BoolV::Set1(int _pos)
{
    if(nbit < _pos)
        return -1;

    v[_pos/32] |= (1<<((m*32-1) - _pos) % 32); 
    
    return 0;
}

int BoolV::Set0(int _pos)
{
    if(nbit < _pos)
        return -1;

    v[_pos/32] &= ~(1<<((m*32-1) - _pos) % 32); 
    
    return 0;
};

int BoolV::operator[](int _pos)
{
    if(nbit < _pos)
        return -1;

    return bool(v[_pos/32] & (1<<((m*32-1) - _pos) % 32));

};

BoolV BoolV::operator=(const BoolV& _other)
{
    if(this == &_other)
        return *this;
    
    m = _other.m;
    nbit = _other.nbit;
    delete [](v);

    v = new unsigned int[m];
    for(int i = 0; i < m; i++)
    {
        v[i] = _other.v[i];
    };

    return *this;
};

bool BoolV::operator==(const BoolV& _other)
{
    if(m == _other.m)
    {
        for(int i = 0; i < m; i++)
        {
            if(v[i] != _other.v[i])
                return false;
        };

        return true;
    };

    return false;
}

BoolV BoolV::operator|(const BoolV& _other)
{
    if(this == &_other)
        return *this;

    for(int i = 0; i < m; i++)
    {
        v[i] |= _other.v[i];  
    }

    return *this;
}

BoolV BoolV::operator&(const BoolV& _other)
{
    if(this == &_other)
        return *this;

    for(int i = 0; i < m; i++)
    {
        v[i] &= _other.v[i];  
    }

    return *this;
}

BoolV BoolV::operator~ ()
{
    for(int i = 0; i < m; i++)
    {
        v[i] = ~v[i];
    }

    return *this;
}

std::istream& operator>>(std::istream& _cin, BoolV& _elem)
{
    int N = 0;
    std::cin >> N;

    if(_elem.v)
        delete [](_elem.v);

    _elem.nbit = N;
    _elem.m = (N / 32) + 1;
    _elem.v = new unsigned int[_elem.m];

    for(int i = 0, j = _elem.m*32 - 1; i < N; i++, j--)
    {
        int n_cel = i / 32;
        int n_bit = j % 32;

        char s;
        _cin >> s;
        if(s == '1')
        {
            _elem.v[n_cel] = _elem.v[n_cel] | (1 << n_bit);
        };
    }

    return _cin;
}

std::ostream& operator<< (std::ostream& _out, const BoolV& _inputVector)
{
    for(int i = 0; i < _inputVector.m; i++)
    {
        _out << ((1<<31 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<30 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<29 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<28 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<27 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<26 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<25 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<24 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<23 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<22 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<21 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<20 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<19 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<18 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<17 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<16 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<15 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<14 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<13 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<12 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<11 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<10 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<9 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<8 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<7 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<6 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<5 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<4 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<3 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<2 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1<<1 & _inputVector.v[i]) ? '1' : '0');
        _out << ((1 & _inputVector.v[i]) ? '1' : '0');

        _out << " ";  
    }

    return _out;
}

BoolM::BoolM(int _n, int _m)
{
    n = _n;
    m = _m;

    bm = new BoolV[_n];
    BoolV x(m);

    for (int i = 0; i < _n; i++)
    {
        bm[i] = x;
    }
}

BoolM BoolM::operator=(const BoolM& _other)
{
    if(this == &_other)
        return *this;

    delete [](bm);
    m = _other.m;
    n = _other.n;

    bm = new BoolV[n];

    for (int i = 0; i < n; i++)
    {
        bm[i] = _other.bm[i];
    }

    return *this;
}


BoolV& BoolM::operator[] (int _other)
{
    if (_other < 0 || _other >= m)
    {
        std::cerr << "\n Выход за границы \n";
        exit(0);
    }
    
    else
    {
        return bm[_other];
    }
}

std::ostream& operator<<(std::ostream& _out, BoolM& _inputMatrix)
{
    for(int i = 0; i < _inputMatrix.n; i++)
    {
        _out << _inputMatrix.bm[i] << std::endl;
    }

    return _out;
}



int main()
{
    using namespace std;

    BoolM test(3,64);

    cout << test << endl;


    return 0;
}