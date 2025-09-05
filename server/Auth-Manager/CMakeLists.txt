cmake_minimum_required(VERSION 3.28)
project(server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GRPC_DIR "$ENV{DEV_ENV}")
set(PROTO_SRC "${CMAKE_SOURCE_DIR}/proto")

set(PROTO_LIB "genproto_lib")
file(GLOB PROTO_SRC
    "${CMAKE_SOURCE_DIR}/proto/*.pb.cc"
    "${CMAKE_SOURCE_DIR}/proto/*.grpc.pb.cc"
)
file(GLOB PROTO_HDR
    "${CMAKE_SOURCE_DIR}/proto/*.pb.h"
    "${CMAKE_SOURCE_DIR}/proto/*.grpc.pb.h"
)
add_library(${PROTO_LIB} ${PROTO_SRC} ${PROTO_HDR})

find_package(Protobuf REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(gRPC REQUIRED)
find_package(utf8_range REQUIRED)
find_package(PostgreSQL REQUIRED) 
find_package(libpqxx REQUIRED)

include_directories(${GRPC_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/proto)
include_directories(usr/local/include)
include_directories(usr/include)

target_include_directories(${PROTO_LIB}
    PUBLIC
        ${PROTOC_DIR}
)

target_link_libraries(${PROTO_LIB}
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc++
        utf8_range::utf8_range
        utf8_range::utf8_validity
)

file(
    GLOB SOURCES
    "${PROTO_SRC}/*.pb.cc"
    "${PROTO_SRC}/*.grpc.pb.cc"
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/db/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/service/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})



##################################################
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${PROTO_LIB}
    pqxx pq
    OpenSSL::Crypto
    OpenSSL::SSL
    protobuf::libprotobuf
    gRPC::grpc++
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)




