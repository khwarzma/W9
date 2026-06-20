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

└── ROADMAP.md