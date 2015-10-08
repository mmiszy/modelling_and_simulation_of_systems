#!/bin/bash

cmake ./
make
diff <(cat tests/test1 | ./modelling_and_simulation_of_systems) <(cat ./tests/wzor1)
diff <(cat tests/test2 | ./modelling_and_simulation_of_systems) <(cat ./tests/wzor2)
diff <(cat tests/test3 | ./modelling_and_simulation_of_systems) <(cat ./tests/wzor3)
diff <(cat tests/test4 | ./modelling_and_simulation_of_systems) <(cat ./tests/wzor4)
diff <(cat tests/test5 | ./modelling_and_simulation_of_systems) <(cat ./tests/wzor5)

