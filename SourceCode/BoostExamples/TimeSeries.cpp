#include "TimeSeries.h"
#include <numeric>		// Need this for std::accumulate, rather than <algorithm>
#include <algorithm>	// For copy(.)

using boost::circular_buffer;

TimeSeries::TimeSeries(Unsigned length) :ts_(circular_buffer<double>(length)){}
TimeSeries::TimeSeries(const boost::circular_buffer<double>& ts) :ts_(ts){}
TimeSeries::TimeSeries(const std::vector<double>& ts)
{
	ts_.set_capacity(ts.size());
	std::copy(ts.begin(), ts.end(), back_inserter(ts_));
}

void TimeSeries::append(double x)
{
	ts_.push_back(x);
}

double TimeSeries::value(Unsigned k) const
{
	return ts_.at(k);
}

double TimeSeries::movingAverage(Unsigned t) const
{
	Unsigned offset = 0;
	double ma = 0.0;
	if (t > ts_.size())		// if set beyond number of elements,
	{						// just compute MA of the entire set.
		t = ts_.size() - 1;
	}
	else if ((t > 0)&&(t <= ts_.size()))
	{
		offset = ts_.size() - t;
	}
	else	// The case t <= 0 should be handled with an exception.
	{		// when the public movingAverage(.) method is called.
		offset = 0;
		t = ts_.size();
	}
	double den = static_cast<double>(t);
	return std::accumulate(ts_.begin() + offset, ts_.end(), 0.0) / den;
}

double TimeSeries::volatility(Unsigned t) const
{
	double vol = 0.0;	// Implementation is an exercise

	return vol;
}

boost::circular_buffer<double> TimeSeries::buffer() const
{
	return ts_;
}

double TimeSeries::mean_(Unsigned t) const
{
	Unsigned offset = 0;
	if (t > 0)
	{
		offset = ts_.size() - t;
	}
	else	// The case t <= 0 should be handled with an exception.
	{		// when the public movingAverage(.) method is called.
		offset = 0;
		t = ts_.size();
	}
	double den = static_cast<double>(t);
	return std::accumulate(ts_.begin() + offset, ts_.end(), 0.0) / den;
}

/*
	Copyright 2019 Daniel Hanson

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
