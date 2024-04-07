#include <iostream>
#include <string>
#include <array>
#include <random>
#include <chrono>   // for runtime profiling

int findMinCombi(int number_of_locks, std::string init_combi, std::string unlock_combi){
    int bigger_num, smaller_num, temp;
    int min_steps = 0;;
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

int findMinCombiASM(int number_of_locks, std::string init_combi, std::string unlock_combi){
    int bigger_num, smaller_num;
    int min_steps = 0;
    while(number_of_locks > 0){
        bigger_num = int(init_combi[number_of_locks - 1] - '0');
        smaller_num = int(unlock_combi[number_of_locks - 1] - '0');
        __asm__ (
            "cmp %3, %2\n"  // determine which is bigger/smaller, swap values if necessary
            "jge skip_swap\n"
            "xchg %3, %2\n"
            "skip_swap:\n"
            "mov %2, %%eax\n"  // eax = bigger_num
            "mov %3, %%ebx\n"  // ebx = smaller_num
            "sub %%ebx, %%eax\n"  // eax = bigger_num - smaller_num (steps to unlock in one direction)
            "add $10, %%ebx\n"
            "sub %2, %%ebx\n"  // ebx = smaller_num + 10 - bigger_num (steps to unlock in the other direction)
            "cmp %%ebx, %%eax\n"
            "jle skip_swap_again\n"  
            "xchg %%ebx, %%eax\n"  
            "skip_swap_again:\n"
            "add %%eax, %0\n"  // steps with smaller value is added to min_steps
            "dec %1\n"  // decrement number_of_locks
            : "+r" (min_steps), "+r" (number_of_locks), "+r" (bigger_num), "+r" (smaller_num)
            :
            : "eax", "ebx"
        );
    }
    return min_steps;
}

double* runtimeProfiler(int number_of_locks, std::string init_combi, std::string unlock_combi){
    double* runtimes_ptr = new double[4]{0, 0 , 0 ,0}; // runtime_same_length, runtime_same_length_asm, runtime_diff_length, runtime_diff_length_asm
    
    // Case 1: Same Length
    // find_min_combi is iterated 1000 times with programmed input
    
    auto start_time = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000; i++)
        findMinCombi(number_of_locks, init_combi, unlock_combi);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;
    runtimes_ptr[0] = elapsed_time.count();

    start_time = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000; i++)
        findMinCombiASM(number_of_locks, init_combi, unlock_combi);
    end_time = std::chrono::high_resolution_clock::now();
    elapsed_time = end_time - start_time;
    runtimes_ptr[1] = elapsed_time.count();

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
        runtimes_ptr[2] += elapsed_time.count();

        start_time = std::chrono::high_resolution_clock::now();
        findMinCombiASM(number_of_locks_random, init_combi_random, unlock_combi_random);
        end_time = std::chrono::high_resolution_clock::now();
        elapsed_time = end_time - start_time;
        runtimes_ptr[3] += elapsed_time.count();
    }
    return runtimes_ptr;  // returns array of runtimes
}

int main(){
    int number_of_locks = 4;    // input
    std::string init_combi = "1234";
    std::string unlock_combi = "9899";
    
    int min_combi, min_combi_asm;  // output
    
    double runtime_same_length, runtime_same_length_asm, runtime_diff_length, runtime_diff_length_asm;

    if(number_of_locks != init_combi.length() || number_of_locks != unlock_combi.length()){
        std::cout << "ERROR: Input mismatch in number of locks" << std::endl;    // exits program if error occurs
        return 1;
    }

    min_combi = findMinCombi(number_of_locks, init_combi, unlock_combi);   // output
    min_combi_asm = findMinCombiASM(number_of_locks, init_combi, unlock_combi);   // output
    double* runtimes = runtimeProfiler(number_of_locks, init_combi, unlock_combi);
    runtime_same_length = runtimes[0];
    runtime_same_length_asm = runtimes[1];
    runtime_diff_length = runtimes[2];
    runtime_diff_length_asm = runtimes[3];

    std::cout << std::endl;   // prints everything in console
    std::cout << "CoE 163 SE01: Profiling and Assembly (C++)" << std::endl;
    std::cout << std::endl;
    std::cout << "Input                                         " << number_of_locks << " " << init_combi << " " << unlock_combi << std::endl;
    std::cout << "Output                                        " << min_combi << std::endl;
    std::cout << "Output (ASM)                                  " << min_combi_asm << std::endl;
    std::cout << "Runtime Case 1: Same Length                   " << runtime_same_length << " ms" << std::endl;
    std::cout << "Runtime Case 1: Same Length (ASM)             " << runtime_same_length_asm << " ms" << std::endl;
    std::cout << "Runtime Case 2: Different Length              " << runtime_diff_length << " ms" << std::endl;
    std::cout << "Runtime Case 2: Different Length (ASM)        " << runtime_diff_length_asm << " ms" << std::endl;
    std::cout << std::endl;

    // more runtime profiling
    // std::cout << "C1" << ",\t\t\t" << "C1 (ASM)" << ",\t" << "C2" << ",\t\t\t" << "C2 (ASM)" << std::endl;
    // for(int i = 0; i < 15; i++){
    //     runtimes = runtimeProfiler(number_of_locks, init_combi, unlock_combi);
    //     std::cout << runtimes[0] << ",\t\t" << runtimes[1] << ",\t\t" << runtimes[2] << ",\t\t" << runtimes[3] << std::endl;
    // }

    return 0;
}