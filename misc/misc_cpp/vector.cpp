#include <iostream>
#include <vector>

int main()
{
  using namespace std;
  std::vector <double> v(100);
  for (int i=0; i<100; i++){
    v[i] = i;
  }

  v.push_back(101);

  for (int i=0; i<100; i++){
    cout << v[i] << " ";
  }


  for (auto i: v) std::cout << i << " ";

  cout << v.capacity() << " ";

}
