# Locate FMOD
# This module defines FMOD_FOUND, FMOD_INCLUDE_DIR and FMOD_LIBRARIES standard variables

SET( FMOD_STUDIO_SEARCH_PATHS
        ${CMAKE_SOURCE_DIR}/FMOD/studio
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
)

FIND_PATH( FMOD_STUDIO_INCLUDE_DIR
        NAMES fmod_studio.h
        HINTS
        $ENV{FMOD_STUDIO_DIR}
        ${FMOD_STUDIO_DIR}
        PATH_SUFFIXES inc include
        PATHS ${FMOD_STUDIO_SEARCH_PATHS}
)

FIND_LIBRARY( FMOD_STUDIO_LIBRARY
        NAMES fmodstudio fmodstudioL libfmodstudio libfmodstudioL
        HINTS
        $ENV{FMOD_STUDIO_DIR}
        ${FMOD_STUDIO_DIR}
        PATH_SUFFIXES lib/x86 lib/x64
        PATHS ${FMOD_STUDIO_SEARCH_PATHS}
)

IF( FMOD_STUDIO_LIBRARY )
    SET( FMOD_STUDIO_LIBRARIES "${FMOD_STUDIO_LIBRARY}")		# Could add "general" keyword, but it is optional
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set FMOD_FOUND to TRUE if all listed variables are TRUE
INCLUDE( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( FMOD_STUDIO DEFAULT_MSG FMOD_STUDIO_LIBRARIES FMOD_STUDIO_INCLUDE_DIR )