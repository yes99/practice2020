#include <iostream>
#define MOD 1000000000
using namespace std;
int main() {
    int N, K;
    cin>>N>>K;
    if(K==1) {
        cout<<1<<endl;
        return 0;
    }
    int sum=0, dp[201][201]={0,};
    for(int i=0; i<K; i++) {
        dp[1][i]=1;
    }
    for(int i=2; i<=N; i++) {
        for(int j=0; j<K; j++) {
            for(int k=j; k<K; k++) {
                dp[i][j]+=dp[i-1][k]%MOD;
                dp[i][j]%=MOD;
            }
        }
    }
    for(int i=0; i<K; i++) {
        sum+=dp[N][i];
        sum%=MOD;
    }
    cout<<sum<<endl;
    return 0;
}