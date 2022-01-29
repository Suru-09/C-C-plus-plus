#include<iostream>
#include<fstream>
#include<cstring>

#define ll long long

ll over;
ll on_table;

ll min_level_max_sum_capacities(ll n, ll a[55][55]) {
    ll maxi = -1, maxi_index = -1, sum = 0;
    for(ll i = 0; i < n ; ++i) {
        for(ll j = 0; j <= i; ++j) {
            // std::cout << "a[" << i << "][" << j << "]= " << a[i][j] << "\n";
            sum += a[i][j];
        }
        if(sum > maxi) {
            maxi = sum;
            maxi_index = i;
        }
        sum = 0;
    }

    return maxi_index + 1;
}

bool second_and_lost_water(ll n, ll a[55][55], ll drops) {
    ll used[55][55];
    for(ll i = 0 ; i < n; ++i)
        memset(&used[i], 0, (i + 3) * sizeof(ll));
    
    used[0][0] = drops;
    on_table = 0;
    over = 0;
    
    // std::cout << "\nEu sunt drops: " << drops << "\n";

    for(ll i = 0 ; i < n; ++i) {
        for(ll j = 0; j <= i; ++j ) {
            // std::cout << used[i][j] << " " << a[i][j] << "\n";
            if(used[i][j] >= a[i][j]) {
                over = used[i][j] - a[i][j];
                // std::cout << "Eu sunt over: " << over << "\n";
                // std::cout << "a[" << i << "][" << j << "]= " << a[i][j] << "\n";
                used[i][j] = a[i][j];
                if(i == (n - 1)) {
                    // std::cout << "Sunt pe ultimul nivel!\n";
                    on_table += over;
                    continue;
                }
                // std::cout << used[i + 1][j] << "  " << used[i + 1][j + 1] << "\n";
                used[i + 1][j] += (over + 1) / 2;
                used[i + 1][j + 1] += (over) / 2;
            }
        }
    }   

    
    // std::cout << "\nStart comparing used with a: \n";

    for(ll i = 0 ; i < n; ++i) {
        for(ll j = 0 ; j <= i; ++j) {
            // std::cout << used[i][j] << " " << a[i][j] << "\n";
            if(used[i][j] != a[i][j])
                return false;
        }
    }
    return true;
}


int main() {

    ll v, n, a[55][55];  // n is number of levels
    // if v == 1, we print the min level which is full, if v == 2 we print the seconds
    // needed to fill all the glasses and water which was lost during this process
    
    std::ifstream in("pic.in");
    std::ofstream out("pic.out");

    in >> v >> n;
    // 1 + 2 + ... + n = n * (n + 1) / 2
    // std::cout << "Eu sunt v: " << v << "\nEu sunt n: " << n << "\n";

    ll i = 0;
    while(i < n) {
        ll temp = i, j = 0;
        while(temp >= 0) {
            ll aux;
            in >> aux;
            // std::cout << "aux: " << aux << "\n";
            a[i][j++] = aux;
            temp--;
        }
        i++;
    }

    // Print the matrix
    // for(int i = 0 ; i < n; ++i) {
    //     for(int j = 0 ; j <= i; ++j) {
    //         std::cout << " " << a[i][j];
    //     }   
    //     std::cout << "\n";
    // }

    switch(v) {
        case 1: {
            ll res = min_level_max_sum_capacities(n, a);
            if( res != - 1) {
                // std::cout << "Min level is: " << res << "\n";
                out << res << "\n";
            }
        } break;
        case 2: {
            ll left = 0, right = (1LL << 60), best = 0;
            while(left <= right) {
                ll mid = left + (right - left ) / 2;

                bool res = second_and_lost_water(n, a, mid);
                // std::cout << "Eu sunt res: " << res << "\n";
                if(res) {
                    // std::cout << "Am intrat pe result true!\n\n\n";
                    best = mid;
                    right = mid - 1;
                }
                else {
                    // std::cout << "Am intrat pe result false!\n";
                    left = mid + 1;
                }
            }
            // std::cout << "Minimum number of seconds: " << best << "\n" <<
            //     "Lost water: " << on_table << "\n";
            out << best << " " << on_table << "\n";
        } break;
        default:
            std::cout << "Invalid value for v received!\n";
            exit(1);
    }
    
    in.close();
    out.close();

    return 0;
}