#include <chrono>
#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

const long numInt = pow(10, 8);

int repeats = 15;

//initialisierung normaler Pointer
void init_normal(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        long* tmp = new long(x);
        delete tmp;
    }
}

//initialisierung unique_ptr mittels Konstruktor
void init_unique(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        unique_ptr<long> tmp(new long(x));
    }
}

//initialisierung unique_ptr mittels Methode make_unique
void init_make_unique(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        unique_ptr<long> tmp(make_unique<long>(x));
    }
}

//initialisierung make_shared mittels Konstruktor
void init_shared(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        shared_ptr<long> tmp(new long(x));
    }
}

//initialisierung make_shared mittels Methode make_shared
void init_make_shared(const int& numInt) {
    for (long int x = 0; x < numInt; x++) {
        shared_ptr<long> tmp(make_shared<long>(x));
    }
}


//dereferenzierung normaler Pointer
void use_normal(long*& ptr, const long& numInt) {
    volatile long tmp;
    for (long int x = 0; x < numInt; x++) {
        tmp = *ptr;
        *ptr = tmp + 1;
    }
}

//dereferenzierung unique_ptr
void use_unique(unique_ptr<long>& ptr, const long& numInt) {
    volatile long tmp;
    for (long int x = 0; x < numInt; x++) {
        tmp = *ptr;
        *ptr = tmp + 1;
    }
}

//dereferenzierung shared_ptr
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


    //Zeitmessung initialisierung normaler Pointer
    totalDur = std::chrono::steady_clock::duration::zero();
    for(int i(0); i < repeats; i++){
      start = chrono::system_clock::now();
      init_normal(numInt);
      dur = chrono::system_clock::now() - start;
      cout << "Time for initialising and deleting " << numInt << " normal pointer: " << dur.count() << "s\n";
      totalDur += dur;
    }
    cout << "Average for initialising and deleting " << numInt << " normal pointer in " << repeats << ": " << totalDur.count()/repeats << "s\n";

    cout << endl;

    //Zeitmessung unique_ptr mittels Konstruktor
    totalDur = std::chrono::steady_clock::duration::zero();
    for(int i(0); i < repeats; i++){
      start = chrono::system_clock::now();
      init_unique(numInt);
      dur = chrono::system_clock::now() - start;
      cout << "Time for initialising and deleting " << numInt << " unique pointer: " << dur.count() << "s\n";
      totalDur += dur;
    }
    cout << "Average for initialising and deleting " << numInt << " unique pointer in " << repeats << ": " << totalDur.count()/repeats << "s\n";

    cout << endl;

    //Zeitmessung unique_ptr mittels Meethode make_unique()
    totalDur = std::chrono::steady_clock::duration::zero();
    for(int i(0); i < repeats; i++){
      start = chrono::system_clock::now();
      init_make_unique(numInt);
      dur = chrono::system_clock::now() - start;
      cout << "Time for initialising and deleting " << numInt << " unique pointer using make_unique: " << dur.count() << "s\n";
      totalDur += dur;
    }
    cout << "Average for initialising and deleting " << numInt << " unique pointer using make_unique in " << repeats << ": " << totalDur.count()/repeats << "s\n";

    cout << endl;

    //Zeitmessung shared_ptr mittels Konstruktor
    totalDur = std::chrono::steady_clock::duration::zero();
    for(int i(0); i < repeats; i++){
      start = chrono::system_clock::now();
      init_shared(numInt);
      dur = chrono::system_clock::now() - start;
      cout << "Time for initialising and deleting " << numInt << " shared pointer: " << dur.count() << "s\n";
      totalDur += dur;
    }
    cout << "Average for initialising and deleting " << numInt << " shared pointer in " << repeats << ": " << totalDur.count()/repeats << "s\n";

    cout << endl;

    //Zeitmessung shared_ptr mittels Methode make_shared()
    totalDur = std::chrono::steady_clock::duration::zero();
    for(int i(0); i < repeats; i++){
      start = chrono::system_clock::now();
      init_make_shared(numInt);
      dur = chrono::system_clock::now() - start;
      cout << "Time for initialising and deleting " << numInt << " shared pointer using make_shared: " << dur.count() << "s\n";
      totalDur += dur;
    }
    cout << "Average for initialising and deleting " << numInt << " shared pointer using make_shared in " << repeats << ": " << totalDur.count()/repeats << "s\n";

    cout << endl;

    /*
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
    */

    return 0;
}
