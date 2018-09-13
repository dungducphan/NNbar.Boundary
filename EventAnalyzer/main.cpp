#include <iostream>
#include "EventAnalyzer.h"

int main() {
    EventAnalyzer* ea = new EventAnalyzer();
//    for (unsigned int evtID = 0; evtID < 10; evtID++) {
//        ea->Loop(evtID);
//    }
    ea->CircularGrade();

    return 0;
}