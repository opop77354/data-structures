# HW 1 幂集合

## 1. 解題說明
冪集是指一個集合的所有子集，包括空集合和集合本身。

假設一個集合S，幂集合為P(S)。

P(S) := {U|U⊆ S}

若S = {a, b, c}
- ∅
- {a}
- {b}
- {c}
- {a, b}
- {a, c}
- {b, c}
- {a, b, c}

實作參見檔案 `combine.cpp`，其遞迴函式：

```cpp
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

```

## 2. 演算法設計與實作

```cpp
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
```

## 3. 效能分析
時間複雜度:
- 生成幂集遞迴呼叫:
 - 每一元素都有2種選擇，有或是無，因此為2^n次
 - 當 n = 0 且 m > 0 時，函數的時間複雜度是O(n)，因為它遞歸呼叫自身n次。
 - 當 m > 0 且 n > 0 時，函數的時間複雜度非常高，可以說是超過指數等級的成長。

## 4. 測試與過程

### Input

```plain
3
3

```

### Output

```plain
61

```

### 驗證

以範例來驗證:

$$A(3, 3) = m > 0, n > 0; ==>A(2, A(3, 2))$$

將A(3, 2)提出並計算

$$A(3, 2) = m > 0, n > 0; ==>A(2, A(3, 1))$$

重複步驟直到A(3, 0)

$$A(3, 1) = m > 0, n > 0; ==>A(2, A(3, 0))$$

此時函式展開為

$$A(2, 2, 2, A(3, 0))$$

將A(3, 0)提出並計算

$$A(3, 0) = m > 0, n = 0; ==>A(2, 1)$$

依此類推
