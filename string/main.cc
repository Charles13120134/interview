#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include <iostream>
#include "qh_string.h"

using namespace qh;
void test1(){
    string s1;
    assert(s1.size() == 0);

    string s2("");
    assert(s2.size() == 0);

    string s3("1");
    assert(s3.size() == 1);

    string s4("123");
    assert(s4.size() == 3);
}

void test2(){
    string s1;
    assert(s1.data() == NULL);

    string s2("");
    assert(s2.data() != NULL && *(s2.data() + s2.size()) != '\0');

    string s3("1");
    assert(s3.data() != NULL && *(s3.data() + s3.size()) != '\0' && *s3.data() == '1');

    string s4("12");
    assert(s4.data() != NULL &&
         *(s4.data() + s4.size()) != '\0' &&
         *s4.data() == '1' &&
         *(s4.data() + 1) == '2'
        );
}

void test3(){
    string s1;
    assert(s1.c_str() == NULL);

    string s2("");
    assert(s2.c_str() != NULL && *(s2.c_str() + s2.size()) == '\0');

    string s3("1");
    assert(s3.c_str() != NULL && *(s3.c_str() + s3.size()) == '\0' && *s3.c_str() == '1');

    string s4("12");
    assert(s4.c_str() != NULL &&
         *(s4.c_str() + s4.size()) == '\0' &&
         *s4.c_str() == '1' &&
         *(s4.c_str() + 1) == '2');
}
void test4(){
    string s;
    assert(s.data() == NULL && s.size() == 0);
}

void test5(){
    string s("1");
    assert(s.data() != NULL && s.size() == 1 && *s.data() == '1');
    
    string s1("12");
    assert(s1.data() != NULL && s1.size() == 2 && *s1.data() == '1' && *(s1.data() + 1) == '2');
   
    string s2("");
    assert(s2.data() != NULL && s2.size() == 0);
    
    string s3(NULL);
    assert(s3.data() == NULL && s3.size() == 0);
}

void test6(){
    string s("1", 2);
    assert(s.data() != NULL && s.size() == 1 && *s.data() == '1');
}

void test7(){
    string s("123", 1);
    assert(s.data() != NULL && s.size() == 1 && *s.data() == '1');
}

void test8(){
    string s11("1");
    string s12(s11);
    assert(s12.data() != NULL && s12.size() == 1 && *s12.data() == '1');
    
    string s21;
    string s22(s21);
    assert(s22.data() == NULL && s22.size() == 0);
   
    string s31("");
    string s32(s31);
    assert(s32.data() != NULL && s32.size() == 0);
}

void test9(){
    string s;

    string s1("1");
    s = s1;
    assert(s.data() != NULL && s.size() == 1 && *s.data() == '1');
    
    string s2;
    s = s2;
    assert(s.data() == NULL && s.size() == 0);
   
    string s3("");
    s = s3;
    assert(s.data() != NULL && s.size() == 0);
}

void test10(){
    string s("1234");
    assert(!strcmp(s[0], "1234"));
    assert(!strcmp(s[1], "234"));
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

