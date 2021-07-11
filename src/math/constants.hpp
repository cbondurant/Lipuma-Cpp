#ifdef LIPUMA_USE_CUSTOM_CONSTANTS
#undef M_PI
#undef M_PIl
#endif

#ifndef M_PI
// Source of pi digits: http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
// Using the first 64 digits of pi, because theres no way a 64 bit float could store *more* precision than the 64 digit decimal form.
#define M_PI 3.141592653589793238462643383279502884197169399375f
#endif

#ifndef M_PIl
#define M_PIl 3.141592653589793238462643383279502884197169399375l
#endif