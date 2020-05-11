#!/bin/bash

EXEC=cub3d.out
LOG=valgrind.log

valgrind \
    --tool=memcheck \
    --leak-check=full \
    --leak-resolution=high \
    --show-reachable=yes \
    --log-file=$LOG \
    ./$EXEC $1 $2 $3\


grep -A1 "valgrind" ${LOG}|grep $EXEC