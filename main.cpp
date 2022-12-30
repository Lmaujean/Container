#include "Container/Vector.hpp"
#include <vector>

int main()
{
    std::vector<int> vec;
    vec.size();
    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    std::cout << vec.size() << std::endl;

    ft::vector<int> vec2;
    vec2.size();
    for (int i = 0; i < 10; i++)
        vec2.push_back(i);
    std::cout << vec2.size() << std::endl;
}