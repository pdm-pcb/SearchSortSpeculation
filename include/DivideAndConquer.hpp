#ifndef _DIVIDEANDCOQUER_HPP
#define _DIVIDEANDCOQUER_HPP

#include <vector>

template <typename T>
class DivideAndConquer {
    public:
        DivideAndConquer() = delete;
        DivideAndConquer(const std::vector<T> &t_vec);

        std::size_t binary_search(const T &t_search) const;
        void merge_sort();

    private:
        std::vector<T> data;

        std::vector<T> merge(const std::vector<T> &t_left,
                             const std::vector<T> &t_right);

        inline bool validate_sort() const {
            T prev_val = *(data.begin());
            for(auto vec_iter = data.begin() + 1;
                vec_iter < data.end(); vec_iter++) {

                if(*vec_iter < prev_val) return false;

                prev_val = *vec_iter;
            }

            return true;
        }
};

#endif //_DIVIDEANDCOQUER_HPP
