#pragma once

#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define MAX 100

using namespace std;

class MyException {
    string _msg;
public:
    MyException(string msg) {
        _msg = msg;
    }

    string what() {
        return _msg;
    }
};

#endif // BASE_H