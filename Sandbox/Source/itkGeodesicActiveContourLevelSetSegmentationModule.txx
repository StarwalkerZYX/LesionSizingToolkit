/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkGeodesicActiveContourLevelSetSegmentationModule.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkGeodesicActiveContourLevelSetSegmentationModule_txx
#define __itkGeodesicActiveContourLevelSetSegmentationModule_txx

#include "itkGeodesicActiveContourLevelSetSegmentationModule.h"
#include "itkGeodesicActiveContourLevelSetImageFilter.h"


namespace itk
{


/**
 * Constructor
 */
template <unsigned int NDimension>
GeodesicActiveContourLevelSetSegmentationModule<NDimension>
::GeodesicActiveContourLevelSetSegmentationModule()
{
}


/**
 * Destructor
 */
template <unsigned int NDimension>
GeodesicActiveContourLevelSetSegmentationModule<NDimension>
::~GeodesicActiveContourLevelSetSegmentationModule()
{
}


/**
 * PrintSelf
 */
template <unsigned int NDimension>
void
GeodesicActiveContourLevelSetSegmentationModule<NDimension>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf( os, indent );
}


/**
 * Generate Data
 */
template <unsigned int NDimension>
void
GeodesicActiveContourLevelSetSegmentationModule<NDimension>
::GenerateData()
{
  const InputSpatialObjectType * inputObject =
    dynamic_cast< const InputSpatialObjectType * >( this->GetInput() );

  const FeatureSpatialObjectType * featureObject =
    dynamic_cast< const FeatureSpatialObjectType * >( this->GetFeature() );


  const InputImageType * inputImage = inputObject->GetImage();
  const FeatureImageType * featureImage = featureObject->GetImage();

  typedef itk::GeodesicActiveContourLevelSetImageFilter<
    InputImageType, FeatureImageType, OutputPixelType > FilterType;

  typedef itk::SpatialObject< NDimension >        SpatialObjectType;

  typename FilterType::Pointer filter = FilterType::New();

  filter->SetInput( inputImage );
  filter->SetFeatureImage( featureImage );

  filter->SetMaximumRMSError( 0.01 );
  filter->SetNumberOfIterations( 90 );
  filter->SetPropagationScaling( 100.0 );
  filter->SetCurvatureScaling( 75.0 );
  filter->SetAdvectionScaling( 1.0 );

  filter->Update();

  std::cout << std::endl;
  std::cout << "Max. no. iterations: " << filter->GetNumberOfIterations() << std::endl;
  std::cout << "Max. RMS error: " << filter->GetMaximumRMSError() << std::endl;
  std::cout << std::endl;
  std::cout << "No. elpased iterations: " << filter->GetElapsedIterations() << std::endl;
  std::cout << "RMS change: " << filter->GetRMSChange() << std::endl;


  typename OutputImageType::Pointer outputImage = filter->GetOutput();

  outputImage->DisconnectPipeline();

  OutputSpatialObjectType * outputObject =
    dynamic_cast< OutputSpatialObjectType * >(this->ProcessObject::GetOutput(0));

  outputObject->SetImage( outputImage );
}

} // end namespace itk

#endif
