#include <iostream>
using namespace std;

// ���k��ƨӥͦ�����
void generatePowerset(char* set, char** powerset, char* current, int index, int size, int& powersetIndex, int currentSize) {
    if (index == size) {
        // �N current �����e�ƻs�� powerset
        powerset[powersetIndex] = new char[currentSize + 1];
        for (int i = 0; i < currentSize; ++i) {
            powerset[powersetIndex][i] = current[i];
        }
        powerset[powersetIndex][currentSize] = '\0';  // null terminate the string
        powersetIndex++;
        return;
    }

    // ���]�A��e����
    generatePowerset(set, powerset, current, index + 1, size, powersetIndex, currentSize);

    // �]�A��e����
    current[currentSize] = set[index];
    generatePowerset(set, powerset, current, index + 1, size, powersetIndex, currentSize + 1);
}

int main() {
    int n;
    cout << "set_size:";
    cin >> n;

    // �ϥ� new �ʺA���t���s
    char* S = new char[n];
    cout << "��J���X������:";
    for (int i = 0; i < n; ++i) {
        cin >> S[i];
    }

    // �p�⾭�����j�p
    int powersetSize = 1 << n;  // 2^n

    // �ϥ� new �ʺA���t���s
    char** powerset = new char* [powersetSize];
    char* current = new char[n];
    int powersetIndex = 0;

    // �ͦ�����
    generatePowerset(S, powerset, current, 0, n, powersetIndex, 0);

    // ��X���G
    for (int i = 0; i < powersetSize; ++i) {
        cout << "{ ";
        for (int j = 0; powerset[i][j] != '\0'; ++j) {
            cout << powerset[i][j] << " ";
        }
        cout << "}" << endl;
        delete[] powerset[i];  // ����ʺA���t�����s
    }

    delete[] powerset;  // ����ʺA���t�����s
    delete[] current;  // ����ʺA���t�����s
    delete[] S;  // ����ʺA���t�����s

    return 0;
}
