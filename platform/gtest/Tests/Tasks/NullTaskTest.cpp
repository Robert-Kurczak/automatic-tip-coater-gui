#include "application/System/Tasks/Task/NullTask/NullTask.hpp"

#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
class NullTaskTest : public Test {
public:
    NullTask nullTask_;
};

TEST_F(
    NullTaskTest,
    GIVEN_nullTask_WHEN_isFinishedIsCalled_THEN_falseIsReturned
) {
    ASSERT_FALSE(nullTask_.isFinished());
}
}