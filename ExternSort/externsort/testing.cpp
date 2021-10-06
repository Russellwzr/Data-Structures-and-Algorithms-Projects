#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("test.txt","w",stdout);
	int a[100010];
	int idx=0,n;
	while(cin>>n){
		a[idx++]=n;
	}
	sort(a,a+idx);
	for(int i=0;i<idx;i++){
		cout<<a[i]<<endl;
	}
	return 0;
}
