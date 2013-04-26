int ds(int n) {
    while (n > 9)
        n = n % 10 + ds(n/10);
    return n;
}