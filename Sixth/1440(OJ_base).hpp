//
// Created by Leonard C on 2021/12/13.
//

#ifndef SRC_HPP_1440_OJ_BASE_HPP
#define SRC_HPP_1440_OJ_BASE_HPP

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

class BaseJudger {
public:
    BaseJudger(size_t time_limit, size_t memory_limit,
               const char *answer)
    // todo
}

virtual void Submit(size_t time, size_t memory, const char *output) = 0;

size_t GetScore() const { return score_; }

virtual ~BaseJudger() {
    // todo
};

protected:
char *answer_;
const size_t time_limit_;
const size_t memory_limit_;
size_t score_;

virtual bool CheckAnswer(const char *output) const {
    // the output must equal to the answer
    return strcmp(answer_, output) == 0;
}

};


class OIJudger
// todo

class ICPCJudger
// todo

class SpacialJudger
// todo

#endif //SRC_HPP_1440_OJ_BASE_HPP
