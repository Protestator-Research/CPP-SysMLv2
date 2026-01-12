q# C++ SysML v2 Implementation
This library gives an implementation of the SysML v2 standard and KerML standard. This allows developers to implment own applications with this library. The existence of this library is the proof, that SysML v2 can be implemented in C++.

## Table of Contents

[toc]

## Build Status
The System and Tests: [![C/C++ CI](https://github.com/Protestator-Research/CPP-SysMLv2/actions/workflows/mainbuild.yml/badge.svg)](https://github.com/Protestator-Research/CPP-SysMLv2/actions/workflows/mainbuild.yml)

## Licensing 

This software is licensed under the GPL v3, allowing a free and open source editing of the code. We want to offer you the option to use this libary also for commercial project. This will be done in a later step, since we are currently developing this from the ground up.



## Building and usage

We offer the build work flow with conan and standalone.

### Conan Build

One of the Todos we have is to offer this library in the conan central repositories. But this can be done, if the implementation is done. You will be informed.

With this build the conan file is provided, allowing you to install the dependencies and then to build the files.

```bash
mkdir build && cd build
conan install ..
conan build ..
```



### Standalone Build

Please install the dependencies required for the build:

#### Dependencies

| Dependency        | Version    |
| ----------------- | ---------- |
| antlr4-cppruntime | 4.13.1     |
| boost             | Min 1.83.0 |
| nlohmann_json     | Min 3.11.2 |
| date              | 3.0.1      |
| gtest             | 1.14.0     |

We are working on an option to only use a part of the dependencies. This will be depended on the modules that are used.

#### Build

For the build we require you to have CMake installed. This allows to have one implementation for all operating systems.

To generate the build files for your system use the following command.

```bash
mkdir build && cd build
cmake ..
make
```

For the install option use the following command install.

```bash
make install 
```

# Autors

## Main Authors:

- Moritz Herzog

## Other Authors:

- Tizian Hoffmann

## SysML v2

The SysML v2 Standard is developed and published by the Object Modelling Group (OMG).
