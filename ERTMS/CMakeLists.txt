cmake_minimum_required(VERSION 3.0)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# If pkg-config is not installed on the system, then the
# CHECK_INSTALL_DIR variable must be set to the install
# location of Check. For example, on Windows, this may
# be: C:/Program Files/check
#set(CHECK_INSTALL_DIR "/usr/include/")

find_package(Check)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

set(TEST_SOURCES
  ertms_test.c
  ertms_init_tests.c
  ertms_serialize_tests.c
  ertms.c
)

set(TEST_HEADERS
  ertms.h
  ertms_test.h
  GSM_R_message.h
  GSM_R_packet.h
  EBT_message.h
  EBT_packet.h
  NRBC_message.h
)

add_executable(check_ertms ${TEST_HEADERS} ${TEST_SOURCES})
target_compile_options(check_ertms PRIVATE -Wall)
target_link_libraries(check_ertms check m rt pthread subunit ${CHECK_LIBRARIES})
