#ifndef __MYCLASS_HPP__
#define __MYCLASS_HPP__

#ifdef __cplusplus
class MyClass
{
public:
  MyClass(void);
  virtual ~MyClass() {};

  static MyClass * create_object(void);
  static void destroy_object(MyClass *object);

  /* use virtual otherwise linker will try to perform static linkage */
  virtual void output(void);
  int setx(int v);
  int getx(void);
  void power(const char *s1, const char *s2);
  void calc(const char *ex);
private:
  int x;
};

extern "C" {
#endif // __cplusplus


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __MYCLASS_HPP__

