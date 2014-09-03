#ifndef BINARYCOMBINATION_H
#define BINARYCOMBINATION_H

#include <vector>

class BinaryCombination
{
public:
    BinaryCombination(int n);

    // Generate next combination
    const std::vector<bool>& next();

    // Return current combination
    const std::vector<bool>& current() const;

    // Return number of all combinations
    int count() const;

    // Current combination is the last one ?
    bool eof() const;

    // Reset combination
    void reset();
private:
    // Number of combination elements
    int n;
    // Current combination number
    int i;

    // Current combination
    std::vector<bool> result;
};

#endif // BINARYCOMBINATION_H
