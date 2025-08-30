cmake_minimum_required(VERSION 3.28)
project(server)

set(CMAKE_CXX_STANDARD 23)
#set(GRPC_DIR "$ENV{GRPC_HOME}")

find_package(Protobuf REQUIRED)
find_package(OpenSSL REQUIRED)
#find_package(gRPC REQUIRED)
find_package(utf8_range REQUIRED)
find_package(PostgreSQL REQUIRED) 
find_package(libpqxx REQUIRED)

set(GENPROTO_LIB "genproto_lib")
set(GENPROTO_DIR "${PROJECT_SOURCE_DIR}/proto")

file(GLOB_RECURSE PROTO_SRC "${GENPROTO_DIR}/*.pb.cc")
file(GLOB_RECURSE PROTO_HDR "${GENPROTO_DIR}/*.pb.h")

add_library(${GENPROTO_LIB} ${PROTO_SRC} ${PROTO_HDR})

include_directories(usr/local/include)

target_include_directories(${GENPROTO_LIB}
  PUBLIC
    ${GENPROTO_DIR}
)

target_link_libraries(${GENPROTO_LIB}
    PUBLIC
        protobuf::libprotobuf
        #gRPC::grpc++
        utf8_range::utf8_range
        utf8_range::utf8_validity
        
)

file(GLOB SOURCES 
      "${CMAKE_SOURCE_DIR}/src/*.cpp" 
      "${CMAKE_SOURCE_DIR}/src/db/*.cpp" 
      "${CMAKE_SOURCE_DIR}/src/service/*.cpp" 
      )


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${GENPROTO_LIB}
    pqxx pq
    OpenSSL::SSL
    OpenSSL::Crypto
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/proto
)