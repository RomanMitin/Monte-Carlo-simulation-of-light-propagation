#pragma once
#include <numbers>

constexpr double THRESHOLD_WEIGHT = 1e-4;;

constexpr double CHANCE = 0.1;

constexpr double COS0 = 1 - 1e-12;
constexpr double COS90 = 1e-6;

constexpr bool PARTIAL_REFLECTION = true;

constexpr double PI = std::numbers::pi_v<double>;
