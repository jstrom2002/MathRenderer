#pragma once
#include "stdafx.h"
std::vector<GLfloat> jetColormap(double in, double colorBound) {
	std::vector<GLfloat> outp;
	double newVal = in;
	if (newVal > colorBound) {//red = max
		outp.push_back(1.0f);
		outp.push_back(0.0f);
		outp.push_back(0.0f);
		return outp;
	}
	if (newVal < -colorBound) {//blue = min 
		outp.push_back(0.0f);
		outp.push_back(0.0f);
		outp.push_back(1.0f);
		return outp;
	}

	if (newVal >= 0) {
		if (newVal < (0.5 * colorBound)) {	//1st coloring - green (low) to yellow (high)
			outp.push_back(((newVal / colorBound) / 0.5f));
			outp.push_back(1.0f);
			outp.push_back(0.0f);
			return outp;
		}
		if (newVal >= (0.5 * colorBound)) {	//2rd coloring - yellow (low) to red (high)
			outp.push_back(1.0f);
			outp.push_back(1.0f - (newVal / colorBound));
			outp.push_back(0.0f);
			return outp;
		}
	}

	if (newVal < 0) {
		if (newVal > (-0.5 * colorBound)) {	//1st coloring - green (low) to teal (high)
			outp.push_back(0.0f);
			outp.push_back(1.0f);
			outp.push_back((abs((newVal / colorBound)) / 0.5f));
			return outp;
		}
		if (newVal <= (-0.5 * colorBound)) {	//2rd coloring - teal (low) to blue (high)
			outp.push_back(0.0f);
			outp.push_back((1.0f - abs((newVal / colorBound))));
			outp.push_back(1.0f);
			return outp;
		}
	}

	return outp;
}

std::vector<GLfloat> dec2RGB(double in, double colorBound) {
	//My own custom color mapping with lots of contrast between the regions,
	//and 3 regions of gradation instead of two
	std::vector<GLfloat> outp;
	double newVal = in;
	//newVal *= 10.0f;	//adjust values of Im(f(z)) to place it within suitable range
	if (newVal > colorBound) {
		outp.push_back(1.0f);
		outp.push_back(1.0f);
		outp.push_back(1.0f);
		return outp;
	}
	if (newVal < -colorBound) {
		outp.push_back(0.2f);
		outp.push_back(0.2f);
		outp.push_back(0.2f);
		return outp;
	}

	if (newVal >= 0) {
		if (newVal < (0.333 * colorBound)) {	//1st coloring - blue (low) to green (high)
			outp.push_back(0.0f);
			outp.push_back(((newVal / colorBound) / 0.333f));
			outp.push_back(1.0f - ((newVal / colorBound) / 0.333f));
			return outp;
		}
		if (newVal >= (0.333 * colorBound) && newVal < (0.666 * colorBound)) { //2nd coloring - green (low) to red (high)
			outp.push_back(((newVal / colorBound) / 0.666f));
			outp.push_back(1.0f - ((newVal / colorBound) / 0.666f));
			outp.push_back(0.0f);
			return outp;
		}
		if (newVal >= (0.666 * colorBound)) {	//3rd coloring - red (low) to white (high)
			outp.push_back((1.0f - ((1.0f - (newVal / colorBound)) / 0.333f)));
			outp.push_back((1.0f - ((1.0f - (newVal / colorBound)) / 0.333f)));
			outp.push_back(1.0f);
			return outp;
		}
	}

	if (newVal < 0) {
		if (newVal > (-0.333 * colorBound)) {	//1st coloring - purple (low) to yellow (high)
			outp.push_back(1.0f);
			outp.push_back((abs((newVal / colorBound)) / 0.333f));
			outp.push_back(1.0f - (abs((newVal / colorBound)) / 0.333f));
			return outp;
		}
		if (newVal <= (-0.333 * colorBound) && newVal > (-0.666 * colorBound)) { //2nd coloring - yellow (low) to teal (high)
			outp.push_back(1.0f - (abs((newVal / colorBound)) / 0.666f));
			outp.push_back(1.0f);
			outp.push_back((abs((newVal / colorBound)) / 0.666f));
			return outp;
		}
		if (newVal <= (-0.666 * colorBound)) {	//3rd coloring - teal (low) to grey (high)
			outp.push_back((1.0f - abs((newVal / colorBound))) + 0.2f);
			outp.push_back((1.0f - abs((newVal / colorBound))) + 0.2f);
			outp.push_back((1.0f - abs((newVal / colorBound))) + 0.2f);
			return outp;
		}
	}

	return outp;
}