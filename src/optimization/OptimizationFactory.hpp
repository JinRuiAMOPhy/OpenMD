/*
 * Copyright (c) 2004-2020 The University of Notre Dame. All Rights Reserved.
 *
 * The University of Notre Dame grants you ("Licensee") a
 * non-exclusive, royalty free, license to use, modify and
 * redistribute this software in source and binary code form, provided
 * that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
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
 *
 * SUPPORT OPEN SCIENCE!  If you use OpenMD or its source code in your
 * research, please cite the appropriate papers when you publish your
 * work.  Good starting points are:
 *
 * [1] Meineke, et al., J. Comp. Chem. 26, 252-271 (2005).
 * [2] Fennell & Gezelter, J. Chem. Phys. 124, 234104 (2006).
 * [3] Sun, Lin & Gezelter, J. Chem. Phys. 128, 234107 (2008).
 * [4] Vardeman, Stocker & Gezelter, J. Chem. Theory Comput. 7, 834 (2011).
 * [5] Kuang & Gezelter, Mol. Phys., 110, 691-701 (2012).
 * [6] Lamichhane, Gezelter & Newman, J. Chem. Phys. 141, 134109 (2014).
 * [7] Lamichhane, Newman & Gezelter, J. Chem. Phys. 141, 134110 (2014).
 * [8] Bhattarai, Newman & Gezelter, Phys. Rev. B 99, 094106 (2019).
 */
 
#ifndef OPTIMIZATION_OPTIMIZATIONFACTORY_HPP
#define OPTIMIZATION_OPTIMIZATIONFACTORY_HPP
#include <cassert>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "optimization/Method.hpp"

using namespace QuantLib;
namespace OpenMD {

  //forward declaration
  class OptimizationCreator;
  class SimInfo;
  /**
   * @class OptimizationFactory
   * Factory pattern and Singleton Pattern are used to define an interface for creating an Optimization.
   */
  class OptimizationFactory {
  public:
                
    typedef std::map<std::string, OptimizationCreator*> CreatorMapType;
    typedef std::vector<std::string> IdentVectorType;
    typedef std::vector<std::string>::iterator IdentVectorIterator;

    ~OptimizationFactory();
                    
    /**
     * Returns an instance of Optimization factory
     * @return an instance of Optimization factory
     */        
    static OptimizationFactory* getInstance() {

      if (instance_ == NULL) {
	instance_ = new OptimizationFactory();
      }
      return instance_;
            
    }

    /**
     * Registers a creator with a type identifier
     * @return true if registration is succeed, otherwise return false
     * @param creator the object responsible to create the concrete object 
     */
    bool registerOptimization(OptimizationCreator* creator);

    /**
     * Unregisters the creator for the given type identifier. If the type identifier 
     * was previously registered, the function returns true.
     * @return truethe type identifier was previously registered and the creator is removed,
     * otherwise return false
     * @param id the identification of the concrete object
     */
    bool unregisterOptimization(const std::string& id);
    /**
     * Looks up the type identifier in the internal map. If it is found, it invokes the
     * corresponding creator for the type identifier and returns its result. 
     * @return a pointer of the concrete object, return NULL if no creator is registed for 
     * creating this concrete object
     * @param id the identification of the concrete object
     * @param info pointer to the SimInfo object
     */
    QuantLib::OptimizationMethod* createOptimization(const std::string& id, SimInfo* info);

    /** 
     *  Returns all of the registed  type identifiers
     * @return all of the registed  type identifiers
     */
    IdentVectorType getIdents();
        
  private:
    OptimizationFactory() {}
        
    static OptimizationFactory* instance_;
    CreatorMapType creatorMap_;
  };

  /** write out all of the type identifiers to an output stream */
  std::ostream& operator <<(std::ostream& o, OptimizationFactory& factory);

}//namespace OpenMD
#endif //OPTIMIZATIONS_OPTIMIZATIONFACTORY_HPP

