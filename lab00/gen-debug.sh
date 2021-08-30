#!/bin/bash

echo "OSTYPE='$OSTYPE'" > debug.txt
echo "SH_VERSION='$(sh --version 2>&1 | cat)'" >> debug.txt
echo "GIT_VERSION='$(git --version 2>&1 | cat)'" >> debug.txt
echo "PYTHON3_VERSION='$(python3 --version 2>&1 | cat)'" >> debug.txt
echo "PYTHON_VERSION='$(python --version 2>&1 | cat)'" >> debug.txt
echo "PY_VERSION='$(py --version 2>&1 | cat)'" >> debug.txt
echo "GCC_VERSION='$(gcc --version 2>&1 | cat)'" >> debug.txt
echo "JAVA_VERSION='$(java -version 2>&1 | cat)'" >> debug.txt
