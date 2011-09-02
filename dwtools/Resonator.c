/* Resonator.c
 *
 * Copyright (C) 2008 David Weenink
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * djmw 20081029
 * djmw 20081124 +ConstantGainResonator
 */

#include "Resonator.h"

#define SETBC(f,bw) \
	double r = exp (-NUMpi * my dT * bw); \
	my c = -(r * r); \
	my b = 2.0 * r * cos (2.0 * NUMpi * f * my dT);

static void classFilter_resetMemory (I)
{
	iam (Filter);
	my p1 = my p2 = 0;
}

static void classFilter_setFB (I, double f, double bw)
{
	iam (Filter);
	SETBC (f, bw)
	my a = 1.0 - my b - my c;
}

static double classFilter_getOutput (I, double input)
{
	iam (Resonator);
	double output = my a * input + my b * my p1 + my c * my p2;
	my p2 = my p1;
	my p1 = output;
	return output;
}

class_methods (Filter, Data)
	class_method_local (Filter, setFB)
	class_method_local (Filter, getOutput)
	class_method_local (Filter, resetMemory)
class_methods_end

class_methods (Resonator, Filter)
class_methods_end

static void classAntiResonator_setFB (I, double f, double bw)
{
	iam (AntiResonator);
	
	if (f <= 0 && bw <= 0)
	{
		my a = 1; my b = -2; my c = 1; // all-pass except dc
	}
	else
	{
		SETBC (f, bw)
		my a = 1 / (1.0 - my b - my c);
		// The next equations are incorporated in the getOutput function
		//my c *= - my a; my b *= - my a;
	}
}

/* y[n] = a * (x[n] - b * x[n-1] - c * x[n-2]) */
static double classAntiResonator_getOutput (I, double input)
{
	iam (AntiResonator);
	double output = my a * (input - my b * my p1 - my c * my p2);
	my p2 = my p1;
	my p1 = input;
	return output;
}

class_methods (AntiResonator, Filter)
	class_method_local (AntiResonator, setFB)
	class_method_local (AntiResonator, getOutput)
class_methods_end

static void classConstantGainResonator_resetMemory (I)
{
	iam (ConstantGainResonator);
	my p1 = my p2 = my p3 = my p4 = 0;
}

static void classConstantGainResonator_setFB (I, double f, double bw)
{
	iam (ConstantGainResonator);

	SETBC (f, bw)
	my a = 1 - r;
	my d = -r;
}

/* y[n] = a * (x[n] + d * x[n-2]) + b * y[n-1] + c * y[n-2] */
static double classConstantGainResonator_getOutput (I, double input)
{
	iam (ConstantGainResonator);
	double output = my a * (input + my d * my p4) + my b * my p1 + my c * my p2;
	my p2 = my p1;
	my p1 = output;
	my p4 = my p3;
	my p3 = input;
	return output;
}

class_methods (ConstantGainResonator, Filter)
	class_method_local (ConstantGainResonator, setFB)
	class_method_local (ConstantGainResonator, getOutput)
	class_method_local (ConstantGainResonator, resetMemory)
class_methods_end

Resonator Resonator_create (double dT)
{
	Resonator me = new (Resonator);
	my a = 1; // all-pass
	my dT = dT;
	return me;
}

ConstantGainResonator ConstantGainResonator_create (double dT)
{
	ConstantGainResonator me = new (ConstantGainResonator);
	my a = 1; // all-pass
	my dT = dT;
	return me;
}

AntiResonator AntiResonator_create (double dT)
{
	AntiResonator me = new (AntiResonator);
	my a = 1; // all-pass
	my dT = dT;
	return me;
}

void Filter_setFB (I, double f, double b)
{
	iam (Filter);
	our setFB (me, f, b);
}

double Filter_getOutput (I, double input)
{
	iam (Filter);
	return our getOutput (me, input);
}

void Filter_resetMemory (I)
{
	iam (Filter);
	our resetMemory (me);
}

Sound Sound_filterByResonator (Sound me, double f, double b, int anti, int constantGain)
{
	Sound thee = NULL;
	Filter r = anti ? (Filter) AntiResonator_create (my dx) : (constantGain ?  (Filter) ConstantGainResonator_create (my dx): (Filter) Resonator_create (my dx));
	Filter_setFB (r, f, b);
	thee = Data_copy (me);
	for (long ic = 1; ic <= my ny; ic++)
	{
		Filter_resetMemory (r);
		for (long is = 1; is <= my nx; is++)
		{
			thy z[ic][is] = Filter_getOutput (r, my z[ic][is]);
		}
	}
	Melder_free (r);
	return thee;
}

/* End of file Resonator.c */
