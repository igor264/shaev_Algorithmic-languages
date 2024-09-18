#ifndef STRUCTURS_H_
#define STRUCTURS_H_

#include <string>

struct Pipeline
{
    std::string kilometer_sign = "default";
    int length_of_pipe = 1;
    short int diameter = 1;
    bool repair_indicator = 0;
};

struct CS
{
    std::string name = "default";
    int number_of_workshops = -1;
    int workshops_in_work = -1;
    short int efficiency = -1;
};

#endif /* STRUCTURS_H_ */