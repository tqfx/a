set(LUA_RELEASE
  "5.4.6 7d5ea1b9cb6aa0b59ca3dde1c6adcb57ef83a1ba8e5432c0ecd06bf439b3ad88"
  "5.4.5 59df426a3d50ea535a460a452315c4c0d4e1121ba72ff0bdde58c2ef31d6f444"
  "5.4.4 164c7849653b80ae67bec4b7473b884bf5cc8d2dca05653475ec2ed27b9ebf61"
  "5.4.3 f8612276169e3bfcbcfb8f226195bfc6e466fe13042f1076cbde92b7ec96bbfb"
  "5.4.2 11570d97e9d7303c0a59567ed1ac7c648340cd0db10d5fd594c09223ef2f524f"
  "5.4.1 4ba786c3705eb9db6567af29c91a01b81f1c0ac3124fdbf6cd94bdd9e53cca7d"
  "5.4.0 eac0836eb7219e421a96b7ee3692b93f0629e4cdb0c788432e3d10ce9ed47e28"
  "5.3.6 fc5fd69bb8736323f026672b1b7235da613d7177e72558893a0bdcd320466d60"
  "5.3.5 0c2eed3f960446e1a3e4b9a1ca2f3ff893b6ce41942cf54d5dd59ab4b3b058ac"
  "5.3.4 f681aa518233bc407e23acf0f5887c884f17436f000d453b2491a9f11a52400c"
  "5.3.3 5113c06884f7de453ce57702abaac1d618307f33f6789fa870e87a59d772aca2"
  "5.3.2 c740c7bb23a936944e1cc63b7c3c5351a8976d7867c5252c8854f7b2af9da68f"
  "5.3.1 072767aad6cc2e62044a66e8562f51770d941e972dc1e4068ba719cd8bffac17"
  "5.3.0 ae4a5eb2d660515eb191bfe3e061f2b8ffe94dce73d32cfd0de090ddcc0ddb01"
  "5.2.4 b9e2e4aad6789b3b63a056d442f7b39f0ecfca3ae0f1fc0ae4e9614401b69f4b"
  "5.2.3 13c2fb97961381f7d06d5b5cea55b743c163800896fd5c5e2356201d3619002d"
  "5.2.2 3fd67de3f5ed133bf312906082fa524545c6b9e1b952e8215ffbd27113f49f00"
  "5.2.1 64304da87976133196f9e4c15250b70f444467b6ed80d7cfd7b3b982b5177be5"
  "5.2.0 cabe379465aa8e388988073d59b69e76ba0025429d2c1da80821a252cdf6be0d"
  "5.1.5 2640fc56a795f29d28ef15e13c34a47e223960b0240e8cb0a82d9b0738695333"
  "5.1.4 b038e225eaf2a5b57c9bcc35cd13aa8c6c8288ef493d52970c9545074098af3a"
  "5.1.3 6b5df2edaa5e02bf1a2d85e1442b2e329493b30b0c0780f77199d24f087d296d"
  "5.1.2 5cf098c6fe68d3d2d9221904f1017ff0286e4a9cc166a1452a456df9b88b3d9e"
  "5.1.1 c5daeed0a75d8e4dd2328b7c7a69888247868154acbda69110e97d4a6e17d1f0"
)

string(REGEX REPLACE "([^ ]+)[^;]+" "\\1" LUA_VERSION-STRINGS "${LUA_RELEASE}")
list(GET LUA_VERSION-STRINGS 0 LUA_VERSION)
set(LUA_VERSION ${LUA_VERSION} CACHE STRING "specifies building version for lua")
set_property(CACHE LUA_VERSION PROPERTY STRINGS ${LUA_VERSION-STRINGS})

string(REPLACE "." "\\." VERSION "$CACHE{LUA_VERSION}")
string(REGEX MATCH ";${VERSION}[^;]*;" VERSION ";${LUA_VERSION-STRINGS};")
if(NOT VERSION)
  foreach(VERSION ${LUA_VERSION-STRINGS})
    if(LUA_VERSION VERSION_EQUAL VERSION)
      set(LUA_VERSION ${VERSION})
      break()
    endif()
  endforeach()
else()
  list(GET VERSION 1 LUA_VERSION)
endif()
list(FIND LUA_VERSION-STRINGS ${LUA_VERSION} VERSION)
if(${VERSION} EQUAL -1)
  message(FATAL_ERROR "The Lua ${LUA_VERSION} is not supported.")
endif()

string(REPLACE "." "\\." VERSION "${LUA_VERSION}")
set(LUA_SOURCE_DIR ${CMAKE_BINARY_DIR}/lua-${LUA_VERSION})
set(LUA_ARCHIVE_URL http://www.lua.org/ftp/lua-${LUA_VERSION}.tar.gz)
string(REGEX REPLACE ".*${VERSION}[ ]+([^;]+).*" "\\1" LUA_ARCHIVE_HASH "${LUA_RELEASE}")
if(CMAKE_HOST_WIN32)
  file(TO_CMAKE_PATH $ENV{USERPROFILE}/.cache/lua-${LUA_VERSION}.tar.gz LUA_ARCHIVE_TGZ)
else()
  file(TO_CMAKE_PATH $ENV{HOME}/.cache/lua-${LUA_VERSION}.tar.gz LUA_ARCHIVE_TGZ)
endif()

file(GLOB_RECURSE LUA_H ${LUA_SOURCE_DIR}/*lua.h)
if(NOT EXISTS ${LUA_H})
  file(DOWNLOAD ${LUA_ARCHIVE_URL} ${LUA_ARCHIVE_TGZ} EXPECTED_HASH SHA256=${LUA_ARCHIVE_HASH} SHOW_PROGRESS)
  execute_process(WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMAND ${CMAKE_COMMAND} -E tar xf ${LUA_ARCHIVE_TGZ})
endif()
string(REGEX REPLACE "^([0-9]+\\.[0-9]+).*" "${CMAKE_BINARY_DIR}/lua\\1" LUA_BINARY_DIR "${LUA_VERSION}")
file(COPY src/CMakeLists.txt DESTINATION ${LUA_SOURCE_DIR})
