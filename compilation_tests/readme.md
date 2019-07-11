# Compilation Tests

This directory creates unit tests to validate compile time code. This includes
things like `static_assert()` statements, C++20 concepts, etc.

These tests attempt to compile code that should not compile. A passing test is
one which fails to compile.
