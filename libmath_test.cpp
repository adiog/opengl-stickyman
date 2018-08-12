#include "googletest"
#include "libmath.h"

TEST(libmath, reduce111)
{
    // given
    V3 v = {1,1,1};

    // when
    M33 m = getRotationMatrixReducingYAndX(v);
    V3 r = v * m;

    // then
    EXPECT_EQ(getNorm(v), getNorm(r));
}


GTEST_MAIN()

