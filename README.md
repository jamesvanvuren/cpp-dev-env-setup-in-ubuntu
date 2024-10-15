# Summary

A project with steps to set up a C++ development environment with Boost using Clang, Conan, CMake, and Ninja.


# Versions

This example uses:

Ubuntu 24.04.1 LTS.

Clang 18.1.3 - This version of Clang suports C++ 17 fully, C++ 20 and C++ 23 partially - see https://clang.llvm.org/cxx_status.html#:~:text=Clang%20has%20support%20for%20some,std%3Dc%2B%2B2c%20option.

Conan 2.8.0

CMake 3.30.5

Ninja 1.11.1-2


# Install Clang

Identify the version of Clang you wish to install at https://clang.llvm.org/cxx_status.html

For example, if you want to use all features of C++ 17, you will need to install at least Clang version 5.

As of this writing, the latest version of Clang is 16, which has full support for C++ 17 and partial support for C++ 20, 23, and 2c.

First try installing Clang and LLDB with

sudo apt install clang

sudo apt install lldb

Test the version of Clang

clang -v

If you need a more recent version of clang, do the following.

Uninstall clang

sudo apt remove clang

Locate the Dockerfile for the version of Clang you wish to install under https://github.com/teeks99/clang-ubuntu-docker/tree/master

Example

https://github.com/teeks99/clang-ubuntu-docker/tree/master/clang-16/Dockerfile

Mimic the steps in this Dockerfile.

Add the clang repository

sudo vim /etc/apt/sources.list.d/llvm.list

Add lines for the LLVM toolchain repository.

deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-<CLANG VERSION> main
deb-src http://apt.llvm.org/jammy/ llvm-toolchain-jammy-<CLANG VERSION> main

Example

deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-16 main
deb-src http://apt.llvm.org/jammy/ llvm-toolchain-jammy-16 main

Add the LLVM GPG key

In the following command, get the URL of the LLVM snapshot GPG key by opening 

https://github.com/teeks99/clang-ubuntu-docker/blob/master/clang-<CLANG VERSION>/llvm-snapshot.gpg.key.gpg

in a web browser and right-clicking the "Download" button.

Example URL

https://github.com/teeks99/clang-ubuntu-docker/blob/master/clang-16/llvm-snapshot.gpg.key.gpg 

Download the key

curl -L -O <URL of the LLVM snapshot GPG key>

Example

curl -L -O https://github.com/teeks99/clang-ubuntu-docker/raw/master/clang-16/llvm-snapshot.gpg.key.gpg

Install the key

sudo cp llvm-snapshot.gpg.key.gpg /etc/apt/trusted.gpg.d

Make sure the key file's user and group are root.

sudo chown root:root /etc/apt/trusted.gpg.d

Install the software-properties-common package

sudo apt-get install -y software-properties-common

Install packages needed to access the LLVM repositories

sudo apt-get install -y gnupg

sudo apt-get install -y apt-transport-https

sudo apt-get install -y ca-certificates 

sudo apt-get update

sudo apt-get install -y ca-certificates

sudo apt-get install -y build-essential

Install Clang

Get the commands to install Clang from https://github.com/teeks99/clang-ubuntu-docker/tree/master/clang-16/Dockerfile

The various version numbers may be different from the following example for the version of Clang you are installing.

Example commands

sudo apt-get install -y clang-16
sudo apt-get install -y clang-tools-16
sudo apt-get install -y clang-format-16
sudo apt-get install -y python3-clang-16
sudo apt-get install -y libfuzzer-16-dev
sudo apt-get install -y lldb-16
sudo apt-get install -y lld-16
sudo apt-get install -y libc++-16-dev
sudo apt-get install -y libc++abi-16-dev
sudo apt-get install -y libomp-16-dev
sudo apt-get install -y libunwind-16-dev
sudo apt-get install -y libpolly-16-dev
sudo apt-get install -y libclc-16-dev
sudo apt-get install -y # MLIR
sudo apt-get install -y libmlir-15-dev mlir-15-tools
sudo apt-get install -y # Bolt
sudo apt-get install -y # Doesn't work on aarch64 libbolt-16-dev bolt-16
sudo apt-get install -y # LLVM WASM
sudo apt-get install -y libclang-rt-16-dev-wasm32
sudo apt-get install -y libclang-rt-16-dev-wasm64
sudo apt-get install -y libc++-16-dev-wasm32
sudo apt-get install -y libc++abi-16-dev-wasm32
sudo apt-get install -y libclang-rt-16-dev-wasm32
sudo apt-get install -y libclang-rt-16-dev-wasm64

 Make an alias for the versioned executable

