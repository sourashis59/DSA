```cpp
class StringMatcherRabinKarp {
    // large random prime. but dont take too large prime such that overflow happens 
    // in between some computation (before taking mod)
    const long long Q = 30158354233661; 
    const int R; // radix

    const string &s;
    const string &pat;
    int n; // s.size()
    int m; // pat.size()

    long long pat_hash;


    long long posMod(long long x, long long mod) {
        x = x % mod;
        if (x < 0) x += mod;
        return x;
    }

    // computes hash of s[0...len-1]
    long long computeHash(const string &s, int len) {
        long long res = 0;
        for (int i = 0; i < len; ++i) {
            res = ((res * R) % Q + s[i] - 'a') % Q;
        }
        return res;
    }
public:
    StringMatcherRabinKarp(int R, const string &s, const string &pattern): R(R), s(s), pat(pattern) {
        n = s.size();
        m = pat.size();
        // init pattern hash
        pat_hash = computeHash(pat, m);
    }

    vector<int> findAllMatchingIndices() {
        if (n < m) return {};

        // RM1 = R ^ (m - 1)
        long long RM1 = 1;
        for (int i = 0; i < m - 1; ++i) {
            RM1 = (RM1 * R) % Q;
        }

        vector<int> res;
        // roling hash of string s
        long long rhs = computeHash(s, m);
        if (rhs == pat_hash) res.push_back(0);
        for (int i = m; i < n; ++i) {
            // update: 
            // rhs -> rhs - RM1 * s[i - m]
            // rhs -> rhs * R + s[i]
            rhs = (rhs - (RM1 * (s[i - m] - 'a')) % Q);
            rhs = posMod(rhs, Q);
            rhs = ((rhs * R) % Q + (s[i] - 'a')) % Q;

            if (rhs == pat_hash) {
                // monte-carlo version
                // match found
                res.push_back(i - m + 1);
            }
        }
        return res;
    }
};
```
