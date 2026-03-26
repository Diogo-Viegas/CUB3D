#!/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

echo "==== VALID CONFIGS ===="
for file in maps/valid_config/*.cub; do
    ./cub3D "$file" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${NC} $file"
    else
        echo -e "${RED}FAIL${NC} $file"
    fi
done

echo "==== INVALID CONFIGS ===="
for file in maps/invalid_config/*.cub; do
    ./cub3D "$file" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${GREEN}OK${NC} $file"
    else
        echo -e "${RED}FAIL${NC} $file"
    fi
done

echo "==== VALID MAPS ===="
for file in maps/valid_map/*.cub; do
    ./cub3D "$file" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}OK${NC} $file"
    else
        echo -e "${RED}FAIL${NC} $file"
    fi
done

echo "==== INVALID MAPS ===="
for file in maps/invalid_map/*.cub; do
    ./cub3D "$file" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${GREEN}OK${NC} $file"
    else
        echo -e "${RED}FAIL${NC} $file"
    fi
done