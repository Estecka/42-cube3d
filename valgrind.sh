#!/bin/bash

EXEC=cub3d.out
ARGS=./.maps/old-subject.cub
LOG=valgrind.log

valgrind \
    --tool=memcheck \
    --leak-check=full \
    --leak-resolution=high \
    --show-reachable=yes \
    --log-file=$LOG \
    ./$EXEC $ARGS \


grep -A1 "valgrind" ${LOG}|grep $EXEC