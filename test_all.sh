#!/bin/bash

cmake ./
make
diff <(cat tests/test1 | ./modelling_and_simulation_of_systems) <(cat ./tests/wzor1)

