#ifndef SPECIES
#define SPECIES
class Species{

public:
double P(double p, double newP) {
        return p + newP;
}

public:
double SetP(double i) {
    return i;
}

public:
double AddP(double p, double i) {
    return p+i;
}

};
#endif