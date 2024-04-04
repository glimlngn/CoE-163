#include <iostream>
#include <string>
#include <algorithm>    // for std::max and std::min
#include <cmath>    // for std::pow and std::abs
#include <chrono>   // for runtime profiling
#include <random>

int findMinCombi(int number_of_locks, long int init_combi, long int unlock_combi){
    int bigger_num, smaller_num, min_steps = 0;
    while(number_of_locks > 0){   // loop goes through all digits of the lock
        bigger_num = std::max(init_combi % 10, unlock_combi % 10);    // decides placement of values for the following formula
        smaller_num = std::min(init_combi % 10, unlock_combi % 10);
        min_steps += std::min(std::abs(bigger_num - smaller_num), std::abs((bigger_num - 10) - smaller_num));    // adds min. steps of digit, number wrapping is emulated
        init_combi /= 10;     // iterates to the next digit (from right to left)
        unlock_combi /= 10;
        number_of_locks--;
    }
    return min_steps;    // returns minimum number of steps of the lock
}

 std::pair<double, double> runtimeProfiler(int number_of_locks, long int init_combi, long int unlock_combi){
    // NOTE: Leading zeroes are considered in runtime profiling.
    int number_of_locks_random;
    uint64_t init_combi_random, unlock_combi_random;
    double runtime_same_length, runtime_diff_length = 0;
    
    // Case 1: Same Length
    // find_min_combi is iterated 1000 times with programmed input
    auto start_time = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000; i++)
        findMinCombi(number_of_locks, init_combi, unlock_combi);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;
    runtime_same_length = elapsed_time.count();

    // Case 2: Different Length
    std::random_device rd;  // initialize random number generator
    std::mt19937_64 gen(rd()); 
    std::uniform_int_distribution<long long> dis1(1, 100); // for random number of locks N: [1, 100)

    for(int i = 0; i < 1000; i++){
        number_of_locks_random = dis1(gen) + 1;
        std::uniform_int_distribution<long long> dis2(0, std::llround(std::pow(10, number_of_locks_random))); // for random lock configurations
        init_combi_random = dis2(gen);
        unlock_combi_random = dis2(gen);
        
        start_time = std::chrono::high_resolution_clock::now();
        
        findMinCombi(number_of_locks_random, init_combi_random, unlock_combi_random);
        // std::cout << i << ": " << number_of_locks_random << " " << init_combi_random << " " << unlock_combi_random << " " << findMinCombi(number_of_locks_random, init_combi_random, unlock_combi_random) << std::endl;
        
        end_time = std::chrono::high_resolution_clock::now();

        elapsed_time = end_time - start_time;
        runtime_diff_length += elapsed_time.count();
        }
        return std::make_pair(runtime_same_length, runtime_diff_length);  // returns runtimes
    }

int main(){
    int number_of_locks = 4;    // input
    std::string init_combi = "1234";
    std::string unlock_combi = "9899";
    
    int min_combi;  // output
    
    double runtime_same_length, runtime_different_length;

    if(number_of_locks != init_combi.length() || number_of_locks != unlock_combi.length()){
        std::cout << "ERROR: Input mismatch in number of locks" << std::endl;    // exits program if error occurs
        return 1;
    }

    long int init_combi_long_int = std::stol(init_combi);
    long int unlock_combi_long_int = std::stol(unlock_combi);

    min_combi = findMinCombi(number_of_locks, init_combi_long_int, unlock_combi_long_int);   // output
    std::pair<double, double> runtimes = runtimeProfiler(number_of_locks, init_combi_long_int, unlock_combi_long_int);
    runtime_same_length = runtimes.first;
    runtime_different_length = runtimes.second;

    std::cout << "*********************************************************" << std::endl;   // prints everything in console
    std::cout << std::endl;
    std::cout << "CoE 163 SE01: Profiling and Assembly (C++)" << std::endl;
    std::cout << std::endl;
    std::cout << "Input:                                 " << number_of_locks << " " << init_combi << " " << unlock_combi << std::endl;
    std::cout << "Output:                                " << min_combi << std::endl;
    std::cout << "Runtime (Case 1: Same Length):         " << runtime_same_length << " ms" << std::endl;
    std::cout << "Runtime (Case 2: Different Length):    " << runtime_different_length << " ms" << std::endl;
    std::cout << std::endl;
    std::cout << "*********************************************************" << std::endl;
    return 0;
}