#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>
#include <iomanip>

const size_t MEMORY_SIZE = 2LL * 1024 * 1024 * 1024; // 2GB
const size_t CHUNK_SIZE = 4096; // 4KB (typical page size)
const size_t NUM_CHUNKS = MEMORY_SIZE / CHUNK_SIZE;
const int SEQUENTIAL_ITERATIONS = 10000;
const int RANDOM_ITERATIONS = 10000;

// Function to perform sequential memory access
void sequentialAccess(char* memory, size_t size) {
    std::cout << "\n=== Sequential Memory Access Test ===\n";
    std::cout << "Accessing " << size / (1024*1024) << " MB sequentially...\n";
    
    auto start = std::chrono::steady_clock::now();
    
    // Write phase
    for (int iter = 0; iter < SEQUENTIAL_ITERATIONS; iter++) {
        for (size_t i = 0; i < size; i += CHUNK_SIZE) {
            memory[i] = (char)(i % 256);
        }
        
        // Progress indicator
        if (iter % 1000 == 0) {
            std::cout << "Sequential iteration " << iter << " completed\n";
        }
    }
    
    auto end = std::chrono::steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "Sequential access completed in " << total << " ms\n";
    std::cout << "Average time per iteration: " << (double)total / SEQUENTIAL_ITERATIONS << " ms\n";
}

// random memory access
void randomAccess(char* memory, size_t size) {
    std::cout << "\n=== Random Memory Access Test ===\n";
    std::cout << "Performing " << RANDOM_ITERATIONS << " random accesses...\n";
    
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, (size / CHUNK_SIZE) - 1);
    
    auto start = std::chrono::steady_clock::now();
    
    for (int iter = 0; iter < RANDOM_ITERATIONS; iter++) {
        // Generate random chunk index
        size_t chunkIndex = dis(gen);
        size_t address = chunkIndex * CHUNK_SIZE;
        
        // Access memory at random location
        memory[address] = (char)(iter % 256);
        
        // Read back to ensure access
        volatile char temp = memory[address];
        
        if (iter % 1000 == 0) {
            std::cout << "Random iteration " << iter << " completed\n";
        }
    }
    
    auto end = std::chrono::steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "Random access completed in " << total << " ms\n";
    std::cout << "Average time per access: " << (double)total / RANDOM_ITERATIONS << " ms\n";
}

int main() {
    std::cout << "Virtual Memory Demonstration Program\n";
    std::cout << "====================================\n";
    std::cout << "This program will allocate " << MEMORY_SIZE / (1024*1024*1024) << " GB of memory\n";
    std::cout << "and demonstrate virtual memory behavior.\n";

    
    // Allocate large memory block
    std::cout << "\nAllocating " << MEMORY_SIZE / (1024*1024*1024) << " GB of memory...\n";
    
    char* largeMemory = nullptr;
    
    try {
        largeMemory = new char[MEMORY_SIZE];
        std::cout << "Memory allocation successful!\n";
        std::cout << "Memory allocated at address: " << (void*)largeMemory << '\n';
    } catch (const std::bad_alloc& e) {
        std::cout << "Memory allocation failed: " << e.what() << '\n';
        std::cout << "Try reducing MEMORY_SIZE or ensure sufficient virtual memory.\n";
        return 1;
    }
    
    // Perform sequential access test
    sequentialAccess(largeMemory, MEMORY_SIZE);
   
    // Perform random access test
    randomAccess(largeMemory, MEMORY_SIZE);
    
    delete[] largeMemory;
    std::cout << "Memory deallocated. Program complete.\n";
    
    return 0;
}