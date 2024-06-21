///Stores the values of x and y , and returns gcd(a,b)
long long ExtendedEuclidAlgo(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = ExtendedEuclidAlgo(b, a % b, x1, y1);
    x = y1;
    y = x1 - floor(a / b) * y1;
    return gcd;
}

