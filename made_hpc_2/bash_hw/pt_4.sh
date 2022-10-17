#!/bin/bash

FILENAME="Linux"

if [ -f "$FILENAME" ]; then
    echo "$FILENAME exists"
else
    echo "very easy"
    echo "create file" > Linux
fi
