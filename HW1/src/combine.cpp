#include <iostream>
using namespace std;

// 遞歸函數來生成冪集
void generatePowerset(char* set, char** powerset, char* current, int index, int size, int& powersetIndex, int currentSize) {
    if (index == size) {
        // 將 current 的內容複製到 powerset
        powerset[powersetIndex] = new char[currentSize + 1];
        for (int i = 0; i < currentSize; ++i) {
            powerset[powersetIndex][i] = current[i];
        }
        powerset[powersetIndex][currentSize] = '\0';  // null terminate the string
        powersetIndex++;
        return;
    }

    // 不包括當前元素
    generatePowerset(set, powerset, current, index + 1, size, powersetIndex, currentSize);

    // 包括當前元素
    current[currentSize] = set[index];
    generatePowerset(set, powerset, current, index + 1, size, powersetIndex, currentSize + 1);
}

int main() {
    int n;
    cout << "set_size:";
    cin >> n;

    // 使用 new 動態分配內存
    char* S = new char[n];
    cout << "輸入集合的元素:";
    for (int i = 0; i < n; ++i) {
        cin >> S[i];
    }

    // 計算冪集的大小
    int powersetSize = 1 << n;  // 2^n

    // 使用 new 動態分配內存
    char** powerset = new char* [powersetSize];
    char* current = new char[n];
    int powersetIndex = 0;

    // 生成冪集
    generatePowerset(S, powerset, current, 0, n, powersetIndex, 0);

    // 輸出結果
    for (int i = 0; i < powersetSize; ++i) {
        cout << "{ ";
        for (int j = 0; powerset[i][j] != '\0'; ++j) {
            cout << powerset[i][j] << " ";
        }
        cout << "}" << endl;
        delete[] powerset[i];  // 釋放動態分配的內存
    }

    delete[] powerset;  // 釋放動態分配的內存
    delete[] current;  // 釋放動態分配的內存
    delete[] S;  // 釋放動態分配的內存

    return 0;
}
