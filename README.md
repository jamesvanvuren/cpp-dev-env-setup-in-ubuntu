# Summary

A project with steps to set up a C++ development environment with Boost using Clang, Conan, CMake, and Ninja.


# Versions

This uses:

Ubuntu 22.04.2.

Ubuntu clang version 16.0.6 - suports C++ 17 fully, C++ 20 and C++ 23 partially - see https://clang.llvm.org/cxx_status.html#:~:text=Clang%20has%20support%20for%20some,std%3Dc%2B%2B2c%20option.

Conan version 2.0.7

cmake version 3.22.1

Ninja version 1.10.1




The process is:


# Fully update Ubuntu

Update Ubuntu

Fetch update software list

sudo apt-get update

sudo reboot now


Update Ubuntu software

sudo apt-get upgrade


Finally, reboot the Ubuntu box

sudo reboot now




# Set the machine's hostname.

Rename an Ubuntu machine

sudo vim /etc/hostname

sudo vim /etc/hosts

sudo reboot now





# Install mDNS so that can refer to the machine by its hostname (with ".local" appended) over the network.

Install mDNS on Ubuntu 20.04 so that can access the Ubuntu server on local area network with "hostname.local" instead of IP address

https://en.wikipedia.org/wiki/Multicast_DNS

In computer networking, the multicast DNS (mDNS) protocol resolves hostnames to IP addresses within small networks that do not include a local name server. It is a zero-configuration service, using essentially the same programming interfaces, packet formats and operating semantics as unicast Domain Name System (DNS). It was designed to work as either a stand-alone protocol or compatibly with standard DNS servers.[1] It uses IP multicast User Datagram Protocol (UDP) packets, and is implemented by the Apple Bonjour and open source Avahi software packages, included in most Linux distributions. Although the Windows 10 implementation was limited to discovering networked printers, subsequent releases resolved hostnames as well.[2] mDNS can work in conjunction with DNS Service Discovery (DNS-SD), a companion zero-configuration networking technique specified separately in RFC 6763.[3]

Protocol overview
When an mDNS client needs to resolve a hostname, it sends an IP multicast query message that asks the host having that name to identify itself. That target machine then multicasts a message that includes its IP address. All machines in that subnet can then use that information to update their mDNS caches. Any host can relinquish its claim to a name by sending a response packet with a time to live (TTL) equal to zero.

By default, mDNS exclusively resolves hostnames ending with the .local top-level domain. This can cause problems if .local includes hosts that do not implement mDNS but that can be found via a conventional unicast DNS server. Resolving such conflicts requires network-configuration changes that mDNS was designed to avoid.

https://en.wikipedia.org/wiki/Bonjour_(software)

Bonjour is Apple's implementation of zero-configuration networking (zeroconf), a group of technologies that includes service discovery, address assignment, and hostname resolution. Bonjour locates devices such as printers, other computers, and the services that those devices offer on a local network using multicast Domain Name System (mDNS) service records. The software comes built-in with Apple's macOS and iOS operating systems. Bonjour can also be installed onto computers running Microsoft Windows. Bonjour components may also be included within other software such as iTunes and Safari.

https://askubuntu.com/questions/1335936/how-to-install-and-configure-mdns-on-ubuntu-18-04

Yes, that would prove it’s working. If you have an apple device you don’t have to install anything. They use mDNS, not sure about Android.
PonJar
 May 4, 2021 at 8:51

sudo apt update

sudo apt install avahi-daemon

systemctl status avahi-daemon

If you have a firewall UDP port 5353 needs to be open.

hostname

From another machine:

ping <hostname>.local


sudo apt install avahi-utils







# Set up "ll" alias to list hidden files and folders, list folders first.

vim ~/.bashrc

Change

alias ll='ls -alF'

to

alias ll='ls --color=auto -alh --group-directories-first'




# Install Clang



If don't need the absolute latest version of clang, it's much easier to just sudo apt get clang.




Mimicing what's done in 

https://github.com/teeks99/clang-ubuntu-docker/tree/master/clang-16

