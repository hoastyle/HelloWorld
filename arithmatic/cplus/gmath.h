#ifndef _gmath_h 
#define _gmath_h

/*Export constant need to be extern in both h and c file*/
extern const double PI;

/* The parameter of sin/cos should be radian.
 * Radian = angel * pi / 180.
*/
double sinDegrees(double angle);

double cosDegrees(double angle);

double toDegrees(double radians);

double toRadians(double degrees);

#endif
