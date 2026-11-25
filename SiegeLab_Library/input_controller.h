#ifndef SIEGE_LAB_INPUT_CONTROLLER_H_
#define SIEGE_LAB_INPUT_CONTROLLER_H_

#include "input_snapshot.h"

namespace siege_lab
{
    class InputController
    {
    public:
        InputSnapshot Capture() const;
    };
}

#endif