#include "LCS.h"


namespace utility {
    void pair_comparison(char first_file[], char second_file[], bool isTabular) {

        string tmp;
        vector<string> A;

        ifstream file_A(first_file);
        if(!file_A) {
            perror("There was an error while opening the file A!\n");
            exit(3);
        }

        while( file_A >> tmp ){
            A.push_back(tmp);
        }
        file_A.close();

        vector<string> B;

        ifstream file_B(second_file);
        if(!file_B) {
            perror("There was an error while opening the file B!\n");
            exit(4);
        }

        while( file_B >> tmp ) {
            B.push_back(tmp);
        }
        file_B.close();

        if( isTabular ) {

            // vector<vector<int>> dp(2);
            // init_matrix(dp, B.size() + 1);

            LCS::lcs_without_table(A, B);
            // algorithm_B(A, B, A.size(), B.size(), dp);
            // cout << "Eu sunt size de result: " << dp[1][B.size()] << "\n";
            // cout << "Plagiarism A/result : " << dp[1][B.size()] / (double) A.size() * 100  << "% \nPlagiarism B/result: " << dp[1][B.size()] / (double) B.size() * 100  << "%\n";
        }
        else {

            vector<string> result;
            LCS::algorithm_C(A, B, A.size(), B.size(), result);
            for(const auto& x: result)
                cout << "  " << x;
            cout << "\n";

            cout << "Eu sunt size de result: " << result.size() << "\n";
            cout << "Plagiarism A/result : " <<  result.size() / (double)A.size() * 100 << "% \nPlagiarism B/result: " << result.size() / (double) B.size() * 100 << "%\n";
        }

    }

    void tabular(char path[]) {

        DIR *dir = opendir(path);

        vector<string> paths;

        if(!dir) {
            perror("There was an error while opening the director!\n");
            exit(6);
        }

        char next_path[4096];
        struct dirent *dir_data;

        while( (dir_data = readdir(dir)) ) {

            if( (!strcmp(dir_data -> d_name, ".")) || (!strcmp(dir_data -> d_name, "..")) )
                continue;

            strcpy(next_path, path);
            strcat(next_path, "/");
            strcat(next_path, dir_data->d_name);

            struct stat state{};
            if ( stat(next_path, &state) ) {
                printf("Couldn't access state of the directory!\n");
                exit(7);
            }

            if(  (state.st_mode & S_IFMT) == S_IFREG ) {
                paths.emplace_back(dir_data->d_name);
            }
        }


        // for(auto x: paths)
        //     cout << "FILE : "  << x << "\n";

        for(unsigned long int i = 0 ; i < paths.size() - 1; ++i)
            for(unsigned long int j = i + 1 ; j < paths.size(); ++j) {
                char aux1[150] {};
                strcpy(aux1, path);
                strcat(aux1, "/");
                strcat(aux1, paths[i].c_str() );

                char aux2[150] {};
                strcpy(aux2, path);
                strcat(aux2, "/");
                strcat(aux2, paths[j].c_str() );

                cout << "FILES: "<< aux1 << "   " << aux2 << "\n";

                utility::pair_comparison(aux1, aux2, true);
                cout << "\n";
            }
    }
}

namespace LCS {

    template <typename T>
    void lcs_without_table(T &A, T &B) {

        const unsigned long int m = B.size();
        const unsigned long int n = A.size();

        //printf("Eu sunt m : %ld si eu sunt n %ld \n", m, n );

        int dp[2][m + 1];

        bool index;

        for(size_t i = 0; i <= n ; ++i) {

            index = i & 1;

            for(size_t j = 0;  j <= m ; ++j) {

                if(i == 0 || j == 0) {
                    dp[index][j] = 0;
                }
                else if( A[i - 1] == B[j - 1] ) {
                    dp[index][j] = dp[1 - index][j - 1] + 1;
                }
                else {
                    dp[index][j] = std::max(dp[1 - index][j], dp[index][j - 1]);
                }
            }
        }

        int count_duplicated = dp[index][m];

        double plag_procent1 = (count_duplicated / double(n) ) * 100;
        double plag_procent2 = (count_duplicated / double(m) ) * 100;

        cout << "Count_duplicated :" << count_duplicated;
        cout << "\nPlagiarism count / A: " << plag_procent1 << "%  \nPlagiarism count / B: " << plag_procent2 << "\n\n";
    }

    vector<vector<int>> init_matrix(vector< vector<int> > &dp, int col_dimension) {

        for(auto & i : dp)
            i = vector<int>(col_dimension);

        return dp;
    }

    void algorithm_B(vector<string> &A, vector<string> &B, int m, int n, vector<vector<int>> &dp) {

        vector<vector<int>> K(2);
        K = init_matrix(K, n + 1);

        for(int j = 0 ; j <= n; ++j)
            K[1][j] = 0;

        for(int i = 1;  i <= m ; ++i) {

            for(int l = 0 ; l <= n ; ++l)
                K[0][l] = K[1][l];

            for(int j = 1; j <= n ; ++j) {
                if(A[i - 1] == B[j - 1]) {
                    K[1][j] = K[0][j - 1] + 1;
                }
                else {
                    K[1][j] = std::max(K[1][j - 1], K[0][j]);
                }
            }
        }

        for(int j = 0 ; j <= n ; ++j) {
            dp[1][j] = K[1][j];
        }

    }

    vector<string> selectFromVector(vector<string> &A, int i, int j) {

        int aux = j - i;
        if( aux < 0)
            aux = i - j;

        vector<string> tmp(aux);
        std::copy(A.begin() + i, A.begin() + j, tmp.begin());

        return tmp;
    }

    void algorithm_C(vector<string> &A, vector<string> &B, int m, int n, vector<string> &result) {

        if( !n ) {
            return;
        }
        else if(m == 1) {
            for(int j = 0 ; j < n; ++j)
                if(A[0] == B[j]) {
                    result.push_back(A[0]);
                    return;
                }
            return;
        }
        else {
            // m / 2 == flooring !!
            int i = m / 2;

            vector<vector<int>> LL1(2);
            init_matrix(LL1, n + 1);

            vector<vector<int>> LL2(2);
            init_matrix(LL2, n + 1);

            vector<string> tmp_A = selectFromVector(A, 0, i);

            vector<string> reverse_A(A.size());
            std::reverse_copy(A.begin(), A.end(), reverse_A.begin());

            vector<string> reverse_B(B.size());
            std::reverse_copy(B.begin(), B.end(), reverse_B.begin());

            vector<string> tmp_A1 = selectFromVector(reverse_A, 0, m - i);

            LCS::algorithm_B(tmp_A, B, tmp_A.size(), B.size(), LL1);
            LCS::algorithm_B( tmp_A1, reverse_B , tmp_A1.size(), reverse_B.size(), LL2);

            int M = 0;
            int k = 0;

            for(int j = 0 ; j <= n ; ++j)
                M = std::max(M, LL1[1][j] + LL2[1][n - j]);

            for(int j = 0 ; j <= n; ++j) {
                if(LL1[1][j] + LL2[1][n - j] == M) {
                    k = j;
                    break;
                }
            }

            vector<string> tmp_B2 = selectFromVector(B, 0, k);

            vector<string> tmp_A3 = selectFromVector(A, i , m);
            vector<string> tmp_B3 = selectFromVector(B, k , n);

            LCS::algorithm_C(tmp_A, tmp_B2, tmp_A.size(), tmp_B2.size() , result);
            LCS::algorithm_C(tmp_A3, tmp_B3, tmp_A3.size(), tmp_B3.size() , result);
        }


    }

}

