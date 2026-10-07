@echo off
"C:\msys64\usr\bin\bash.exe" -lc "/mingw64/bin/gcc --version; /mingw64/bin/gcc -c '/c/Users/Caesar/Desktop/Unit Fraction/UnitFraction.c' -o '/c/Users/Caesar/Desktop/Unit Fraction/test.o' > '/c/Users/Caesar/Desktop/Unit Fraction/compile.log' 2>&1; echo RC:$?; ls -l '/c/Users/Caesar/Desktop/Unit Fraction/compile.log'; cat '/c/Users/Caesar/Desktop/Unit Fraction/compile.log'"
