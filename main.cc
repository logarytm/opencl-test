#include "pch.hh"

namespace compute = boost::compute;

thread_local std::mt19937 gen{ std::random_device{}() };
template<typename T>
T random(T min, T max)
{
    using dist = std::conditional_t<
            std::is_integral<T>::value,
            std::uniform_int_distribution<T>,
            std::uniform_real_distribution<T>>;

    return dist{ min, max }(gen);
}

int main()
{
    std::ios_base::sync_with_stdio(0);

    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);

    std::clog << "Using device: " << device.name() << std::endl;

    double host_data[1000000];
    std::generate(
            std::begin(host_data),
            std::end(host_data),
            []() -> double { return random<double>(0.0, 1.0); });

    compute::vector<double> device_vector(length(host_data), context);
    compute::copy(std::begin(host_data), std::end(host_data), device_vector.begin(), queue);

    std::vector<double> host_vector(length(host_data));

    compute::transform(
            device_vector.begin(),
            device_vector.end(),
            device_vector.begin(),
            compute::exp<double>(),
            queue);

    compute::copy(
            device_vector.begin(),
            device_vector.end(),
            host_vector.begin(),
            queue);

    return 0;
}
