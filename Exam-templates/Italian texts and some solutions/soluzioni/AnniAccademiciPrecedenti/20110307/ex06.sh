#!/bin/bash

# -k n1,n2 da campo n1 a campo n2
# n = numeric sort
awk -f ex06.awk $1 | sort -k 1 -n 
