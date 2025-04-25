#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    map<int, vector<pair<int, int>>> m;

    map<int, int> sum;

    for (int i = 0; i < n; i++) {
        int l, c;
        cin >> l >> c;
        sum[c] += l;
        m[c].emplace_back(l, i + 1);
    }

    int min_sum = INT_MAX;
    for (auto& p : sum) {
        min_sum = min(min_sum, p.second);
    }

    int g = -1;
    for (int target = 1; target <= min_sum / 2; target++) {
        bool ok = true;
        for (int color = 1; color <= k; color++) {
            int sz = m[color].size();
            vector<vector<bool>> dp(sz + 1, vector<bool>(target * 2 + 1, false));
            dp[0][0] = true;

            for (int i = 1; i <= sz; i++) {
                int len = m[color][i - 1].first;
                for (int j = 0; j <= target * 2; j++) {
                    dp[i][j] = dp[i - 1][j];
                    if (j >= len && dp[i - 1][j - len]) {
                        dp[i][j] = true;
                    }
                }
            }


            bool found = false;
            for (int i = 1; i <= sz; i++) {
                if (!dp[i][target]) continue;


                vector<bool> used(sz + 1, false);
                int cur = target;
                for (int j = i; j >= 1 && cur > 0; j--) {
                    int len = m[color][j - 1].first;
                    if (cur >= len && dp[j - 1][cur - len]) {
                        used[j] = true;
                        cur -= len;
                    }
                }


                vector<vector<bool>> dp2(sz + 1, vector<bool>(target + 1, false));
                dp2[0][0] = true;
                for (int j = 1; j <= sz; j++) {
                    int len = m[color][j - 1].first;
                    for (int t = 0; t <= target; t++) {
                        dp2[j][t] = dp2[j - 1][t];
                        if (!used[j] && t >= len && dp2[j - 1][t - len]) {
                            dp2[j][t] = true;
                        }
                    }
                }

                if (dp2[sz][target]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                ok = false;
                break;
            }
        }

        if (ok) {
            g = target;
            break;
        }
    }

    if (g == -1) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";


    vector<int> result;
    for (int color = 1; color <= k; color++) {
        int sz = m[color].size();
        vector<vector<bool>> dp(sz + 1, vector<bool>(g + 1, false));
        vector<vector<bool>> take(sz + 1, vector<bool>(g + 1, false));
        dp[0][0] = true;



        for (int i = 1; i <= sz; i++) {
            int len = m[color][i - 1].first;
            for (int j = 0; j <= g; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= len && dp[i - 1][j - len]) {
                    dp[i][j] = true;
                    take[i][j] = true;
                }
            }
        }


        int cur = g;
        for (int i = sz; i >= 1 && cur > 0; i--) {
            if (take[i][cur]) {
                result.push_back(m[color][i - 1].second);
                cur -= m[color][i - 1].first;
            }
        }
    }



    for (int x : result)
        cout << x << " ";
    cout << "\n";

    return 0;
}
