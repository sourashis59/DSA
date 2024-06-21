void sieveSPF(int n, vector<int> &spf) {
    spf = vector<int>(n + 1);
    for (int i = 0; i <= n; i++) spf[i] = 1;
    for (int i = 2; i <= n; i++) {
        if (spf[i] == 1) {
            spf[i] = i;
            for (int j = i * i; j <= n; j += i)
                if (spf[j] == 1)
                    spf[j] = i;
        }
    }
}

void primeFactorization(int n, vector<pair<int, int>> &res, vector<int> &spf) {
    while (n > 1) {
        int currentSPF = spf[n];
        int freq = 0;
        while (currentSPF == spf[n]) {
            n = n / currentSPF;
            freq++;
        }
        res.push_back(make_pair(currentSPF, freq));
    }
}
