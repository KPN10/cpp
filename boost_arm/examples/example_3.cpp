#include <iostream>
#include <cmath>
#include <boost/chrono.hpp>

int main(void) {
  std::cout << "example_3" << std::endl;
  boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();

  for (uint64_t i = 0; i < 1000000; ++i) {
    std::sqrt(123.456L); // burn some time
  }
  

  boost::chrono::duration<double> sec = boost::chrono::steady_clock::now() - start;
  std::cout << "took " << sec.count() << " seconds\n";

  return 0;
}