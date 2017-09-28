/*************************************************************************
	> File Name: matrix_multiplication.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 28 Sep 2017 10:38:34 AM EDT
    > CLRS 4.2 matrix multiplication
    > brute force and Strassen's algorithm
 ************************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class matrix {
public:
    matrix(int n):_size(n) {
        _vec.resize(n);
        for (int i = 0; i < n; i++) {
            _vec[i].resize(n);
        }
    }

    int get_size() const{
        return _size;
    }

    vector<int>& operator[](int n) {
        return _vec[n];
    }
    
    const vector<int>& operator[](int n) const {
        return _vec[n];
    }

    void init() {
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                _vec[i][j] = 0;
            }
        }
    }

    matrix operator+(const matrix& mat2) const {
        matrix mat_result(_size);
        for (int i = 0; i < _size; i++) {
            for(int j = 0; j < _size; j++) {
                mat_result[i][j] = _vec[i][j] + mat2[i][j];
            }
        }
    }

private:
    vector<vector<int> > _vec;
    int _size;
};


// O(n^3)
matrix mat_mult_brute_force(const matrix& mat1, const matrix& mat2) {
    int n = mat1.get_size();
    matrix mat_result(n);
    mat_result.init();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                mat_result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return mat_result;
}

// Strassen
// O(n^(log7))
matrix mat_mult_strassen(const matrix& mat1, const matrix& mat2, int thres) {
    int n = mat1.get_size();
    matrix result(n);
    // It is crucial to use brute force approach when n is smaller than a certain threshold!
    // Because the Strassen approach as a large O-constant, and is slower when n is small.
    if (n <= thres) {
        return mat_mult_brute_force(mat1, mat2);
    }
    vector<matrix> s(10, matrix(n / 2));
    matrix A11(n / 2), A22(n / 2), B11(n / 2), B22(n / 2);
    for (int i = 0; i < 10; i++) {
        s[i].init();
    }
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            s[0][i][j] = mat2[i][j + n / 2] - mat2[i + n / 2][j + n / 2];
            s[1][i][j] = mat1[i][j] + mat1[i][j + n / 2];
            s[2][i][j] = mat1[i + n / 2][j] + mat1[i + n / 2][j + n / 2];
            s[3][i][j] = mat2[i + n / 2][j] - mat2[i][j];
            s[4][i][j] = mat1[i][j] + mat1[i + n / 2][j + n / 2];
            s[5][i][j] = mat2[i][j] + mat2[i + n / 2][j + n / 2];
            s[6][i][j] = mat1[i][j + n / 2] - mat1[i + n / 2][j + n / 2];
            s[7][i][j] = mat2[i + n / 2][j] + mat2[i + n / 2][j + n / 2];
            s[8][i][j] = mat1[i][j] - mat1[i + n / 2][j];
            s[9][i][j] = mat2[i][j] + mat2[i][j + n / 2];
            A11[i][j] = mat1[i][j];
            A22[i][j] = mat1[i + n / 2][j + n / 2];
            B11[i][j] = mat2[i][j];
            B22[i][j] = mat2[i + n / 2][j + n / 2];
        }
    }

    matrix P1 = mat_mult_strassen(A11, s[0], thres);
    matrix P2 = mat_mult_strassen(s[1], B22, thres);
    matrix P3 = mat_mult_strassen(s[2], B11, thres);
    matrix P4 = mat_mult_strassen(A22, s[3], thres);
    matrix P5 = mat_mult_strassen(s[4], s[5], thres);
    matrix P6 = mat_mult_strassen(s[6], s[7], thres);
    matrix P7 = mat_mult_strassen(s[8], s[9], thres);

    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            result[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
            result[i][j + n / 2] = P1[i][j] + P2[i][j];
            result[i + n / 2][j] = P3[i][j] + P4[i][j];
            result[i + n / 2][j + n / 2] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }

    // for the remain edges
    if (n % 2 != 0) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1; j++) {
                result[i][j] += mat1[i][n - 1] * mat2[n - 1][j];
            }
        }
        for (int i = 0; i < n - 1; i++) {
            result[i][n - 1] = 0;
            for (int k = 0; k < n; k++) {
                result[i][n - 1] += mat1[i][k] * mat2[k][n - 1];
            }
        }
        for (int j = 0; j < n; j++) {
            result[n - 1][j] = 0;
            for (int k = 0; k < n; k++) {
                result[n - 1][j] += mat1[n - 1][k] * mat2[k][j];
            }
        }
    }

    return result;
}


int main() {
    srand(time(NULL));
    int n = 1500;
    // threshold in Strassen approach
    // Use brute force approach when the size of matrix is smaller than or equal to the threshold.
    int thres = 256; 
    matrix A(n), B(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 1000;
            B[i][j] = rand() % 1000;
        }
    }

    time_t t1, t2;
    double t_brute_force, t_strassen;

    time(&t1);
    matrix C1 = mat_mult_brute_force(A, B);
    time(&t2);
    t_brute_force = difftime(t2, t1);

    time(&t1);
    matrix C2 = mat_mult_strassen(A, B, thres);
    time(&t2);
    t_strassen = difftime(t2, t1);

    bool is_correct = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (C1[i][j] != C2[i][j]) {
                is_correct =false;
            }
        }
    }

    if (is_correct)
        cout << "Right!" << endl;
    else
        cout << "Wrong!" << endl;

    // test result (personal computer):
    // n = 1500, thres = 256
    // brute force: 100s. Strassen: 53s
    cout << "Brute force:" << t_brute_force << "s" << endl;
    cout << "Strassen:" << t_strassen << "s" << endl;

    return 0;

}
