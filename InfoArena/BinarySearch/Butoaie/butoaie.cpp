#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

#define ll long long

ll kill_bugs(const std::vector<ll>& bugs, ll& base, ll& extra, ll& nr_extra, ll &days) {
    
    ll max_upgrades = nr_extra * days;
    // std::cout << "Eu sunt max_upgrades: " << max_upgrades << "\n";
    bool all_bugs_killed = true;

    for(size_t i = 0 ; i < bugs.size(); ++i) {

        if( (bugs[i] - base * days) > 0 ) {
            ll val = (bugs[i] - days * base) / extra + 1;
            if( (bugs[i] - days * base) % extra == 0) {
                val--;
            }

            if(val <= max_upgrades && val <= days) {
                max_upgrades -= val;
            }
            else {
                all_bugs_killed = false;
            }
        }
    }

    return all_bugs_killed;
}
int main() {

    long long n, k, P, Q;
    std::vector<long long> bugs;
    ll base, extra, nr_extra;

    std::ifstream in("butoaie.in");
    std::ofstream out("butoaie.out");

    in >> n >> k >> P >> Q;
    if(P > Q) {
        base = Q;
        extra = P - Q;
        nr_extra = k;
    }
    else {
        base = P;
        extra = Q - P;
        nr_extra = n - k;
    }

    long long tmp = n;
    while(tmp --) {
        long long aux;
        in >> aux;
        bugs.push_back(aux);    
    }

    // for(const auto& x: bugs)
    //     std::cout << x << " ";
    // std::cout << "\n";

    long long left = 0, right = *std::max_element(bugs.begin(), bugs.end()), mid, best = -2;
    while(left <= right) {
        mid = left + (right - left) / 2;
        bool ans = kill_bugs(bugs, base, extra, nr_extra, mid);
        // std::cout << "Ans: " << ans << "\n";
        // std::cout << "Eu sunt mid: " << mid << "\n";
        if(ans) {
            best = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    // std::cout << "All bugs killed in: " << best << " days\n";
    out << best << "\n"; 

    in.close();
    out.close();

return 0;
}