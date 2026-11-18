cmake_minimum_required(VERSION 3.16)

project(TBO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Quick
    QuickControls2
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(TBO
    src/main.cpp
    src/AppBackend.hpp
    src/AppBackend.cpp
    src/WorkbookManager.hpp
    src/WorkbookManager.cpp
    src/Wpis.hpp
    src/WpisModel.hpp
    src/WpisModel.cpp
    src/CsvManager.hpp
    src/CsvManager.cpp
    src/Recents.cpp
    src/Recents.hpp
)

set_target_properties(TBO PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_source_files_properties(qml/Main.qml
    PROPERTIES QT_RESOURCE_ALIAS "Main.qml"
)

set_source_files_properties(qml/pages/Workbook.qml
    PROPERTIES QT_RESOURCE_ALIAS "pages/Workbook.qml"
)

set_source_files_properties(qml/pages/RecentFiles.qml
    PROPERTIES QT_RESOURCE_ALIAS "pages/RecentFiles.qml"
)

set_source_files_properties(qml/components/Sidebar.qml
    PROPERTIES QT_RESOURCE_ALIAS "components/Sidebar.qml"
)

set_source_files_properties(qml/components/AppButton.qml
    PROPERTIES QT_RESOURCE_ALIAS "components/AppButton.qml"
)

set_source_files_properties(qml/components/TransactionsTable.qml
    PROPERTIES QT_RESOURCE_ALIAS "components/TransactionsTable.qml"
)

qt_add_qml_module(TBO
    URI TBO
    VERSION 1.0

    QML_FILES
        qml/Main.qml
        qml/pages/Workbook.qml
        qml/pages/RecentFiles.qml
        qml/components/Sidebar.qml
        qml/components/AppButton.qml
        qml/components/TransactionsTable.qml
)

target_link_libraries(TBO PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)
