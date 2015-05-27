###############################################
#
# CMake file to build sample particle library
#
###############################################

SET ( SAMPLE_PARTICLE_SRC
     particle.cpp
)

SET ( SAMPLE_PARTICLE_INC
     particle.hpp
)

ADD_LIBRARY( sample_particle SHARED ${SAMPLE_PARTICLE_SRC} )

SET_TARGET_PROPERTIES(sample_particle
                      PROPERTIES    FRAMEWORK               TRUE
                                    PUBLIC_HEADER           "${SAMPLE_PARTICLE_INC}"
)

INSTALL( TARGETS sample_particle
LIBRARY DESTINATION lib 
ARCHIVE DESTINATION lib
PUBLIC_HEADER DESTINATION include 
)
