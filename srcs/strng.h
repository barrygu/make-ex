#ifndef __MYSTRN__
#define __MYSTRN__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int slen(const char *s);
int scopy(char *dest, const char *src, int len);
int sjoin(char *dest, const char *s1, const char *s2, int len);
int srev(char *s);
int sfind(const char *s, const char c);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __MYSTRN__
