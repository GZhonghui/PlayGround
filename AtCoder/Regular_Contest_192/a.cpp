#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const int maxn = 200000 + 8;

int n,a[maxn];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        cnt += a[i];
    }

    if(n % 4 == 0) {
        cout << "Yes" << endl;
    } else if(n % 4 == 1 || n % 4 == 3) {
        cout << (cnt >= 1 ? "Yes" : "No") << endl;
    } else if(n % 4 == 2) {
        int ans[2] = {0, 0};
        for(int i = 1; i <= n; i++){
            if(a[i]) {
                ans[i % 2] = 1;
            }
        }
        cout << (ans[0] + ans[1] == 2 ? "Yes" : "No") << endl;
    }

    return 0;
}