# File Overview

In QMK, different file types serve specific responsibilities:

- **.h (Header Files)**:
  These declare functions, macros, and other definitions. They act as a blueprint for the `.c` files and help other
  files understand the data structures and functions they can access.

- **.c (C Source Files)**:
  These contain the actual implementation of functions and logic. For example, your keymap will be defined here, along
  with any additional functionality (such as your trackball logic).

- **rules.mk (Make Rules)**:
  This file tells QMK's build system which features and source files to include in the compilation. It effectively
  instructs which parts of the firmware are compiled.
