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
 * @file DumpReader.hpp 
 * @author tlin 
 * @date 11/15/2004 
 * @time 09:25am 
 * @version 2.0 
 */ 
 
#ifndef IO_DUMPREADER_HPP 
#define IO_DUMPREADER_HPP 
 
#include <cstdio> 
#include <string> 
#include "brains/SimInfo.hpp" 
#include "primitives/StuntDouble.hpp" 
namespace oopse { 
 
  /** 
   * @class DumpReader DumpReader.hpp "io/DumpReader.hpp" 
   * @todo get rid of more junk code from DumpReader 
   */ 
  class DumpReader { 
  public: 
 
    DumpReader(SimInfo* info, const std::string & filename); 
    //DumpReader(SimInfo * info, istream & is); 
 
    ~DumpReader(); 
 
    /** Returns the number of frames in the dump file*/ 
    int getNFrames(); 
 
         
    void readFrame(int whichFrame); 
 
  private: 
 
    void scanFile(); 
 
    void readSet(int whichFrame); 
 
    void parseDumpLine(char *line, StuntDouble* integrableObject); 
 
    void parseCommentLine(char* line, Snapshot* s); 
 
 
#ifdef IS_MPI 
 
    void anonymousNodeDie(void); 
    void nodeZeroError(void); 
 
#endif                 
    // the maximum length of a typical MPI package is 15k 
    const static int maxBufferSize = 8192; 
         
    SimInfo* info_; 
 
    std::string filename_; 
    bool isScanned_; 
 
    int nframes_; 
 
    std::istream* inFile_; 
     
    std::vector<std::streampos> framePos_; 
 
    bool needPos_; 
    bool needVel_; 
    bool needQuaternion_; 
    bool needAngMom_; 
  }; 
 
}      //end namespace oopse 
 
#endif //IO_DUMPREADER_HPP 
