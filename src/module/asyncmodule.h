#ifndef MODULE_ASYNC_H
#define MODULE_ASYNC_H
/*
 *Ок было бы добавить в конфиг для таких модулей строки типа
 * async_modules = weather barrel_roll ps
 * ps = /bin/ps aux
 * barrel_roll = bash ~/barrel_roll.sh
 * weather = bash ~/weather.sh
 * Потом fork/exec, а откуда ждать результатов - надо придумать (Это делает этот generate_answer).
 * */
#define MAX_ARG_NUM 1
#include "module.h"
class AsyncModule : public Module
    {
        public:
            virtual std::string generate_answer(const std::string& sender,
                                                const std::vector<std::string>& text);
    };
#endif
