#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<iomanip>
#include<cstring>
#include<fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<ctype.h>
#include <dirent.h>

using namespace std;

namespace LCS {


    /**
     *  @brief  Calculating LCS without retaining the entire table, it is used for the tabular
     * @tparam T Used a template, therefore it is possible to use lcs both on
     *           words and letters
     * @param A first string / vector of strings to compare
     * @param B second string / vector of strings to compare
     */
    template <typename T>
    void lcs_without_table(T &A, T &B);

    /**
     * @brief calls constructor so that we allocate memory for the columns
     * @param dp the vector<vector<int>> which is actually a matrix
     * @param col_dimension the dimension of the columns
     * @return the allocated matrix
     */
    vector<vector<int>> init_matrix(vector< vector<int> > &dp, int col_dimension);

    /*
    Created this algorithm based on the:

    'A Linear Space Algorithm for Computing Maximal
    Common Subsequences' paper from Princeton University

    link for the paper:
        https://www.ics.uci.edu/~dan/pubs/p341-hirschberg.pdf
*/

    /**
     *
     * @param A the first file
     * @param B the second file
     * @param m size of first file
     * @param n size of second file
     * @param dp the LCS calculated in the last column
     */

    void algorithm_B(vector<string> &A, vector<string> &B, int m, int n, vector<vector<int>> &dp);
    vector<string> selectFromVector(vector<string> &A, int i, int j);

    /**
     *@brief Hirschberg algorithm, optimization in space O(m + n)
     * @param A the first file
     * @param B the second file
     * @param m size of first file
     * @param n size of second file
     * @param result The LCS string !
     */
    void algorithm_C(vector<string> &A, vector<string> &B, int m, int n, vector<string> &result);

}

namespace utility {

    /**
     * @param first_file name of the first file
     * @param second_file name of the second file
     * @param isTabular whether we are using -t or not
     */
    void pair_comparison(char first_file[], char second_file[], bool isTabular);

    /**
     * @param path path of the directory in which we have the files
     */
    void tabular(char path[]);
}
