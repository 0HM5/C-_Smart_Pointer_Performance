#include <chrono>
#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

void init_normal(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        long* tmp = new long(x);
        delete tmp;
    }
}

void init_unique(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        unique_ptr<long> tmp(new long(x));
    }
}

void init_make_unique(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        unique_ptr<long> tmp(make_unique<long>(x));
    }
}

void init_shared(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        shared_ptr<long> tmp(new long(x));
    }
}

void init_make_shared(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        shared_ptr<long> tmp(make_shared<long>(x));
    }
}

void use_normal(long*& ptr, const long& numInt) {
    long tmp;
    for (long int x = 0; x < numInt; x++) {
        tmp = *ptr;
        *ptr = tmp + 1;
    }
}

void use_unique(unique_ptr<long>& ptr, const long& numInt) {
    long tmp;
    for (long int x = 0; x < numInt; x++) {
        tmp = *ptr;
        *ptr = tmp + 1;
    }
}

void use_shared(shared_ptr<long>& ptr, const long& numInt) {
    long tmp;
    for (long int x = 0; x < numInt; x++) {
        tmp = *ptr;
        *ptr = tmp + 1;
    }
}

int main() {
    const long long numInt = pow(10, 7);

    auto start = chrono::system_clock::now();

    init_normal(numInt);

    chrono::duration<double> dur = chrono::system_clock::now() - start;
    cout << "Time for initialising and deleting " << numInt << " normal pointer: " << dur.count() << "s\n";
    start = chrono::system_clock::now();

    init_unique(numInt);

    dur = chrono::system_clock::now() - start;
    cout << "Time for initialising and deleting " << numInt << " unique pointer: " << dur.count() << "s\n";
    start = chrono::system_clock::now();

    init_make_unique(numInt);

    dur = chrono::system_clock::now() - start;
    cout << "Time for initialising and deleting " << numInt << " unique pointer using make_unique: " << dur.count() << "s\n";
    start = chrono::system_clock::now();

    init_shared(numInt);

    dur = chrono::system_clock::now() - start;
    cout << "Time for initialising and deleting " << numInt << " shared pointer: " << dur.count() << "s\n";
    start = chrono::system_clock::now();

    init_make_shared(numInt);

    dur = chrono::system_clock::now() - start;
    cout << "Time for initialising and deleting " << numInt << " shared pointer using make_shared: " << dur.count() << "s\n";

    cout << endl;

    long* tmp0 = new long(2);
    start = chrono::system_clock::now();

    use_normal(tmp0, numInt);

    dur = chrono::system_clock::now() - start;
    delete tmp0;
    cout << "Time for reading and writing to and from a normal pointer " << numInt << " times: " << dur.count() << "s\n";
    unique_ptr<long> tmp1(new long(2));
    start = chrono::system_clock::now();

    use_unique(tmp1, numInt);

    dur = chrono::system_clock::now() - start;
    cout << "Time for reading and writing to and from a unique_ptr pointer " << numInt << " times: " << dur.count() << "s\n";
    shared_ptr<long> tmp2(new long(2));
    start = chrono::system_clock::now();

    use_shared(tmp2, numInt);

    dur = chrono::system_clock::now() - start;
    cout << "Time for reading and writing to and from a shared_ptr pointer " << numInt << " times: " << dur.count() << "s\n";
    return 0;
}