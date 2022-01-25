#include<iostream>
#include<fstream>
#include<cmath>

#define UPPER_BOUND 10000000


int calc_digits_of_factorial(const int& n) {
    if(n < 0)
        return 0;
    
    if(n <= 1)
        return 1;
    
    double digits = 0;
    // this is like calculaton log10(n!)  
    // !!! keep in mind that log10(a) + log10(b) = log10(ab)
    for(int i = 2; i <= n ; ++i)
        digits += log10(i);
    
    return floor(digits) + 1;
}

int calc_zeros(int n)
{
    int sum = 0;
    while(n >= 5) {
        sum += n / 5;
        n /= 5;
    }

    return sum;
}

int _binary_search_n(const int& p, int left, int right) {

    int best = -1;
    if(!p) {
        return 1;
    } else {
        while(left <= right) {

            int mid = left + (right - left ) / 2;
            int digits = calc_zeros(mid);

            if( digits >= p) {
                best = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }

        }
    }

    if(calc_zeros(best) == p) {
        return best;
    }
    return -1;
}

int main() {

    int p;

    std::ifstream in("fact.in");
    std::ofstream out("fact.out");

    in >> p;

    int result = _binary_search_n(p, 1, UPPER_BOUND);
    // std::cout << result << "\n";
    out << result << "\n";

    in.close();
    out.close();

    return 0;
}