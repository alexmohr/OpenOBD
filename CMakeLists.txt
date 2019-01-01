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
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensor.cpp
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensor.h
        src/OBD/data/BitEncoded/Engine.cpp
        src/OBD/data/BitEncoded/Engine.cpp
        src/OBD/data/BitEncoded/Engine.h
        src/OBD/data/BitEncoded/FreezeDTC.cpp
        src/OBD/data/BitEncoded/FreezeDTC.h
        src/OBD/data/BitEncoded/MonitorStatus.cpp
        src/OBD/data/BitEncoded/MonitorStatus.h
        src/OBD/data/BitEncoded/OBDCompliance.cpp
        src/OBD/data/BitEncoded/OBDCompliance.h
        src/OBD/data/BitEncoded/Oxygen/OxygenSensors.cpp
        src/OBD/data/BitEncoded/Oxygen/OxygenSensors.h
        src/OBD/data/BitEncoded/PidSupport.cpp
        src/OBD/data/BitEncoded/PidSupport.h
        src/OBD/data/dataObject/CalculatedDataObject.h
        src/OBD/data/dataObject/CalculatedValues.cpp
        src/OBD/data/dataObject/CalculatedValues.h
        src/OBD/data/dataObject/DataObjectDescription.h
        src/OBD/data/dataObject/DataObject.h
        src/OBD/data/Enumerated/StateOfCommandedSecondaryAir.h
        src/OBD/data/Enumerated/StateOfFuelSystem.h
        src/OBD/data/OBDTest.cpp
        src/OBD/data/OBDTest.h
        src/OBD/DataTroubleCode.cpp
        src/OBD/DataTroubleCode.h
        src/OBD/OBDHandler.cpp
        src/OBD/OBDHandler.h
        src/OBD/Pid.cpp
        src/OBD/Pid.h
        src/OBD/Service.h
        src/Vehicle.cpp
        src/Vehicle.h
        src/OBD/data/BitEncoded/Oxygen/FuelRailOxygenSensor.cpp
        src/OBD/data/BitEncoded/Oxygen/FuelRailOxygenSensor.h
        src/OBD/data/dataObject/DataObjectUnit.h
        src/OBD/data/dataObject/DataObjectDescriptionText.h
        src/OBD/data/dataObject/DataObjectDescriptionText.cpp
        src/OBD/data/BitEncoded/Oxygen/ExtendedRangeOxygenSensor.cpp
        src/OBD/data/BitEncoded/Oxygen/ExtendedRangeOxygenSensor.h
        src/OBD/data/BitEncoded/Catalyst.cpp
        src/OBD/data/BitEncoded/Catalyst.h
        src/OBD/data/dataObject/IFrameObject.h

        src/OBD/data/Enumerated/FuelSystemStates.cpp
        src/OBD/data/Enumerated/FuelSystemStates.h
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensorsCollection.cpp
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensorsCollection.h
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensors4BankCollection.cpp
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensors4BankCollection.h)


add_executable(open_obd2 src/main.cpp ${CPPSRC})

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