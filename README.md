# Romcal Version 6

This is the code of [Romcal](https://www.romcal.net/) Version 6 with the changes needed to make it compile in 2022.

- The git history begins with the contents of the tar file, which are dated January 8, 2003.
- It now compiles without warnings (`make all`) on Apple clang version 13.1.6 (clang-1316.0.21.2).
- The one complaint during make is that it's unsafe to use `gets()` in the programs that generate header files, but since the input is fixed, I'm not concerned.
