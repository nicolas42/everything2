// https://www.youtube.com/watch?v=hHeq-SB8uVg

// to find a root keep on doing this
// set x to some value, say 0.
// x = x - ( f(x) / f'(x) )
// This will give you one of the closest roots

// i think the general idea is something like this
// f(x_current) = (x_current - x_next) * f'(x_current)
// so 
// x_next = x_current - f(x_current)/f'(x_current) 


#include <iostream>
#include <math.h>

int main()
{
  double g; // guess
  
  // x^4 = 78
  g = 0;
  for (int i=0; i<10; i++){
    g -= (g*g*g*g -78) / (4*g*g*g -78);
  }
  std::cout << g << "\n";

  //  std::cin.get()

  // 3x^2 -sinx -13 = 0
  g = 0;
  for (int i=0; i<10; i++){
    g -= (3*g*g - sin(g) - 13) / (6*g - cos(g));
  }
  std::cout << g << "\n";


  // test should equal close to zero.
  std::cout << (3*g*g - sin(g) - 13) << std::endl;
  
}
