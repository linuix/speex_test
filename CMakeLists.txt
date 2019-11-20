cmake_minimum_required(VERSION 3.2.1)

project(speex)

#notice the "recycling" of CMAKE_C_FLAGS
#this is necessary to pick up android flags
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic" )

set(SRC_SPEEX_PATH ${PROJECT_SOURCE_DIR}/libspeexdsp)
# 设置可执行输出路径
message("${PROJECT_SOURCE_DIR}"${PROJECT_SOURCE_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ./bin/)    
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ./bin/) 

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/libs) 

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SRC_SPEEX_PATH})

# add_definitions(-DFIXED_POINT -DUSE_KISS_FFT -DHAVE_CONFIG_H)
add_definitions(-DUSE_KISS_FFT -DHAVE_CONFIG_H)

message("SRC_SPEEX_PATH = "${SRC_SPEEX_PATH})
# 定义要编译的文件列表变量
file(GLOB CPP_FILES_IN_UTILS "${SRC_SPEEX_PATH}/*.c")

list(REMOVE_ITEM CPP_FILES_IN_UTILS 
"${SRC_SPEEX_PATH}/testecho.c" 
"${SRC_SPEEX_PATH}/testdenoise.c" 
"${SRC_SPEEX_PATH}/testenc_wb.c" 
"${SRC_SPEEX_PATH}/testjitter.c" 
"${SRC_SPEEX_PATH}/testenc_uwb.c" 
"${SRC_SPEEX_PATH}/testenc.c"
"${SRC_SPEEX_PATH}/testresample2.c"
"${SRC_SPEEX_PATH}/testresample.c"
"${PROJECT_SOURCE_DIR}/test_speex.c"
) 

set(SOURCE_FILES  ${CPP_FILES_IN_UTILS})

add_library(speex SHARED ${SOURCE_FILES})
target_link_libraries(speex m)

add_executable(speex_echo ${SRC_SPEEX_PATH}/testecho.c)

target_link_libraries(speex_echo speex)

add_executable(test_speex ${PROJECT_SOURCE_DIR}/test_speex.c)

target_link_libraries(test_speex speex)
