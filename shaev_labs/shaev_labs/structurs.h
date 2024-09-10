#ifndef STRUCTURS_H_
#define STRUCTURS_H_

#include <string>

struct Pipeline
{
    /*
     kilometer_sign - отметка километра на котором находится труба
     length_of_pipe - длинна трубы в метрах (целое неотрицательное число)
     diameter - диаметр трубы в мм (целое неотрицательное число)
     repair_indicator - индикатор трубы на ремонте
    */
    std::string kilometer_sign;
    unsigned int length_of_pipe;
    unsigned short int diameter;
    bool repair_indicator;
};

struct CS
{
    /*
     name - наиминование (20 символов)
     number_of_workshops - количество цехов (целое неотрицательное число)
     workshops_in_work - количество цехов в работе (целое неотрицательное число)
     efficiency - эффективность измеряется от 0 до 100 (целое неотрицательное число)
    */
    char name[30];
    unsigned int number_of_workshops;
    unsigned int workshops_in_work;
    unsigned short int efficiency;
};

#endif /* STRUCTURS_H_ */