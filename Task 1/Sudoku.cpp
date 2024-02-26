#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Вывод решённого судоку
void printSudoku(vector<vector<int>>& sudoku, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
}

// Проверка правил судоку
bool isValid(vector<vector<int>>& sudoku, int row, int col, int num, double sqrtn) {
    // Проверка по строке
    for (int i = 0; i < sudoku.size(); i++) {
        if (sudoku[row][i] == num) {
            return false;
        }
    }
    
    // Проверка по столбцу
    for (int i = 0; i < sudoku.size(); i++) {
        if (sudoku[i][col] == num) {
            return false;
        }
    }

    // Проверка по квадрату
    int startRow = row - row % int(sqrtn);
    int startCol = col - col % int(sqrtn);
    for (int i = 0; i < int(sqrtn); i++) {
        for (int j = 0; j < int(sqrtn); j++) {
            if (sudoku[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Решение судоку
bool solveSudoku(vector<vector<int>>& sudoku, int n, double sqrtn) {
    int row, col;

    // Находим первую пустую клетку
    bool isempty = false;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (sudoku[row][col] == 0) {
                isempty = true;
                break;
            }
        }
        if (isempty) {
            break;
        }
    }

    // Нет пустых клеток - судоку решено
    if (!isempty) {
        return true;
    }

    // Проверяем числа от 1 до n
    for (int num = 1; num <= n; num++) {
        if (isValid(sudoku, row, col, num, sqrtn)) {
            sudoku[row][col] = num;
            if (solveSudoku(sudoku, n, sqrtn)) {
                return true;
            }
            sudoku[row][col] = 0;
        }
    }
    return false;
}

// Проверка существования поля для судоку
void checkN(double n, double sqrtn) {
    if ((sqrtn-(int)sqrtn)!=0)
    {
        cout << "Invalid field";
        exit (0);
    }
}

int main() {
    double n, sqrtn;
    cin >> n;
    sqrtn = sqrt(n);
    checkN(n, sqrtn);

    vector<vector<int>> sudoku(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> sudoku[i][j];
        }
    }

    if (solveSudoku(sudoku, n, sqrtn)) {
        printSudoku(sudoku, n);
    }
    
    return 0;
}
