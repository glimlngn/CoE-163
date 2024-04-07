#include <iostream>
#include <string>
#include <random>
#include <chrono>   // for runtime profiling

int findMinCombi(int number_of_locks, std::string init_combi, std::string unlock_combi){
    int bigger_num, smaller_num, temp;
    int min_steps = 0;
    while(number_of_locks > 0){
        bigger_num = int(init_combi[number_of_locks - 1] - '0');
        smaller_num = int(unlock_combi[number_of_locks - 1] - '0');
        if(bigger_num < smaller_num){
            temp = bigger_num;
            bigger_num = smaller_num;
            smaller_num = temp;
        }
        if(bigger_num - smaller_num <= (smaller_num + 10) - bigger_num)
            min_steps += bigger_num - smaller_num;
        else
        min_steps += (smaller_num + 10) - bigger_num;
        number_of_locks--;
    }
    return min_steps;
}

std::pair<double, double> runtimeProfiler(int number_of_locks, std::string init_combi, std::string unlock_combi){
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
    int number_of_locks_random;
    std::string init_combi_random, unlock_combi_random;

    std::random_device rd;  // initialize random number generator
    std::mt19937_64 gen(rd()); 
    std::uniform_int_distribution<int> dis1(1, 100); // for random number of locks N: [1, 100]
    std::uniform_int_distribution<int> dis2(0, 9); // for random digits: [0, 9]

    for(int i = 0; i < 1000; i++){
        number_of_locks_random = dis1(gen);
        init_combi_random = "", unlock_combi_random = "";
        for(int j = 0; j < number_of_locks_random; j++){
            init_combi_random += std::to_string(dis2(gen));
            unlock_combi_random += std::to_string(dis2(gen));
        }

        start_time = std::chrono::high_resolution_clock::now();
        findMinCombi(number_of_locks_random, init_combi_random, unlock_combi_random);
        // std::cout << i + 1 << ": " << number_of_locks_random << " " << init_combi_random << " " << unlock_combi_random << " " << findMinCombi(number_of_locks_random, init_combi_random, unlock_combi_random) << std::endl;
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

    min_combi = findMinCombi(number_of_locks, init_combi, unlock_combi);   // output
    std::pair<double, double> runtimes = runtimeProfiler(number_of_locks, init_combi, unlock_combi);
    runtime_same_length = runtimes.first;
    runtime_different_length = runtimes.second;

    std::cout << std::endl;   // prints everything in console
    std::cout << "CoE 163 SE01: Profiling and Assembly (C++)" << std::endl;
    std::cout << std::endl;
    std::cout << "Input                                         " << number_of_locks << " " << init_combi << " " << unlock_combi << std::endl;
    std::cout << "Output                                        " << min_combi << std::endl;
    std::cout << "Runtime Case 1: Same Length                   " << runtime_same_length << " ms" << std::endl;
    std::cout << "Runtime Case 2: Different Length              " << runtime_different_length << " ms" << std::endl;
    std::cout << std::endl;
    return 0;
}