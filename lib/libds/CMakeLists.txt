project(libds)

include_directories(include)

file(GLOB LIBDS_SRC
        "*/*.hpp"
        "*/*.cpp"
        "*/*/*.hpp"
        "*/*/*.cpp"
        "*/*.h"
        "*/*.c"
        "*/*/*.h"
        "*/*/*.c"
        )

add_library(libds ${LIBDS_SRC})
target_link_libraries(libds socky pthread) #Link socky and pthread to libds