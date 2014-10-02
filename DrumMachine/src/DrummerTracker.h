#pragma once

#include "HumanTracker.h"
#include <XnCppWrapper.h>

#include <iostream>

class DrummerTracker : public HumanTracker
{
public:
  DrummerTracker(xn::UserGenerator& user_generator);
  ~DrummerTracker() {};

private:
};
