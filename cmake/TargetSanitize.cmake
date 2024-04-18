get_cmake_property(ENABLED_LANGUAGES ENABLED_LANGUAGES)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

function(list_append var)
  foreach(arg ${ARGN})
    list(FIND ${var} ${arg} index)
    if(${index} EQUAL -1)
      list(APPEND ${var} ${arg})
    endif()
  endforeach()
  set(${var} ${${var}} PARENT_SCOPE)
endfunction()

macro(sanitize_flag_cx)
  foreach(arg ${ARGN})
    string(REPLACE "+" "x" var ${arg})
    string(REGEX REPLACE "[^A-Za-z0-9_-]+" "-" var ${var})
    set(CMAKE_REQUIRED_FLAGS "${REQUIRED_FLAGS} ${arg}")
    list(FIND ENABLED_LANGUAGES C index)
    if(${index} GREATER -1)
      check_c_compiler_flag(${arg} cx${var})
      if(cx${var})
        list_append(SANITIZE_CX ${arg})
      endif()
    endif()
    list(FIND ENABLED_LANGUAGES CXX index)
    if(${index} GREATER -1)
      check_cxx_compiler_flag(${arg} cx${var})
      if(cx${var})
        list_append(SANITIZE_CX ${arg})
      endif()
    endif()
  endforeach()
  set(CMAKE_REQUIRED_FLAGS)
  set(index)
  set(var)
endmacro()

macro(sanitize_flag_ld)
  foreach(arg ${ARGN})
    string(REPLACE "+" "x" var ${arg})
    string(REGEX REPLACE "[^A-Za-z0-9_-]+" "-" var ${var})
    set(CMAKE_REQUIRED_FLAGS "${REQUIRED_FLAGS} ${arg}")
    list(FIND ENABLED_LANGUAGES C index)
    if(${index} GREATER -1)
      check_c_compiler_flag(${arg} ld${var})
      if(ld${var})
        list_append(SANITIZE_LD ${arg})
      endif()
    endif()
    list(FIND ENABLED_LANGUAGES CXX index)
    if(${index} GREATER -1)
      check_cxx_compiler_flag(${arg} ld${var})
      if(ld${var})
        list_append(SANITIZE_LD ${arg})
      endif()
    endif()
  endforeach()
  set(CMAKE_REQUIRED_FLAGS)
  set(index)
  set(var)
endmacro()

if(
  CMAKE_C_COMPILER_ID MATCHES "GNU|.*[Cc]lang|.*LLVM" OR
  CMAKE_CXX_COMPILER_ID MATCHES "GNU|.*[Cc]lang|.*LLVM"
)
  set(REQUIRED_FLAGS -fsanitize=address)
  sanitize_flag_cx(-fsanitize=address)
  sanitize_flag_cx(-fsanitize=leak)
  sanitize_flag_cx(-fsanitize=undefined)
  sanitize_flag_cx(-fsanitize-recover=all)
  sanitize_flag_cx(-fno-omit-frame-pointer)
  if(
    CMAKE_C_COMPILER_ID MATCHES "GNU" OR
    CMAKE_CXX_COMPILER_ID MATCHES "GNU"
  )
    sanitize_flag_ld(-static-libasan)
    sanitize_flag_ld(-static-liblsan)
    sanitize_flag_ld(-static-libubsan)
  else()
    sanitize_flag_ld(-static-libsan)
  endif()
  set(REQUIRED_FLAGS)
elseif(
  CMAKE_C_COMPILER_ID MATCHES "MSVC" OR
  CMAKE_CXX_COMPILER_ID MATCHES "MSVC"
)
  list_append(SANITIZE_LD /INCREMENTAL:NO)
  sanitize_flag_cx(/fsanitize=address)
endif()

function(target_compile_sanitize)
  set(scope PRIVATE)
  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
    else()
      target_compile_options(${target} ${scope} ${SANITIZE_CX})
    endif()
  endforeach()
endfunction()

function(target_link_sanitize_3_13)
  function(string_append var)
    foreach(arg ${ARGN})
      string(FIND "${${var}}" "${arg}" index)
      if(${index} EQUAL -1)
        string(STRIP "${${var}} ${arg}" ${var})
      endif()
    endforeach()
    set(${var} "${${var}}" PARENT_SCOPE)
  endfunction()
  foreach(target ${ARGN})
    if(TARGET ${target})
      get_property(LINK_FLAGS TARGET ${target} PROPERTY LINK_FLAGS)
      if(MSVC)
        string_append(LINK_FLAGS ${SANITIZE_LD})
      else()
        string_append(LINK_FLAGS ${SANITIZE_CX} ${SANITIZE_LD})
      endif()
      set_property(TARGET ${target} PROPERTY LINK_FLAGS "${LINK_FLAGS}")
    endif()
  endforeach()
endfunction()

function(target_link_sanitize)
  if(CMAKE_VERSION VERSION_LESS 3.13)
    target_link_sanitize_3_13(${ARGN})
    return()
  endif()
  set(scope PRIVATE)
  foreach(target ${ARGN})
    if(target MATCHES "^INTERFACE|PUBLIC|PRIVATE")
      set(scope ${target})
    elseif(MSVC)
      target_link_options(${target} ${scope} ${SANITIZE_LD})
    else()
      target_link_options(${target} ${scope} ${SANITIZE_CX} ${SANITIZE_LD})
    endif()
  endforeach()
endfunction()
