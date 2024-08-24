#include <iostream>
#include <map>
using namespace std;

/*
int get_month_days(int month) {
    int days = 0;
    if (1 == month) { days = 31; }
    else if (2 == month) { days = 28; }
    else if (3 == month) { days = 31; }
    else if (4 == month) { days = 30 ; }
    else if (5 == month) { days = 31; }
    else if (6 == month) { days = 30; }
    else if (7 == month) { days = 31; }
    else if (8 == month) { days = 31; }
    else if (9 == month) { days = 30; }
    else if (10 == month) { days = 31; }
    else if (11 == month) { days = 30; }
    else if (12 == month) { days = 31; }
    return days;
}
*/

// table driven
static int MonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int get_month_days(int month) {
    return MonthDays[month-1];
}

int process0(void* param_in, void* param_out) {
    cout << "process0..." << endl;
    return 0;
}
int process1(void* param_in, void* param_out) {
    cout << "process1..." << endl;
    return 1;
}
int process2(void* param_in, void* param_out) {
    cout << "process2..." << endl;
    return 2;
}

/*
int process_control(uint function_no, void* param_in, void* param_out) {
    int result;
    switch (function_no) {
        case 0:
            result = process0(param_in, param_out);
            break;
        case 1:
            result = process1(param_in, param_out);
            break;
        case 2:
            result = process2(param_in, param_out);
            break;
        default:
            result = -1;
            break;
    }
    return result;
}
*/

// table driven 1
typedef int (*ProcessFuncPtr) (void*, void*);
typedef struct DispatchItem {
    uint func_no;
    ProcessFuncPtr func_ptr;
} DispatchItem;
DispatchItem dispatch_talbe[3] = {
        DispatchItem {0, process0},
        DispatchItem {1, process1},
        DispatchItem {2, process2}
};

int process_control(uint function_no, void* param_in, void* param_out) {
    for(auto& item : dispatch_talbe) {
        if (function_no == item.func_no) {
            return item.func_ptr(param_in, param_out);
        }
    }
    return -1;
}

// table driven 2
typedef map<uint,ProcessFuncPtr> HandlerMap;
HandlerMap hm;
void init_handler_map() {
    hm[0] = process0;
    hm[1] = process1;
    hm[2] = process2;
}
int process_control2(uint function_no, void* param_in, void* param_out) {
    HandlerMap::iterator it = hm.find(function_no);
    if (it != hm.end()) {
        ProcessFuncPtr handler = it->second;
        return handler(param_in, param_out);
    }
    return -1;
}

int main() {
    cout << get_month_days(10) << endl;
    cout << "--------------------------------------------------" << endl;
    uint func_nos[3] = {0,1,2};
    for(auto n :func_nos) {
        cout << process_control(n, nullptr, nullptr) << endl;
    }
    cout << "--------------------------------------------------" << endl;
    init_handler_map();
    for(auto n :func_nos) {
        cout << process_control2(n, nullptr, nullptr) << endl;
    }

    return 0;
}