That dockerfile really helped - had exact steps to get things working.



Mimic this line from https://github.com/teeks99/clang-ubuntu-docker/blob/master/clang-16/Dockerfile

ADD llvm.list /etc/apt/sources.list.d/

sudo vim /etc/apt/sources.list.d/llvm.list

Add these lines

deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-16 main
deb-src http://apt.llvm.org/jammy/ llvm-toolchain-jammy-16 main




Mimic this line from https://github.com/teeks99/clang-ubuntu-docker/blob/master/clang-16/Dockerfile

ADD llvm-snapshot.gpg.key.gpg /etc/apt/trusted.gpg.d

curl -L -O https://github.com/teeks99/clang-ubuntu-docker/raw/master/clang-16/llvm-snapshot.gpg.key.gpg        <-- Get this URL by going to https://github.com/teeks99/clang-ubuntu-docker/blob/master/clang-16/llvm-snapshot.gpg.key.gpg and right-clicking Download button.

sudo cp llvm-snapshot.gpg.key.gpg /etc/apt/trusted.gpg.d

ls -al /etc/apt/trusted.gpg.d

Make sure the file's user and group are root.




Then run these commands

sudo apt-get update

sudo apt-get install -y software-properties-common

sudo apt-get install -y gnupg

Needed for repo access

sudo apt-get install -y apt-transport-https

sudo apt-get install -y ca-certificates 


sudo apt-get update

sudo apt-get install -y ca-certificates

sudo apt-get install -y build-essential

Install Tool

sudo apt-get install -y clang-16
sudo apt-get install -y clang-tools-16
sudo apt-get install -y clang-format-16
sudo apt-get install -y python3-clang-16
sudo apt-get install -y libfuzzer-16-dev
sudo apt-get install -y lldb-16                                               <-- This installs LLDB.
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

sudo ln -s /usr/bin/clang-16 /usr/bin/clang
sudo ln -s /usr/bin/clang++-16 /usr/bin/clang++

I added this line
sudo ln -s /usr/bin/lldb-16 /usr/bin/lldb



sudo reboot now








# Install the latest stable CMake






THESE STEPS HAVE BEEN REPLACED BY NEXT STEPS

Update CMake.

sudo apt install cmake


which cmake
/usr/bin/cmake


ls -l /usr/bin | grep -i cmake
-rwxr-xr-x 1 root root     6747024 Aug 17  2022 cmake


cmake --version
cmake version 3.22.1











https://cmake.org/download/

Latest Release (3.26.4)

cd ~

curl -L -O https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-linux-x86_64.sh

chmod +x cmake-3.26.4-linux-x86_64.sh

./cmake-3.26.4-linux-x86_64.sh

cd cmake-3.26.4-linux-x86_64/bin

./cmake --version

cmake version 3.26.4

CMake suite maintained and supported by Kitware (kitware.com/cmake).

export CONAN_CMAKE_PROGRAM="/home/james/cmake-3.26.4-linux-x86_64/bin/cmake"

export PATH=/home/james/cmake-3.26.4-linux-x86_64/bin:$PATH

which cmake

cmake --version


















# Install Ninja

sudo apt install ninja-build









This is the tutorial I should have started with:

https://docs.conan.io/2/tutorial.html

https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html

This uses

[generators]
CMakeDeps
CMakeToolchain

This tutorial works.

It's only small flaw is that it uses ZLib, not Boost.







# Install Conan

cd ~
sudo pip install conan




cd ~
rm -rf /home/james/.conan2





# START EACH BUILD HERE

Need to set CC and CXX before running "conan profile detect --force", so that it detects clang instead of gcc.

export CC=clang

export CXX=clang++

export CMAKE_GENERATOR="Ninja"

conan profile detect --force

CC and CXX: clang, clang++ 
Found clang 16.0
clang>=8, using the major as version
gcc C++ standard library: libstdc++11
Detected profile:
[settings]
arch=x86_64
build_type=Release
compiler=clang
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=16
os=Linux


cat /home/james/.conan2/profiles/default









