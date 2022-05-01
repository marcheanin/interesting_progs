#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int gcd(int a, int b){
    if (b != 0) return gcd(b, a % b);
    return a;
}

struct Fraction{
    int a, b;
    Fraction(int _a, int _b){
        a = _a;
        b = _b;
        simplify();
    }
    Fraction(){
        a = 1;
        b = 1;
    }
    Fraction (const Fraction &x){
        this->a = x.a;
        this->b = x.b;
        simplify();
    }
    Fraction(int _a){
        a = _a;
        b = 1;
        simplify();
    }
    double to_double(){
        return this->a / this->b;
    }
    void simplify(){
        int t = gcd(abs(a), abs(b));
        this->a = a / t;
        this->b = b / t;
    }
};

Fraction sum(Fraction a, Fraction b) {
    int a1 = a.a, a2 = a.b;
    int b1 = b.a, b2 = b.b;
    int y = abs((a2 * b2)) / gcd(abs(a2), abs(b2));
    a1 *= y / a2;
    b1 *= y / b2;
    int x = a1 + b1;
    return Fraction(x, y);
}

Fraction difference(Fraction a, Fraction b) {
    int a1 = a.a, a2 = a.b;
    int b1 = b.a, b2 = b.b;
    int y = abs((a2 * b2)) / gcd(abs(a2), abs(b2));
    a1 *= y / a2;
    b1 *= y / b2;
    int x = a1 - b1;
    return Fraction(x, y);
}

Fraction mult(Fraction a, Fraction b){
    a.a *= b.a;
    a.b *= b.b;
    a.simplify();
    return a;
}

Fraction division(Fraction a, Fraction b){
    if (b.a > 0)
        return mult(a, Fraction(b.b, b.a));
    return mult(a, Fraction(-b.b, -b.a));
}

Fraction abs(Fraction a){
    return Fraction(abs(a.a), a.b);
}


Fraction * gauss(Fraction **a, Fraction *b, int n)
{
    Fraction *x = new Fraction [n];
    int k = 0, index;
    while (k < n)
    {
        Fraction mux = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (difference((abs(a[i][k])), mux).a == 0)
            {
                mux = abs(a[i][k]);
                index = i;
            }
        }
        if (mux.a == 0)
        {
            return x;
        }
        for (int i = 0; i < n; i++)
        {
            swap(a[k][i], a[index][i]);
        }
        swap(b[k], b[index]);
        for (int i = k; i < n; i++)
        {
            Fraction t = a[i][k];
            if (t.a == 0) {continue;} // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = division(a[i][j], t);
            b[i] = division(b[i], t); //b[i] /= t;
            if (i == k)  continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = difference(a[i][j], a[k][j]); //a[i][j] -= a[k][j];
            b[i] = difference(b[i], b[k]);  //b[i] -= b[k];
        }
        k++;
    }
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = b[k];
        for (int i = 0; i < k; i++)
        {
            b[i] = difference(b[i], mult(a[i][k], x[k])); //b[i] -= a[i][k] * x[k];
        }
    }
    return x;
}


int main()
{
    Fraction **a, *b;
    int n;
    cin >> n;
    b = new Fraction [n];
    a = new Fraction *[n];
    int x;
    for(int i = 0; i < n; i++)
    {
        a[i] = new Fraction [n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> x;
            a[i][j] = Fraction(x);
        }
        cin >> x;
        b[i] = Fraction(x);
    }
    Fraction *ans = gauss(a, b, n);
    for (int i = 0; i < n; i++)
    {
        cout << ans[i].a << " / " << ans[i].b << endl;
    }
}
