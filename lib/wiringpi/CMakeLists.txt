project(wiringpi)

include_directories(include)

file(GLOB WIRINGPI_SRC
        "*.h"
        "*.c"
        "*/*.h"
        "*/*.c"
        )

add_library(wiringpi ${WIRINGPI_SRC})