mkdir starting-conan-cmake-boost-project

cd starting-conan-cmake-boost-project











So I did read this the first time I attempted creating a Conan+CMake+Boost build.  And I thought it was important enough to follow up on.
One of the things Conan can do is generate a toolchain file that you pass in a "-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake" parameter when running CMake to generate your build files.





# Install Boost using Conan


Key point - each version of CMake "knows about" (was written to handle producing build files for) the version of Boost that was current at the time the verion of CMake was created. Therefore you should use a version of Boost created no later then when the version of CMake was created.



See when latest stable CMake was released

https://github.com/Kitware/CMake/releases

v3.26.4

May 18, 2023




What was the version of Boost at that time?

https://www.boost.org/users/history

Version 1.82.0
April 14th, 2023 03:08 GMT








https://conan.io/center/boost

Latest version of boost is 1.82.




vim conanfile.txt

[requires]
boost/1.82.0

[generators]
CMakeDeps
CMakeToolchain





# Create CMakeLists.txt

vim CMakeLists.txt

Set project name to whatever you want:

cmake_minimum_required(VERSION 3.26.4)
project(starting-conan-cmake-boost-project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.82.0 REQUIRED system filesystem)

add_executable(starting-conan-cmake-boost-project find-eventual-safe-states.cpp)
target_link_libraries(starting-conan-cmake-boost-project PRIVATE Boost::headers Boost::system Boost::filesystem)




Google search
cmake tutorial

https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html#exercise-3-adding-a-version-number-and-configured-header-file





Was able to finish creating the above CMakeLists.txt file by leaning heavily on a comment at this web page which I found when googling for "cmakelists.txt find boost"

https://gist.github.com/FlorianWolters/11225791

alexreinking commented on Feb 16

This made sense in 2014, but since it still comes up highly in the Google search results for "boost cmake", I thought I'd add the "modern CMake" way of doing this:

    cmake_minimum_required(VERSION 3.25)
    project(boost-example)

    find_package(Boost 1.70.0 REQUIRED system filesystem)

    add_executable(myapp main.cpp)
    target_link_libraries(myapp PRIVATE Boost::headers Boost::system Boost::filesystem)

Since version 1.70.0, Boost provides its own CMake package complete with imported targets. These set everything up for you when you link to them.

This is also pretty well documented at https://cmake.org/cmake/help/latest/module/FindBoost.html in one of the examples at the bottom.







# Create the source code

vim starting-conan-cmake-boost-project.cpp

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







https://stackoverflow.com/questions/59509768/is-there-a-way-to-tell-conan-to-use-different-cmake-executable-durning-conan-ins






cd /home/james/Interviews/leetcode/starting-conan-cmake-boost-project

rm -rf build

rm CMakeUserPresets.json

export CONAN_CMAKE_PROGRAM="/home/james/cmake-3.26.4-linux-x86_64/bin/cmake"

export CMAKE_GENERATOR="Ninja"






This step creates the "build" folder and the "CMakeUserPresets.json" file.


Build debug version of Boost:
conan install . --output-folder=build --build=missing -s build_type=Debug

OR

Build release version of Boost:
conan install . --output-folder=build --build=missing


For reference, see 

https://docs.conan.io/2.0/tutorial/consuming_packages/different_configurations.html

and

https://docs.conan.io/2.0/examples/dev_flow/debug/step_into_dependencies.html




If need to capture output:

conan install . --output-folder=build --build=missing >conan-install-output.txt 2>&1

less --line-numbers --IGNORE-CASE conan-install-output.txt



If you want to install everything fresh, but you see messages like the following:

bzip2/1.0.8: Already installed! (1 of 4)
libbacktrace/cci.20210118: Already installed! (2 of 4)
zlib/1.2.13: Already installed! (3 of 4)
boost/1.82.0: Already installed! (4 of 4)


Then do the following:


Conan 2 currently stores its packages under

/home/james/.conan2/p


Conan 2 docs are under

https://docs.conan.io/2


Google search

remove package site:https://docs.conan.io/2


https://docs.conan.io/2.0/reference/commands/remove.html

