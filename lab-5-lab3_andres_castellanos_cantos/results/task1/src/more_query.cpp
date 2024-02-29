#include <CL/sycl.hpp>


// This allow us to remove cl::sycl:: from all invokations
using namespace cl::sycl;

int main() {

    cpu_selector selector;
    queue q(selector);
    device d = q.get_device();

    std::cout << "Device: " << q.get_device().get_info<info::device::name>()<< std::endl;
    std::cout << "Profile: " << q.get_device().get_info<info::device::profile>()<< std::endl;
    std::cout << "Version: " << d.get_info<info::device::version>()<< std::endl;
    std::cout << "Global memory size: " << d.get_info<info::device::global_mem_size>()<< std::endl;
    std::cout << "Global cache memory size: " << d.get_info<info::device::global_mem_cache_size>()<< std::endl;
    std::cout << "Max clock frequency: " << d.get_info<info::device::max_clock_frequency>()<< std::endl;

    return 0;
}

