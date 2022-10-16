#include "Helpers_func.h"
#include "Defines.h"

double RFresnel(double n1, double n2, double ca1, double* ca2_Ptr)
{
	double r;

	if (n1 == n2) 
	{ /** matched boundary. **/
		*ca2_Ptr = ca1;
		r = 0.0;
	}
	else if (ca1 > COS0) 
	{ /** normal incident. **/
		*ca2_Ptr = ca1;
		r = (n2 - n1) / (n2 + n1);
		r *= r;
	}
	else if (ca1 < COS90) 
	{ /** very slant. **/
		*ca2_Ptr = 0.0;
		r = 1.0;
	}
	else
	{ /** general. **/
		double sa1, sa2;
		/* sine of the incident and transmission angles. */
		double ca2;

		sa1 = sqrt(1 - ca1 * ca1);
		sa2 = n1 * sa1 / n2;
		if (sa2 >= 1.0) {
			/* double check for total internal reflection. */
			*ca2_Ptr = 0.0;
			r = 1.0;

		}
		else
		{
			double cap, cam; /* cosines of the sum ap or */
			/* difference am of the two */
				/* angles. ap = a1+a2 */
				/* am = a1 - a2. */
			double sap, sam; /* sines. */

			*ca2_Ptr = ca2 = sqrt(1 - sa2 * sa2);

			cap = ca1 * ca2 - sa1 * sa2; /* c+ = cc - ss. */
			cam = ca1 * ca2 + sa1 * sa2; /* c- = cc + ss. */
			sap = sa1 * ca2 + ca1 * sa2; /* s+ = sc + cs. */
			sam = sa1 * ca2 - ca1 * sa2; /* s- = sc - cs. */
			r = 0.5 * sam * sam * (cam * cam + cap * cap) / (sap * sap * cam * cam);
			/* rearranged for speed. */

		}
	}

	return r;
}