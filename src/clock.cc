#include "clock.h"

#include <errno.h>
#include <time.h>

namespace RPiClock {

    int32_t setDelayNs(const int32_t durationNs) {
        const int32_t startNs = getNowNs();

        if (startNs == -1) {
            return -1;
        }

        while (1) {
            int32_t stopNs = getNowNs();

            if (stopNs == -1) {
                return -1;
            }

            if (getDurationNs(startNs, stopNs) >= durationNs) {
                break;
            }
        }

        return 0;
    }

    int32_t getDurationNs(const int32_t startNs, const int32_t stopNs) {
        int32_t durationNs = stopNs - startNs;

        if (durationNs < 0) {
            durationNs += 1000000000;
        }

        return durationNs;
    }

    int32_t getNowNs(void) {
#ifndef __MACH__
        struct timespec now;

        if (clock_gettime(CLOCK_REALTIME, &now) == -1) {
            return -1;
        }

        return now.tv_nsec;
#else
        errno = EPERM;

        return -1;
#endif
    }
}
