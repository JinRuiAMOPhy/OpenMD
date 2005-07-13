#ifdef __C
#ifndef __FSWITCHINGFUNCTION
#define __FSWITCHINGFUNCTION

#define NSWITCHTYPES         3
#define LJ_SWITCH            1
#define ELECTROSTATIC_SWITCH 2
#define GROUP_SWITCH         3

#endif
#endif /*__C*/

#ifdef  __FORTRAN90

  INTEGER, PARAMETER:: NSWITCHTYPES         = 3
  INTEGER, PARAMETER:: LJ_SWITCH            = 1
  INTEGER, PARAMETER:: ELECTROSTATIC_SWITCH = 2
  INTEGER, PARAMETER:: GROUP_SWITCH         = 3

#endif
