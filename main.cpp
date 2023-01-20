#include "Container/Vector.hpp"
#include <vector>

int main()
{
  std::vector<int> first;
  std::vector<int> second;
  std::vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  std::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';

  std::cout << "FTTTTTTTTTT" << std::endl;

  ft::vector<int> first2;
  ft::vector<int> second2;
  ft::vector<int> third2;

  first2.assign (7,100);             // 7 ints with a value of 100

  ft::vector<int>::iterator it2;
  it2=first2.begin()+1;

  second2.assign (it2,first2.end()-1); // the 5 central values of first

  int myints2[] = {1776,7,4};
  third2.assign (myints2,myints2+3);   // assigning from array.

  std::cout << "Size of first: " << int (first2.size()) << '\n';
  std::cout << "Size of second: " << int (second2.size()) << '\n';
  std::cout << "Size of third: " << int (third2.size()) << '\n';

  
  return 0;
}