#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int get_next(int i,int q);
stack<int> people_stk; stack<int> day_stk;
int schdule[7][31]; int flag[6];
int pre_schdule[7][31];
int init()
{
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<31;j++)
		{
			pre_schdule[i][j] = -1;
		}
	}
	schdule[0][0] = 1;schdule[0][1] = 1;schdule[0][2] = 0;schdule[0][3] = 1;
	schdule[1][0] = 1;schdule[1][1] = 1;schdule[1][2] = 0;schdule[1][3] = 1;
	schdule[2][0] = 1;schdule[2][1] = 0;schdule[2][2] = 1;schdule[2][3] = 1;
	schdule[3][0] = 1;schdule[3][1] = 0;schdule[3][2] = 1;schdule[3][3] = 1;
	schdule[4][0] = 0;schdule[4][1] = 1;schdule[4][2] = 1;schdule[4][3] = 0;
	schdule[5][0] = 0;schdule[5][1] = 1;schdule[5][2] = 1;schdule[5][3] = 0;
	//pre_schdule[5][25] = 0;
}

int count_working_day(int people,int day)
{
	int sum=0;
	for(int i = 0;i<=day;i++)
	{
		sum = sum+schdule[people][i];
	}
	return sum;
}

int fit_rule(int i)
{
	int max_working = 0;int min_working=32;
	for(int person = 0;person<6;person++)
	{
		int temp= count_working_day(person,i);
		if(temp<min_working){min_working=temp;}
		if(temp>max_working){max_working=temp;}
	}
	if((schdule[0][i]+schdule[1][i]+schdule[2][i]+schdule[3][i]+schdule[4][i]+schdule[5][i]!=4))
		{
			return -1;
		}
		else if(max_working-min_working>1)
		{
			return -1;
		}
		else if((schdule[0][i]+schdule[1][i]==0)||(schdule[1][i]+schdule[2][i]==0)||(schdule[1][i]+schdule[3][i]==0))
		{
			return -1;
		}
		else 
		{
			return 0;
		}
}

int get_next(int day,int people)
{
cout<<"get_next"<<day<<" "<<people<<endl;
if(day<6)
{
	if(pre_schdule[people][day]!=-1)
	{
		schdule[people][day] = pre_schdule[people][day];
	}
	else if(schdule[people][day-4+3] ==0)
	{
		schdule[people][day]=1;
	}
	else if((schdule[people][day-4+1] ==1)&&(schdule[people][day-4+2] ==1)&&(schdule[people][day-4+3] ==1))
	{
		schdule[people][day] = 0;
	}
	else 
	{
		schdule[people][day] = 0;
		people_stk.push(people);
		day_stk.push(day);
	}
}
else
{
	if(pre_schdule[people][day]!=-1)
	{
		schdule[people][day] = pre_schdule[people][day];
	}
	else if(schdule[people][day-4+3] ==0)
	{
		schdule[people][day]=1;
	}
	else if((schdule[people][day-4+1] ==1)&&(schdule[people][day-4+2] ==1)&&(schdule[people][day-4+3] ==1))
	{
		schdule[people][day] = 0;
	}
	else if((schdule[people][day-4-2] ==1)&&\
			(schdule[people][day-4-1] ==1)&&\
			(schdule[people][day-4-0] ==1)&&\
			(schdule[people][day-4+1] ==0)&&\
			(schdule[people][day-4+2] ==1)&&\
			(schdule[people][day-4+3] ==1))
	{
		schdule[people][day] = 0;
	}
	else 
	{
		schdule[people][day] = 0;
		people_stk.push(people);
		day_stk.push(day);
	}
}	
	cout<<schdule[0][day]<<schdule[1][day]<<schdule[2][day]<<schdule[3][day]<<schdule[4][day]<<schdule[5][day]<<" ";
	cout<<"people_stk top and size"<<people_stk.top()<<" "<<people_stk.size()<<" day_stk top and size"<<day_stk.top()<<" "<<day_stk.size()<<endl;
}

int print_schdule()
{
	cout<<"newest schdule as follow "<<endl;
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<6;j++)
		{
			cout<<schdule[j][i];
		}
		cout<<endl;
	}
	cout<<count_working_day(0,31)<<count_working_day(1,31)<<count_working_day(2,31)<<count_working_day(3,31)<<count_working_day(4,31)<<count_working_day(5,31)<<endl;
}

int main(int argc, char const *argv[])
{
	int flag_j=0;
	int input;
	init();
	for(int i = 4;i<30;i++)
	{
		for(int j = flag_j;j<6;j++)
		{
			get_next(i,j);
		}
		flag_j=0;
		int temp = fit_rule(i);
		//cout<<"temp is "<<temp<<endl;
		if(temp ==0)
		{
			print_schdule();
			continue;
		}
		else{
			if(people_stk.size()!=0)
			{
				i = day_stk.top();
				flag_j = people_stk.top();
				people_stk.pop();
				day_stk.pop();
				schdule[flag_j][i]=1;
				flag_j=flag_j+1;
				i=i-1;
			}
			else
			{
				cout<<"no match schedule"<<endl;
				return 0;
			}
			
		}
		// cin>>input;
	}
	return 0;
}	