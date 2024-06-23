#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/lambda/lambda.hpp>

int main()
{
    std::cout << "example_2" << std::endl;

    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );
    return 0;
}