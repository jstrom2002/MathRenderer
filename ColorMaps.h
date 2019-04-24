#ifndef COLORMAPS_H
#define COLORMAPS_H
#pragma once
#include "stdafx.h"

std::vector<GLfloat> jetColormap(double in, double colorBound);
std::vector<GLfloat> dec2RGB(double in, double colorBound);

#endif