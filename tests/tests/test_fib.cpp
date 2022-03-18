#include <gtest/gtest.h>

extern "C" {
    #include "food.h"
}


TEST(Input, TestInputDouble) {
    istream = fopen("../test_1/test_1.in", "r");
    ostream = fopen("/dev/null", "w");
    ostream_result = fopen("../test_1/test_1.out", "w");
    main_logic();
//    EXPECT_EQ(0, );
}

TEST(Fib, TestBasics) {
    EXPECT_EQ(1, fib(1));
//    EXPECT_EQ(1, fib(2));
}

TEST(Fib, Test10) {
    EXPECT_EQ(55, fib(10));
}
