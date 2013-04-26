#include <iostream>

int calculate(int);
int main()
{
 int number, sum;
 std::cin >> number;

 do
 {
   sum = calculate(number);
   number = sum;
 }
 while(number > 9);
 std::cout << number;
 return 0;
}

int calculate(int number)
{
 int sum = 0;
 while(number > 0)
  {
   sum = sum + number % 10;
   number = (number / 10);
  }
 return sum;
}