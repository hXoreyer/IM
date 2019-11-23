#ifndef SQL_DO_H
#define SQL_DO_H
#include "../mysql/sql.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;
bool find_email(SQL *s, string user_email);
bool add_email(SQL *s,string user_name, string user_email, string user_pass);
int login(SQL *s,string user_email, string user_pass); // 0-未注册 1-登录成功 2-密码错误


#endif