#pragma once

#include <thread>
#include <chrono>

#define AuthSysSleep(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))