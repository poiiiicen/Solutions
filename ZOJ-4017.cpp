#include <iostream>
#include <vector>
#include <queue>

int main() {
    int T;
    std::cin >> T;
    for (; T--;) {
        int n, m;
        char x;
        std::vector<int> disk;
        std::cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> x;
                if (x == '0') {
                    disk.push_back(0);
                } else if (x == '1') {
                    disk.push_back(1);
                } else {
                    disk.push_back(-1);
                }
            }
        }

        int l, r;
        l = r = -1;
        for (int i = 0; i < m; ++i) {
            if (disk[i] == -1) {
                if (l == -1) l = i;
                else {
                    r = i;
                    break;
                }
            }
        }

        std::vector<int> val[2];
        for (int i = 0, v; i < n; ++i) {
            std::cin >> x;
            v = 0;
            for (int j = 0; j < m; ++j) {
                if (disk[i * m + j] != -1) {
                    v ^= disk[i * m + j];
                }
            }
            if (x == '0') val[0].push_back(v);
            else val[0].push_back(v ^ 1);
        }
        for (int i = 0, v; i < n; ++i) {
            std::cin >> x;
            v = 0;
            for (int j = 0; j < m; ++j) {
                if (disk[((n + i - j) % n + n) % n * m + j] != -1) {
                    v ^= disk[((n + i - j) % n + n) % n * m + j];
                }
            }
            if (x == '0') val[1].push_back(v);
            else val[1].push_back(v ^ 1);
        }

        std::vector<bool> used(static_cast<unsigned long long int>(2 * n), false);
        std::vector<int> bo(static_cast<unsigned long long int>(2 * n));
        std::vector<int> cnt[2];
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                used[i] = true;
                bo[i] = 0;
                cnt[0].push_back(1);
                cnt[1].push_back(0);
                std::queue<int> que;
                int tmp;
                que.push(i);
                while (!que.empty()) {
                    tmp = que.front();
                    que.pop();
                    if (!used[tmp + n]) {
                        used[tmp + n] = true;
                        bo[tmp + n] = val[0][tmp] ^ bo[tmp];
                        cnt[bo[tmp + n]][cnt[bo[tmp + n]].size() - 1]++;
                        if (!used[((tmp + r - l + n) % n + n) % n]) {
                            used[((tmp + r - l + n) % n + n) % n] = true;
                            bo[((tmp + r - l + n) % n + n) % n] = val[1][(tmp + r) % n] ^ bo[tmp + n];
                            cnt[bo[((tmp + r - l + n) % n + n) % n]][cnt[bo[((tmp + r - l + n) % n + n) % n]].size() - 1]++;
                            que.push(((tmp + r - l + n) % n + n) % n);
                        } else if (bo[((tmp + r - l + n) % n + n) % n] ^ bo[tmp + n] != val[1][(tmp + r) % n]) {
                            std::cout << "No Solution\n";
                            flag = false;
                            break;
                        }
                    } else if (bo[tmp + n] ^ bo[tmp] != val[0][tmp]) {
                        std::cout << "No Solution\n";
                        flag = false;
                        break;
                    }
                    if (!used[((tmp + l - r + n) % n + n) % n + n]) {
                        used[((tmp + l - r + n) % n + n) % n + n] = true;
                        bo[((tmp + l - r + n) % n + n) % n + n] = val[1][(tmp + l) % n] ^ bo[tmp];
                        cnt[bo[((tmp + l - r + n) % n + n) % n + n]][cnt[bo[((tmp + l - r + n) % n + n) % n + n]].size() - 1]++;
                        if (!used[((tmp + l - r + n) % n + n) % n]) {
                            used[((tmp + l - r + n) % n + n) % n] = true;
                            bo[((tmp + l - r + n) % n + n) % n] = val[0][((tmp + l - r + n) % n + n) % n] ^ bo[((tmp + l - r + n) % n + n) % n + n];
                            cnt[bo[((tmp + l - r + n) % n + n) % n]][cnt[bo[((tmp + l - r + n) % n + n) % n]].size() - 1]++;
                            que.push(((tmp + l - r + n) % n + n) % n);
                        } else if (bo[((tmp + l - r + n) % n + n) % n] ^ bo[((tmp + l - r + n) % n + n) % n + n] != val[0][((tmp + l - r + n) % n + n) % n]) {
                            std::cout << "No Solution\n";
                            flag = false;
                            break;
                        }
                    } else if (bo[((tmp + l - r + n) % n + n) % n + n] ^ bo[tmp] != val[1][(tmp + l) % n]) {
                        std::cout << "No Solution\n";
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
            }
        }
        if (!flag) continue;

        int min = 0, max = 0;
        for (int i = 0; i < cnt[0].size(); ++i) {
            if (cnt[0][i] > cnt[1][i]) {
                max += cnt[0][i];
                min += cnt[1][i];
            } else {
                max += cnt[1][i];
                min += cnt[0][i];
            }
        }
        std::cout << min << " " << max << "\n";
    }
    return 0;
}
