#!/bin/bash

# Using the test command to check if file.txt exists
if test -f "file.txt"; then
    echo "file.txt exists."
else
    echo "file.txt does not exist."
fi
