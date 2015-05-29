####################################################
#
# CMakeLists.txt for top-level sample_particle repository
#
#####################################################

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

ENABLE_TESTING()
PROJECT ( SAMPLE_PARTICLE )

# Need C++ 11 for data initialization and stof
list( APPEND CMAKE_CXX_FLAGS "-std=c++11" ${CMAKE_CXX_FLAGS})


###################################
#
# SETUP GTEST DEPENDENCY
# - only build during make check
#
###################################

SET ( GTEST_INC_DIR "" )
ADD_SUBDIRECTORY( gtest EXCLUDE_FROM_ALL )
INCLUDE_DIRECTORIES( ${GTEST_INC_DIR} )

ADD_SUBDIRECTORY(src)