sudo ln -s /usr/bin/clang-<CLANG VERSION> /usr/bin/clang
sudo ln -s /usr/bin/clang++-<CLANG VERSION> /usr/bin/clang++
sudo ln -s /usr/bin/lldb-<CLANG VERSION> /usr/bin/lldb

Example

sudo ln -s /usr/bin/clang-16 /usr/bin/clang
sudo ln -s /usr/bin/clang++-16 /usr/bin/clang++
sudo ln -s /usr/bin/lldb-16 /usr/bin/lldb

Reboot

sudo reboot now


# Install the latest stable CMake

In a web browser, open https://cmake.org/download and identify the latest version of CMake

Example commands for latest CMake release at the time of this writing (3.30.5)

cd ~

curl -L -O https://github.com/Kitware/CMake/releases/download/v3.30.5/cmake-3.30.5-linux-x86_64.sh

chmod +x cmake-3.30.5-linux-x86_64.sh

./cmake-3.30.5-linux-x86_64.sh

Enter y to accept the license.

Enter Y to install in a subdirectory named "cmake-3.30.5-linux-x86_64".

export PATH=/home/<username>/cmake-3.30.5-linux-x86_64/bin:$PATH

Test that you are using the version of CMake you just installed

which cmake

cmake --version

# Install Ninja

sudo apt install ninja-build

# Install Python

sudo apt install python3

Then always run Python with

python3



# Install pip

sudo apt install python3-pip




# Install venv

https://docs.python-guide.org/dev/virtualenvs/

sudo apt install python3-virtualenv

virtualenv --version




# Create a test project

cd ~

mkdir starting-conan-cmake-boost-project

cd starting-conan-cmake-boost-project




# Create a venv for the project folder

cd into the project folder.

virtualenv -p /usr/bin/python3 venv

source venv/bin/activate

To leave the venv

deactivate



# Install Conan

With the venv activated:

pip install conan

rm -rf /home/<your username>/.conan2

# Tell Conan which CMake to use

Tell the Conan package manager where CMake is installed

export CONAN_CMAKE_PROGRAM="/home/<username>/cmake-3.30.5-linux-x86_64/bin/cmake"

# Tell Conan to use Clang as its C++ compiler

Set CC and CXX before running "conan profile detect --force", so that it detects clang instead of gcc.

export CC=clang

export CXX=clang++

export CMAKE_GENERATOR="Ninja"

conan profile detect --force

# Identify the version of the Boost libraries you wish to use

Each version of CMake "knows about" (was written to handle producing build files for) the version of Boost that was current at the time the verion of CMake was created. Therefore you should use a version of Boost created no later then when the version of CMake was created.

Identify your version of CMake

cmake --version

Identify when that version of CMake was released at https://github.com/Kitware/CMake/releases

Example

v3.30.5
Oct. 15, 2024

Identify what the version of Boost was at that same time at https://www.boost.org/users/history

Example

Version 1.86.0
August 14th, 2024 16:07 GMT

Go to https://conan.io/center and search for "boost". Make sure the latest boost version supported by Conan is greater than or equal to the version of Boost you want to use.

Example search result

https://conan.io/center/recipes/boost?version=1.86.0


# Create a Conan package file

vim conanfile.txt

Edit the file to use the version of Boost you identified.

Example conanfile.txt contents

[requires]
boost/1.86.0

[generators]
CMakeDeps
CMakeToolchain

# Create CMakeLists.txt

vim CMakeLists.txt

Example file contents for C++ 17 using CMake 3.30.5 and Boost 1.86:

cmake_minimum_required(VERSION 3.30.5)
project(starting-conan-cmake-boost-project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.86.0 REQUIRED system filesystem)

add_executable(starting-conan-cmake-boost-project starting-conan-cmake-boost-project.cpp)
target_link_libraries(starting-conan-cmake-boost-project PRIVATE Boost::headers Boost::system Boost::filesystem)

# Create the source code

For example:

vim starting-conan-cmake-boost-project.cpp

Example file contents:

#include <boost/filesystem.hpp>
#include <iostream>

using namespace std; 
using namespace boost::filesystem;

int main()
{
    boost::filesystem::directory_iterator iterator(string("."));
    for(; iterator != boost::filesystem::directory_iterator(); ++iterator)
    {
        cout << (iterator->path().filename()) << endl;
    }

    boost::filesystem::path full_path( boost::filesystem::current_path() );
    std::cout << "Current path is : " << full_path << std::endl;

    return 0;

}

