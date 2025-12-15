#include "dataset.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void testFeatures(const string& name, vector<int>& arr) {
    cout << "\n测试数组: " << name << endl;
    cout << "  - 大小: " << getDatasetSize(arr) << endl;
    cout << "  - 有序度: " << fixed << setprecision(2) << calculateSortedness(arr) << "%" << endl;
    cout << "  - 唯一元素比例: " << fixed << setprecision(4) << calculateUniqueRatio(arr) << endl;
}

int main() {
    cout << "=== 特征提取函数测试 ===" << endl;
    
    // 测试1: 完全有序数组
    cout << "\n[测试1] 完全有序数组" << endl;
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    testFeatures("完全有序", sorted);
    
    // 测试2: 完全逆序数组
    cout << "\n[测试2] 完全逆序数组" << endl;
    vector<int> reversed = generateReversed(10);
    testFeatures("完全逆序", reversed);
    
    // 测试3: 随机数组
    cout << "\n[测试3] 随机数组" << endl;
    vector<int> random = generateRandom(50);
    testFeatures("随机数组", random);
    
    // 测试4: 少量唯一元素
    cout << "\n[测试4] 少量唯一元素数组" << endl;
    vector<int> fewUnique = generateFewUnique(100, 5);
    testFeatures("少量唯一元素", fewUnique);
    
    // 测试5: 几乎有序
    cout << "\n[测试5] 几乎有序数组" << endl;
    vector<int> nearlySorted = generateNearlySorted(50, 5);
    testFeatures("几乎有序", nearlySorted);
    
    // 测试6: 空数组
    cout << "\n[测试6] 边界情况 - 空数组" << endl;
    vector<int> empty;
    testFeatures("空数组", empty);
    
    // 测试7: 单元素数组
    cout << "\n[测试7] 边界情况 - 单元素数组" << endl;
    vector<int> single = {42};
    testFeatures("单元素", single);
    
    // 测试8: 所有元素相同
    cout << "\n[测试8] 所有元素相同" << endl;
    vector<int> allSame(20, 7);
    testFeatures("所有元素相同", allSame);
    
    cout << "\n=== 所有特征提取测试完成 ===" << endl;
    
    return 0;
}
