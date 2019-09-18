#ifndef TIME_SERIES_H
#define TIME_SERIES_H

#include <boost/circular_buffer.hpp>
#include <vector>
using Unsigned = size_t;

class TimeSeries
{
public:
	TimeSeries(Unsigned length);
	TimeSeries(const boost::circular_buffer<double>& ts);
	TimeSeries(const std::vector<double>& ts);
	void append(double x);
	double value(Unsigned k) const;
	double movingAverage(Unsigned t = 0) const;
	double volatility(Unsigned t = 0) const;		// Exercise
	boost::circular_buffer<double> buffer() const;

private:
	boost::circular_buffer<double> ts_;
	double mean_(Unsigned t = 0) const;
};

#endif

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
