#include <chrono>
#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

const long numInt = pow(10, 8);

int repeats = 15;

// Initialising traditional pointers and deleting them
void init_normal(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        long* tmp = new long(x);
        delete tmp;
    }
}

// Initialising std::unique_ptr using new and deleting them
void init_unique(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        unique_ptr<long> tmp(new long(x));
    }
}

// Initialising std::unique_ptr using std::make_unique and deleting them
void init_make_unique(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        unique_ptr<long> tmp(make_unique<long>(x));
    }
}

// Initialising std::shared_ptr using new and deleting them
void init_shared(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        shared_ptr<long> tmp(new long(x));
    }
}

// Initialising std::shared_ptr using make_shared and deleting them
void init_make_shared(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        shared_ptr<long> tmp(make_shared<long>(x));
    }
}


// reading and writing from and to an object referenced by a traditional pointer
void use_normal(long*& ptr, const long& numInt) {
    volatile long tmp;
    for (long int x = 0; x < numInt; x++) {
        tmp = *ptr;
        *ptr = tmp + 1;
    }
}

// reading and writing from and to an object referenced by a std::unique_ptr
void use_unique(unique_ptr<long>& ptr, const long& numInt) {
    volatile long tmp;
    for (long int x = 0; x < numInt; x++) {
        tmp = *ptr;
        *ptr = tmp + 1;
    }
}

// reading and writing from and to an object referenced by a std::shared_ptr
void use_shared(shared_ptr<long>& ptr, const long& numInt) {
    volatile long tmp;
    for (long int x = 0; x < numInt; x++) {
        tmp = *ptr;
        *ptr = tmp + 1;
    }
}

int main() {
    chrono::duration<double> totalDur;
    chrono::duration<double> dur;
    auto start = chrono::system_clock::now();


    // Measururing the time it takes for initialising traditional pointers and deleting them
    totalDur = std::chrono::steady_clock::duration::zero();
    for (int i(0); i < repeats; i++) {
        start = chrono::system_clock::now();
        init_normal(numInt);
        dur = chrono::system_clock::now() - start;
        cout << "Time for initialising and deleting " << numInt << " traditional pointer: " << dur.count() << "s\n";
        totalDur += dur;
    }
    cout << "Average time for initialising and deleting " << numInt << " traditional pointer in " << repeats << " repeats: " << totalDur.count() / repeats << "s\n\n";


    // Measururing the time it takes for initialising std::unique_ptr using new and deleting them
    totalDur = std::chrono::steady_clock::duration::zero();
    for (int i(0); i < repeats; i++) {
        start = chrono::system_clock::now();
        init_unique(numInt);
        dur = chrono::system_clock::now() - start;
        cout << "Time for initialising and deleting " << numInt << " std::unique_ptr using new: " << dur.count() << "s\n";
        totalDur += dur;
    }
    cout << "Average time for initialising and deleting " << numInt << " std::unique_ptr using new in " << repeats << " repeats: " << totalDur.count() / repeats << "s\n\n";


    // Measururing the time it takes for initialising std::unique_ptr using std::make_unique and deleting them
    totalDur = std::chrono::steady_clock::duration::zero();
    for (int i(0); i < repeats; i++) {
        start = chrono::system_clock::now();
        init_make_unique(numInt);
        dur = chrono::system_clock::now() - start;
        cout << "Time for initialising and deleting " << numInt << " std::unique_ptr using make_unique: " << dur.count() << "s\n";
        totalDur += dur;
    }
    cout << "Average time for initialising and deleting " << numInt << " std::unique_ptr using make_unique in " << repeats << " repeats: " << totalDur.count() / repeats << "s\n\n";


    // Measururing the time it takes for initialising std::shared_ptr using new and deleting them
    totalDur = std::chrono::steady_clock::duration::zero();
    for (int i(0); i < repeats; i++) {
        start = chrono::system_clock::now();
        init_shared(numInt);
        dur = chrono::system_clock::now() - start;
        cout << "Time for initialising and deleting " << numInt << " std::shared_ptr using new: " << dur.count() << "s\n";
        totalDur += dur;
    }
    cout << "Average time for initialising and deleting " << numInt << " std::shared_ptr using new in " << repeats << " repeats: " << totalDur.count() / repeats << "s\n\n";


    // Measururing the time it takes for initialising std::shared_ptr using std::make_shared and deleting them
    totalDur = std::chrono::steady_clock::duration::zero();
    for (int i(0); i < repeats; i++) {
        start = chrono::system_clock::now();
        init_make_shared(numInt);
        dur = chrono::system_clock::now() - start;
        cout << "Time for initialising and deleting " << numInt << " std::shared_ptr using make_shared: " << dur.count() << "s\n";
        totalDur += dur;
    }
    cout << "Average time for initialising and deleting " << numInt << " std::shared_ptr using make_shared in " << repeats << " repeats: " << totalDur.count() / repeats << "s\n\n";


    // Measururing the time it takes to read from and write to a traditional pointer
    totalDur = std::chrono::steady_clock::duration::zero();
    for (int i(0); i < repeats; i++) {
        long* tmp0 = new long(2);
        start = chrono::system_clock::now();
        use_normal(tmp0, numInt);
        dur = chrono::system_clock::now() - start;
        delete tmp0;
        cout << "Time for reading from and writing to a traditional pointer " << numInt << " times: " << dur.count() << "s\n";
        totalDur += dur;
    }
    cout << "Average time for reading from and writing to a traditional pointer " << numInt << " times in " << repeats << " repeats: " << dur.count() << "s\n\n";


    // Measururing the time it takes to read from and write to a std::unique_ptr
    totalDur = std::chrono::steady_clock::duration::zero();
    for (int i(0); i < repeats; i++) {
        unique_ptr<long> tmp1(new long(2));
        start = chrono::system_clock::now();
        use_unique(tmp1, numInt);
        dur = chrono::system_clock::now() - start;
        cout << "Time for reading from and writing to a std::unique_ptr pointer " << numInt << " times: " << dur.count() << "s\n";
        totalDur += dur;
    }
    cout << "Average time for reading from and writing to a std::unique_ptr " << numInt << " times in " << repeats << " repeats: " << dur.count() << "s\n\n";


    // Measururing the time it takes to read from and write to a std::shared_ptr
    totalDur = std::chrono::steady_clock::duration::zero();
    for (int i(0); i < repeats; i++) {
        shared_ptr<long> tmp2(new long(2));
        start = chrono::system_clock::now();
        use_shared(tmp2, numInt);
        dur = chrono::system_clock::now() - start;
        cout << "Time for reading from and writing to a std::shared_ptr pointer " << numInt << " times: " << dur.count() << "s\n";
    }
    cout << "Average time for reading from and writing to a std::shared_ptr " << numInt << " times in " << repeats << " repeats: " << dur.count() << "s\n\n";

    return 0;
}
