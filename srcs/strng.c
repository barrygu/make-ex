#include "strng.h"
#include "myclass.hpp"

int slen(const char *s) {
    const char *p = s;
    for (; *p; p++) {};
    return p - s;
}
int scopy(char *dest, const char *src, int len)
{
    int n;
    if (!dest || !src) return -1;
    for (n = 0; n < len - 1 && *src; n++) {
        *dest++ = *src++;
    }
    *dest = 0;
    return n;
}
int sjoin(char *dest, const char *s1, const char *s2, int len)
{
    int n;
    if (!dest) return -1;
    if (!(s1 || s2)) return -2;
    if (s1 && !s2) {
        if (dest == s1) return slen(s1);
        return scopy(dest, s1, len);
    }
    if (!s1 && s2) {
        if (dest == s2) return slen(s2);
        return scopy(dest, s2, len);
    }
    if (dest != s1) {
        n = scopy(dest, s1, len);
    } else
        n = slen(s1);
    len -= n;
    dest += n;
    n += scopy(dest, s2, len);
    return n;
}
static void cswap(char *a, char *b)
{
    char c = *a;
    *a = *b;
    *b = c;
}

int srev(char *s)
{
    int n = slen(s);
    char *t = s + n - 1;
    n /= 2;
    for (int i = 0; i < n; i++) {
        cswap(s++, t--);
    }
    return 0;
}

int sfind(const char *s, const char c)
{
    for (int i = 0; *s; i++) {
        if (*s == c) return i;
        s++;
    }
    return -1;
}
