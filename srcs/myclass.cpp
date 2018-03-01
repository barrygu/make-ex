#include <stdio.h>
#include "myclass.hpp"
#include "power.h"
#include "conv.h"
#include "strng.h"
#include <iostream>
#include "print.h"

using namespace std;

MyClass* MyClass::create_object(void)
{
  return new MyClass;
}

void MyClass::destroy_object( MyClass* object )
{
  delete object;
}

MyClass::MyClass(void)
{
  x = 20;
}

int MyClass::setx(int v)
{
  int r = x;
  x = v;
  return r;
}

int MyClass::getx(void)
{
  return x;
}

void MyClass::output(void)
{
  pr_num(getx());
  pr_str_ln("");
}

void MyClass::power(const char *s1, const char *s2)
{
  int x = s2n(s1);
  int y = s2n(s2);
  printf("x=%d,y=%d\n", x, y);
  setx(ipower(x, y));
}

void MyClass::calc(const char *ex)
{
  char s1[10], s2[10];
  int n = sfind(ex, '^');
  if (n < 0) return;
  scopy(s1, ex, n + 1);
  scopy(s2, ex + n + 1, 10);
  power(s1, s2);
}