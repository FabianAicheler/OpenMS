// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                   OpenMS Mass Spectrometry Framework
// --------------------------------------------------------------------------
//  Copyright (C) 2003-2007 -- Oliver Kohlbacher, Knut Reinert
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
// $Maintainer: Ole Schulz-Trieglaff $
// --------------------------------------------------------------------------

#ifndef OPENMS_TRANSFORMATIONS_FEATUREFINDER_MODELDESCRIPTION_H
#define OPENMS_TRANSFORMATIONS_FEATUREFINDER_MODELDESCRIPTION_H

#include <OpenMS/FORMAT/Param.h>
#include <OpenMS/DATASTRUCTURES/String.h>
#include <OpenMS/TRANSFORMATIONS/FEATUREFINDER/BaseModel.h>
#include <OpenMS/CONCEPT/Factory.h>

#include <sstream>

namespace OpenMS
{
	/** @brief Base class for a model (e.g. isotope distributions, rt model) in the FeatureFinder.
	
		@ingroup FeatureFinder
				
	*/  
  template <UnsignedInt D, typename Traits = KernelTraits>
	class ModelDescription
	{
		public:
		
		/// standard constructor 
		ModelDescription(): name_(), parameters_(){}
		
		/// copy constructor 
		ModelDescription(const ModelDescription& source):
			name_(source.name_),
			parameters_(source.parameters_)
		{}

		/// constructor provided for convenience
		ModelDescription(const BaseModel<D,Traits>* model):
			name_(model->getName()),
			parameters_(model->getParam())
		{}

		/// destructor 
		virtual ~ModelDescription(){}
		
		/// assignment operator 
		virtual ModelDescription& operator = (const ModelDescription& source)
		{
			name_ = source.name_;
			parameters_ = source.parameters_;
			return *this;
		}
		
		/// creates model from the parameters defined in this class
		/// returns 0 if no description is set. 
		BaseModel<D,Traits>* createModel()
		{
			if (name_ == "") return 0;				
			BaseModel<D,Traits>* model = Factory< BaseModel<D,Traits> >::create(name_);
			model->setParam(parameters_);
			return model;
		}
		
		/**	Accessors	*/
		//@{
		/// Non-mutable access to model name
		inline const String& getName() const { return name_; }
		/// Mutable access to the model name
		inline String& getName() { return name_; }
		/// Set the model name
		inline void setName(const String& name) { name_ = name; }

		/// Non-mutable access to model parameters
		inline const Param& getParam() const { return parameters_; }
		/// Mutable access to the model parameters
		inline Param& getParam() { return parameters_; }
		/// Set the model parameters
		inline void setParam(const Param& param) { parameters_ = param; }
    
		/**	@name Predicates */
		//@{
		virtual bool operator == (const ModelDescription& rhs) const;
		virtual bool operator != (const ModelDescription& rhs) const;			
		//@}
		
    protected:
    	
    	String name_;
		Param parameters_;
	};

	template <UnsignedInt D, typename Traits>
	bool ModelDescription<D, Traits>::operator == (const ModelDescription<D, Traits>& rhs) const
	{
		std::stringstream stream1;
		stream1 << parameters_;
		std::stringstream stream2;
		stream2 << rhs.parameters_;
		return ((name_ == rhs.name_) && (stream1.str() == stream2.str()));
	}

	template <UnsignedInt D, typename Traits>
	bool  ModelDescription<D, Traits>::operator != (const  ModelDescription<D, Traits>& rhs) const
	{
		return !(operator == (rhs));
	}
}
#endif // OPENMS_TRANSFORMATIONS_FEATUREFINDER_MODELDESCRIPTION_H
