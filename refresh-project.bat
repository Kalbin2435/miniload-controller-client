cmd /c "rmdir /S /Q %~dp0build\" | cmake -S %~dp0 -B %~dp0build -G Ninja -D CMAKE_BUILD_TYPE=Debug -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_EXPORT_COMPILE_COMMANDS=ON
