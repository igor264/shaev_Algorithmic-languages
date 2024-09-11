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
    int length_of_pipe;
    short int diameter;
    bool repair_indicator;
};

struct CS
{
    /*
     name - наиминование 30 символов)
     number_of_workshops - количество цехов (целое неотрицательное число)
     workshops_in_work - количество цехов в работе (целое неотрицательное число)
     efficiency - эффективность измеряется от 0 до 100 (целое неотрицательное число)
    */
    std::string name;
    int number_of_workshops;
    int workshops_in_work;
    short int efficiency;
};

#endif /* STRUCTURS_H_ */