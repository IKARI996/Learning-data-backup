#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
// ���ֲ����Ͻ磬���ҷ�ΧΪ����A��[x,y)�� 
template <typename T>
int upperbound(vector<T> A, int x, int y, T v)
{
  int m;
  while(x<y)
  {
    m = x + (y-x)/2;
    if (A[m] <= v) x = m+1;
    else y = m;
  }
  return x; 
}


template <typename Comparable>
int binarySearch(const vector<Comparable> table, int bot, int top, const Comparable &x)
{

//  int result = upperbound(table, bot, top+1, x);
  int result = int(upper_bound(table.begin()+bot, table.begin()+top+1, x) - table.begin());

  if ( result==0 || (result>top && table[top] != x) ) return -1;
  return --result;
}

int main()
{
    int a[ ] = {0,1, 1,2,3,3,6};

    vector<int> v(a,a+7);

    cout << upperbound(v, 0, v.size(), 0) << endl; 
    cout << upperbound(v, 0, v.size(), 6) << endl; 
    cout << upperbound(v, 0, v.size(), 9) << endl; 
    cout << endl;
    cout << binarySearch(v, 0, v.size()-1, 0)<<endl;  // ���0
    cout << binarySearch(v, 0, v.size()-1, 1)<<endl;  // ���2
    cout << binarySearch(v, 0, v.size()-1, 2)<<endl;  // ���3
    cout << binarySearch(v, 0, v.size()-1, 3)<<endl;  // ���5
    cout << binarySearch(v, 0, v.size()-1, 6)<<endl;  // ���6
    cout << binarySearch(v, 0, v.size()-1, 7)<<endl;  //���-1
}
