FIND_PATH(ZMQ_INCLUDE_DIR zmq.hpp
        /usr/include
        /usr/local/include
        /usr/local/include/zmq
        )

FIND_LIBRARY(ZMQ_LIBRARY NAMES zmq PATHS
        /usr/lib
        /usr/local/lib
        /usr/local/lib/zmq
        )

# Copy the results to the output variables.
IF (ZMQ_INCLUDE_DIR AND ZMQ_LIBRARY)
    SET(ZMQ_LIBRARIES ${ZMQ_LIBRARY})
    SET(ZMQ_INCLUDE_DIRS ${ZMQ_INCLUDE_DIR})
    MESSAGE(STATUS "Found these zmq libs: ${ZMQ_LIBRARIES}")
ENDIF (ZMQ_INCLUDE_DIR AND ZMQ_LIBRARY)

link_directories( ${ZMQ_INCLUDE_DIR} )