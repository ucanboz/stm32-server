cmake_minimum_required(VERSION 3.10)
project(stm32-server)
set(CMAKE_C_STANDARD 11)
add_executable(tcp_server tcp_server.c)

# Install rule: installs tcp_server to /usr/local/bin by default
install(TARGETS tcp_server DESTINATION bin)