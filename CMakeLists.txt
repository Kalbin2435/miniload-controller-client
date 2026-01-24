cmake_minimum_required(VERSION 4.2.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(THIRD_PARTY_DIR       ${CMAKE_SOURCE_DIR}/external)
set(THIRD_PARTY_INCLUDE   ${THIRD_PARTY_DIR}/include)
set(THIRD_PARTY_LIB_DIR   ${THIRD_PARTY_DIR}/lib)
set(IMGUI_DIR             ${CMAKE_SOURCE_DIR}/external/imgui-include)
set(SRC_DIR               ${CMAKE_SOURCE_DIR}/src)

# --- imgui library ---
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_impl_dx11.cpp
    ${IMGUI_DIR}/imgui_impl_win32.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${THIRD_PARTY_INCLUDE}
)
project(project C CXX)
add_executable(${PROJECT_NAME} 
    main.cpp 
    ${SRC_DIR}/MainWindow.cpp 
    ${SRC_DIR}/UIElements.cpp 
    ${SRC_DIR}/UIHelpers.cpp 
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${THIRD_PARTY_INCLUDE}
)
file(GLOB THIRD_PARTY_LIBS
    "${THIRD_PARTY_LIB_DIR}/*.a"
)
set(SYSTEM_LIBS
    ws2_32
    crypt32
    wldap32
    advapi32
    bcrypt
    iphlpapi
    secur32
    
    # dx11
    d3d11
    dxgi
    d3dcompiler
    dwmapi
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    ${THIRD_PARTY_LIBS}
    ${SYSTEM_LIBS}
)