conan remove -c "*"

Remove summary:
Local Cache
  boost/1.82.0#902463606663219fc8c6d2102f1b8c6a: Removed recipe and all binaries
  bzip2/1.0.8#411fc05e80d47a89045edc1ee6f23c1d: Removed recipe and all binaries
  libbacktrace/cci.20210118#ec1aa63bbc10145c6a299e68e711670c: Removed recipe and all binaries
  zlib/1.2.13#e377bee636333ae348d51ca90874e353: Removed recipe and all binaries


Then install the packages:

conan install . --output-folder=build --build=missing >conan-install-output.txt 2>&1


Output includes

Component configuration:

    - atomic                   : building
    - chrono                   : building
    - container                : building
    - context                  : building
    - contract                 : building
    - coroutine                : building
    - date_time                : building
    - exception                : building
    - fiber                    : building
    - filesystem               : building
    - graph                    : building
    - graph_parallel           : not building
    - headers                  : not building
    - iostreams                : building
    - json                     : building
    - locale                   : building
    - log                      : building
    - math                     : building
    - mpi                      : not building
    - nowide                   : building
    - program_options          : building
    - python                   : not building
    - random                   : building
    - regex                    : building
    - serialization            : building
    - stacktrace               : building
    - system                   : building
    - test                     : building
    - thread                   : building
    - timer                    : building
    - type_erasure             : building
    - url                      : building
    - wave                     : building

...

======== Finalizing install (deploy, generators) ========
conanfile.txt: Writing generators to /home/james/Interviews/leetcode/simple_cmake_project/build
conanfile.txt: Generator 'CMakeDeps' calling 'generate()'
conanfile.txt: Generator 'CMakeToolchain' calling 'generate()'
conanfile.txt: CMakeToolchain generated: conan_toolchain.cmake


conanfile.txt: Preset 'conan-release' added to CMakePresets.json. Invoke it manually using '

cmake --preset conan-release                                                                            <-- So we'll be doing this one, because our version of CMake is >=3.23

' if using CMake>=3.23


conanfile.txt: If your CMake version is not compatible with CMakePresets (<3.23) call cmake like: '

cmake <path> -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=/home/james/Interviews/leetcode/simple_cmake_project/build/conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Release


conanfile.txt: CMakeToolchain generated: CMakePresets.json
conanfile.txt: CMakeToolchain generated: ../CMakeUserPresets.json
conanfile.txt: Generating aggregated env files
conanfile.txt: Generated aggregated env files: ['conanbuild.sh', 'conanrun.sh']
Install finished successfully




The generated CMakePresets.json file

/home/james/Interviews/leetcode/starting-conan-cmake-boost-project/build/CMakePresets.json

