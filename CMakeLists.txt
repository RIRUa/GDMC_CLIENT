cmake_minimum_required(VERSION 3.1)
project (GDMC_CLIENT)

# cmakeがヘッダーを自動で割り出すので無視

# 変数APIにAPIディレクトリ下のcppファイルを追加
file(GLOB UNTOUCHABLE "untouchable/*pp")
file(GLOB UTIL "util/*pp")
file(GLOB PROCESS "Procession/*pp")

source_group("untouchable" FILES ${UNTOUCHABLE})
source_group("util" FILES ${UTIL})
source_group("Procession" FILES ${PROCESS})

# オプション
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")


# 実行ファイルに追加
add_executable(GDMC_CLIENT
	main.cpp
	${UNTOUCHABLE}
	${UTIL}
	${PROCESS}
)

# libcurl用の設定
set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(GDMC_CLIENT ${CURL_LIBRARIES})
