#include <thread>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include "Rand_gen.hpp"

constexpr int num_threads = 8;
constexpr size_t num_iter = 1000000;
constexpr size_t total_num = num_threads * num_iter;

bool check_hypothesis(std::vector<double>&& generated_numbers)
{
    constexpr double chi_crit = 50.0;

    const size_t interval_num = 5 * std::log10(total_num);
    const double interval_length = 1.0 / interval_num;
 
    int j = 0;

    double chi_square = 0.0;

    for(int i = 0; i < interval_num; i++)
    {
        size_t count = 0;
        while (j < generated_numbers.size() && generated_numbers[j] < (i + 1) * interval_length)
        {
            count++;
            j++;
        }

        chi_square += std::pow(static_cast<double>(count) / total_num - interval_length, 2) / interval_length;
    }

    chi_square *= total_num;
    std::cout << "chi square = " << chi_square << "\n";

    return chi_square < chi_crit;
}

int main()
{
    Rand_gen_t gen(num_threads);

    std::vector<std::thread> threads;
    std::vector<std::vector<double>> generated_numbers_vec {num_threads};

    for(size_t i = 0; i < num_threads; i++)
    {
        threads.emplace_back([&](int id) {
            generated_numbers_vec[id].reserve(num_iter);
            for(size_t i = 0; i < num_iter; i++)
            {
                generated_numbers_vec[id].push_back(gen(id));
            }
        }, i);
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    std::vector<double> generated_numbers;
    generated_numbers.reserve(total_num);
    for(auto& vec: generated_numbers_vec)
    {
        std::copy(vec.begin(), vec.end(), std::back_inserter(generated_numbers));
        vec.clear();
    }

    std::sort(generated_numbers.begin(), generated_numbers.end());
    
    return !check_hypothesis(std::move(generated_numbers));
}