#include <iostream>
#include <vector>
#include <stack>
using namespace std;
stack<int> people_stk; stack<int> day_stk;
int schdule[7][31]; int flag[6];
int count_working_day(int people,int day)
{
	int sum=0;
	for(int i = 0;i<=day;i++)
	{
		sum = sum+schdule[people][i];
	}
	return sum;
}