#!/bin/bash
cmake .. -G"MinGW Makefiles" \
         -DCMAKE_BUILD_TYPE=RELEASE \
         -DCMAKE_C_COMPILER="gcc" \
         -DCMAKE_CXX_COMPILER="g++" \
         -DCMAKE_CXX_FLAGS="\
             -Wall -Wextra -Wpedantic -Wno-braced-scalar-init \
             -Wno-pragmas -Wno-missing-field-initializers \
             -O3 -DNDEBUG -fallow-store-data-races \
             -fno-math-errno -ffinite-math-only -fno-rounding-math \
             -fno-signaling-nans -fcx-limited-range -fexcess-precision=fast \
             -fno-unsafe-math-optimizations"
