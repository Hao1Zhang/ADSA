int main()
{
	string first_num, second_num, base;
	cin >> first_num >> second_num >> base;
	int base_int = stoi(base);
	// cout << substraction(first_num, second_num, base_int)<<endl;
	cout << addition(first_num, second_num, base_int)<<" "<<Karatsuba(first_num, second_num, base_int)<<endl;
	return 0;
}