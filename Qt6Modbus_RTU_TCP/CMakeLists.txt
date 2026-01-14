cmake_minimum_required(VERSION 4.2)

project(Qt6Modbus_RTU_TCP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Enforce C++23 support

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick QuickControls2 SerialBus)


qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appQt6Modbus_RTU_TCP
    main.cpp
)

qt_add_qml_module(appQt6Modbus_RTU_TCP
    URI ${PROJECT_NAME}
    QML_FILES
        Main.qml
        SOURCES MainBackendHelper.h MainBackendHelper.cpp
        SOURCES BoilerPlate.h BoilerPlate.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQt6Modbus_RTU_TCP PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQt6Modbus_RTU_TCP
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQt6Modbus_RTU_TCP
    PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::SerialBus
)

include(GNUInstallDirs)
install(TARGETS appQt6Modbus_RTU_TCP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
