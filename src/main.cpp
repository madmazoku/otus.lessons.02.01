#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/lexical_cast.hpp>

#include "../bin/version.h"

struct xray
{
    xray()
    {
        std::cout << "ctor: " << this << ' ' << __FUNCTION__ << " [" << __FILE__ << ":" << __LINE__ << "]" << std::endl;
    }
    xray(const xray& x)
    {
        std::cout << "copy ctor: " << this << " from " << &x << ' ' << __FUNCTION__ << std::endl;
    }
    ~xray()
    {
        std::cout << "dtor: " << this << ' ' << __FUNCTION__ << std::endl;
    }
    void operator()()
    {
        std::cout << "tick" << std::endl;
    }
};

struct closure
{
    int m_offset;
    closure(const int &offset = 0) : m_offset(offset)
    {

    }
    int operator()(int a, int b)
    {
        return m_offset + a + b;
    }
};

struct closure2
{
    xray m_x;
    closure2(const xray &x) : m_x(x)
    {

    }
    int operator()(int a, int b)
    {
        m_x();
        return a + b;
    }
};

auto min(int a, float b) -> decltype(a + b)
{
    if(a < b)
        return a;
    else
        return b;
}

auto foo()
{
    return std::make_tuple(std::string("as"), std::string("qw"), 1);
}

int main(int argc, const char** argv)
{
    auto console = spdlog::stdout_logger_st("console");
    auto wellcome = std::string("Application started, \"") + argv[0] + "\" version: " + boost::lexical_cast<std::string>(version());
    console->info(wellcome);

    // auto
    std::cout << std::endl << "auto\n";
    auto r = min(2, 1.1);
    std::cout << "max: " << r << " type: " << typeid(r).name() << "\n";

    // offset
    int offset = 100;

    // closure
    auto fc = closure(offset);
    std::cout << "closure\n";
    std::cout << closure(offset)(1,2) << '\n';
    std::cout << fc(3,4) << '\n';

    // lambda
    std::cout << std::endl << "lambda\n";
    auto fl = [offset](int a, int b) {
        return offset + a + b;
    };
    std::cout << [offset](int a, int b) {
        return offset + a + b;
    }(1, 2) << '\n';
    std::cout << fl(3, 4) << '\n';

    // lambda with reference
    std::cout << std::endl << "lambda &offset\n";
    auto fl2 = [&offset](int a, int b) {
        offset += a + b;
    };
    for(auto i = 0; i < 10; i++) {
        std::cout << "# " << i << '\n';
        std::cout << offset << '\n';
        fl2(5,6);
        std::cout << offset << '\n';
    }

    // lambda with all variables
    std::cout << std::endl << "lambda reference\n";
    auto fl3 = [=](int a, int b) {
        return offset + a + b;
    };
    std::cout << fl3(7,8) << '\n';

    // xray
    std::cout << std::endl << "xray\n";
    xray x;

    for(int i = 0; i < 10; i++) {
        closure2 fc2(x);
        auto fl4 = [&x](int a, int b) {
            x();
            return a + b;
        };
        std::cout << "closure: " << fc2(1,i) << '\n';
        std::cout << "lambda: " << fl4(10, i) << '\n';
    }

    // tuple
    auto rt = foo();
    std::cout << "0: " << std::get<0>(rt) << '\n';
    std::cout << "1: " << std::get<1>(rt) << '\n';
    std::cout << "2: " << std::get<2>(rt) << '\n';

    std::string name, surname;
    int age;

    std::tie(name, surname, age) = foo();
    std::cout << "tie> " << "name: \"" << name << "\"; surname: \"" << surname << "\"; age: \"" << age << "\"\n";

    console->info("Application finished successfully.");
    return 0;
}

