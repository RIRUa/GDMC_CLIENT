cmake_minimum_required(VERSION 3.1)
project (GDMC_CLIENT)

# windowsの場合のコンパイラの設定
if(WIN32)
	set(CMAKE_CXX_COMPILER C:/Mingw/bin/g++)
	set(CMAKE_C_COMPILER C:/Mingw/bin/gcc)
endif(WIN32)


# cmakeがヘッダーを自動で割り出すので無視

# 変数APIにAPIディレクトリ下のcppファイルを追加
file(GLOB API "API/*pp")
file(GLOB INTERFACE "Interface/*pp")
file(GLOB UTIL "util/*pp")
file(GLOB PROCESS "Procession/*pp")

source_group("API" FILES ${API})
source_group("Interface" FILES ${INTERFACE})
source_group("util" FILES ${UTIL})
source_group("Procession" FILES ${PROCESS})

# オプション
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")


# 実行ファイルに追加
add_executable(GDMC_CLIENT
	main.cpp
	${API}
	${INTERFACE}
	${UTIL}
	${PROCESS}
)

# libcurl用の設定
set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(GDMC_CLIENT ${CURL_LIBRARIES})