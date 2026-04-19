#
# Copyright © 2025 Luca Carlon
#
#  This file is part of RpiKioskOsMainApp.
#
#  RpiKioskOsMainApp is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  RpiKioskOsMainApp is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with RpiKioskOsMainApp. If not, see <https://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.16)

project(RpiKioskOsMainApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick WebEngineQuick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appRpiKioskOsMainApp
    main.cpp
)

qt_add_qml_module(appRpiKioskOsMainApp
    URI RpiKioskOsMainApp
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appRpiKioskOsMainApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appRpiKioskOsMainApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appRpiKioskOsMainApp
    PRIVATE Qt6::Quick
)

install(TARGETS appRpiKioskOsMainApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