# Install the Boost library using Conan

cd <project parent folder>/starting-conan-cmake-boost-project

rm -rf build

rm CMakeUserPresets.json

export CONAN_CMAKE_PROGRAM="/home/james/cmake-3.30.5-linux-x86_64/bin/cmake"

export CMAKE_GENERATOR="Ninja"

This step creates the "build" folder and the "CMakeUserPresets.json" file.

Build the debug version of Boost:

conan install . --output-folder=build --build=missing -s build_type=Debug

Build the release version of Boost:

conan install . --output-folder=build --build=missing

For reference regarding building the debug and release versions of packages, see 

https://docs.conan.io/2.0/tutorial/consuming_packages/different_configurations.html

and

https://docs.conan.io/2.0/examples/dev_flow/debug/step_into_dependencies.html




# Deactivate the venv

Now that you are finished using Conan, deactivate the python venv.

deactivate




# Run CMake to create the Makefile

cd build

export CONAN_CMAKE_PROGRAM="/home/james/cmake-3.30.5-linux-x86_64/bin/cmake"

export PATH=/home/james/cmake-3.30.5-linux-x86_64/bin:$PATH

cmake --version

These commands create the following files and folders in the "build" folder: CMakeFiles (a folder), CMakeCache.txt, cmake_install.cmake, Makefile

Build debug - you need to have built the debug version of Boost first, or the build will fail:

cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug

OR

Build release - need to have built the release version of Boost first, or the build will fail:

cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

For reference, see
https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html



# Build the Project

cmake --build .

This will create the intermediate build files and the executable file, which should be named the same as your project.

Example:

CMakeFiles/starting-conan-cmake-boost-project.dir/main.cpp.o

CMakeFiles/starting-conan-cmake-boost-project.dir/main.cpp.d

starting-conan-cmake-boost-project (the executable)

If the output contains an error like

    [1/2] Building CXX object CMakeFiles/dining-philosophers.dir/main.cpp.o
    FAILED: CMakeFiles/dining-philosophers.dir/main.cpp.o 
    /usr/bin/clang++   -m64 -stdlib=libstdc++ -g -std=gnu++17 -MD -MT CMakeFiles/dining-philosophers.dir/main.cpp.o -MF CMakeFiles/dining-philosophers.dir/main.cpp.o.d -o CMakeFiles/dining-philosophers.dir/main.cpp.o -c /home/james/Interviews/dining-philosophers/main.cpp
    /home/james/Interviews/dining-philosophers/main.cpp:1:10: fatal error: 'boost/filesystem.hpp' file not found
    #include <boost/filesystem.hpp>
            ^~~~~~~~~~~~~~~~~~~~~~
    1 error generated.
    ninja: build stopped: subcommand failed.

it probably means you only built the release version of Boost and are now building the debug version of the program, or you only build the debug version of Boost and are now building the release version of then program.

For reference, see
https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html



# Run

Example:

./starting-conan-cmake-boost-project

If you are using the example code from above, it should list the files in the current folder.

If you need to load a non-statically-linked Boost library at runtime

export LD_LIBRARY_PATH=/home/james/Interviews/starting-projects/starting-cmake-boost-project/boost/lib



# Configure Visual Studio Code to find the Boost header files.

Find where the boost filesystem library created by Conan lives:

cd ~/.conan2

find ~/.conan2 -iname '*libboost_filesystem*'

Example output:

/home/<username>/.conan2/p/b/boost50b2e067d28a3/b/build-release/boost/bin.v2/libs/filesystem/build/clng-lnx-18/rls/x86_6/cxstd-17-gnu/lnk-sttc/nm-on/thrd-mlt/vsblt-hdn/libboost_filesystem.a
/home/<username>/.conan2/p/b/boost50b2e067d28a3/b/build-release/boost/bin.v2/libs/filesystem/build/clng-lnx-18/rls/x86_6/cxstd-17-gnu/lnk-sttc/nm-on/thrd-mlt/vsblt-hdn/libboost_filesystem-variant-static.cmake
/home/<username>/.conan2/p/b/boost50b2e067d28a3/p/lib/libboost_filesystem.a
/home/<username>/.conan2/p/b/booste8cee9d88e893/b/build-debug/boost/bin.v2/libs/filesystem/build/clng-lnx-18/dbg/x86_6/cxstd-17-gnu/lnk-sttc/nm-on/thrd-mlt/vsblt-hdn/libboost_filesystem.a
/home/<username>/.conan2/p/b/booste8cee9d88e893/b/build-debug/boost/bin.v2/libs/filesystem/build/clng-lnx-18/dbg/x86_6/cxstd-17-gnu/lnk-sttc/nm-on/thrd-mlt/vsblt-hdn/libboost_filesystem-variant-static.cmake
/home/<username>/.conan2/p/b/booste8cee9d88e893/p/lib/libboost_filesystem.a

