project(socky)

include_directories(include)

file(GLOB SOCKY_SRC
        "*.h"
        "*.c"
        "*/*.h"
        "*/*.c"
        )

add_library(socky ${SOCKY_SRC})