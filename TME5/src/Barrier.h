#pragma once

#include <mutex>
#include <condition_variable>

namespace pr {
class Barrier{

    mutable std::mutex m;
    static int cpt;
    int nbThread;
    std::condition_variable cv;

    public : 
        Barrier(int nbThread): nbThread(nbThread){}


};
}