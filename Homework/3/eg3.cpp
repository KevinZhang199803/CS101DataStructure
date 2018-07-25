#include<iostream>
#include<string>

using namespace std;

void binary_print( int &v)
{
    int i;
    int bit;
    int size = sizeof(v)*8;
    //这里的size是输入参数v的位数，直接用32代替也可以，但写成sizeof(v)*8这样更为通用。
    for(i = 0; i < size; i ++)
    {
        bit = v&(1<<(size-i-1));//提取出第i位的值
        if(bit == 0) cout << 0;
        else cout << 1;
        if(i % 4 == 3)cout << ' '; //为了方便阅读输出，在每输出四位后加一个空格
    }
}

int main(){
	string a;

	a = "110994e53d681e5371a9714b02";

	long int i, j;
	j = 0;

	while (j < a.length()){
		i = stoi(a.substr(j, 2), nullptr, 16);
		string temp = to_string(i)
		j += 2;
	}
	

	return 0;
}