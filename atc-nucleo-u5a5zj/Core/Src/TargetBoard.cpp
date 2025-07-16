#include "TargetBoard.hpp"

namespace ATC {
    TargetBoard::TargetBoard() : Board(targetDevices_) {}


TargetBoard& TargetBoard::getBoard() {
    static TargetBoard board;
    return board;
}

};