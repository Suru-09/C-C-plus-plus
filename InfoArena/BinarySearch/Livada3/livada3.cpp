#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

#define ll long long


ll maxi;
// A[i][j] = (x * A[i - 1][j] + y * A[i][j - 1] + z * A[i - 1][j - 1] + w) % u;

void complete_matrix(std::vector<std::vector<ll>>& matrix, ll& x, ll& y, ll& z , ll& w, ll& u, ll &n, ll& m) {
    for(ll i = 1 ; i < n; ++i) {
        for(ll j = 1 ; j < m; ++ j) {
            matrix[i][j] = ((x * matrix[i - 1][j] + y * matrix[i][j - 1] + z * matrix[i - 1][j - 1] + w) % u);
            maxi = std::max(matrix[i][j], maxi);
        }   
    }
}

ll line_sum(const std::vector<std::vector<ll>>& matrix, const ll&line, ll m, ll proposed_val) {
    ll sum = 0;
    for(int i = 0 ; i < m; ++i) {
        if(matrix[line][i] > proposed_val)
            break;
        sum += matrix[line][i];
    }

    return sum;
}

ll binary_search(const std::vector<std::vector<ll>>& matrix, const ll& c, const ll& r, ll n, ll m) {

    ll left = 0 , right = maxi, mid, best = -1;
    while(left <= right) {
        mid = left + (right - left) / 2;
        std::vector<ll> aux;
        for(int i = 0 ; i < n; ++i) {
            aux.push_back(line_sum(matrix, i, m, mid));
        }
        
        sort(aux.begin(), aux.end(), std::greater<ll>());

        ll sum = 0;
        for(int i = 0; i < r; ++i) {
            sum += aux[i];
        }

        if(sum >= c) {
            best = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }

    }
    return best;
}

int main() {

    ll n, m, c, r;
    ll x, y, z, w, u;

    std::vector<ll> first_line;
    std::vector<ll> n_values;

    std::ifstream in("livada3.in");
    std::ofstream out("livada3.out");

    in >> n >> m >> c >> r;
    in >> x >> y >> z >> w >> u;

    // std:: cout << x << " " << y << " " << z << " " << w << " " << u << "\n";

    ll copy_m = m;
    while(copy_m--) {
        ll aux;
        in >> aux;
        first_line.push_back(aux);
    }

    std::vector<std::vector<ll>> matrix(n, std::vector<ll>(m));
    matrix[0] = first_line;
    maxi = *std::max_element(first_line.begin(), first_line.end());
    
    ll copy_n = n - 1, i = 1;
    while(copy_n--) {
        ll temp;
        in >> temp;
        matrix[i++][0] = temp;
        maxi = std::max(matrix[i - 1][0], maxi);
    }

    complete_matrix(matrix, x, y, z, w, u, n , m);
    
    // for(ll i = 0 ; i < n; ++i) {
    //     for(ll j = 0 ; j < m; ++j) {
    //         std::cout << matrix[i][j] << "  ";
    //     }
    //     std::cout << "\n";
    // }

    // std::cout << binary_search(matrix, c, r, n, m) << "\n";
    out << binary_search(matrix, c, r, n, m) << "\n";

    in.close();
    out.close();

    return 0;
}