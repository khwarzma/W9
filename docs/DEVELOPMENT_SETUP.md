# W9 Development Setup Guide


## Overview


This document explains how to prepare a development environment for working on the W9 JavaScript Engine.


The goal is to make every developer able to build, test, and run W9 locally.


---

# System Requirements


## Supported Operating Systems


Currently supported:


- Linux
- Windows
- macOS



## Required Tools


### C++ Compiler


W9 uses C++23.


Recommended:


Linux:

- GCC 13+
- Clang 16+


Windows:

- MSVC latest


macOS:

- Apple Clang latest



---

# Build Tools


Required:


## CMake


Minimum version:

3.20+



Check:


```bash
cmake --version
Make

Check:

make --version
Clone Repository

Clone the project:

git clone https://github.com/khwarzma/W9.git

Enter directory:

cd W9
Project Structure

Main directories:

engine/

Core JavaScript engine modules


docs/

Project documentation


tests/

Automated tests


examples/

Example JavaScript files

Linux Setup

Install compiler:

Ubuntu/Debian:

sudo apt update

sudo apt install build-essential cmake

Install C++ compiler:

sudo apt install g++
Windows Setup

Install:

Visual Studio
Desktop development with C++
CMake tools

Verify:

cmake --version
macOS Setup

Install Xcode tools:

xcode-select --install

Install CMake:

brew install cmake
Building W9

Recommended:

make

Manual:

mkdir build

cd build

cmake ..

make
Running

After successful build:

make run

Expected output:

W9 JavaScript Engine initialized
Development Workflow

Before coding:

Update local repository:

git pull

Create branch:

Example:

git checkout -b feature/parser

After changes:

git add .

git commit -m "Implement parser foundation"

git push
Code Style

Follow:

C++23 standard
Clear naming
Small classes
Minimal dependencies
Document important decisions
Debug Build

For debugging:

cmake -DCMAKE_BUILD_TYPE=Debug ..
Release Build

For performance testing:

cmake -DCMAKE_BUILD_TYPE=Release ..
Testing

Run tests:

ctest
Before Adding Code

Read:

docs/

ARCHITECTURE.md

ENGINE_DESIGN.md

API_DESIGN.md

ROADMAP.md

TEAM_GUIDE.md

The architecture must be respected before implementation.

Development Principle

W9 is built as a long-term engine.

Every contribution should improve:

Performance
Stability
Maintainability
