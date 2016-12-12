//
// Created by alevalv on 06/12/16.
//

#ifndef MACLEA_ELEMENT_H
#define MACLEA_ELEMENT_H

#include <array>

class Element {
    std::vector<double> elements;
public:
    Element();
    Element(int size);
    Element(std::vector<double> values);
    double distance(const Element& element);
    double& operator[](int pos);
};


#endif //MACLEA_ELEMENT_H
