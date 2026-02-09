#include "application/System/Drivers/LoggerSink/UartLoggerSink/UartLoggerSink.hpp"

#include "platform/gtest/Mocks/Ports/UartMock.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace testing;

namespace ATC {
MATCHER_P(SpanStrEq, expected, "") {
    return std::string_view(arg.data(), arg.size()) == expected;
}

class UartLoggerSinkTest : public Test {
public:
    UartMock uartMock_ {};

    UartLoggerSink uartLoggerSink_ {uartMock_};
};

TEST_F(
    UartLoggerSinkTest,
    GIVEN_uartLoggerSink_WHEN_textIsPiped_THEN_textIsForwarded
) {
    const std::string testLabel = "[LABEL]";
    const std::string testString = " test string";

    {
        InSequence sequence;
        EXPECT_CALL(uartMock_, write(SpanStrEq(testLabel)));
        EXPECT_CALL(uartMock_, write(SpanStrEq(testString)));
    }

    uartLoggerSink_ << testLabel << testString;
}
}