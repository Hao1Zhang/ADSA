/*
 * @Author       : Hao Zhang
 * @Date         : 2021-04-03 21:11:33
 * @LastEditors  : Hao Zhang
 * @LastEditTime : 2021-04-04 11:07:03
 * @FilePath     : \adsa\assignment1\main.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

//school method for addition
string addition(string first_num, string second_num, int base)
{

	int num1_len = first_num.size();
	int num2_len = second_num.size();
	int result_len = max(num1_len, num2_len) + 1; //result has at most one more digit than input
	string result_str;
	int carry = 0;
	//add 0s in beginning to make length equal
	if (num1_len < num2_len)
	{
		for (int i = 0; i < num2_len - num1_len; i++)
		{
			first_num = '0' + first_num;
		}
		num1_len = num2_len;
	}
	else if (num1_len > num2_len)
	{
		for (int i = 0; i < num1_len - num2_len; i++)
		{
			second_num = '0' + second_num;
		}
		num2_len = num1_len;
	}

	//add one by one
	for (int i = 0; i < result_len - 1; i++)
	{
		int num1, num2, curr_result;
		num1 = first_num[num1_len - 1 - i] - '0';
		num2 = second_num[num2_len - 1 - i] - '0';
		curr_result = num1 + num2 + carry;
		int result = curr_result;
		if (curr_result >= base)
		{
			carry = 1;
			result = curr_result - base;
		}
		else
		{
			carry = 0;
		}
		
		result_str = to_string(result) + result_str;
	}
	result_str = to_string(carry) + result_str;

	//remove all 0s in the beginning
	int breakpoint = result_str.size();
	for (int i = 0; i < breakpoint; i++)
	{
		if (result_str[i] != '0')
		{
			breakpoint = i;
			break;
		}
	}

	result_str = result_str.substr(breakpoint, result_str.size() - breakpoint);
	if (result_str.size() == 0) {
		return "0";
	}
	return result_str;
}

string substraction(string first_num, string second_num, int base)
{

	int num1_len = first_num.size();
	int num2_len = second_num.size();
	int result_len = max(num1_len, num2_len);
	string result_str="";
	int carry = 0;
	//add 0s in beginning to make length equal
	if (num1_len < num2_len)
	{
		for (int i = 0; i < num2_len - num1_len; i++)
		{
			first_num = '0' + first_num;
		}
		num1_len = num2_len;
	}
	else if (num1_len > num2_len)
	{
		for (int i = 0; i < num1_len - num2_len; i++)
		{
			second_num = '0' + second_num;
		}
		num2_len = num1_len;
	}

	//add one by one
	for (int i = 0; i < result_len; i++)
	{
		int num1, num2, curr_result;
		num1 = first_num[num1_len - 1 - i] - '0';
		num2 = second_num[num2_len - 1 - i] - '0';
		num1 = num1 - carry;
		if (num1 < num2)
		{
			carry = 1;
			curr_result = base + num1 - num2;
		}
		else
		{
			carry = 0;
			curr_result = num1 - num2;
		}
		result_str = to_string(curr_result) + result_str;
	}

	//remove all 0s in the beginning
	int breakpoint = result_str.size();
	for (int i = 0; i < breakpoint; i++)
	{
		if (result_str[i] != '0')
		{
			breakpoint = i;
			break;
		}
	}

	result_str = result_str.substr(breakpoint, result_str.size() - breakpoint);
	return result_str;
}

string convertBase(int number, int base, string result)
{
	if (number < base)
	{
		return to_string(number);
	}
	else
	{
		int x = number % base;
		number = number / base;
		result = convertBase(number, base, result);
		result = result + to_string(x);
	}
	return result;
}


string Karatsuba(string first_num, string second_num, int base)
{

	int strlen1 = first_num.size();
	int strlen2 = second_num.size();
	if (strlen1 < strlen2)
	{
		for (int i = 0; i < strlen2 - strlen1; i++)
		{
			first_num = '0' + first_num;
		}
	}
	else if (strlen1 > strlen2)
	{
		for (int i = 0; i < strlen1 - strlen2; i++)
		{
			second_num = '0' + second_num;
		}
	}

	//return a string with base mutiplication
	if (first_num.size() == 1 && second_num.size() == 1)
	{
		int num1 = first_num[0] - '0';
		int num2 = second_num[0] - '0';
		int mul = num1 * num2;
		string result = "";
		result = convertBase(mul, base, result);
		return result;
	}
	else
	{
		int mid = first_num.size() / 2;
		string a1 = first_num.substr(0, mid);
		string a0 = first_num.substr(mid, first_num.size() - mid);
		string b1 = second_num.substr(0, mid);
		string b0 = second_num.substr(mid, second_num.size() - mid);
		int k = first_num.size() - mid;
		
		string a1b1 = Karatsuba(a1, b1,base);
		string a1_a0 = addition(a1, a0, base);
		string b1_b0 = addition(b1, b0, base);
		string a0b0 =Karatsuba(a0, b0, base);

		string part1 = a1b1;
		for (int i =0;i<2*k;i++){
			part1 =part1 +"0";
		}

		string part2 = Karatsuba(a1_a0, b1_b0, base);
		string part3 = addition(a1b1, a0b0,base);
		string part_mid = substraction(part2,part3,base);
		for (int i =0;i<k;i++){
			part_mid =part_mid +"0";
		}

		string part4 = a0b0;

		string result = part1;
		result = addition(result,part_mid,base);
		result = addition(result,part4,base);
		return result;

	}

	return "0";
}



int main()
{
	string first_num, second_num, base;
	cin >> first_num >> second_num >> base;
	int base_int = stoi(base);
	// cout << substraction(first_num, second_num, base_int)<<endl;
	cout << addition(first_num, second_num, base_int)<<" "<<Karatsuba(first_num, second_num, base_int)<<endl;
	return 0;
}
