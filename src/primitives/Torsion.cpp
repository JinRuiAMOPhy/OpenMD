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
 
#include "config.h"
#include <cmath>

#include "primitives/Torsion.hpp"
#include "utils/Constants.hpp"

namespace OpenMD {

  Torsion::Torsion(Atom *atom1, Atom *atom2, Atom *atom3, Atom *atom4,
		   TorsionType *tt) : ShortRangeInteraction(),
                                      torsionType_(tt) {
    atoms_.resize(4);
    atoms_[0] = atom1;
    atoms_[1] = atom2;
    atoms_[2] = atom3;
    atoms_[3] = atom4;
  }

  void Torsion::calcForce(RealType& angle, bool doParticlePot) {

    Vector3d pos1 = atoms_[0]->getPos();
    Vector3d pos2 = atoms_[1]->getPos();
    Vector3d pos3 = atoms_[2]->getPos();
    Vector3d pos4 = atoms_[3]->getPos();

    Vector3d r21 = pos1 - pos2;
    snapshotMan_->getCurrentSnapshot()->wrapVector(r21);
    Vector3d r32 = pos2 - pos3;
    snapshotMan_->getCurrentSnapshot()->wrapVector(r32);
    Vector3d r43 = pos3 - pos4;
    snapshotMan_->getCurrentSnapshot()->wrapVector(r43);

    //  Calculate the cross products and distances
    Vector3d A = cross(r21, r32);
    RealType rA = A.length();
    Vector3d B = cross(r32, r43);
    RealType rB = B.length();

    /* 
       If either of the two cross product vectors is tiny, that means
       the three atoms involved are colinear, and the torsion angle is
       going to be undefined.  The easiest check for this problem is
       to use the product of the two lengths.
    */
    if (rA * rB < OpenMD::epsilon) return;
    
    A.normalize();
    B.normalize();  
    
    //  Calculate the sin and cos
    RealType cos_phi = dot(A, B) ;
    if (cos_phi > 1.0) cos_phi = 1.0;
    if (cos_phi < -1.0) cos_phi = -1.0; 
    
    RealType dVdcosPhi;
    torsionType_->calcForce(cos_phi, potential_, dVdcosPhi);
    Vector3d f1 ;
    Vector3d f2 ;
    Vector3d f3 ;
    
    Vector3d dcosdA = (cos_phi * A - B) /rA;
    Vector3d dcosdB = (cos_phi * B - A) /rB;
    
    f1 = dVdcosPhi * cross(r32, dcosdA);
    f2 = dVdcosPhi * ( cross(r43, dcosdB) - cross(r21, dcosdA));
    f3 = dVdcosPhi * cross(dcosdB, r32);
    
    atoms_[0]->addFrc(f1);
    atoms_[1]->addFrc(f2 - f1);
    atoms_[2]->addFrc(f3 - f2);
    atoms_[3]->addFrc(-f3);
    
    if (doParticlePot) {
      atoms_[0]->addParticlePot(potential_);
      atoms_[1]->addParticlePot(potential_);
      atoms_[2]->addParticlePot(potential_);
      atoms_[3]->addParticlePot(potential_);
    }
    
    angle = acos(cos_phi) /Constants::PI * 180.0;    
  }  
}
