/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkKLMSegmentationRegion.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkKLMSegmentationRegion_h
#define _itkKLMSegmentationRegion_h

#include "itkObject.h"
#include "itkKLMSegmentationBorder.h"
#include "itkSegmentationRegion.h"

#include "vnl/vnl_vector.h"

namespace itk
{

/** \class KLMSegmentationRegion
 * \brief Base class for KLMSegmentationRegion object
 *
 * itkKLMSegmentationRegion is the base class for the KLMSegmentationRegion
 * objects. It provides the basic function definitions that are inherent to
 * KLMSegmentationRegion objects.
 *
 * This object supports data handling of multiband images. The object
 * accepts images in vector format, where each pixel is a vector and each
 * element of the vector corresponds to an entry from 1 particular band of
 * a multiband dataset.
 *
 * We expect the user to provide the input to the routine in vector format.
 * A single band image is treated as a vector image with a single element
 * for every vector.
 *
 * Data structure for a region:
 * A region is defined as a closed area in the image that is surrounded
 * by a list of borders objects (see itkKLMSegmentationBorder class).
 *
 * Shown below is an initial two-dimensional 8x9 image with a 4x3 grid size
 * partition. The initial region blocks are labelled in hexadecimal.
 * Below the grid partition, the borders are shown as E, where C
 * is an image pixel from the initial image.  Note that each border is
 * placed in between two regions.  Each two-dimensional region is
 * surrounded by four borders.
 *
 * Initial regions of a 8 by 9 image with a 4 by 3 grid partition.
 * \f[\begin{tabular}{|c|c|c|c|c|c|c|c|c|}
 * \hline
 *   1 & 1 & 1 & 2 & 2 & 2 & 3 & 3 & 3 \\ \hline
 *   1 & 1 & 1 & 2 & 2 & 2 & 3 & 3 & 3 \\ \hline
 *   4 & 4 & 4 & 5 & 5 & 5 & 6 & 6 & 6 \\ \hline
 *   4 & 4 & 4 & 5 & 5 & 5 & 6 & 6 & 6 \\ \hline
 *   7 & 7 & 7 & 8 & 8 & 8 & 9 & 9 & 9 \\ \hline
 *   7 & 7 & 7 & 8 & 8 & 8 & 9 & 9 & 9 \\ \hline
 *   a & a & a & b & b & b & c & c & c \\ \hline
 *   a & a & a & b & b & b & c & c & c \\ \hline
 *  \end{tabular}\f]
 *
 * Region borders are shown as ``E''.
 * \f[\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|}
 * \hline
 *   C & C & C &   & C & C & C &   & C & C & C \\ \hline
 *   C & C & C & E & C & C & C & E & C & C & C \\ \hline
 *     & E &   &   &   & E &   &   &   & E &   \\ \hline
 *   C & C & C &   & C & C & C &   & C & C & C \\ \hline
 *   C & C & C & E & C & C & C & E & C & C & C \\ \hline
 *     & E &   &   &   & E &   &   &   & E &   \\ \hline
 *   C & C & C &   & C & C & C &   & C & C & C \\ \hline
 *   C & C & C & E & C & C & C & E & C & C & C \\ \hline
 *     & E &   &   &   & E &   &   &   & E &   \\ \hline
 *   C & C & C &   & C & C & C &   & C & C & C \\ \hline
 *   C & C & C & E & C & C & C & E & C & C & C \\ \hline
 *  \end{tabular}\f]
 *
 * \ingroup RegionGrowingSegmentation
 */
class KLMSegmentationBorder;

class ITKCommon_EXPORT KLMSegmentationRegion : public SegmentationRegion
{
private:
  /** Type definition for an double vector. */
  typedef vnl_vector<double> MeanRegionIntensityType;

public:
  /** Standard class typedefs. */
  typedef KLMSegmentationRegion     Self;
  typedef SegmentationRegion        Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(KLMSegmentationRegion,SegmentationRegion);

  /** Type definition for vector container that stores the borders
   * associated with a current region. */
  typedef std::vector< KLMSegmentationBorder * > RegionBorderVectorType;

  /** Type definition for the region border vector iterators to be used. */
  typedef RegionBorderVectorType::iterator RegionBorderVectorIterator;

