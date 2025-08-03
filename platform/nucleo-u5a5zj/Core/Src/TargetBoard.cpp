#include "TargetBoard.hpp"

namespace ATC {
TargetBoard::TargetBoard() : Board(targetDevices_, uartLogger) {}

TargetBoard& TargetBoard::getBoard() {
    static TargetBoard board;
    return board;
}

};