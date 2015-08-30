#include "ini_parser.h"

#include <string.h>
#include <assert.h>
#include <iostream>

void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    const std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    const std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    const std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test4()
{
    qh::INIParser parser;
    if(!parser.Parse(std::string("configure")))
        assert(false);

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    const std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");

}

void test5()
{
    const char* ini_text= "a=1\n[test]\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text))) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    const std::string& a2 = parser.Get("test", "a", NULL);
    assert(a2 == "");

    const std::string b = parser.Get("b", NULL);
    assert(b == "");

    const std::string& b2 = parser.Get("test", "b", NULL);
    assert(b2 == "2");
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}


