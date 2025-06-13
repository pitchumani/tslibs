# TSLIBS : Thread safe libraries
## Idea for Thread-Safe Data Structures:
**Concept:** Implement thread-safe versions of common data structures (e.g., queue, stack, map) using mutexes and condition variables.

**Multithreading:** Ensure concurrent access to the data structure is synchronized to avoid data races and inconsistencies.

**Design Patterns:**
- Monitor Object: Use a monitor object (like a mutex with condition variables) to protect access to the shared data structure.

## Features:
- **Thread-Safe Stack:** A stack implementation that allows multiple threads to push and pop elements safely.
- **Thread-Safe Queue:** To be implemented.
- **Thread-Safe Map:** To be implemented.

## Usage:
```cpp
#include <tsstack>
#include <iostream>
int main() {
    tslibs::TSStack<int> stack;

    // Push elements onto the stack
    stack.push(1);
    stack.push(2);
    stack.push(3);

    // Pop elements from the stack
    int value;
    while (stack.pop(value)) {
        std::cout << "Popped: " << value << std::endl;
    }

    return 0;
}
```

## How to Build:
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/pitchumani/tslibs.git
   cd tslibs
   ```
2. **Build the Project:**
   ```bash
   mkdir build
   cd build
   cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/install
   make && make install
   ```
   Below files are expected to be installed (in `/path/to/install`):
   - include/tsstack

3. **Build and Run Examples:**
   ```bash
   cd examples
   mkdir build
   cd build
   cmake ..
   make
   make run_examples
   ```
   The stack example is expected to fail randomly due to the concurrent access issue while multithreading.
   To run individual examples, you can use:
   ```bash
   make run_tsstack_example
   make run_stack_example
   ```
   or directly execute the binaries:
   ```bash
   ./tsstack_example
   ./stack_example
   ```

4. **Run Tests:**
   ```bash
   TBD
   ```