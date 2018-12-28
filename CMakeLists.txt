cmake_minimum_required(VERSION 3.12)
project(open_obd2)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

include_directories("${gtest_SOURCE_DIR}/include include//*")

set(CPPSRC
        lib/easylogging++.cc
        src/CAN/CanIsoTP.cpp
        src/CAN/CanIsoTP.h
        src/common/conversion.cpp
        src/common/conversion.h
        src/common/endian.h
        src/Config.cpp src/Config.h
        src/OBD/data/Enumerated/StateOfCommandedSecondaryAir.h
        src/OBD/data/BitEncoded/Engine.cpp
        src/OBD/data/BitEncoded/Engine.cpp
        src/OBD/data/BitEncoded/Engine.h
        src/OBD/data/BitEncoded/FreezeDTC.cpp
        src/OBD/data/BitEncoded/FreezeDTC.h
        src/OBD/data/BitEncoded/MonitorStatus.cpp
        src/OBD/data/BitEncoded/MonitorStatus.h
        src/OBD/data/BitEncoded/PidSupport.cpp
        src/OBD/data/BitEncoded/PidSupport.h
        src/OBD/data/CalculatedDataObject.h
        src/OBD/data/CalculatedValues.cpp
        src/OBD/data/CalculatedValues.h
        src/OBD/data/DataObject.h
        src/OBD/data/Enumerated/StateOfFuelSystem.h
        src/OBD/data/OBDTest.cpp
        src/OBD/data/OBDTest.h
        src/OBD/DataTroubleCode.cpp
        src/OBD/DataTroubleCode.h
        src/OBD/OBDHandler.cpp
        src/OBD/OBDHandler.h
        src/OBD/Pid.cpp
        src/OBD/Pid.h src/Service.h
        src/Vehicle.cpp
        src/Vehicle.h
        )


add_executable(open_obd2 ${CPPSRC})

add_executable(Test
        tests/src/OBD/OBDHandlerTest.h
        tests/src/OBD/OBDHandlerTest.cpp
        tests/src/OBD/OBDHandlerTestsService1.cpp
        tests/src/OBD/OBDHandlerTestsService2.cpp
        tests/src/CAN/CanIsoTPTests.cpp
        tests/src/OBD/OBDHandlerTestSimulatedCAN.cpp
        tests/src/OBD/data/DataObjectTest.cpp
        tests/src/OBD/DataTroubleCodeTest.cpp
        tests/src/ConfigTest.cpp
        ${CPPSRC})

target_link_libraries(Test gtest_main)
add_test(NAME obdtest COMMAND Test)