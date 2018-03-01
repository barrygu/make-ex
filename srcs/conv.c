#include "strng.h"
#include "power.h"

int s2n(const char *s)
{
    int i, n = 0, len = slen(s);
    const char *p = s + len - 1;
    for (i = 0; i < len; i++, p--) {
        if (p == s && *p == '-') {
            return -n;
        }
        n += (*p - '0') * ipower(10, i);
    }
    return n;
}

int n2s(char *s, int n)
{
    int m;
    char b[20];
    char *p = b;

    if (!s) return -1;
    *s = 0;
    if (n < 0) {
        n = -n;
        *s++ = '-';
        *s = 0;
    }
    do {
        m = n % 10;
        *p++ = '0' + m;
        n /= 10;
    } while (n);
    m = --p - b;
    for (; p >= b;) {
        *s++ = *p--;
    }
    *s = 0;
    return m;
}
