#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> v;
  cout << "v.size(): " << v.size() << endl;
  v.push_back(123);
  v[1] = 3;
  for (int val : v) {
    cout << val << endl;
  }

  //vector<int> v(10,0) creates [0,0,0,0,0,0,0,0,0,0]
  //vector<int> v{1,2,3,1} creates [1,2,3,1]
}
