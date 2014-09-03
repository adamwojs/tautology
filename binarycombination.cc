#include "binarycombination.h"

BinaryCombination::BinaryCombination(int n) {
    this->n = n;
    this->reset();
}

const std::vector<bool>& BinaryCombination::next() {
    if(this->eof()) {
        this->reset();
    }
    else {
        this->i++;

        std::vector<bool>::reverse_iterator i;
        for(i = this->result.rbegin(); i != this->result.rend(); ++i) {
            if(*i == false) {
                *i = true;
                break;
            }
            else {
                *i = !*i;
            }
        }
    }

    return this->result;
}

const std::vector<bool>& BinaryCombination::current() const {
    return this->result;
}

int BinaryCombination::count() const {
    return 2 << (this->n - 1);
}

bool BinaryCombination::eof() const {
    return this->i == this->count();
}

void BinaryCombination::reset() {
    this->i = 0;
    this->result.assign(this->n, false);
}
