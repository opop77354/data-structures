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
    cout << "element:";
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

生成幂集遞迴呼叫:
- 每一元素都有2種選擇，有或是無，因此為2^n次
- 每次遞迴，複製當前子集合，時間複雜度O(n)
- 時間複雜度O(n*2^n)

列印幂集:
- 外層遍歷2^n個子集，內層遍歷每一個子集合內元素，最多遍歷n次
- 時間複雜度O(n*2^n)

空間複雜度:

儲存幂集:
- 陣列需儲存2^n個子集合，每一個子集合長度最多為n
- 空間複雜度O(n*2^n)

遞迴:
- 遞迴深度最多為n
- 空間複雜度O(n)

整體複雜度
- 時間複雜度O(n*2^n)
- 空間複雜度O(n*2^n)
## 4. 測試與過程

### Input

```plain
set_size:3
element:a b c

```

### Output

```plain
{ }
{ c }
{ b }
{ b c }
{ a }
{ a c }
{ a b }
{ a b c }

```

### 驗證

以範例來驗證:

設定集合大小為3
- set_size : 3

再設定集合內的元素
- element : a b c

那麼目前集合

$$S = {a, b, c}$$


