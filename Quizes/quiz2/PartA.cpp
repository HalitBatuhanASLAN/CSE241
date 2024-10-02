#include<iostream>
#include<string>

void ConvertToBinary(unsigned int i,string& str)
{
	int divided,remainder;
	divided = i;
	str{};
	while(remainder > 0)
	{
		remainder = divided % 2;
		str = remainder + str;
		div /= 2;
	}
}
