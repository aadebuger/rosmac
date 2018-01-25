project( rosmac )
cmake_minimum_required( VERSION 2.8 )

# remove compiler checks if you are using VS2010, it supports
#   1. auto
#   2. lambda
#   3. const iterator
# and, sadly, it doesn't support `for(item, cotainer)'
include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "-std=c++11"   COMPILER_SUPPORTS_CXX11 )
check_cxx_compiler_flag( "-std=c++0x"   COMPILER_SUPPORTS_CXX0X )
if( COMPILER_SUPPORTS_CXX11 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )
    else()
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    endif()
elseif( COMPILER_SUPPORTS_CXX0X)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
else()
    # MSVC, On by default (if available)
endif()
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package( Boost  COMPONENTS thread system filesystem regex chrono REQUIRED )
find_package (Log4CXX REQUIRED)    
find_package(Glog REQUIRED)
find_package(GTest REQUIRED)
if (LOG4CXX_FOUND)
#	ADD_DEFINITIONS(-DWITH_LOG4CXX)
	include_directories(${LOG4CXX_INCLUDE_DIR})
	message("Logging to file   : yes")
else()
#	set(LOG4CXX_LIBRARIES "")
	message("Logging to file   : no (install log4cxx-devel)")
endif()


include_directories( ${Boost_INCLUDE_DIR} )
include_directories( deps/ros_comm/clients/roscpp/include)
include_directories( deps/roscpp_core/rostime/include)

include_directories( deps/roscpp_core/cpp_common/include)
include_directories( deps/ros_comm/tools/rosconsole/include )

include_directories( deps/roscpp_core/roscpp_serialization/include)
include_directories( deps/roscpp_core/roscpp_traits/include)

include_directories( deps//ros_comm/utilities/xmlrpcpp/include )
include_directories( deps//ros_comm/utilities/xmlrpcpp/libb64/include )

include_directories( lib)

aux_source_directory(deps/ros_comm/clients/roscpp/src/libros  libros )
aux_source_directory(deps/roscpp_core/rostime/src  rostime )

aux_source_directory(deps/ros_comm/clients/roscpp/src/libros/transport  librostransport )

aux_source_directory(deps//ros_comm/utilities/xmlrpcpp/src  xmlrpcpp )

aux_source_directory(deps//ros_comm/utilities/xmlrpcpp/libb64/src  libb64 )

aux_source_directory(deps/roscpp_core/roscpp_serialization/src  roscpp_serialization )

aux_source_directory(deps/roscpp_core/cpp_common/src  cpp_common )
aux_source_directory(deps/console_bridge/src  console_bridge )

file(GLOB_RECURSE rosconsole "deps/ros_comm/tools/rosconsole/src/rosconsole/*.cpp" )

list(REMOVE_ITEM rosconsole  "deps/ros_comm/tools/rosconsole/src/rosconsole/impl/rosconsole_glog.cpp")





add_library( libroslib  ${libros}   ) 
add_library( librostransportlib  ${librostransport}   ) 

add_library( rostimelib  ${rostime} ) 

add_library( xmlrpcpplib  ${xmlrpcpp} ) 

add_library( libb64 ${libb64} ) 

add_library( roscpp_serialization  ${roscpp_serialization} ) 

add_library( cpp_common ${cpp_common} ) 

add_library( console_bridge ${console_bridge} )

add_library( rosconsole ${rosconsole} )


message(STATUS "${GLOG_LIBRARY}")

add_executable( ${PROJECT_NAME} main.cpp )
target_link_libraries( ${PROJECT_NAME}  libroslib   librostransportlib rostimelib   xmlrpcpplib  libb64  roscpp_serialization   cpp_common   console_bridge rosconsole  ${GLOG_LIBRARY}  ${Boost_LIBRARIES} )


add_executable( time_test deps/roscpp_core/rostime/test/time.cpp )
target_link_libraries( time_test ${GTEST_BOTH_LIBRARIES} rostimelib ${Boost_LIBRARIES} )


add_executable( test_version deps/ros_comm/test/test_roscpp/test/test_version.cpp )
target_link_libraries( test_version ${GTEST_BOTH_LIBRARIES} rostimelib ${Boost_LIBRARIES} )


add_executable( test_args  deps/ros_comm/test/test_roscpp/test/test_args.cpp )
target_link_libraries( test_args  ${GTEST_BOTH_LIBRARIES} libroslib librostransportlib  roscpp_serialization  cpp_common  xmlrpcpplib libb64  rostimelib console_bridge rosconsole  ${GLOG_LIBRARY}   ${Boost_LIBRARIES} )

add_executable( test_callback_queue  deps/ros_comm/test/test_roscpp/test/test_callback_queue.cpp )
target_link_libraries( test_callback_queue  ${GTEST_BOTH_LIBRARIES} libroslib librostransportlib  roscpp_serialization  cpp_common  xmlrpcpplib libb64  rostimelib console_bridge rosconsole  ${GLOG_LIBRARY}   ${Boost_LIBRARIES} )

add_executable( test_header   deps/ros_comm/test/test_roscpp/test/test_header.cpp )
target_link_libraries( test_header  ${GTEST_BOTH_LIBRARIES} libroslib librostransportlib  roscpp_serialization  cpp_common  xmlrpcpplib libb64  rostimelib console_bridge rosconsole  ${GLOG_LIBRARY}   ${Boost_LIBRARIES} )


add_executable( test_names   deps/ros_comm/test/test_roscpp/test/test_names.cpp )
target_link_libraries( test_names  ${GTEST_BOTH_LIBRARIES} libroslib librostransportlib  roscpp_serialization  cpp_common  xmlrpcpplib libb64  rostimelib console_bridge rosconsole  ${GLOG_LIBRARY}   ${Boost_LIBRARIES} )


