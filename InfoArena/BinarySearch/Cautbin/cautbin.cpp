#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;


// 0 x - biggest position for element with value x or -1 if we can't find it
// 1 x biggest posisition for element with value <= x. It is guaranteed that smallest number <= x
// 2 x smallest position for element with value >= x. it is guaranteed that biggest number is >= x

int binary_seach_1(const vector<int>& values, int left, int right, int searched_value) {

    int best_index = -2;
    
    while(left <= right) {
        // cout << "Eu sunt best_index: " << best_index << "\n";

        int mid = left + (right - left) / 2;
        // cout << "Eu sunt mid: " << mid << "\n";

        if (values[mid] >= searched_value) {
            if(values[mid] == searched_value) {
                best_index = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }          
        }
        else {
            left = mid + 1;
        }
    }

    //If we cannot find any value, we return -1
    // cout << "Before Returning best_index: " << best_index << "\n";
    return best_index + 1;
}

int binary_seach_2(const vector<int>& values, int left, int right, int searched_value) {

    int best_index = -2;
    
    while(left <= right) {
        // cout << "Eu sunt best_index: " << best_index << "\n";

        int mid = left + (right - left) / 2;
        // cout << "Eu sunt mid: " << mid << "\n";
        
        if (values[mid] <= searched_value) {
            best_index = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    //If we cannot find any value, we return -1
    // cout << "Before Returning best_index: " << best_index << "\n";
    return best_index + 1;
}

int binary_seach_3(const vector<int>& values, int left, int right, int searched_value) {

    int best_index = -2;
    
    while(left <= right) {
        // cout << "Eu sunt best_index: " << best_index << "\n";

        int mid = left + (right - left) / 2;
        // cout << "Eu sunt mid: " << mid << "\n";
        
        if (values[mid] >= searched_value) {
            best_index = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    //If we cannot find any value, we return -1
    // cout << "Before Returning best_index: " << best_index << "\n";
    return best_index + 1;
}

int main() {

    int N, M;
    vector<int> values;

    // N - number of elements
    // M - number of questions (0 x     1x      2 x)

    ifstream in("cautbin.in");
    ofstream out("cautbin.out");

    in >> N;
    while(N--) {
        int tmp;
        in >> tmp;
        values.push_back(tmp);
    }

    in >> M;
    while( M-- ) {
        int choice, x;
        in >> choice >> x;
        int val = -1;

        switch(choice) {
            case 0:
                val = binary_seach_1(values, 0, values.size() - 1, x);
                break;
            case 1:
                val = binary_seach_2(values, 0, values.size() - 1, x);
                break;
            case 2:
                val = binary_seach_3(values, 0, values.size() - 1, x);
                break;
            default:
                cout << "You shouldn't be here!\n";
                exit(1);
        }
        cout << val << "\n";
        out << val << "\n";
    }

    out.close();
    in.close();
    return 0;
}