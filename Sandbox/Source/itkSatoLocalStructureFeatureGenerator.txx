/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkSatoLocalStructureFeatureGenerator.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkSatoLocalStructureFeatureGenerator_txx
#define __itkSatoLocalStructureFeatureGenerator_txx

#include "itkSatoLocalStructureFeatureGenerator.h"


namespace itk
{

/*
 * Constructor
 */
template <unsigned int NDimension>
SatoLocalStructureFeatureGenerator<NDimension>
::SatoLocalStructureFeatureGenerator()
{
  this->SetNumberOfRequiredInputs( 1 );

  this->m_HessianFilter = HessianFilterType::New();
  this->m_EigenAnalysisFilter = EigenAnalysisFilterType::New();
  this->m_LocalStructureFilter = LocalStructureFilterType::New();

  typename OutputImageSpatialObjectType::Pointer outputObject = OutputImageSpatialObjectType::New();

  this->ProcessObject::SetNthOutput( 0, outputObject.GetPointer() );

  this->m_Sigma =  1.0;
}


/*
 * Destructor
 */
template <unsigned int NDimension>
SatoLocalStructureFeatureGenerator<NDimension>
::~SatoLocalStructureFeatureGenerator()
{
}

template <unsigned int NDimension>
void
SatoLocalStructureFeatureGenerator<NDimension>
::SetInput( const SpatialObjectType * spatialObject )
{
  // Process object is not const-correct so the const casting is required.
  this->SetNthInput(0, const_cast<SpatialObjectType *>( spatialObject ));
}

template <unsigned int NDimension>
const typename SatoLocalStructureFeatureGenerator<NDimension>::SpatialObjectType *
SatoLocalStructureFeatureGenerator<NDimension>
::GetFeature() const
{
  if (this->GetNumberOfOutputs() < 1)
    {
    return 0;
    }

  return static_cast<const SpatialObjectType*>(this->ProcessObject::GetOutput(0));

}


/*
 * PrintSelf
 */
template <unsigned int NDimension>
void
SatoLocalStructureFeatureGenerator<NDimension>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf( os, indent );
}


/*
 * Generate Data
 */
template <unsigned int NDimension>
void
SatoLocalStructureFeatureGenerator<NDimension>
::GenerateData()
{
  typename InputImageSpatialObjectType::ConstPointer inputObject = 
    dynamic_cast<const InputImageSpatialObjectType * >( this->ProcessObject::GetInput(0) );

  if( !inputObject )
    {
    itkExceptionMacro("Missing input spatial object");
    }

  const InputImageType * inputImage = inputObject->GetImage();

  if( !inputImage )
    {
    itkExceptionMacro("Missing input image");
    }

  this->m_HessianFilter->SetInput( inputImage );
  this->m_EigenAnalysisFilter->SetInput( this->m_HessianFilter->GetOutput() );
  this->m_LocalStructureFilter->SetInput( this->m_EigenAnalysisFilter->GetOutput() );

  this->m_HessianFilter->SetSigma( this->m_Sigma );
  this->m_EigenAnalysisFilter->SetDimension( Dimension );
  this->m_LocalStructureFilter->SetAlpha( this->m_Alpha );
  this->m_LocalStructureFilter->SetGamma( this->m_Gamma );

  this->m_LocalStructureFilter->Update();

  typename OutputImageType::Pointer outputImage = this->m_LocalStructureFilter->GetOutput();

  outputImage->DisconnectPipeline();

  typedef itk::ImageSpatialObject< Dimension, OutputPixelType > OutputImageSpatialObjectType;

  OutputImageSpatialObjectType * outputObject =
    dynamic_cast< OutputImageSpatialObjectType * >(this->ProcessObject::GetOutput(0));

  outputObject->SetImage( outputImage );
}

} // end namespace itk

#endif
