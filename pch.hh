#include <boost/compute/core.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/math.hpp>

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>

template<typename T, size_t N>
constexpr size_t length(T(&)[N]) {
    return N;
}
