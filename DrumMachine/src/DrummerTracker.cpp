#include "DrummerTracker.h"

#include <iostream>

DrummerTracker::DrummerTracker(xn::UserGenerator& user_generator)
  : HumanTracker(XN_SKEL_PROFILE_ALL, user_generator)
{
}
