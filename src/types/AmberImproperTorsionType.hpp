/*
 * Copyright (c) 2005 The University of Notre Dame. All Rights Reserved.
 *
 * The University of Notre Dame grants you ("Licensee") a
 * non-exclusive, royalty free, license to use, modify and
 * redistribute this software in source and binary code form, provided
 * that the following conditions are met:
 *
 * 1. Acknowledgement of the program authors must be made in any
 *    publication of scientific results based in part on use of the
 *    program.  An acceptable form of acknowledgement is citation of
 *    the article in which the program was described (Matthew
 *    A. Meineke, Charles F. Vardeman II, Teng Lin, Christopher
 *    J. Fennell and J. Daniel Gezelter, "OOPSE: An Object-Oriented
 *    Parallel Simulation Engine for Molecular Dynamics,"
 *    J. Comput. Chem. 26, pp. 252-271 (2005))
 *
 * 2. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 3. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 * This software is provided "AS IS," without a warranty of any
 * kind. All express or implied conditions, representations and
 * warranties, including any implied warranty of merchantability,
 * fitness for a particular purpose or non-infringement, are hereby
 * excluded.  The University of Notre Dame and its licensors shall not
 * be liable for any damages suffered by licensee as a result of
 * using, modifying or distributing the software or its
 * derivatives. In no event will the University of Notre Dame or its
 * licensors be liable for any lost revenue, profit or data, or for
 * direct, indirect, special, consequential, incidental or punitive
 * damages, however caused and regardless of the theory of liability,
 * arising out of the use of or inability to use software, even if the
 * University of Notre Dame has been advised of the possibility of
 * such damages.
 */
 
/**
 * @file AmberImproperTorsionType.hpp
 * @version 1.0
 */ 

#ifndef TYPES_AMBERIMPROPERTORSIONTYPE_HPP
#define TYPES_AMBERIMPROPERTORSIONTYPE_HPP

#include "types/PolynomialInversionType.hpp"

namespace oopse {

  /**
   * @class AmberImproperTorsionType AmberImproperTorsionType.hpp "types/AmberImproperTorsionType.hpp"
   * 
   * This impropertorsion potential has the form:
   * 
   *  Vimptors = 0.5*v2*(1-cos(2*(phi-phi0)))
   *
   */
  class AmberImproperTorsionType : public PolynomialInversionType{
    
  public:
    
    AmberImproperTorsionType(RealType v2) :  
      PolynomialInversionType(),  v2_(v2) {
      
      //convert AmberImproper Torsion Type to Polynomial Inversion type
      RealType c0 = v2;
      RealType c2 = -v2;
      
      setCoefficient(0, c0);
      setCoefficient(2, c2);
    }
    
    friend std::ostream& operator <<(std::ostream& os, AmberImproperTorsionType& ott);
    
  private:
    
    RealType v2_;
    
  };
  
  std::ostream& operator <<(std::ostream& os, AmberImproperTorsionType& ott) {
    
    os << "This AmberImproperTorsionType has below form:" << std::endl;
    os << ott.v2_ << "/2*(1-cos(2*(phi-phi0)))" << std::endl;
    return os;
  }
  
  
} //end namespace oopse
#endif //TYPES_OPLSTORSIONTYPE_HPP

