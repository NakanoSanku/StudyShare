#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define random(x) rand() % (x)
using namespace std;
//计算从end-start累加和
int accumulate(vector<int> array, int start, int end)
{
    int res = 0;
    for (int i = start; i < end; i++)
        res += array[i];
    return res;
};
int findIcon(vector<int> array, int start, int end)
{
    int left, right;
    while (start != end)
    {
        left = accumulate(array, start, end / 2 );
        right = accumulate(array, end / 2, end);
        if ((end - start) % 2 == 1)
            left = accumulate(array, start, end / 2);
        if (left % 2 == 1)
            end = end / 2;
        if (right % 2 == 1)
            start = end / 2;
    }
    return start;
}
int main()
{
    int size = 100;
    vector<int> array(size, 2);
    srand((int)time(0));
    array[random(size)] = 1;
    findIcon(array, 0, size);
}