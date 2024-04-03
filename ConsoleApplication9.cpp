#include <iostream>
#include <vector>
#include <random>
#include <omp.h>
#include <thread>
#include <locale>
using namespace std;
double parallelSum(const vector<int>& arr) 
{
    double ans = 0;
    const int n = arr.size();
    const int processor_count = thread::hardware_concurrency();
#pragma omp parallel for num_threads(processor_count) reduction(+:ans)
    for (int i = 0; i < n; i++) 
    {
        ans += arr[i];
    }
    return ans;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    const int n = 12;
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    generate(arr.begin(), arr.end(), [&]() { return dis(gen); });
    double sum = parallelSum(arr);
    cout << "Сумма элементов : " << sum << endl;
    return 0;
}
