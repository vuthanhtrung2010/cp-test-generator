#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int n;
int d[N], r[N], a[N];
int cnt, res;
signed main()
{
    //freopen(".inp","r",stdin);
    //freopen(".out","w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> d[i] >> r[i];
        a[i] = d[i] * r[i];
    }
    for(int i = 1; i <= n; i++){
        cnt = 0;
        for(int j = i + 1; j <= n; j++){
            if(a[j] < a[i] || (a[j] == a[i] && d[j] < d[i])) cnt++;
        }
        res = max(res, cnt + 1);
    }
    cout << res;
    return 0;
}