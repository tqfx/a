macro(install_libtool_version version)
  string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]).*" "\\1" patch "${version}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9]).*" "\\1" minor "${version}")
  string(REGEX REPLACE "^([0-9]).*" "\\1" major "${version}")
  math(EXPR LT_CURRENT "0${major}+0${minor}")
  math(EXPR LT_REVISION "0${patch}")
  math(EXPR LT_AGE "0${minor}")
endmacro()
function(install_libtool)
  set(one_value_keywords "CURRENT;AGE;REVISION;INSTALLED;SHOULDNOTLINK;DLOPEN;DLPREOPEN;LIBDIR")
  set(multi_value_keywords "TARGETS;DEPENDENCY_LIBS;WEAK_LIBRARY_NAMES;INHERITED_LINKER_FLAGS")
  cmake_parse_arguments(LT "" "${one_value_keywords}" "${multi_value_keywords}" ${ARGN})
  list(APPEND LT_TARGETS ${LT_UNPARSED_ARGUMENTS})
  if(NOT DEFINED LT_INSTALLED OR LT_INSTALLED)
    set(LT_INSTALLED yes)
  else()
    set(LT_INSTALLED no)
  endif()
  if(NOT DEFINED LT_SHOULDNOTLINK OR LT_SHOULDNOTLINK)
    set(LT_SHOULDNOTLINK yes)
  else()
    set(LT_SHOULDNOTLINK no)
  endif()
  if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib)
  endif()
  if(NOT DEFINED LT_LIBDIR)
    set(LT_LIBDIR ${CMAKE_INSTALL_LIBDIR})
  elseif(IS_ABSOLUTE ${LT_LIBDIR})
    get_filename_component(LT_LIBDIR ${LT_LIBDIR} NAME)
  endif()
  foreach(target ${LT_TARGETS})
    get_property(name TARGET ${target} PROPERTY OUTPUT_NAME)
    if(NOT name)
      set(name ${CMAKE_STATIC_LIBRARY_PREFIX}${target})
    else()
      set(name ${CMAKE_STATIC_LIBRARY_PREFIX}${name})
    endif()
    get_property(type TARGET ${target} PROPERTY TYPE)
    if(type MATCHES "(SHARED|MODULE)_LIBRARY")
      if(UNIX)
        set(LT_DLNAME $<TARGET_FILE_NAME:${target}>)
      else()
        set(LT_DLNAME $<TARGET_LINKER_FILE_NAME:${target}>)
      endif()
      list(APPEND LT_LIBRARY_NAMES ${LT_DLNAME})
      get_property(version TARGET ${target} PROPERTY VERSION)
      get_property(soversion TARGET ${target} PROPERTY SOVERSION)
      if(UNIX AND (DEFINED version AND DEFINED soversion))
        set(LT_DLNAME $<TARGET_SONAME_FILE_NAME:${target}>)
        list(APPEND LT_LIBRARY_NAMES $<TARGET_SONAME_FILE_NAME:${target}>)
      endif()
      if(UNIX AND (DEFINED version OR DEFINED soversion))
        list(APPEND LT_LIBRARY_NAMES $<TARGET_LINKER_FILE_NAME:${target}>)
      endif()
      install_libtool_version(${version})
    elseif(type MATCHES "STATIC_LIBRARY")
      set(LT_OLD_LIBRARY $<TARGET_FILE_NAME:${target}>)
      if(NOT DEFINED LT_DLNAME)
        set(LT_DLNAME $<TARGET_FILE_NAME:${target}>)
      endif()
    endif()
  endforeach()
  file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${name}.la
  CONTENT "# ${name}.la - a libtool library file
# Generated by CMake ${CMAKE_VERSION} (like GNU libtool)\n#
# Please DO NOT delete this file!\n# It is necessary for linking the library.\n
# The name that we can dlopen(3).\ndlname='${LT_DLNAME}'\n
# Names of this library.\nlibrary_names='$<JOIN:${LT_LIBRARY_NAMES}, >'\n
# The name of the static archive.\nold_library='${LT_OLD_LIBRARY}'\n
# Linker flags that cannot go in dependency_libs.\ninherited_linker_flags='$<JOIN:${LT_INHERITED_LINKER_FLAGS}, >'\n
# Libraries that this one depends upon.\ndependency_libs='$<JOIN:${LT_DEPENDENCY_LIBS}, >'\n
# Names of additional weak libraries provided by this library\nweak_library_names='$<JOIN:${WEAK_LIBRARY_NAMES}, >'\n
# Version information for ${name}.\ncurrent=${LT_CURRENT}\nage=${LT_AGE}\nrevision=${LT_REVISION}\n
# Is this an already installed library?\ninstalled=${LT_INSTALLED}\n
# Should we warn about portability when linking against -modules?\nshouldnotlink=${LT_SHOULDNOTLINK}\n
# Files to dlopen/dlpreopen\ndlopen='${LD_DLOPEN}'\ndlpreopen='${LD_DLPREOPEN}'\n
# Directory that this library needs to be installed in:\nlibdir='${CMAKE_INSTALL_PREFIX}/${LT_LIBDIR}'
")
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${name}.la DESTINATION ${LT_LIBDIR})
endfunction()
