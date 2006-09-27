// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                   OpenMS Mass Spectrometry Framework
// --------------------------------------------------------------------------
//  Copyright (C) 2003-2006 -- Oliver Kohlbacher, Knut Reinert
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Maintainer: Cornelia Friedle $
// --------------------------------------------------------------------------

#ifndef OPENMS_FILTERING_DATAREDUCTION_MAXREDCUER_H
#define OPENMS_FILTERING_DATAREDUCTION_MAXREDCUER_H

#include<OpenMS/FILTERING/DATAREDUCTION/DataReducer.h>

namespace OpenMS
{	

	class MaxReducer:public DataReducer
	{
		typedef DPeak<1> PeakT;
		typedef MSSpectrum< PeakT > 	SpectrumType;
		typedef DSpectrum< 1, DPeakArrayNonPolymorphic<1, PeakT > > 	BaseSpectrum;

	public:

		///constructor
		MaxReducer();

		///destructor
		~MaxReducer();

		/// calculates the reduced MSExperiment
	 	virtual  void applyReduction(const  ExperimentType& in,  ExperimentType& out );
	
		/// returns an instance of this class
		static DataReducer* create()
		{
			return new MaxReducer();
		}

		/// returns the name of this module
		static const  String getName()
		{
			return "MaxReducer";
		}
	private:
		/// find the peak for the reduced MSExperiment  
		BaseSpectrum::Iterator findMaxIntensity(std::vector<PeakT >& peaks);

	};
}
#endif
