#ifndef BMG_OPEN_NI_UTIL_H_
#define BMG_OPEN_NI_UTIL_H_

#include <functional>
#include <XnCppWrapper.h>

namespace bmg {

void OnError(XnStatus status, std::function<void()> func) {
  if (status != XN_STATUS_OK) {
    func();
  }
}

// ~~ bmg::
}

#endif