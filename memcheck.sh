#!/bin/sh
valgrind --leak-check=full ./main $@