  /** Type definition for the const region border vector iterators to be used. */
  typedef RegionBorderVectorType::const_iterator RegionBorderVectorConstIterator;

  /** type definition for the region label type. */
  typedef Superclass::RegionLabelType RegionLabelType;

  /** Get a head pointer to the vector container storing the borders
   * associated with a region. */
  RegionBorderVectorIterator GetRegionBorderItBegin();
  RegionBorderVectorConstIterator GetRegionBorderConstItBegin();

  /** Get a tail pointer to the vector container storing the borders
   * associated with a region. */
  RegionBorderVectorIterator GetRegionBorderItEnd();
  RegionBorderVectorConstIterator GetRegionBorderConstItEnd();

  /** Get the number of borders in the vector container storing the borders
   * associated with a region. */
  int GetRegionBorderSize() const;

  /** Set/Get the mean pixel intensity in the region. */
  itkSetMacro(MeanRegionIntensity, MeanRegionIntensityType)
  itkGetConstMacro(MeanRegionIntensity, MeanRegionIntensityType);

  /** Set the region with parameter values
   * defining the region. */
  void SetRegion(MeanRegionIntensityType meanRegionIntensity,
                 double          regionArea,
                 RegionLabelType label);

  /** Set the region with parameter values (mean and area)
   * defining the region when merged with the new region. */
  void AddRegion(const Self *region);

  /** Function to print the region parameters using std::cout. */
  void PrintRegionInfo();

protected:
  KLMSegmentationRegion();
  ~KLMSegmentationRegion();
  void PrintSelf(std::ostream& os, Indent indent) const;

public:
  /** Insert a region border to the front of the list. */
  void PushFrontRegionBorder(KLMSegmentationBorder *pBorderCandidate);

  /** Insert a region border to the back of the list. */
  void PushBackRegionBorder(KLMSegmentationBorder *pBorderCandidate);

  /** Insert a region border to the list, where position is unknown
    * (sorting based on region labels is done to maintain consistency). */
  void InsertRegionBorder(KLMSegmentationBorder *pBorderCandidate);

  /** Insert a region border at a given location. */
  void InsertRegionBorder(RegionBorderVectorIterator it,
                          KLMSegmentationBorder *pBorderCandidate);

  /** Delete a region border. */
  void DeleteRegionBorder(KLMSegmentationBorder *pBorderCandidate);

  /** Delete all region borders */
  void DeleteAllRegionBorders();

  /** Reset a regions label to that of the supplied region and update
    * the regions borders. */
  void ResetRegionLabelAndUpdateBorders(Self *region);

  /** Splice the regions borders from the new region into the current
    * region.  If duplicate borders are found, the duplicate border
    * region is not inserted into the new region borders list, rather,
    * it has its pointers to region1 and region2 set to NULL and
    * Lambda set to -1.0.
    *
    * For example, take an image with 3 regions A, B, C
    * \f[\begin{tabular}{|c|c|}
    * \hline
    *   A & A \\ \hline
    *   B & C \\ \hline
    *  \end{tabular}\f]
    * where region A has region borders A-B and A-C;
    * region B has region borders A-B and B-C; and
    * region C has region borders A-C and B-C.
    *
    * Suppose region border A-B has been removed, so that region B
    * can be merged into region A.  When splicing the region
    * borders from A and B into the new region A, duplicate
    * region borders A-C and A-C (one of which was formerly B-C)
    * will be present.  In this case, one of the region borders
    * A-C is given the combined length of the two former borders
    * and is put into the region borders list.  The other is
    * nullified by having its pointers to region1 and region2 set
    * to NULL and its Lambda value set to -1.0.
    */
  void SpliceRegionBorders(Self *region);

  /** Recalculate the Lambda values using EvaluateLambda() for all
   * the borders defining the region. */
  void UpdateRegionBorderLambda();

private:
  KLMSegmentationRegion(const Self&); // purposely not implemented
  void operator=(const Self&); // purposely not implemented

  RegionBorderVectorType    m_RegionBorderVector;
  MeanRegionIntensityType   m_MeanRegionIntensity;

}; // class SegmentationRegion


} // namespace itk


#endif
