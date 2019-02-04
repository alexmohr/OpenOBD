cmake_minimum_required(VERSION 3.12)
project(open_obd2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")
SET(COVERAGE OFF CACHE BOOL "Coverage")
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${PROJECT_SOURCE_DIR}/submodules/wampcc/cmake"
        "${PROJECT_SOURCE_DIR}/submodules/cpp-readline/cmake/modules")

include_directories(
        ${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


find_package(Readline REQUIRED)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)


find_package(OpenSSL REQUIRED)
find_package(Libuv REQUIRED)
set(HAVE_LIBUV ON)
find_package(Jansson REQUIRED)
set(HAVE_JANSSON ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
        "${PROJECT_SOURCE_DIR}/submodules/wampcc/cmake/config.h.incmake"
        "${PROJECT_BINARY_DIR}/generated/config.h"
)


include_directories(
        "${gtest_SOURCE_DIR}/include include//*
        ${Readline_INCLUDE_DIRS}"
        ${PROJECT_BINARY_DIR}/
        ${PROJECT_SOURCE_DIR}/submodules/wampcc/3rdparty
        ${PROJECT_SOURCE_DIR}/submodules/wampcc/3rdparty/websocketpp
        ${PROJECT_SOURCE_DIR}/submodules/wampcc/3rdparty/msgpack-c/include/
        ${PROJECT_SOURCE_DIR}/submodules/wampcc/include
        ${PROJECT_BINARY_DIR}/generated/
        ${PROJECT_SOURCE_DIR}/submodules/wampcc/libs/json)

file(GLOB LIB_WAMPCC_JSON_SRC_FILES submodules/wampcc/libs/json/*.cc)
file(GLOB LIB_WAMPCC_SRC_FILES submodules/wampcc/libs/wampcc/*.cc)
file(GLOB LIB_3RDPTY_HTTPPARSER_SRC_FILES submodules/wampcc/3rdparty/http_parser/*.c)
file(GLOB LIB_3RDPTY_APACH_SRC_FILES submodules/wampcc/3rdparty/apache/*.c)
set(websocketpp "${PROJECT_SOURCE_DIR}/submodules/wampcc/3rdparty/websocketpp")

set(wamp
        ${LIB_3RDPTY_APACH_SRC_FILES}
        ${LIB_WAMPCC_SRC_FILES}
        ${LIB_3RDPTY_HTTPPARSER_SRC_FILES}
        ${websocketpp}
        ${msgpackfile}
        ${JANSSON_LIBRARIES}
        ${LIB_WAMPCC_JSON_SRC_FILES}
        )

set(cpp-readline
        submodules/cpp-readline/src/Console.cpp
        submodules/cpp-readline/src/Console.hpp)

set(CPPSRC
        lib/easylogging++.cc
        src/ui/cli/CliHandler.cpp src/ui/cli/CliHandler.h
        src/ui/cli/CommandHandler.cpp
        src/ui/cli/CommandHandler.h
        src/ui/CommandInfo.cpp src/ui/CommandInfo.h
        src/common/conversion.cpp
        src/common/conversion.h
        src/common/endian.h
        src/communication/CanIsoTP.cpp
        src/communication/CanIsoTP.h
        src/communication/ELM327.cpp
        src/communication/ELM327.h
        src/communication/ELM327WifiServer.cpp
        src/communication/ELM327WifiServer.h
        src/communication/ELMClient.cpp
        src/communication/ELMClient.h
        src/communication/ICloseable.h
        src/communication/ICommunicationInterface.h
        src/communication/ISocketServerClientHandler.h
        src/communication/ISocketServer.h
        src/communication/SerialClient.cpp
        src/communication/SerialClient.h
        src/communication/SocketClient.cpp
        src/communication/SocketClient.h
        src/communication/SocketCommunicationBase.cpp
        src/communication/SocketCommunicationBase.h
        src/communication/SocketServer.cpp
        src/communication/SocketServer.h
        src/Config.cpp src/Config.h
        src/OBD/data/BitEncoded/Catalyst.cpp
        src/OBD/data/BitEncoded/Catalyst.h
        src/OBD/data/BitEncoded/Engine.cpp
        src/OBD/data/BitEncoded/Engine.cpp
        src/OBD/data/BitEncoded/Engine.h
        src/OBD/data/BitEncoded/FreezeDTC.cpp
        src/OBD/data/BitEncoded/FreezeDTC.h
        src/OBD/data/BitEncoded/MonitorStatus.cpp
        src/OBD/data/BitEncoded/MonitorStatus.h
        src/OBD/data/BitEncoded/OBDCompliance.cpp
        src/OBD/data/BitEncoded/OBDCompliance.h
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensor.cpp
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensor.h
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensors4BankCollection.cpp
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensors4BankCollection.h
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensorsCollection.cpp
        src/OBD/data/BitEncoded/Oxygen/BankOxygenSensorsCollection.h
        src/OBD/data/BitEncoded/Oxygen/ExtendedRangeOxygenSensor.cpp
        src/OBD/data/BitEncoded/Oxygen/ExtendedRangeOxygenSensor.h
        src/OBD/data/BitEncoded/Oxygen/FuelRailOxygenSensor.cpp
        src/OBD/data/BitEncoded/Oxygen/FuelRailOxygenSensor.h
        src/OBD/data/BitEncoded/Oxygen/OxygenSensors.cpp
        src/OBD/data/BitEncoded/Oxygen/OxygenSensors.h
        src/OBD/data/BitEncoded/Pid/PidSupport.cpp
        src/OBD/data/BitEncoded/Pid/PidSupport.h
        src/OBD/data/BitEncoded/Pid/SupportedPidCollection.cpp
        src/OBD/data/BitEncoded/Pid/SupportedPidCollection.h
        src/OBD/data/BitEncoded/Throttle.cpp src/OBD/data/BitEncoded/Throttle.h
        src/OBD/data/dataObject/CalculatedDataObjectFactory.cpp
        src/OBD/data/dataObject/CalculatedDataObjectFactory.h
        src/OBD/data/dataObject/CalculatedDataObject.h
        src/OBD/data/dataObject/CalculatedValues.cpp
        src/OBD/data/dataObject/CalculatedValues.h
        src/OBD/data/dataObject/DataObjectDescription.h
        src/OBD/data/dataObject/DataObjectDescriptionText.cpp
        src/OBD/data/dataObject/DataObjectDescriptionText.h
        src/OBD/data/dataObject/DataObject.h
        src/OBD/data/dataObject/DataObjectStateFactory.cpp
        src/OBD/data/dataObject/DataObjectStateFactory.h
        src/OBD/data/dataObject/DataObjectState.h
        src/OBD/data/dataObject/DataObjectUnit.h
        src/OBD/data/dataObject/IDataObject.h
        src/OBD/data/dataObject/IFrameObject.h
        src/OBD/data/Enumerated/FuelSystemStates.cpp
        src/OBD/data/Enumerated/FuelSystemStates.h
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
        src/ui/VehicleDataProvider.cpp src/ui/VehicleDataProvider.h
        src/Vehicle.h src/ui/webBackend/Wamp.cpp src/ui/webBackend/Wamp.h src/OBD/PidCollection.cpp src/OBD/PidCollection.h src/OBD/data/dataObject/ErrorType.h)


add_executable(open_obd2 src/main.cpp ${CPPSRC} ${cpp-readline} ${wamp})
target_link_libraries(open_obd2 pthread readline crypto uv ssl ${JANSSON_LIBRARIES} atomic)

add_executable(Test
        ${wamp}
        ${CPPSRC}
        ${cpp-readline}
        tests/src/cli/CommandHandlerTest.cpp tests/main.cpp
        tests/src/communication/CanIsoTPTests.cpp
        tests/src/communication/ELM327WifiClientTest.cpp
        tests/src/communication/ELM327WifiServerTest.cpp
        tests/src/ConfigTest.cpp
        tests/src/MockCommInterface.cpp
        tests/src/MockCommInterface.h
        tests/src/OBD/data/DataObjectTest.cpp
        tests/src/OBD/DataTroubleCodeTest.cpp
        tests/src/OBD/OBDHandlerTest.cpp
        tests/src/OBD/OBDHandlerTest.h
        tests/src/OBD/OBDHandlerTestService1Explicit.cpp
        tests/src/OBD/OBDHandlerTestSimulatedCAN.cpp
        tests/src/OBD/OBDHandlerTestsService1.cpp
        tests/src/OBD/OBDHandlerTestsService2.cpp)


install(TARGETS open_obd2 EXPORT open_obd2 DESTINATION bin)
target_link_libraries(Test PRIVATE gtest readline pthread readline crypto uv ssl atomic ${JANSSON_LIBRARIES})

if (COVERAGE)
    target_compile_options(Test PRIVATE --coverage)
    target_link_libraries(Test PRIVATE gtest --coverage)
endif ()
add_test(NAME obdtest COMMAND Test)
