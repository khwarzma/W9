===== FILE: README.md =====
# W9 JavaScript Engine

<p align="center">
  High Performance JavaScript Engine written in modern C++
</p>


## Overview

W9 is a modern, high-performance JavaScript execution engine designed to power a custom browser engine.

The goal of W9 is to provide a complete JavaScript runtime capable of executing modern ECMAScript applications while maintaining a clean, modular, and extensible architecture.


W9 is designed as an independent engine.

It does not implement:

- HTML parsing
- CSS parsing
- Layout
- Rendering


Instead, W9 provides the JavaScript execution environment that can be integrated with an external browser engine.


---

# Vision

The long-term vision of W9 is to create a production-grade JavaScript engine capable of running modern web applications with high performance and strong compatibility.


W9 separates responsibilities:


## Browser Engine

Responsible for:


- HTML
- CSS
- DOM
- CSSOM
- Layout
- Painting
- Rendering
- User Interface


## W9 Engine

Responsible for:


- JavaScript execution
- ECMAScript runtime
- Memory management
- Compilation pipeline
- Virtual Machine
- JIT compilation
- Browser API bindings



---

# Goals


## Performance First

W9 focuses on:


- Fast execution
- Efficient memory usage
- Optimized runtime
- Native machine code generation



## Cross Platform


Target platforms:


- Windows
- Linux
- macOS


Target architectures:


- x64
- ARM64



## Modern JavaScript Support


Planned support:


- ES6+
- Classes
- Modules
- Promises
- Async/Await
- Modern language features



---

# Features


## Current


- C++23 foundation
- Modular architecture
- Build system
- Engine documentation
- Extensible design



## Planned


### Compiler

- Lexer
- Parser
- AST
- Intermediate Representation
- Bytecode generation


### Runtime

- JavaScript values
- Objects
- Functions
- Scope system
- Built-in objects


### Execution

- Bytecode Virtual Machine
- Execution stack
- Call frames
- Error handling


### Optimization

- JIT compiler
- LLVM backend
- Native machine code generation
- Runtime optimization



### Memory

- Heap management
- Garbage collector
- Memory optimization



### Browser Integration

Binding support:


- window
- document
- navigator
- location
- fetch
- timers
- storage



---

# Architecture


High level pipeline:



JavaScript Source Code

    |

    v

Lexer

    |

    v

Parser

    |

    v

Abstract Syntax Tree (AST)

    |

    v

Intermediate Representation (IR)

    |

    v

Bytecode

    |

    v

Virtual Machine

    |

    v

JIT Compiler

    |

    v

Native Machine Code




---

# Project Structure



W9/

├── engine/

│ ├── lexer/

│ ├── parser/

│ ├── ast/

│ ├── runtime/

│ ├── vm/

│ ├── jit/

│ ├── gc/

│ └── bindings/

├── docs/

├── tests/

├── examples/

├── include/

├── src/

├── CMakeLists.txt

├── Makefile

└── README.md




---

# Build Requirements


Requirements:


- C++23 compiler
- CMake 3.20+
- Make


Recommended:


- GCC 13+
- Clang 16+
- MSVC latest



---

# Building


Clone:


