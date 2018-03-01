#include <stdio.h>
#include <iostream>
#include "myclass.hpp"
#include "power.h"
#include "conv.h"
#include "strng.h"
#include "print.h"

using namespace std;

int main(int argc, char **argv)
{
  MyClass* myClass = MyClass::create_object();
  myClass->output();
  myClass->setx(100);
  myClass->output();
  myClass->power("-5", "3");
  pr_str("-5^3: ");
  myClass->output();
  myClass->calc("3^6");
  pr_str("3^6: ");
  myClass->output();
  MyClass::destroy_object( myClass );

  pr_num(s2n("215"));
  pr_str(", ");
  pr_num(s2n("-30"));
  pr_str_ln("");
  pr_str_ln("Single line string");

  char buff[64];
  
  sprintf(buff, "2^3: %d", ipower(2,3));
  pr_str_ln(buff);
  const char *p = "12345678";
  sjoin(buff, p, ": ", 20);
  int n = slen(buff);
  scopy(buff + n, p, 20);
  pr_str_ln(buff);
  srev(buff + n);
  pr_str_ln(buff);
  p = "abcdefg";
  sjoin(buff, p, ": ", 20);
  n = slen(buff);
  scopy(buff + n, p, 20);
  srev(buff + n);
  pr_str_ln(buff);
  n2s(buff, 132);
  srev(buff);
  pr_str_ln(buff);
  n2s(buff, -2);
  pr_str_ln(buff);
  return 0;
}