Find where the boost filesystem headers created by Conan live:

find ~/.conan2 -iname 'filesystem.hpp'

Example output:

/home/<username>/.conan2/p/b/boost50b2e067d28a3/p/include/boost/process/v1/filesystem.hpp
/home/<username>/.conan2/p/b/boost50b2e067d28a3/p/include/boost/process/filesystem.hpp
/home/<username>/.conan2/p/b/boost50b2e067d28a3/p/include/boost/gil/io/detail/filesystem.hpp
/home/<username>/.conan2/p/b/boost50b2e067d28a3/p/include/boost/nowide/filesystem.hpp
/home/<username>/.conan2/p/b/boost50b2e067d28a3/p/include/boost/filesystem.hpp
/home/<username>/.conan2/p/b/booste8cee9d88e893/p/include/boost/process/v1/filesystem.hpp
/home/<username>/.conan2/p/b/booste8cee9d88e893/p/include/boost/process/filesystem.hpp
/home/<username>/.conan2/p/b/booste8cee9d88e893/p/include/boost/gil/io/detail/filesystem.hpp
/home/<username>/.conan2/p/b/booste8cee9d88e893/p/include/boost/nowide/filesystem.hpp
/home/<username>/.conan2/p/b/booste8cee9d88e893/p/include/boost/filesystem.hpp
/home/<username>/.conan2/p/boost25609d7719073/s/src/boost/process/v1/filesystem.hpp
/home/<username>/.conan2/p/boost25609d7719073/s/src/boost/process/filesystem.hpp
/home/<username>/.conan2/p/boost25609d7719073/s/src/boost/gil/io/detail/filesystem.hpp
/home/<username>/.conan2/p/boost25609d7719073/s/src/boost/nowide/filesystem.hpp
/home/<username>/.conan2/p/boost25609d7719073/s/src/boost/filesystem.hpp             <-- Use the "/home/<username>/.conan2/p/boostb0117c3bfd046/s/src" part of this path.


In Visual Studio Code, hit Shift-Cmd-P.

Type

    C/C++: Edit configurations (UI)

Back in Visual Studio Code, in the "Include path" section, add this line:

Example

    /home/<username>/.conan2/p/boostb0117c3bfd046/s/src

Hit Cmd-S to save.

The .vscode folder in the project folder should now have a file named

c_cpp_properties.json

containing something like:

{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/home/<username>/.conan2/p/boostb0117c3bfd046/s/src"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-clang-x64"
        }
    ],
    "version": 4
}

Restart Visual Studio Code.

You should now get autocomplete for Boost library code.



# Debug using LLDB and Visual Studio Code

In Visual Studio Code, open the extensions marketplace.

Search for "lldb".

This currently finds the following most-used LLDB extension:

    CodeLLDB v1.9.2 by Vadim Chugunov

Click the install button.

During installation, it should display a message like

In VS Code, select the triangular "Run and debug" icon on the left side.

Click "Create a launch.json file".

In the "Select debugger" select box, select "C++ (GDB/LLDB) (suggested)".

It will create a launch.json file like this:

{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
    ]
}

Click "Show all automatic debug configurations".

It will place your cursor in a command edit with the text "debug " filled in.

Below it, click "Add configuration      configure".

From the list, click "CodeLLDB: Launch".

It will add a configuration to the launch.json file so that it looks like this:

{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "type": "lldb",
            "request": "launch",
            "name": "Launch",
            "program": "${workspaceFolder}/<program>",
            "args": [],
            "cwd": "${workspaceFolder}"
        }

    ]
}

This matches the documentation for CodeLLDB at https://github.com/vadimcn/codelldb/blob/v1.9.2/MANUAL.md#starting-a-new-debug-session

Edit the launch.json file to look like this:

Example

{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "type": "lldb",
            "request": "launch",
            "name": "Launch",
            "program": "${workspaceFolder}/build/starting-cmake-boost-project",
            "args": [],
            "cwd": "${workspaceFolder}/build"
        }

    ]
}

Check that you are building a debug version of project.

Then set breakpoints in your C++ code and launch the "launch" config.
