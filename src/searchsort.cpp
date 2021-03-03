#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <ratio>
#include <sstream>
#include <string>

#define ELEMENT_COUNT 1'000'000

typedef std::chrono::nanoseconds NS;
typedef std::chrono::high_resolution_clock HRT;

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
std::size_t binary_search(const std::vector<T> &t_vec, const T &t_search) {
    typename std::vector<T>::const_iterator left_iter  = t_vec.begin();
    typename std::vector<T>::const_iterator right_iter = t_vec.end() - 1;

    while(left_iter <= right_iter) {
        typename std::vector<T>::const_iterator mid_iter = 
            left_iter + std::distance(left_iter, right_iter) / 2;
        if(*mid_iter == t_search) {
            return std::distance(t_vec.begin(), mid_iter);
        }
        if(*mid_iter < t_search) {
            left_iter = mid_iter + 1;
        }
        else {
            right_iter = mid_iter - 1;
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
std::vector<T> merge(const std::vector<T> &t_left,
                     const std::vector<T> &t_right) {
    std::size_t left_index = 0;
    std::size_t right_index = 0;
    std::size_t result_index = 0;

    std::vector<T> result;
    result.resize(t_left.size() + t_right.size());

    while(left_index < t_left.size() && right_index < t_right.size()) {
        if(t_left[left_index] <  t_right[right_index]) {
            result[result_index] = t_left[left_index];
            left_index++;
        }
        else {
            result[result_index] = t_right[right_index];
            right_index++;
        }

        result_index++;
    }

    while(left_index < t_left.size()) {
        result[result_index] = t_left[left_index];
        left_index++;
        result_index++;
    }

    while(right_index < t_right.size()) {
        result[result_index] = t_right[right_index];
        right_index++;
        result_index++;
    }

    return result;
}

template <typename T>
std::vector<T> merge_sort(const std::vector<T> &t_vec) {
    if(t_vec.size() <= 1) {
        return t_vec;
    }

    std::size_t midpoint = t_vec.size() / 2;
    std::vector<T> left(t_vec.begin(), t_vec.begin() + midpoint);
    std::vector<T> right(t_vec.begin() + midpoint, t_vec.end());

    return merge(merge_sort(left), merge_sort(right));
}

std::string format_duration(const NS &t_duration) {
    std::stringstream retval;
    retval.imbue(std::locale(""));
    retval.setf(std::ios::fixed, std::ios::floatfield);
    retval.setf(std::ios::showpoint);
    retval.precision(2);

    uint64_t count = t_duration.count();

    if(count < 1'000) {
        retval << count << "ns"; 
    }
    else if(count < 1'000'000) {
        retval.precision(2);
        retval << count/1'000.0 << "us";
    }
    else if(count < 1'000'000'000) {
        retval << count/1'000'000.0 << "ms";
    }
    else {
        retval << count/1'000'000'000.0 << "s";
    }

    return retval.str();
}

template <typename T>
bool validate_sort(const std::vector<T> &t_vec) {
     T prev_val = *(t_vec.begin());
     for(auto vec_iter = t_vec.begin() + 1;
         vec_iter < t_vec.end(); vec_iter++) {

         if(*vec_iter < prev_val) return false;

         prev_val = *vec_iter;
     }

     return true;
}

template <typename T>
std::size_t sequential_search_wrapper(const std::vector<T> &t_vec,
                                      const T &search_term) {
    HRT::time_point start = HRT::now();
    std::size_t found = sequential_search(t_vec, search_term);
    auto duration = std::chrono::duration_cast<NS>(HRT::now() - start);

    std::cout << "\nSequential search took: " << format_duration(duration)
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
std::size_t binary_search_wrapper(const std::vector<T> &t_vec,
                                  const T &search_term) {
    HRT::time_point start = HRT::now();
    std::size_t found  = binary_search(t_vec, search_term);
    auto duration = std::chrono::duration_cast<NS>(HRT::now() - start);

    std::cout << "\nBinary search took: " << format_duration(duration)
              << std::endl;

    if(found < t_vec.size()) {
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

    HRT::time_point start = HRT::now();
    std::vector<int> sorted = insertion_sort(datums);
    auto duration = std::chrono::duration_cast<NS>(HRT::now() - start);

    std::cout << "insertion sort took: " << format_duration(duration)
              << std::endl;

    if(!validate_sort(sorted)) {
        std::cerr << "Insertion sort was invalid!" << std::endl;
    }

    std::cout << "\nSorting using merge sort..." << std::endl;

    start = HRT::now();
    sorted = merge_sort(datums);
    duration = std::chrono::duration_cast<NS>(HRT::now() - start);

    std::cout << "merge sort took: " << format_duration(duration)
              << std::endl;

    if(!validate_sort(sorted)) {
        std::cerr << "Merge sort was invalid!" << std::endl;
    }

    std::cout << "\nSearching " << ELEMENT_COUNT << " elements for "
              << search_term << ", but sorted this time." << std::endl;
    
    sequential_search_wrapper(sorted, search_term);
    binary_search_wrapper(sorted, search_term);

    return 0;
}
