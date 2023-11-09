# C++ Data Type with Endianness

`EndianLib` is a C++ library providing data types with specific endianness handling. This library allows you to create integers and floating-point numbers with defined endianness (big or little endian). These types are fully compatible with standard C++ types, supporting arithmetic, assignment operators, and implicit conversions.

## Installation

### Requirements
- C++ compiler (C++11 or later)
- CMake (version 3.14 or higher)

### Building and Installing from Source
1. Clone the repository:
   ```bash
   git clone https://github.com/karaketir16/EndianLib.git
   cd EndianLib
   ```

2. Build and install:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   sudo make install
   ```

### Using with CMake FetchContent

You can also integrate `EndianLib` into your project using CMake's `FetchContent` module. Add the following to your CMakeLists.txt:

```cmake
include(FetchContent)

FetchContent_Declare(
    endianlib
    GIT_REPOSITORY https://github.com/karaketir16/EndianLib.git
    GIT_TAG master # or any particular tag or commit hash
)

FetchContent_MakeAvailable(endianlib)
```

After this, link `EndianLib` to your target:

```cmake
target_link_libraries(your_target_name PRIVATE EndianLib)
```

To include instructions for using `EndianLib` as a subdirectory in your project's README file, you can add the following section:


## Using EndianLib as a Subdirectory

If you want to include `EndianLib` as a subdirectory in your CMake project, follow these steps:

1. Clone or download the `EndianLib` repository and place it in a subdirectory of your project. For example, you can create a directory called `external` in your project's root directory and put the `EndianLib` code there.

2. In your project's `CMakeLists.txt` file, include the `EndianLib` subdirectory using the `add_subdirectory()` command:

   ```cmake
   # Specify the minimum CMake version
   cmake_minimum_required(VERSION 3.14)

   # Define your project
   project(YourProjectName)

   # Add the subdirectory for EndianLib
   add_subdirectory(external/EndianLib)

   # Your project's source code and targets go here...
   ```

   Make sure to adjust the path in `add_subdirectory()` to point to the location where you placed the `EndianLib` code.

3. Now, you can use `EndianLib` in your project just like any other library. For example, you can include its headers and link against it in your target:

   ```cmake
   # Example target that uses EndianLib
   add_executable(your_target_name your_source_files.cpp)

   # Link against EndianLib
   target_link_libraries(your_target_name PRIVATE EndianLib)

   ```

   Replace `your_target_name` and `your_source_files.cpp` with your actual target and source files.

By following these steps, you can integrate `EndianLib` as a subdirectory in your CMake project and use it seamlessly.


## Usage

### Big Endian Types

```cpp
be_int8_t
be_int16_t
be_int32_t
be_int64_t

be_uint8_t
be_uint16_t
be_uint32_t
be_uint64_t

be_float
be_double
```

### Little Endian Types

```cpp
le_int8_t
le_int16_t
le_int32_t
le_int64_t

le_uint8_t
le_uint16_t
le_uint32_t
le_uint64_t

le_float
le_double
```

### Example

```cpp
#include <EndianLib/endian.hpp>

using namespace _endian_;

int main() {
    be_int32_t      k;
    le_uint32_t     l;
    int64_t         m;

    k = l = m = 0xAABB;
   //  assert(k == l && l == m && k == m);
    
    // Use the endian types as you would with native types
}
```

### Notes

- This repository is currently in the development phase and may not be fully tested. If you encounter any issues, please open an issue on the GitHub repository.
- Ensure your environment supports C++11 or higher.

## Contributing

Contributions are welcome! If you'd like to contribute, feel free to fork the repository, make changes, and submit a pull request.
