#include <iostream>
using namespace std;

int main()
{
  int N, sum = 0, t;
  cin >> N;
  for(int i=0;i<N;++i)
  {    
    cin >> t;
    sum = (sum + t) % 1000001;
  }
  cout << sum << endl;
  return 0;
}