#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <limits>

#include "CMakeConfig.hpp"
#include "Timer.hpp"
#include "DivideAndConquer.hpp"

#define ELEMENT_COUNT 100'000

Timer timer;

template <typename T>
std::size_t sequential_search(const std::vector<T> &t_vec, T t_search) {
    for(uint32_t index = 0; index < t_vec.size(); index++) {
        if(t_search == t_vec[index]) {
            return index;
        }
    }

    return -1;
}

template <typename T>
std::vector<T> insertion_sort(const std::vector<T> &t_vec) {
    std::size_t index;
    std::size_t prev_index;
    T key;

    std::vector<T> result = t_vec;

    for(index = 1; index < result.size(); index++) {
        key = result[index];
        prev_index = index - 1;

        while(prev_index < result.size() && result[prev_index] > key) {
            result[prev_index + 1] = result[prev_index];
            prev_index--;
        }

        result[prev_index + 1] = key;
    }

    return result;
}

template <typename T>
std::size_t sequential_search_wrapper(const std::vector<T> &t_vec,
                                      const T &search_term) {
    timer.start();
    std::size_t found = sequential_search(t_vec, search_term);
    std::string duration = timer.stop();

    std::cout << "\nSequential search took: " << duration
              << std::endl;

    if(found < t_vec.size()) {
        std::cout << "Found at " << found << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }

    return found;
}

template <typename T>
std::size_t binary_search_wrapper(const DivideAndConquer<T> &t_dnq,
                                  const T &search_term) {
    timer.start();
    std::size_t found  = t_dnq.binary_search(search_term);
    std::string duration = timer.stop();

    std::cout << "\nBinary search took: " << duration
              << std::endl;

    if(found < std::numeric_limits<std::size_t>::max()) {
        std::cout << "Found at " << found << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }

    return found;
}

int main() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<> distribution(1, ELEMENT_COUNT);
    std::vector<int> datums;
    datums.resize(ELEMENT_COUNT);

    for(uint32_t index = 0; index < datums.size(); index++)
    {
        datums[index] = distribution(mersenne);
    }

    int search_term = distribution(mersenne);

    std::cout.imbue(std::locale(""));

    std::cout << "Searching " << ELEMENT_COUNT << " elements for "
              << search_term << ". Unsorted!" << std::endl;

    sequential_search_wrapper(datums, search_term);

    std::cout << "\nSorting using insertion sort..." << std::endl;

    timer.start();
    std::vector<int> sorted = insertion_sort(datums);
    std::string duration = timer.stop();

    std::cout << "insertion sort took: " << duration
              << std::endl;

    DivideAndConquer<int> dnq(datums);
    std::cout << "\nSorting using merge sort..." << std::endl;

    timer.start();
    dnq.merge_sort();
    duration = timer.stop();

    std::cout << "merge sort took: " << duration
              << std::endl;

    std::cout << "\nSearching " << ELEMENT_COUNT << " elements for "
              << search_term << ", but sorted this time." << std::endl;

    sequential_search_wrapper(sorted, search_term);
    binary_search_wrapper(dnq, search_term);

    return 0;
}