contains this text:

    "configurePresets": [
        {
            "name": "conan-release",
            "displayName": "'conan-release' config",
            "description": "'conan-release' configure using 'Unix Makefiles' generator",
            "generator": "Unix Makefiles",
            "cacheVariables": {
                "CMAKE_POLICY_DEFAULT_CMP0091": "NEW",
                "CMAKE_BUILD_TYPE": "Release"
            },
            "toolchainFile": "/home/james/Interviews/leetcode/simple_cmake_project/build/conan_toolchain.cmake",
            "binaryDir": "/home/james/Interviews/leetcode/simple_cmake_project/build"
        }

In other words, it just points CMake at the conan_toolchain.cmake toolchain file.










Find where the boost filesystem library created by Conan lives:

cd /home/james/.conan2

find /home/james/.conan2 -iname '*libboost_filesystem*'

./p/b/boostbb4ee73c50288/b/build-release/boost/bin.v2/libs/filesystem/build/clng-lnx-16/rls/lnk-sttc/nm-on/thrd-mlt/vsblt-hdn/libboost_filesystem-variant-static.cmake
./p/b/boostbb4ee73c50288/b/build-release/boost/bin.v2/libs/filesystem/build/clng-lnx-16/rls/lnk-sttc/nm-on/thrd-mlt/vsblt-hdn/libboost_filesystem.a
./p/b/boostbb4ee73c50288/p/lib/libboost_filesystem.a



Find where the boost filesystem headers created by Conan live:

find /home/james/.conan2 -iname 'filesystem.hpp'

/home/james/.conan2/p/b/boost8164c4ff728cc/p/include/boost/process/filesystem.hpp
/home/james/.conan2/p/b/boost8164c4ff728cc/p/include/boost/nowide/filesystem.hpp
/home/james/.conan2/p/b/boost8164c4ff728cc/p/include/boost/gil/io/detail/filesystem.hpp
/home/james/.conan2/p/b/boost8164c4ff728cc/p/include/boost/filesystem.hpp
/home/james/.conan2/p/boostb0117c3bfd046/s/src/boost/process/filesystem.hpp
/home/james/.conan2/p/boostb0117c3bfd046/s/src/boost/nowide/filesystem.hpp
/home/james/.conan2/p/boostb0117c3bfd046/s/src/boost/gil/io/detail/filesystem.hpp
/home/james/.conan2/p/boostb0117c3bfd046/s/src/boost/filesystem.hpp                      <-- Use "/home/james/.conan2/p/boostb0117c3bfd046/s/src" from this path.








# Run CMake to create the Makefile


These next commands create the following files and folders in the "build" folder:

CMakeFiles - a folder

CMakeCache.txt

cmake_install.cmake

Makefile



The commands are:

cd build

export CONAN_CMAKE_PROGRAM="/home/james/cmake-3.26.4-linux-x86_64/bin/cmake"

export PATH=/home/james/cmake-3.26.4-linux-x86_64/bin:$PATH

cmake --version

    cmake version 3.26.4



These commands run CMake to consume CMakeLists.txt in the parent folder and produce the file "Makefile" in the current "build" folder:




Build debug - need to have built the debug version of Boost first:

cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug


OR


Build release - need to have built the release version of Boost first:

cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release






For reference, see
https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html






To see the different compiler and linker options for debug and release, after generating make files, look at the files:

/home/james/Interviews/leetcode/find-eventual-safe-states/build/CMakeFiles/find-eventual-safe-states.dir/flags.make

/home/james/Interviews/leetcode/find-eventual-safe-states/build/CMakeFiles/find-eventual-safe-states.dir/link.txt









# Build


These next commands create the following files:

CMakeFiles/find-eventual-safe-states.dir/main.cpp.o

CMakeFiles/find-eventual-safe-states.dir/main.cpp.d

find-eventual-safe-states



Commands are:

cmake --build .


If the output looks like

[1/2] Building CXX object CMakeFiles/dining-philosophers.dir/main.cpp.o
FAILED: CMakeFiles/dining-philosophers.dir/main.cpp.o 
/usr/bin/clang++   -m64 -stdlib=libstdc++ -g -std=gnu++17 -MD -MT CMakeFiles/dining-philosophers.dir/main.cpp.o -MF CMakeFiles/dining-philosophers.dir/main.cpp.o.d -o CMakeFiles/dining-philosophers.dir/main.cpp.o -c /home/james/Interviews/dining-philosophers/main.cpp
/home/james/Interviews/dining-philosophers/main.cpp:1:10: fatal error: 'boost/filesystem.hpp' file not found
#include <boost/filesystem.hpp>
         ^~~~~~~~~~~~~~~~~~~~~~
1 error generated.
ninja: build stopped: subcommand failed.

it probably means you only built the release version of Boost and are now building the debug version of the program, or vice versa.





For reference, see
https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html








# Run

./starting-conan-cmake-boost-project

It actually works better than the versions built without using Conan - it lists the files in the current folder instead of just generating a garbled error message.




If need to load a non-statically-linked Boost library at runtime

export LD_LIBRARY_PATH=/home/james/Interviews/starting-projects/starting-cmake-boost-project/boost/lib











# To uninstall boost

To uninstall debian version
sudo apt-get -y --purge remove libboost-all-dev libboost-doc libboost-dev

To uninstall the version which we installed from source
sudo rm -rf /usr/local/include/boost
sudo rm -f /usr/local/lib/libboost_*

To uninstall the one we had Conan install 

?????








# To install LLDB

lldb
Command 'lldb' not found, but can be installed with:
sudo apt install lldb
















# Configure Visual Studio Code to find the Boost header files.

Get Visual Studio Code intellisense working.

In Visual Studio Code, hit Shift-Cmd-P.

Type

C/C++: Edit configurations (UI)




cd ~/.conan2
find ~/.conan2 -iname 'filesystem.hpp'

/home/james/.conan2/p/b/boosta6dfccc3b8dd0/p/include/boost/process/filesystem.hpp
/home/james/.conan2/p/b/boosta6dfccc3b8dd0/p/include/boost/nowide/filesystem.hpp
/home/james/.conan2/p/b/boosta6dfccc3b8dd0/p/include/boost/gil/io/detail/filesystem.hpp
/home/james/.conan2/p/b/boosta6dfccc3b8dd0/p/include/boost/filesystem.hpp
/home/james/.conan2/p/b/boost193bd5c3451ba/p/include/boost/process/filesystem.hpp
/home/james/.conan2/p/b/boost193bd5c3451ba/p/include/boost/nowide/filesystem.hpp
/home/james/.conan2/p/b/boost193bd5c3451ba/p/include/boost/gil/io/detail/filesystem.hpp
/home/james/.conan2/p/b/boost193bd5c3451ba/p/include/boost/filesystem.hpp
/home/james/.conan2/p/boostb0117c3bfd046/s/src/boost/process/filesystem.hpp
/home/james/.conan2/p/boostb0117c3bfd046/s/src/boost/nowide/filesystem.hpp
/home/james/.conan2/p/boostb0117c3bfd046/s/src/boost/gil/io/detail/filesystem.hpp
/home/james/.conan2/p/boostb0117c3bfd046/s/src/boost/filesystem.hpp                          <-- try "/home/james/.conan2/p/boostb0117c3bfd046/s/src" from this path.





Back in Visual Studio Code, in the "Include path" section, add this line:

/home/james/.conan2/p/boost0eafd9621eb61/s/src

Hit Cmd-S to save.

The .vscode folder in the project folder should now have a file named

c_cpp_properties.json

containing

{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/home/james/.conan2/p/boost0eafd9621eb61/s/src"
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

Now working. Getting autocomplete for Boost library code.

Very slick.












# DEBUG USING LLDB AND VISUAL STUDIO CODE



lldb --version

which lldb

/usr/bin/lldb

Apparently this was installed when I installed Clang





Searching for LLDB in Visual Studio Code extensions marketplace finds this as the most-used LLDB extension:

CodeLLDB
v1.9.2
Vadim Chugunov
3,863,761
(79)
A native debugger powered by LLDB. Debug C++, Rust and other compiled languages.

Installed it while VS Code was connected to 192.168.0.11 and the message

Extension is enabled on 'SSH: 192.168.0.11'

was displayed.


https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb

More information

CodeLLDB User's Manual - how to use this extension.
https://github.com/vadimcn/codelldb/blob/v1.9.2/MANUAL.md

Debugging in VS Code - if you are new to VSCode debugging.
https://code.visualstudio.com/docs/editor/debugging

LLDB Tutorial - all of LLDB's CLI commands and scripting features may be used in CodeLLDB.
https://lldb.llvm.org/use/tutorial.html

Wiki pages - troubleshooting and other tips and tricks.
https://github.com/vadimcn/codelldb/wiki

Discussions - for questions and discussions.
https://github.com/vadimcn/codelldb/discussions





In VS Code, select the Run and debug icon down the left side.

Click create a launch.json file.

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

Click Show all automatic debug configurations.

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


Edit it to look like this:

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
            "program": "${workspaceFolder}/build/find-eventual-safe-states",
            "args": [],
            "cwd": "${workspaceFolder}/build"
        }

    ]
}

Check that are building a debug version of project.

Then set your breakpoints and launch the "launch" config.



