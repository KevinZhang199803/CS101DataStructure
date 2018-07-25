#include<iostream>
#include<string>
#include<cctype>


using namespace std;


int rankme(string s)
{
	if (s == "+" || s == "-"){
		return 1;
	}else if (s == "*" || s == "/"){
		return 2;
	}else if (s == "("){
		return 0;
	}
}


int main()
{
	string str_input,temp,exc_str;
	string element[100000] = "";

	getline(cin, str_input);

	//******** split the input string by whitespace*********
	long long int begin = str_input.find(" ", 0);
	while (begin != -1){
		str_input.replace(begin, 1, "");
		begin = str_input.find(" ", begin);
	}
	//wipe out the whitespaces
	//cout << "1";

	long long int i = 0;
	exc_str = "";
	long long int count = 0;
	while (i < str_input.size()){
		if (isdigit(str_input[i]) || str_input.substr(i, 1) == "."){
			while (isdigit(str_input[i]) || str_input.substr(i, 1) == "."){
				exc_str += str_input.substr(i, 1);
				i += 1;
			}
			element[count] = exc_str;
			exc_str = "";
			++count;
		}else{
			element[count] = str_input.substr(i, 1);
			++count;
			++i;

		}
	}
	
	//for (begin = 0; begin < count;++begin) cout << element[begin] << " &" << endl;
	//cout << endl;

	//*************** infix to postfix **********************
	/*

	1.遇到操作数：直接输出（添加到后缀表达式中）
	2.栈为空时，遇到运算符，直接入栈
	3.遇到左括号：将其入栈 f
	4.遇到右括号：执行出栈操作，并将出栈的元素输出，直到弹出栈的是左括号，括号不输出。f
	5.遇到其他运算符：加减乘除：弹出所有优先级大于或者等于该运算符的栈顶元素，然后将该运算符入栈 f
	6.最终将栈中的元素依次出栈，输出。
	*/
	
	string postfix[100000] = "";
	string stack_r[100000];
	long long int pos = 0;
	long long int pos_r = 0;
	
	for (i = 0;i <= count;++i){
		if (element[i] == "("){
			++pos_r;
			stack_r[pos_r] = element[i];
		}else if (element[i] == ")"){
			string mid;
			while (stack_r[pos_r] != "("){
				mid = stack_r[pos_r];
				pos_r = pos_r - 1;
				postfix[pos] = mid;
				++pos;
			}
			pos_r = pos_r - 1;
		}else if (element[i] == "+" || element[i] == "-" || element[i] == "*" || element[i] == "/"){
			string mid;
			while (pos_r != 0 && rankme(stack_r[pos_r]) >= rankme(element[i])){
				mid = stack_r[pos_r];
				pos_r = pos_r - 1;
				postfix[pos] = mid;
				++pos;
			}
			++pos_r;
			stack_r[pos_r] = element[i];
		}else{
			postfix[pos] = element[i];
			++pos;
		}
	}
	while (pos_r != 0){
		string mid;
		mid = stack_r[pos_r];
		pos_r = pos_r - 1;
		postfix[pos] = mid;
		++pos;
	}
	//for (begin = 0; begin < pos;++begin) cout << postfix[begin] << " &" << endl;
	

	//*************** infix to postfix ends *****************

	//*************** Calculation starts ********************
	/*
	从左到右遍历表达式的每个数字和符号，遇到是数字就进栈，遇到是符号，就将处于栈顶两个数字出栈，进行运算，运算结果进栈，一直到最终获得结果。
	*/
	long double cal[100000];
	pos = 0;
	for (i = 0;i < pos;++pos)
	{
		if (element[i] == "+"){
			long double num2 = cal[pos];
			pos = pos - 1;
			long double num1 = cal[pos];
			pos = pos - 1;
			cal[pos] = num1 + num2;
			++pos;
		}else if (element[i] == "-"){
			long double num2 = cal[pos];
			pos = pos - 1;
			long double num1 = cal[pos];
			pos = pos - 1;
			cal[pos] = num1 - num2;
			++pos;
		}else if (element[i] == "*"){
			long double num2 = cal[pos];
			pos = pos - 1;
			long double num1 = cal[pos];
			pos = pos - 1;
			cal[pos] = num1 * num2;
			++pos;
		}else if (element[i] == "/"){
			long double num2 = cal[pos];
			pos = pos - 1;
			long double num1 = cal[pos];
			pos = pos - 1;
			cal[pos] = num1 / num2;
			++pos;
		}else{
			cal[pos] = stod(element[i]);
			++pos;
		}
	}
	cout << cal[0];
	//*************** Calculation ends **********************
	
	return 0;
}