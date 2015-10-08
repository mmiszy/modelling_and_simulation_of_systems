#!/bin/bash

cmake ./
make
time cat tests/test1 | ./modelling_and_simulation_of_systems

