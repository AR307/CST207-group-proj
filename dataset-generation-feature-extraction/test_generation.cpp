#include "dataset.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printArray(const string& name, vector<int>& arr, int maxShow = 10) {
    cout << "\n" << name << " (size: " << arr.size() << ")" << endl;
    cout << "First " << min((int)arr.size(), maxShow) << " elements: ";
    for (int i = 0; i < min((int)arr.size(), maxShow); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== 数据生成函数测试 ===" << endl;
    
    // 测试1: generateRandom
    cout << "\n[测试1] generateRandom(20)" << endl;
    vector<int> arr1 = generateRandom(20);
    printArray("随机数组", arr1, 20);
    
    // 测试2: generateNearlySorted
    cout << "\n[测试2] generateNearlySorted(20, 3)" << endl;
    vector<int> arr2 = generateNearlySorted(20, 3);
    printArray("几乎有序数组 (3次交换)", arr2, 20);
    
    // 测试3: generateReversed
    cout << "\n[测试3] generateReversed(15)" << endl;
    vector<int> arr3 = generateReversed(15);
    printArray("逆序数组", arr3, 15);
    
    // 测试4: generateFewUnique
    cout << "\n[测试4] generateFewUnique(30, 5)" << endl;
    vector<int> arr4 = generateFewUnique(30, 5);
    printArray("少量唯一元素数组 (5个唯一值)", arr4, 30);
    
    // 测试5: generateLargeRandom
    cout << "\n[测试5] generateLargeRandom(2000)" << endl;
    vector<int> arr5 = generateLargeRandom(2000);
    printArray("大规模随机数组", arr5);
    
    cout << "\n=== 所有数据生成测试完成 ===" << endl;
    
    return 0;
}
