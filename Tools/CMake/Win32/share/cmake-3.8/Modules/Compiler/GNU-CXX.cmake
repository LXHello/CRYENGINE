include(Compiler/GNU)
__compiler_gnu(CXX)

if (WIN32)
  if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6)
    set(CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY_INLINES_HIDDEN "-fno-keep-inline-dllexport")
  endif()
else()
  if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.0)
    set(CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY_INLINES_HIDDEN "-fvisibility-inlines-hidden")
  endif()
endif()

if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.4)
  # Supported since 4.3
  set(CMAKE_CXX98_STANDARD_COMPILE_OPTION "-std=c++98")
  set(CMAKE_CXX98_EXTENSION_COMPILE_OPTION "-std=gnu++98")
endif()

if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
  set(CMAKE_CXX11_STANDARD_COMPILE_OPTION "-std=c++11")
  set(CMAKE_CXX11_EXTENSION_COMPILE_OPTION "-std=gnu++11")
elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.4)
  # 4.3 supports 0x variants
  set(CMAKE_CXX11_STANDARD_COMPILE_OPTION "-std=c++0x")
  set(CMAKE_CXX11_EXTENSION_COMPILE_OPTION "-std=gnu++0x")
endif()

if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
  set(CMAKE_CXX14_STANDARD_COMPILE_OPTION "-std=c++14")
  set(CMAKE_CXX14_EXTENSION_COMPILE_OPTION "-std=gnu++14")
elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
  set(CMAKE_CXX14_STANDARD_COMPILE_OPTION "-std=c++1y")
  set(CMAKE_CXX14_EXTENSION_COMPILE_OPTION "-std=gnu++1y")
endif()

if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
  set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++1z")
  set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++1z")
endif()

if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.4)
  if (NOT CMAKE_CXX_COMPILER_FORCED)
    if (NOT CMAKE_CXX_STANDARD_COMPUTED_DEFAULT)
      message(FATAL_ERROR "CMAKE_CXX_STANDARD_COMPUTED_DEFAULT should be set for ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER}) version ${CMAKE_CXX_COMPILER_VERSION}")
    endif()
    set(CMAKE_CXX_STANDARD_DEFAULT ${CMAKE_CXX_STANDARD_COMPUTED_DEFAULT})
  elseif(NOT DEFINED CMAKE_CXX_STANDARD_DEFAULT)
    # Compiler id was forced so just guess the default standard level.
    set(CMAKE_CXX_STANDARD_DEFAULT 98)
  endif()
endif()

macro(cmake_record_cxx_compile_features)
  set(_result 0)
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.4)
    if(_result EQUAL 0 AND CMAKE_CXX17_STANDARD_COMPILE_OPTION)
      _record_compiler_features_cxx(17)
    endif()
    if(_result EQUAL 0 AND CMAKE_CXX14_STANDARD_COMPILE_OPTION)
      _record_compiler_features_cxx(14)
    endif()
    if (_result EQUAL 0)
      _record_compiler_features_cxx(11)
    endif()
    if (_result EQUAL 0)
      _record_compiler_features_cxx(98)
    endif()
  endif()
endmacro()