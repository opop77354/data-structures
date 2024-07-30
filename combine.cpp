#include <iostream>
using namespace std;

void generatePowerset(char* set, char** powerset, char* current, int index, int size, int& powersetIndex, int currentSize) 
{
    if (index == size) 
    {
        powerset[powersetIndex] = new char[currentSize + 1];
        for (int i = 0; i < currentSize; ++i) 
        {
            powerset[powersetIndex][i] = current[i];
        }
        powerset[powersetIndex][currentSize] = '\0';
        powersetIndex++;
        return;
    }
    generatePowerset(set, powerset, current, index + 1, size, powersetIndex, currentSize);
    current[currentSize] = set[index];
    generatePowerset(set, powerset, current, index + 1, size, powersetIndex, currentSize + 1);
}

int main() 
{
    int n;
    cout << "set_size:";
    cin >> n;
    char* S = new char[n];
    cout << "輸入集合的元素:";
    for (int i = 0; i < n; ++i) 
    {
        cin >> S[i];
    }
    int powersetSize = 1 << n;
    char** powerset = new char* [powersetSize];
    char* current = new char[n];
    int powersetIndex = 0;
    generatePowerset(S, powerset, current, 0, n, powersetIndex, 0);
    for (int i = 0; i < powersetSize; ++i) 
    {
        cout << "{ ";
        for (int j = 0; powerset[i][j] != '\0'; ++j) 
        {
            cout << powerset[i][j] << " ";
        }
        cout << "}" << endl;
        delete[] powerset[i];
    }

    delete[] powerset;
    delete[] current;
    delete[] S;
    return 0;
}
