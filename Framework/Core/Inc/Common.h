#pragma once

#define WIN32_LEAN_AND_MEAN // eliminates all unnnecesary windows apis for a smaller build
#define NOMINMAX // removes min/max keywords so we can create those fucntions


//Win 32 headers
#include <objbase.h>
#include <Windows.h>

// std headers
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>