set(PROJECT_VERSION 0.1.4)
set(PROJECT_LICENSE MPL-2.0)
set(PROJECT_CONTACT tqfx@tqfx.org)
set(PROJECT_DESCRIPTION "An algorithm library based on C/C++ language")
set(PROJECT_HOMEPAGE_URL "https://github.com/tqfx/liba.git")
string(REGEX MATCH "[^.]+\\.[^.]+\\.[^.]+\\.[^.]+" PROJECT_VERSION_TWEAK "${PROJECT_VERSION}")
string(REGEX REPLACE "^[^.]+\\.[^.]+\\.[^.]+\\.([^.]+).*" "\\1" PROJECT_VERSION_TWEAK "${PROJECT_VERSION_TWEAK}")
string(REGEX MATCH "[^.]+\\.[^.]+\\.[^.]+" PROJECT_VERSION_PATCH "${PROJECT_VERSION}")
string(REGEX REPLACE "^[^.]+\\.[^.]+\\.([^.]+).*" "\\1" PROJECT_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
string(REGEX MATCH "[^.]+\\.[^.]+" PROJECT_VERSION_MINOR "${PROJECT_VERSION}")
string(REGEX REPLACE "^[^.]+\\.([^.]+).*" "\\1" PROJECT_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
string(REGEX MATCH "[^.]+" PROJECT_VERSION_MAJOR "${PROJECT_VERSION}")
if(PROJECT_NAME)
  set(${PROJECT_NAME}_VERSION ${PROJECT_VERSION})
  set(${PROJECT_NAME}_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(${PROJECT_NAME}_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(${PROJECT_NAME}_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(${PROJECT_NAME}_VERSION_TWEAK ${PROJECT_VERSION_TWEAK})
endif()
if(PROJECT_NAME)
  set(${PROJECT_NAME}_DESCRIPTION ${PROJECT_DESCRIPTION})
endif()
if(PROJECT_NAME)
  set(${PROJECT_NAME}_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL})
endif()
if(PROJECT_NAME)
  set(${PROJECT_NAME}_LICENSE ${PROJECT_LICENSE})
endif()
if(CMAKE_VERSION VERSION_LESS 3.21)
  if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(PROJECT_IS_TOP_LEVEL 1)
  else()
    set(PROJECT_IS_TOP_LEVEL 0)
  endif()
endif()
if(NOT CMAKE_PROJECT_VERSION_TWEAK AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION_TWEAK ${PROJECT_VERSION_TWEAK} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_VERSION_PATCH AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION_PATCH ${PROJECT_VERSION_PATCH} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_VERSION_MINOR AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION_MINOR ${PROJECT_VERSION_MINOR} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_VERSION_MAJOR AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_HOMEPAGE_URL AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_DESCRIPTION AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_DESCRIPTION ${PROJECT_DESCRIPTION} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
if(NOT CMAKE_PROJECT_VERSION AND PROJECT_IS_TOP_LEVEL)
  set(CMAKE_PROJECT_VERSION ${PROJECT_VERSION} CACHE STATIC "Value Computed by CMake" FORCE)
endif()
set(CPACK_RPM_PACKAGE_LICENSE ${PROJECT_LICENSE})
set(CPACK_PACKAGE_CONTACT ${PROJECT_CONTACT})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
