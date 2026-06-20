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
