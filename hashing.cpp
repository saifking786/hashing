#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Hash {
    const int MOD = 1e9 + 7, BASE1 = 5689, BASE2 = 8861;
    vector<pair<int, int>> hashes, Pow;

    Hash(string s) {
        hashes.assign(s.size() + 1, {0, 0});
        Pow.assign(s.size() + 1, {1, 1});

        for (int i = 0; i < s.size(); i++) {
            hashes[i + 1] = {
                (1ll * hashes[i].first * BASE1 + s[i] - 'a' + 1) % MOD,
                (1ll * hashes[i].second * BASE2 + s[i] - 'a' + 1) % MOD
            };

            Pow[i + 1] = {
                (1ll * Pow[i].first * BASE1) % MOD,
                (1ll * Pow[i].second * BASE2) % MOD
            };
        }
    }

    pair<int, int> get(int l, int r) {
        l++, r++;
        int hash1 = (hashes[r].first - 1ll * hashes[l - 1].first * Pow[r - l + 1].first % MOD + MOD) % MOD;
        int hash2 = (hashes[r].second - 1ll * hashes[l - 1].second * Pow[r - l + 1].second % MOD + MOD) % MOD;
        return {hash1, hash2};
    }
};

int main() {
    // Example usage
    string s = "abbaab";
    Hash h(s);

    // Get hash of substring s[2..4] (i.e., "bab")
    pair<int, int> hash_value = h.get(2, 4); 
    cout << "Hash of 'bab': " << hash_value.first << " " << hash_value.second << endl;

    return 0;
}