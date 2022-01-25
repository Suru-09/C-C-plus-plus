#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

// condition for a valid triangle:   a + b > c

int _binary_search(const std::vector<int>& arr, int left, int right, int x, int y, int& counter) {
    int best = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        // std::cout << "Eu sunt mid: " << mid << "\n";
        // std::cout << "Eu sunt left: " << left << " " <<
        // "Eu sunt right: " << right << "\n";

        // std::cout << arr[x] << " " << arr[y] << " > " << arr[mid] << "\n";
        if(arr[x] + arr[y] >= arr[mid]) {
            best = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    //in case we don't find any value return -1
    // std::cout << "Eu sunt x: " << x << " Eu sunt y: " << y << "\n";
    // std::cout << "Eu sunt best: " << best << "\n";
    if(best <= y) {
        return -1;
    }
    counter += best - y;
    return best;
}


int main() {

    int n;  // nr bete
    std::vector<int> values;

    std::ifstream in("nrtri.in");
    std::ofstream out("nrtri.out");

    in >> n;

    while(n--) {
        int tmp;
        in >> tmp;
        values.push_back(tmp);
    }

    sort(values.begin(), values.end());
    int res = -2;

    // for(const auto& x: values)
    //     std::cout << x << " ";
    // std::cout << "\n\n";

    int counter = 0;

    for(size_t i = 0 ; i < values.size() - 1; ++i) {
        for(size_t j = i + 1; j < values.size(); ++j) {
            res = _binary_search(values, j + 1, values.size() - 1, i, j, counter);
        }
    }
    
    out << counter << "\n";

    in.close();
    out.close();

    return 0;
}