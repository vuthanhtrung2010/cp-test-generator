#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using ll = long long;

// Random number generation, random device is optional to XOR with the seed
mt19937_64 Rand(chrono::steady_clock::now().time_since_epoch().count() ^ random_device{}());

ll rand(ll l, ll r) {
    return Rand() % (r - l + 1) + l;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n = rand(1, 1e3);
    cout << n << "\n";
    for (int i = 1; i <= n; ++i) {
        ll d = rand(1, 1e9);
        ll r = rand(1, 1e9);
        cout << d << " " << r << "\n";
    }
}