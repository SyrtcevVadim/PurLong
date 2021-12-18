#include "../third_party/catch.hpp"
#include "../src/purlong.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

TEST_CASE("==")
{
    SECTION("PurLong equality with strings")
    {
        auto strNumber = GENERATE(
        "0",
        "123456789",
        "+123456789",
        "-123456789",
        "1234567891234",
        "+1234567891234",
        "-1234567891234"
        );
        CHECK(PurLong(strNumber)==PurLong(strNumber));
        CHECK(PurLong(strNumber)== string(strNumber));
    }

    SECTION("PurLong equality with integers")
    {
        auto integer = GENERATE(
            0,
            123456789,
            +123456789,
            -123456789,
            1234567891234,
            +1234567891234,
            -1234567891234
        );
        CHECK(PurLong(integer) == integer);
    }
    

    CHECK(PurLong(123)==PurLong("123"));
    CHECK(PurLong(123)==PurLong("+123"));
    CHECK(PurLong(-123)==PurLong("-123"));
    CHECK(PurLong(1234)==PurLong("+1234"));
    CHECK(PurLong("322355855855456756657322355855855456756657322355855855456756657322355855855456756657322355855855456756657644711711710913513314644711711710913513314644711711710913513314644711711710913513314644711711710913513314644711711710913513314")
    ==
    PurLong("322355855855456756657322355855855456756657322355855855456756657322355855855456756657322355855855456756657644711711710913513314644711711710913513314644711711710913513314644711711710913513314644711711710913513314644711711710913513314"));
}

TEST_CASE("!=")
{
    CHECK(PurLong(123) != -123);
    CHECK(PurLong(123) != PurLong("-123"));

    CHECK(PurLong(123)!=PurLong());
    CHECK(PurLong(123)!=PurLong(444));
    CHECK(PurLong(123)!=PurLong("-123"));
}

TEST_CASE(">")
{
    SECTION("Positive numbers")
    {
        auto lValue = GENERATE(
        "1234567891234567891234567890000000000",
        "1000000000000000000000000000000000000000000000000000000000000"
        );
        SECTION("comparison with non-negative numbers")
        {
            auto rValue = GENERATE(
                "0",
                "1",
                "+1223421",
                "1234567891234",
                "1234567891234567891234567",
                "899989988998898989898"
            );
            CHECK(PurLong(lValue) > PurLong(rValue));
        }

        SECTION("comparison with negative numbers")
        {
            auto rValue = GENERATE(
                "-123",
                "-1",
                "-1234567891234567",
                "-1000000000000",
                "-123430912049403722104431029",
                "-43120984321894732131278040973190740937140973242819734"
            );
            CHECK(PurLong(lValue) > PurLong(rValue));
        }
    }
    SECTION("Negative numbers")
    {
        auto lValue = GENERATE(
            "-123456789123456789",
            "-123456789123456789123456789"
        );
        SECTION("comparison with non-negative numbers")
        {
            auto rValue = GENERATE(
            "0",
            "123",
            "123456789"
            );
            CHECK_FALSE(PurLong(lValue) > PurLong(rValue));
            //Неотрицательные числа всегда больше отрицательных
            CHECK(PurLong(rValue) > PurLong(lValue));
        }
    }
}

TEST_CASE("<")
{
    CHECK(PurLong("-123456789123456789123456789123456789123456789123456789") < PurLong("-123"));
    CHECK(PurLong("123456789123456789123456789123456789") < PurLong("123456789123456789123456789123456789123456789123456789"));
    CHECK(PurLong("-1") < PurLong(0));
}

TEST_CASE(">=")
{
    CHECK(PurLong("0") >= PurLong("0"));
    CHECK(PurLong("-123456789") >= PurLong("-123456789"));
    CHECK(PurLong("123456789") >= PurLong("-123456789"));
}

TEST_CASE("<=")
{
    CHECK(PurLong("-123") <= PurLong(0));
    CHECK(PurLong("123") <= PurLong(123));
}