```bash
git clone https://github.com/khwarzma/W9.git

cd W9

Build:

make

or:

mkdir build

cd build

cmake ..

make
Running

After building:

make run

The engine should start successfully.

Example future usage:

console.log("Hello from W9");
Development Roadmap
Phase 0

Project foundation

Repository setup
Documentation
Build system
Phase 1

JavaScript Lexer

Tokens
Keywords
Literals
Phase 2

Parser and AST

Expressions
Statements
Functions
Phase 3

Runtime System

Objects
Values
Functions
Phase 4

Bytecode Virtual Machine

Instructions
Execution
Stack management
Phase 5

JavaScript Compatibility

ES6+
Promises
Async/Await
Modules
Phase 6

Garbage Collector

Heap
Allocation
Collection
Phase 7

JIT Compiler

LLVM integration
Native code generation
Phase 8

Browser Bindings

DOM bindings
Browser APIs
Phase 9

Compatibility Testing

ECMAScript tests
Web compatibility
Development Principles

W9 follows:

Clean architecture
Modular components
Stable interfaces
Performance oriented design
Long-term maintainability
Contributing

Contributions are welcome.

Before adding features:

Review architecture documents
Keep modules independent
Add tests
Maintain code quality
Documentation

Detailed design documents:

docs/

├── ARCHITECTURE.md

├── ENGINE_DESIGN.md

├── API_DESIGN.md

└── ROADMAP.md===== FILE: docs/ARCHITECTURE.md =====
# W9 JavaScript Engine Architecture

## Overview

W9 is a high-performance, cross-platform JavaScript execution engine written in modern C++.

The goal of W9 is to provide a complete JavaScript runtime capable of executing modern ECMAScript applications and integrating with an external browser engine through a dedicated binding layer.

W9 is designed as an independent JavaScript engine, separated from HTML, CSS, rendering, and browser UI systems.

---

# Core Design Principles

## 1. Separation of Responsibilities

W9 does not implement HTML or CSS rendering.

The architecture is divided into:

- JavaScript Engine
- Runtime System
- Compiler Pipeline
- Execution Environment
- Browser Integration Layer

The browser engine owns:

- DOM
- CSSOM
- Layout
- Rendering
- Networking UI integration

W9 owns:

- JavaScript execution
- Memory management
- Compilation
- Runtime objects
- ECMAScript APIs


---

# High Level Pipeline


JavaScript Source

        |

        v

Lexer

        |

        v

Parser

        |

        v

Abstract Syntax Tree (AST)

        |

        v

Intermediate Representation (IR)

        |

        v

Bytecode

        |

        v

Virtual Machine

        |

        v

JIT Compiler

        |

        v

Native Machine Code


---

# Main Components


## Lexer

Responsible for converting JavaScript source code into tokens.

Responsibilities:

- Tokenization
- Keyword detection
- Literal parsing
- Identifier parsing


Location:

engine/lexer/


---

## Parser

Transforms tokens into an Abstract Syntax Tree.

Responsibilities:

- Syntax validation
- Expression parsing
- Statement parsing
- Program structure creation


Location:

engine/parser/


---

## AST System

Represents JavaScript program structure.

Supports:

- Expressions
- Statements
- Functions
- Classes
- Modules


Location:

engine/ast/


---

## Runtime

The runtime provides JavaScript language behavior.

Responsibilities:

- Objects
- Arrays
- Functions
- Strings
- Numbers
- Closures
- Built-in objects


Location:

engine/runtime/


---

## Virtual Machine

Executes compiled JavaScript instructions.

Responsibilities:

- Bytecode execution
- Stack management
- Call frames
- Execution control


Location:

engine/vm/


---

## JIT Compiler

The Just-In-Time compiler converts frequently executed code into native machine instructions.

Goals:

- High performance execution
- Runtime optimization
- Platform independence


Technology:

LLVM Backend


Location:

engine/jit/


---

## Garbage Collector

Responsible for automatic memory management.

Goals:

- Safe allocation
- Memory cleanup
- Low latency execution


Location:

engine/gc/


---

# Browser Integration Layer


W9 provides bindings allowing an external browser engine to expose APIs.

Examples:

window

document

navigator

location

fetch


The DOM implementation remains outside W9.


Location:

engine/bindings/


---

# Cross Platform Support


Supported targets:

- Windows
- Linux
- macOS

Architectures:

- x64
- ARM64


---

# Development Standards


Language:

C++23


Build System:

CMake


Testing:

Unit Tests

Integration Tests

ECMAScript Compatibility Tests


---

# Performance Goals


W9 prioritizes:

1. Execution speed
2. Memory efficiency
3. Compatibility
4. Extensibility


Optimization systems include:

- JIT compilation
- Inline caching
- Efficient object representation
- Garbage collection optimization


---

# Future Extensions


Possible future modules:

- WebAssembly
- Web Workers
- WebGPU bindings
- Advanced optimization passes


---

# Project Philosophy


W9 is built with a modular architecture where every subsystem can evolve independently without breaking the entire engine.

The engine should remain:

- Fast
- Maintainable
- Extensible
- Production oriented
===== FILE: docs/ENGINE_DESIGN.md =====
# W9 Engine Technical Design

## Purpose

This document defines the internal technical design of the W9 JavaScript Engine.

W9 is designed as a modern JavaScript execution engine using a multi-stage execution pipeline:

Source Code -> Parser -> AST -> IR -> Bytecode -> VM -> JIT -> Native Code


---

# Execution Architecture


## Interpreter First Design

W9 uses a layered execution architecture.

The initial execution path:

JavaScript
        |
        v
AST
        |
        v
Bytecode
        |
        v
Virtual Machine


The optimized execution path:

Hot Code
        |
        v
JIT Compiler
        |
        v
Native Machine Code


---

# Compiler Pipeline


## Lexer

Input:

JavaScript source text


Output:

Token stream


Example:

let x = 10;


becomes:

LET
IDENTIFIER
ASSIGN
NUMBER


---

## Parser

Transforms tokens into AST nodes.


Example:


x + 5


becomes:


BinaryExpression

left:
 Identifier(x)

operator:
 +

right:
 Number(5)


---

# Intermediate Representation


W9 uses an internal IR layer.

Goals:

- Optimization
- Platform independence
- JIT preparation


The IR should support:

- Variables
- Operations
- Function calls
- Branching
- Loops


---

# Bytecode System


Bytecode is a compact instruction format.

Example:


LOAD_CONSTANT 5

STORE_VARIABLE x

LOAD_VARIABLE x

RETURN


Benefits:

- Fast execution
- Easy debugging
- JIT friendly


---

# Virtual Machine


The VM executes bytecode instructions.


Responsibilities:


- Instruction dispatch
- Stack handling
- Function calls
- Exceptions
- Execution state


---

# Runtime Object Model


JavaScript values are represented internally.


Supported types:


Primitive:

- Undefined
- Null
- Boolean
- Number
- String


Objects:

- Object
- Array
- Function
- Class


---

# Function System


Functions support:


- Closures
- Scope chains
- Arguments
- Return values


---

# Memory Management


W9 uses automatic garbage collection.


Goals:


- Safe memory usage
- High performance
- Low pause time


Future improvements:

- Generational GC
- Incremental GC
- Concurrent GC


---

# JIT Compiler


The JIT compiler converts frequently executed bytecode into native code.


Backend:

LLVM


Supported targets:

- x64
- ARM64


Optimization goals:


- Reduce execution overhead
- Inline functions
- Optimize object access


---

# Error Handling


The engine provides:


- Syntax errors
- Runtime errors
- Stack traces
- Debug information


---

# Debugging Support


Future support:


- Source maps
- Inspector protocol
- Runtime debugging


---

# Design Rule


Each subsystem must remain independent.

Changes in the parser should not require rewriting the VM.

Changes in the JIT should not affect the runtime API.
===== FILE: docs/API_DESIGN.md =====
# W9 Browser Integration API Design


## Overview


W9 does not implement browser rendering.

A browser engine communicates with W9 through a binding layer.


Architecture:


Browser Engine

        |

        v

W9 Binding API

        |

        v

JavaScript Runtime



---

# Binding System


External systems can expose native objects to JavaScript.


Example:


C++:


engine.bind(
 "document",
 documentObject
);



JavaScript:


document.title = "Hello";


---

# Core Browser Objects


Expected bindings:


window

document

navigator

location

history


---

# Event System


Browser events are forwarded into JavaScript.


Examples:


click

load

resize

keyboard


Flow:


Browser

->

Binding Layer

->

JavaScript Callback


---

# Timer API


Supported:


setTimeout

setInterval


Implementation:

Browser controls timing.

W9 executes callbacks.


---

# Networking API


Future support:


fetch()

WebSocket


The browser engine owns networking.


---

# Storage API


Bindings:


localStorage

sessionStorage


---

# Threading Model


W9 executes JavaScript in a controlled runtime thread.


Future support:

Workers

Shared memory


---

# API Stability


The binding interface must remain stable.

Browser implementations should not depend on internal engine classes.===== FILE: docs/ROADMAP.md =====
# W9 Development Roadmap


# Phase 0 - Foundation

Status:

Planning


Tasks:

- Repository setup
- Build system
- Project structure
- Documentation



---

# Phase 1 - Lexer


Goal:

Convert JavaScript source into tokens.


Features:


- Keywords
- Numbers
- Strings
- Operators
- Identifiers



---

# Phase 2 - Parser


Goal:

Generate AST.


Support:


- Expressions
- Statements
- Functions
- Variables



---

# Phase 3 - Runtime


Implement:


- Values
- Objects
- Functions
- Scope


---

# Phase 4 - Bytecode VM


Implement:


- Bytecode format
- Instruction execution
- Stack frames



---

# Phase 5 - JavaScript Features


Support:


- let
- const
- classes
- promises
- async/await
- modules



---

# Phase 6 - Garbage Collector


Implement:


- Heap
- Allocation
- Collection


---

# Phase 7 - JIT Compiler


Implement:


- LLVM backend
- Native code generation
- Optimization passes



---

# Phase 8 - Browser Bindings


Implement:


- window
- document
- events
- timers
- storage


---

# Phase 9 - Compatibility


Goals:


- ECMAScript compliance
- Test262 integration



---

# Phase 10 - Performance


Optimization:


- Inline caching
- Object optimization
- Faster execution


---

# Long Term Goals


- WebAssembly
- Web Workers
- Advanced browser APIs
===== FILE: docs/TEAM_GUIDE.md =====
# W9 Team Development Guide


## Purpose


This document defines internal development rules for the W9 engine team.

The goal is to keep the project organized, maintainable, and scalable.


---

# Development Philosophy


W9 is built as a long-term engine project.

Every change should consider:


- Performance
- Maintainability
- Compatibility
- Future expansion



---

# Branch Strategy


Main branch:


main


Purpose:

Stable project state.



Development branches:


feature/name

example:


feature/lexer


bugfix/name


example:


bugfix/parser-crash



---

# Commit Rules


Commits should describe one clear change.


Good:

Add lexer token system



Bad:



changes




---

# Code Rules


Language:


C++23


Follow:


- Clean architecture
- Clear naming
- Small modules
- No unnecessary dependencies


---

# Architecture Rules


Do not directly connect modules.


Example:


Bad:


Parser -> JIT


Good:


Parser -> AST -> IR -> JIT



Every subsystem must have a clear interface.


---

# Adding Features


Before implementing a new feature:


1. Update design document
2. Define module ownership
3. Implement
4. Add tests


---

# Performance Rules


Performance is a priority.


Avoid:


- Unnecessary allocations
- Expensive copies
- Blocking operations


Measure before optimizing.


---

# Testing


Every major feature should include:


- Unit tests
- Runtime tests
- Regression tests



---

# Documentation


Any major architectural change must update:


docs/


Especially:


- ARCHITECTURE.md
- ENGINE_DESIGN.md
- API_DESIGN.md



---

# Code Review


Before merging:


Check:


- Does it follow architecture?
- Is it maintainable?
- Does it break existing modules?
- Are tests included?



---

# Project Ownership


All team members should understand:


- Engine architecture
- Module boundaries
- Future roadmap


W9 is built as one connected system.
===== FILE: docs/DEVELOPMENT_SETUP.md =====
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
===== FILE: CMakeLists.txt =====
cmake_minimum_required(VERSION 3.20)

project(W9
    VERSION 0.1.0
    DESCRIPTION "W9 JavaScript Engine"
    LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Compiler warnings

if(MSVC)

    add_compile_options(/W4)

else()

    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )

endif()


# Source files

file(GLOB_RECURSE W9_SOURCES

    engine/*.cpp
    src/*.cpp

)


add_executable(
    W9
    ${W9_SOURCES}
)


target_include_directories(
    W9
    PRIVATE

    include
    engine

)


# Tests

enable_testing()


add_subdirectory(tests OPTIONAL)===== FILE: Makefile =====
cmake_minimum_required(VERSION 3.20)

project(W9
    VERSION 0.1.0
    DESCRIPTION "W9 JavaScript Engine"
    LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Compiler warnings

if(MSVC)

    add_compile_options(/W4)

else()

    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )

endif()


# Source files

file(GLOB_RECURSE W9_SOURCES

    engine/*.cpp
    src/*.cpp

)


add_executable(
    W9
    ${W9_SOURCES}
)


target_include_directories(
    W9
    PRIVATE

    include
    engine

)


# Tests

enable_testing()


add_subdirectory(tests OPTIONAL)