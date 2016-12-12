//
// Created by alevalv on 06/12/16.
//

#include <math.h>
#include <vector>
#include "Element.h"

using namespace std;

Element::Element()
{
    elements.assign(1,0);
}

Element::Element(int size)
{
    elements.assign(size, 0);
}

Element::Element(std::vector<double> values)
{
    elements = values;
}

double Element::distance(const Element &element)
{
    double distance = 0;

    for (int i=0; i<elements.size();i++)
    {
        distance += pow((this->elements.at(i) - element.elements.at(i)), (double) 2);
    }

    return distance;
}

double &Element::operator[](int pos)
{
    if (pos < elements.size())
        return elements[pos];
}
