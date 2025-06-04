//Make KM great again
//Vengeance
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
using ui = unsigned int;
using ull = unsigned long long;
using ld = long double;

#define YioUChank main()
using ILove = signed;

constexpr int MAX_N = 1e5 + 1;
int n;
struct Rect {
    bool operator ==(const Rect& b) const {
        return d == b.d && r == b.r;
    }

    bool operator >(const Rect& b) const {
        if (d * r == b.d * b.r)
            return d > b.d;

        return d * r > b.d * b.r;
    }

    bool operator >=(const Rect& b) const {
        return (*this == b || *this > b);
    }

    bool operator <(const Rect& b) const {
        if (d * r == b.d * b.r)
            return d < b.d;
        return d * r < b.d * b.r;
    }

    ll d, r;
} a[MAX_N];

ILove YioUChank {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].d >> a[i].r;
    vector<Rect> dp;
    for (int i = 1; i <= n; ++i) {
        int idx = upper_bound(dp.rbegin(), dp.rend(), a[i]) - dp.rbegin() - 1;
        if (idx == -1) dp.push_back(a[i]);
        else {
            int realIdx = dp.size() - idx - 1;
            dp[realIdx] = a[i];
        }
    }

    cout << dp.size();
}

// Author: devtrung
// Created: 02/06/2025 12:40:27