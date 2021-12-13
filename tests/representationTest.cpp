#include"../third_party/catch.hpp"
#include"../src/purlong.h"

TEST_CASE("getStringRepr")
{
    auto numberStringRepr = GENERATE(
        "123", "-123",
        "123456789123456789123456",
        "1232613321321897321986216782318672319673286729382637369721362196378621387961273621896387216392167389216382917631" 
    );
    CHECK(PurLong(numberStringRepr).getStringRepr() == numberStringRepr);
}