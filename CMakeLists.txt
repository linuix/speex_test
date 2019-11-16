cmake_minimum_required(VERSION 2.8)

project(TXZAudio)

#notice the "recycling" of CMAKE_C_FLAGS
#this is necessary to pick up android flags
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic" )

set(SRC_SPEEX_PATH ${PROJECT_SOURCE_DIR}/libspeexdsp)
# 设置可执行输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/Debug)    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/Release) 

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
"${SRC_SPEEX_PATH}/testenc.c") 

set(SOURCE_FILES  ${CPP_FILES_IN_UTILS})

add_library(TXZAudio SHARED ${SOURCE_FILES})


# target_link_libraries(TXZAudio )
