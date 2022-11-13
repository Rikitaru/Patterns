#include <iostream>

/* элементы числовой последовательности
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, … ,
в которой первые два числа равны 0 и 1, а каждое последующее число равно сумме двух предыдущих чисел */
int Fibonachi(int n) {
    std::cout<<n<<std::endl;
    const int MAXN = 1000;
    static int c[MAXN]; //инициализируется нулями благодаря static
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (c[n]>0) return c[n];
    return c[n] = Fibonachi(n-1) + Fibonachi(n-2);
}

/*Рекурсивная функция быстрого возведения в степень*/
template <typename T>
T mypow(T x, int n) {
    if (n == 0) return (T) 1;
    if (n%2 != 0) return mypow(x, n-1) * x;
    T y = mypow(x, n/2);
    return y*y;
}

/*Задача об интервалах, об комнатах*/
int main() {
    std::cout << Fibonachi(5) << std::endl<<std::endl;
    std::cout << mypow(1, 3) << std::endl;
    return 0;
}