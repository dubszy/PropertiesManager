#include "../../include/Properties.hpp"
#include <limits.h>

#include <gtest/gtest.h>

#define TEST_ZERO       0
#define TEST_SCHAR_MIN  -128
#define TEST_SCHAR_MAX  127
#define TEST_UCHAR_MAX  255
#define TEST_SSHORT_MIN -32768
#define TEST_SSHORT_MAX 32767
#define TEST_USHORT_MAX 65535
#define TEST_SINT_MIN   -2147483648
#define TEST_SINT_MAX   2147483647
#define TEST_UINT_MAX   4294967295
#define TEST_SLONG_MIN  -9223372036854775808
#define TEST_SLONG_MAX  9223372036854775807
#define TEST_ULONG_MAX  18446744073709551615

class GetNumberTests {
    void getSCharTest();
    void getUCharTest();
    void getSShortTest();
    void getUShortTest();
    void getSIntTest();
    void getUIntTest();
    void getSLongTest();
    void getULongTest();
    void getSLongLongTest();
    void getULongLongTest();
};

static Properties *props = new Properties("res/testdata/testdata.properties");
static Logger *log = Logger::forClass<GetNumberTests>(LogLevelInfo);

namespace {

class GetNumberTest : public ::testing::Test {

    GetNumberTest() {

    }

    ~GetNumberTest() {

    }

    void SetUp() {

    }

    void TearDown() {

    }
}

TEST(GetSCharTest, SCharMin) {
    EXPECT_EQ(TEST_SCHAR_MIN, props->get("schar.min")->valueAsNumber<signed char>());
}

TEST(GetSCharTest, SCharMax) {
    EXPECT_EQ(TEST_SCHAR_MAX, props->get("schar.max")->valueAsNumber<signed char>());
}

TEST(GetSCharTest, SCharZero) {
    EXPECT_EQ(TEST_ZERO, props->get("schar.zero")->valueAsNumber<signed char>());
}


TEST(GetUCharTest, UCharMin) {
    EXPECT_EQ(TEST_ZERO, props->get("uchar.min")->valueAsNumber<unsigned char>());
}

TEST(GetUCharTest, UCharMax) {
    EXPECT_EQ(TEST_UCHAR_MAX, props->get("uchar.max")->valueAsNumber<unsigned char>());
}

TEST(GetSShortTest, SShortMin) {
    EXPECT_EQ(TEST_SSHORT_MIN, props->get("sshort.min")->valueAsNumber<signed short>());
}

TEST(GetSShortTest, SShortMax) {
    EXPECT_EQ(TEST_SSHORT_MAX, props->get("sshort.max")->valueAsNumber<signed short>());
}

TEST(GetSShortTest, SShortZero) {
    EXPECT_EQ(TEST_ZERO, props->get("sshort.zero")->valueAsNumber<signed short>());
}


TEST(GetUShortTest, UShortMin) {
    EXPECT_EQ(TEST_ZERO, props->get("ushort.min")->valueAsNumber<unsigned short>());
}

TEST(GetUShortTest, UShortMax) {
    EXPECT_EQ(TEST_USHORT_MAX, props->get("ushort.max")->valueAsNumber<unsigned short>());
}


TEST(GetSIntTest, SIntMin) {
    EXPECT_EQ(TEST_SINT_MIN, props->get("sint.min")->valueAsNumber<signed int>());
}

TEST(GetSIntTest, SIntMax) {
    EXPECT_EQ(TEST_SINT_MAX, props->get("sint.max")->valueAsNumber<signed int>());
}

TEST(GetSIntTest, SIntZero) {
    EXPECT_EQ(TEST_ZERO, props->get("sint.zero")->valueAsNumber<signed int>());
}


TEST(GetUIntTest, UIntMin) {
    EXPECT_EQ(TEST_ZERO, props->get("uint.min")->valueAsNumber<unsigned int>());
}

TEST(GetUIntTest, UIntMax) {
    EXPECT_EQ(TEST_UINT_MAX, props->get("uint.max")->valueAsNumber<unsigned int>());
}


TEST(GetSLongTest, SLongMin) {
    EXPECT_EQ(TEST_SLONG_MIN, props->get("slong.min")->valueAsNumber<signed long>());
}

TEST(GetSLongTest, SLongMax) {
    EXPECT_EQ(TEST_SLONG_MAX, props->get("slong.max")->valueAsNumber<signed long>());
}

TEST(GetSLongTest, SLongZero) {
    EXPECT_EQ(TEST_ZERO, props->get("slong.zero")->valueAsNumber<signed long>());
}


TEST(GetULongTest, ULongMin) {
    EXPECT_EQ(TEST_ZERO, props->get("ulong.min")->valueAsNumber<unsigned long>());
}

TEST(GetULongTest, ULongMax) {
    EXPECT_EQ(TEST_ULONG_MAX, props->get("ulong.max")->valueAsNumber<unsigned long>());
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
