#ifndef CNTYPE_H
#define CNTYPE_H

#include <string.h>

#define CN_MAX_JOINT    32
#define CN_MAX_TRANS    32
#define CN_MAX_USER     32

/* 1MB */
#define CN_MAX_DATA_LENGTH      1048576
#define CN_MAX_STRING_LENGTH    256

#ifndef NULL
#define NULL    0
#endif

typedef char                cn_char;
typedef unsigned char       cn_ui8;
typedef unsigned short      cn_ui16;
typedef unsigned short int	cn_uint16;
typedef unsigned int        cn_ui32;
typedef char                cn_i8;
typedef short               cn_i16;
typedef int                 cn_i32;
typedef char*               cn_string; //[CN_MAX_STRING_LENGTH];

/**
 * @fn cn_safestr
 *   safe string :
 *      first 2 bytes :
 */
typedef float           cn_f32;
typedef double          cn_f64;

/**
 * @fn The CNOBJ_TYPE enum
 */
enum cn_vartype
{
    CNVAR_NONE = -1,
    CNVAR_STRING = 0,   /**< type value is 0, then the value is string */
    CNVAR_UINT8 = 1,
    CNVAR_UINT16,
    CNVAR_UINT32,
    CNVAR_INT8,
    CNVAR_INT16,
    CNVAR_INT32,
    CNVAR_FLOAT,
    CNVAR_DOUBLE,
    CNVAR_JOINT,
    CNVAR_TMAT,
    CNVAR_VECTOR,
    CNVAR_TRANS,
    CNVAR_SAFESTR,
    CNVAR_ARYFLOAT,
    CNVAR_ARYINT32,
    CNVAR_ARYUINT32,
    CNVAR_ARYSTRING,
    CNVAR_DATE,
};

struct cn_safestr
{
    int length;
    char*   data;
};

struct cn_vec3
{
    float   x, y, z;

    void set(float x1 = 0.f, float y1 = 0.f, float z1 = 0.f)
    {
        this->x = x1;
        this->y = y1;
        this->z = z1;
    }

    void operator = (cn_vec3 vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }
};

struct cn_joint
{
    int count;
    float   joint[CN_MAX_JOINT];
};

struct cn_trans
{
    float   n[3];
    float   o[3];
    float   a[3];
    float   p[3];

    float   eu[3];
    float   ext[6];

    void setEuler(float *eulerAngle, bool track = false, int trackAxis = 1)
    {
        this->identity();

        this->p[0] = eulerAngle[0];
        this->p[1] = eulerAngle[1];
        this->p[2] = eulerAngle[2];
        this->eu[0] = eulerAngle[3];
        this->eu[1] = eulerAngle[4];
        this->eu[2] = eulerAngle[5];

        if(track == true)
        {
            if(trackAxis > 6) trackAxis = 6;

            for(int i = 0; i < trackAxis; i++)
                this->ext[i] = eulerAngle[6+i];
        }
    }

    void getEuler(float *eulerAngle, bool track = false, int trackAxis = 1)
    {
        eulerAngle[0] = this->p[0];
        eulerAngle[1] = this->p[1];
        eulerAngle[2] = this->p[2];
        eulerAngle[3] = this->eu[0];
        eulerAngle[4] = this->eu[1];
        eulerAngle[5] = this->eu[2];

        if(track == true)
        {
            if(trackAxis > 6) trackAxis = 6;

            for(int i = 0; i < trackAxis; i++)
                eulerAngle[6+i] = this->ext[i];
        }
    }


    void setVec(float x, float y, float z, float *ret)
    {
        ret[0] = x;
        ret[1] = y;
        ret[2] = z;
    }

    void identity()
    {
        this->setVec(1.f, 0.f, 0.f, this->n);
        this->setVec(0.f, 1.f, 0.f, this->o);
        this->setVec(0.f, 0.f, 1.f, this->a);
        this->setVec(0.f, 0.f, 0.f, this->p);
        memset(this->eu, 0, sizeof(this->eu));
        memset(this->ext, 0, sizeof(this->ext));
    }

};

struct cn_trans2
{
    cn_vec3 n, o, a, p;
    float ext;

    void identity()
    {
        this->n.set(1.f, 0.f, 0.f);
        this->o.set(0.f, 1.f, 0.f);
        this->a.set(0.f, 0.f, 1.f);
        this->p.set();
        ext = 0;
    }

    void operator = (cn_trans2 trans)
    {
        this->n = trans.n;
        this->o = trans.o;
        this->a = trans.a;
        this->p = trans.p;
    }
};


#define LEFTY  0X01		/* cfx robot configuration */
#define BELOW  0X02		/* cfx robot configuration */
#define UWRIST 0X04		/* cfx robot configuration */

#define CN_MAX_TCP  4
#define CN_MAX_HINT 10

struct cn_conf{
    unsigned char   cfx;                        // configuration
    char            angle[8];                   /* angle config : depends on robot type*/

    void init()
    {
        cfx = 0x0;
        memset(angle, 0, sizeof(angle));
    }
};

struct cn_mconf
{
    unsigned char   master_arm[CN_MAX_TCP];     // maser-slave order
    cn_conf         config[CN_MAX_TCP];         // robot의 형상.
    unsigned char   hint[CN_MAX_HINT];          // angle hint

    void init()
    {
        for(int i = 0; i < CN_MAX_TCP; i++)
        {
            config[i].init();
            master_arm[i] = i;
        }

        for(int i = 0; i < CN_MAX_HINT; i++)
            hint[i] = 0;

    }

    void clear()
    {
        for(int i = 0; i < CN_MAX_TCP; i++)
        {
            config[i].init();
            master_arm[i] = 0;
        }

        for(int i = 0; i < CN_MAX_HINT; i++)
            hint[i] = 0;
    }
};

struct cn_mtrans {
    cn_trans   trans[CN_MAX_TCP];              /* each trans */
    float       ext[6];                         /* external axis */

    void identity()
    {
        for(int i = 0; i < CN_MAX_TCP; i++)
        {
            trans[i].identity();
        }

        memset(ext, 0, sizeof(ext));
    }
};


struct cn_location
{
    unsigned short ntrans;
    unsigned short next;
    cn_trans    trans[2];
    float   ext[6];
};

struct cn_usercoord
{
    int count;
    float   uc[32];
};

struct cn_date
{
    unsigned short  year;
    unsigned char   month;
    unsigned char   day;
};


#define CN_MAX_CHARS    256
struct cn_variant {
    cn_vartype type;
    union {
        cn_ui8  ui8;
        cn_ui16 ui16;
        cn_ui32 ui32;
        cn_i8   i8;
        cn_i16  i16;
        cn_i32  i32;
        cn_f32  f32;
        cn_f64  f64;
        cn_char   str[CN_MAX_CHARS];    /**< if type is CNOBJ_STRING and str is not null, careful about alloc/free */
        cn_joint    joint;
        cn_trans    trans;
        cn_location location;
        cn_usercoord uc;
        cn_safestr  sstr;
        cn_date     date;
    } val;
};



/* robot variable type */
#define CN_ROBOT_VARIABLE_JOINT     1
#define CN_ROBOT_VARIABLE_TRANS     2
#define CN_ROBOT_VARIABLE_NUMBER    3
#define CN_ROBOT_VARIABLE_STRING    4


#endif // CNTYPE_H

