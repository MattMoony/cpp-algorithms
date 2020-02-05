void quick_sort(int* a, int left, int right) {
    int p = a[right];
    int l = left, r = right;

    while (l < r) {
        while (l < r && a[l] <= p) l++;
        while (r > l && a[r] >= p) r--;
        int t = a[l];
        a[l] = a[r];
        a[r] = t;
    }

    a[right] = a[l];
    a[l] = p;

    if (l - 1 - left > 0) quick_sort(a, left, l-1);
    if (right - l - 1 > 0) quick_sort(a, l+1, right);
}
