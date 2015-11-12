
# 要求するcmakeのバージョン
cmake_minimum_required(VERSION 2.8)

#プロジェクトの指定
PROJECT(fernand-v4)



#c++11が入ってるかどうか
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)
if(CMAKE_USE_PTHREADS_INIT)
	    set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-pthread")
else()
	message(STATUS "Not find pthread.")
endif()


#実行ファイルの出力
add_executable(out main.cpp raspiConfig.cpp server.cpp)


#コンパイルオプション
#CXXはC++
#-gはデバッグをオン
#-Wallは警告オプション
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ftest-coverage")


#ライブラリのリンク
#target_link_libraries(out ${CMAKE_THREAD_LIBS_INIT} m )



