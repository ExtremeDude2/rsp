#include "vu.h"

static void VMULU(int vd, int vs, int vt, int e)
{
    register int i;

    for (i = 0; i < 8; i++)
        VACC[i].DW = (VR[vs][i]*VR_T(i) << 1) + 0x8000;
    for (i = 0; i < 8; i++) /* Zero-clamp bits 31..16 of ACC to dest. VR. */
    {
        VR_D(i)  = VACC[i].s[MD];   /* VD  = ACC[31..16] */
        VR_D(i) |= VR_D(i) >> 15;   /* VD |= -(result == 0x80008000) */
        VR_D(i) &= ~VACC[i].HW[03]; /* VD  = (ACC < 0) ? 0 : ACC[31..16]; */
    }
    return;
}
