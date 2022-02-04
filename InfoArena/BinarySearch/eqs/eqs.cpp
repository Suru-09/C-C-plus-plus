#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<cmath>

int64_t LOWER_BOUND = -50;
int64_t UPPER_BOUND = 50;

/*
a1*x1^3 + a2*x2^3 + a3*x3^3 + a4*x4^3 + a5*x5^3 = 0
-50 <= a1, a2, a3, a4, a5 <= 50

(x1, x2, x3, x4, x5) - solution

How many solutions are there?

We devide the eqs in left and right like this: 

a1*x1^3 + a2*x2^3 + a3*x3^3  = - a4*x4^3 - a5*x5^3
*/

std::vector<int64_t> all_powers_of_n_in_interval(int64_t n, int64_t lower_bound, int64_t upper_bound) {

    std::vector<int64_t> powers;
    for(int64_t i = lower_bound; i <= upper_bound; ++i) {
        powers.push_back(i * i * i);
    }
    return powers;
}

// All possible values for a1 * x1^3 + a2 * x2^3 + a3 * x3^3
std::vector<int64_t> left_possible_values(const std::vector<int64_t>& powers, 
    int64_t lower_bound, int64_t upper_bound, const int64_t& a1, const int64_t& a2, const int64_t& a3 ) {

    std::vector<int64_t> sol;
    for(int64_t x1 = lower_bound; x1 <= upper_bound; ++x1) {
        if(x1)  {
            for(int64_t x2 = lower_bound; x2 <= upper_bound; ++x2) {
                if(x2) {
                    for(int64_t x3 = lower_bound; x3 <= upper_bound; ++x3) {
                        if(x3) {
                            sol.push_back( (powers[x1 + abs(lower_bound)] * a1 +
                             powers[x2 + abs(lower_bound)] * a2 + powers[x3 + abs(lower_bound)] * a3) );
                        }
                    }
                }
            }
        }
    }
    return sol;
}

int64_t check_how_many_solutions_ok(const std::vector<int64_t>& sol, const std::vector<int64_t>& powers,
     const int64_t& a4, const int64_t& a5, int64_t lower_bound, int64_t upper_bound) {

    int64_t counter = 0;
    for(int64_t x4 = lower_bound; x4 <= upper_bound; ++x4) {
        if(x4) {
            for(int64_t x5 = lower_bound; x5 <= upper_bound; ++x5) {
                if(x5) {
                    int64_t val = -(powers[x4 + 50] * a4 + powers[x5 + 50] * a5);
                    counter += std::upper_bound(sol.begin(), sol.end(), val) - std::lower_bound(sol.begin(), sol.end(), val);
                }
            }
        }
    }
    return counter;
}

int main() {


    std::ifstream in("eqs.in");
    std::ofstream out("eqs.out");

    int64_t a1, a2, a3, a4, a5;
    in >> a1 >> a2 >> a3 >> a4 >> a5;

    std::vector<int64_t> powers = all_powers_of_n_in_interval(3, LOWER_BOUND, UPPER_BOUND);
    std::vector<int64_t> sol = left_possible_values(powers, LOWER_BOUND, UPPER_BOUND, a1, a2, a3 );
    sort(sol.begin(), sol.end());

    // for(const auto& x: powers)
    //     std::cout << x << " ";
    // std::cout << "\n";

    // for(const auto& x: sol)
    //     std::cout << x << " ";
    // std::cout << "\n";

    // std::cout << "There are this many combinations possible: " 
    //     << check_how_many_solutions_ok(sol, powers, a4, a5, LOWER_BOUND, UPPER_BOUND) << "\n";
    out << check_how_many_solutions_ok(sol, powers, a4, a5, LOWER_BOUND, UPPER_BOUND) << "\n";

    in.close();
    out.close();

    return 0;
}