void sieveOfEratosthenes(long long n, vector<bool> &prime) {
    prime = vector<bool>(n + 1);
    for (long long i = 0; i <= n; i++)
        prime[i] = true;

    prime[0] = prime[1] = false;
    for (long long i = 2; i * i <= n; i++) {
        if (prime[i]){
            for (long long j = i * i; j <= n; j += i)
                prime[j] = false;
        }
    }
}


