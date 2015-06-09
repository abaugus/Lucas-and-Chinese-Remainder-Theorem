#include <bits/stdc++.h>
using namespace std;
long long prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
long long val[50];
long long int phi(long long x)
 {
   	long long int ret = 1,i,pow;
   	for (i = 2; x != 1; i++) 
   	{
    	pow = 1;
     	if(i>sqrt(x))
     		break;
     	while (!(x%i)) 
     	{
       		x /= i;
       		pow *= i;
     	}
     	ret *= (pow - (pow/i));
    }
    if(x!=1)
    	ret*=(x-1);
    return ret;
}
long long modPow(long long a,long long x,long long p) {
    long long res = 1;
    while(x > 0) 
    {
        if( x % 2 != 0) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }
    return res;
}
long long modInverse(long long a,long long p) {
    return modPow(a,phi(p)-1, p);
}
long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
long long SmallC(int n, int r, int MOD)
{
    vector< vector<long long> > C(2,vector<long long> (r+1,0));
 
    for (int i=0; i<=n; i++)
    {
        for (int k=0; k<=r && k<=i; k++)
            if (k==0 || k==i)
                C[i&1][k] = 1;
            else
                C[i&1][k] = (C[(i-1)&1][k-1] + C[(i-1)&1][k])%MOD;
    }
    return C[n&1][r];
}
 
long long Lucas(int n, int m, int p)
{
    if (n==0 && m==0) return 1;
    int ni = n % p;
    int mi = m % p;
    if (mi>ni) return 0;
    return Lucas(n/p, m/p, p) * SmallC(ni, mi, p);
}
 
long long C(int n, int r, int MOD)
{
    return Lucas(n, r, MOD);
}
long long int solve(long long n,long long r,long long p)
{
	long long i,num,count,N,y,ans=0;
	for(i=0;i<15;i++)
	{
		if(p%prime[i]==0)
		{
			num=p;
			count=0;
			while(num%prime[i]==0)
			{
				num/=prime[i];
				++count;
			}
			val[prime[i]]=C(n,r,pow(prime[i],count));
			N=p/pow(prime[i],count);
			y=modInverse(N,pow(prime[i],count));
			ans=(ans+val[prime[i]]*N*y)%p;
		}
	}
	return ans%p;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long int n,r,p,ans;
		cin>>n>>r>>p;
		ans=solve(n,r,p)%p;
		cout<<ans<<endl;
	}
	return 0;
}
