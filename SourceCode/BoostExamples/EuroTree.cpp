#include "EuroTree.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using std::exp;
using std::sqrt;
using std::max;
using std::min;

using std::tuple;
using std::make_tuple;

/*EuroTree::EuroTree(double mktPrice, double mktRate, double mktVol, double divRate, double strike,
	const Date& valueDate, const Date& expireDate, Porc porc, int numTimePoints, 
	const DayCount& dayCount)
	
{
	calcPrice_();
}*/

EuroTree::EuroTree(double mktPrice, double mktRate, double mktVol, double divRate, double strike,
	double expiry, Porc porc, int numTimePoints) :mktPrice_(mktPrice), mktRate_(mktRate), mktVol_(mktVol), 
	divRate_(divRate), strike_(strike), expiry_(expiry), porc_(porc),
	numTimePoints_(numTimePoints)
{
	calcPrice_();
}

Node EuroTree::operator()(int i, int j) const
{
	return grid_[i][j];
}

/*boost::multi_array<Node, 2> EuroTree::grid() const
{
	return grid_;
}*/

double EuroTree::optionPrice() const
{
	return optionPrice_;
}

double EuroTree::calcDelta(double shift)
{
	double origMktPrice = mktPrice_;
	double upPrice = mktPrice_ * (1 + shift / 2.0);
	double downPrice = mktPrice_ * (1 - shift / 2.0);

	mktPrice_ = upPrice;
	calcPrice_();
	double upOptPrice = this->operator()(0, 0).payoff;

	mktPrice_ = downPrice;
	calcPrice_();
	double downOptPrice = this->operator()(0, 0).payoff;

	mktPrice_ = origMktPrice;

	double delta = (upOptPrice - downOptPrice) / optionPrice_;
	return delta;
}

double EuroTree::resetMktPrice(double newMktPrice)
{
	mktPrice_ = newMktPrice;
	calcPrice_();
	return optionPrice_;
}

double EuroTree::resetMktRate(double newMktRate)
{
	mktRate_ = newMktRate;
	calcPrice_();
	return optionPrice_;
}

double EuroTree::resetMktVol(double newMktVol)
{
	mktVol_ = newMktVol;
	calcPrice_();
	return optionPrice_;
}

void EuroTree::calcPrice_() 
{	
	gridSetup_();
	paramInit_();
	projectPrices_();
	calcPayoffs_();
	optionPrice_ = this->operator()(0, 0).payoff;
}

void EuroTree::gridSetup_()
{
	grid_.resize(boost::extents[numTimePoints_][numTimePoints_]);
}

void EuroTree::paramInit_()
{
//	double yfToExpiry = dayCount_(valueDate_, expireDate_);
	dt_ = expiry_ / static_cast<double>(numTimePoints_ - 1);
	u_ = exp(mktVol_ * sqrt(dt_));
	d_ = 1.0 / u_;
	p_ = 0.5*(1.0 + (mktRate_ - divRate_ - 0.5*mktVol_*mktVol_)*sqrt(dt_) / mktVol_);
	discFctr_ = exp(-mktRate_ * dt_);
}

void EuroTree::projectPrices_()
{
	grid_[0][0].underlying = mktPrice_;

	for (auto j = 1; j < numTimePoints_; ++j)
	{
		for (auto i = 0; i <= j; ++i)
		{
			if (i < j)
			{
				grid_[i][j].underlying = d_ * grid_[i][j - 1].underlying;
			}
			else
			{
				grid_[i][j].underlying = u_ * grid_[i - 1][j - 1].underlying;
			}
		}
	}
}

void EuroTree::calcPayoffs_()
{
	auto payoff = [this](double underlying)
	{
		if (porc_ == Porc::CALL)
			return max(underlying - strike_, 0.0);
		else
			return max(strike_ - underlying, 0.0);
	};

	for (auto j = numTimePoints_ - 1; j >= 0; --j)
	{
		for (auto i = 0; i <= j; ++i)
		{
			if (j == numTimePoints_ - 1)
			{
				grid_[i][j].payoff = payoff(grid_[i][j].underlying);
			}
			else
			{
				grid_[i][j].payoff = discFctr_ * (p_*grid_[i + 1][j + 1].payoff + (1.0 - p_)*grid_[i][j + 1].payoff);
			}
		}
	}
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

