#ifndef CUIFUNC_H
#define CUIFUNC_H

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif



#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

#ifndef DTOR
#define DTOR    (M_PI/180.)
#endif
#ifndef RTOD
#define RTOD    (180./M_PI)
#endif

/* error code */
#define CUI_ERR_OK              0       /* no error */
#define CUI_ERR_INVALARG 		-1321   /* invalid argument value  */


/* variant type */
#define CUI_VAR_FLOAT   0
#define CUI_VAR_STRING  1
#define CUI_VAR_JOINT   2
#define CUI_VAR_TRANS   3

typedef struct
{
    float   x, y, z;
} cui_vector;

typedef struct
{
    cui_vector  n;
    cui_vector  o;
    cui_vector  a;
    cui_vector  p;
} cui_trans;

struct cui_variant_t
{
    char type;          // CUI_VAR_
    char is_set;        // after return the value is saved
    char is_pointer;    // given value is pointer
    char reserved;
    int  strsize;       // string buffer size in case of CUI_VAR_STRING & is_pointer
    union value_t{
        float       joint[40];
        char        str[256];
        float       real;
        long*       ptr;            // data pointer
        cui_trans   trans;
    } value;

    union value_t retval;           // used when return string variable
};

typedef struct cui_variant_t    cui_variant;

typedef long    (*CUI_UFUNC)(int index, cui_variant* vals, int nvals);

#ifdef __cplusplus
}
#endif



#endif // CUIFUNC_H

