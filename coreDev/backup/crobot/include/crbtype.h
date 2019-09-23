#ifndef __DEF_CRBTYPE_H__
#define __DEF_CRBTYPE_H__	1

/*************************************************************************
 *
 * COREROBOT CONFIDENTIAL
 *
 *  [2015] ~ CORE ROBOT,  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Core Robot and its suppliers,if any.
 * The intellectual and technical concepts contained
 * herein are proprietary to Core Robot
 *
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Core Robot.
 *
 *
 */

/*
 * Type definitions for custom robot
 *
 * History :
 *
 */

#ifdef __cplusplus
extern "C" {
#endif



#define OUT_OF_RANGE    -1357

#define DBL_PI  (M_PI * 2.)
#define HALF_PI  (M_PI_2)

#define DTOR    (M_PI/180.)
#define RTOD    (180./M_PI)

#define LEFTY  0X01         /* robot configuration */
#define BELOW  0X02         /* robot configuration */
#define UWRIST 0X04         /* robot configuration */
#define DBLANGLE  0x08      /* double angle : 180 ~ 360 */


#define CX_MAX_TCP  4       /* Max tool center point = Max. # of Hands */
#define CX_MAX_HINT 10

typedef struct tagCxConfigEx {
    long    cfx;                /* old 6axis robot config : LEFTY/BELOW/UWRIST */
    char    angle[8];           /* angle config : depends on robot type*/
} CxConfigEx;

/**
 * @brief The t_MAConstraint struct
 *      Constraint for Multi-arm
 */
typedef struct tagCxConstraint {
    char    master_arm[CX_MAX_TCP];             /* master arm order */
    CxConfigEx    config[CX_MAX_TCP];             /* config for each arm */
    float    hint[CX_MAX_HINT];                  /* custom hint */
} CxConstraint;

/**
 * @brief cxvector
 *      Simple vector structure
 */
typedef struct tagcxvector {
    float   x, y, z;
} cxvector;

/**
 * @brief cxmatrix
 *      Simple trans matrix structure
 */
typedef struct tagcxtmatrix {
    cxvector    n, o, a, p;
    float       l;
} cxmatrix;

/**
 * @brief cxmmatrix
 *      multiple trans matrix for Multi TCP Robot
 */
typedef struct tagcxmmatrix {
    cxmatrix    trans[CX_MAX_TCP];  /* each trans */
    float       ext[6];             /* external axis */
} cxmmatrix;


/**
 * @brief CxCustomEnv
 *      custrom robot environment
 */
typedef struct tagCustomEnv {
    int             cbsize;             /* size of structure for version checking */
    CxConstraint    constraint;         /* pose constratint */
    cxmatrix        tool[CX_MAX_TCP];   /* tool */
    void*           userdata;           /* given by user */

} CxCustomEnv;


/* custom profile */
/* calc_s return code */
#define NORMAL_SEGMENT  0   /* accel or constant */
#define END_SEGMENT     1	/* profile done */
#define DECEL_SEGMENT	2   /* on decelleration */

#define MAX_CUSTOM_AXIS 20

typedef struct tagCustomProfileData {
    int     cbsize;
    int     motiontype;     /* 0 : joint others : cartesian */
    int     naxis;          /* # of axis */
    float   amax[MAX_CUSTOM_AXIS+1];
    float   dmax[MAX_CUSTOM_AXIS+1];
    float   vmax[MAX_CUSTOM_AXIS+1];
    float   dist[MAX_CUSTOM_AXIS+1];
    float   vfactor;

    /* output */
    int     tcycles;     /* total cycles */
    int     dcycles;     /* decel cycles */
} CXCustomProfileData;


struct CXCustomCmdInputData {
    /* input */
    float*  curjtang; // joint angle
    float*  curuc; // user coordinate
    short*  curtor;

    long*   inc_enc; // incremental encoder;
    long*   abs_enc; // absolute encoder

    float   override_speed;
    int     ctl_mode;

    long*   user_input1;
    long*   user_input2;
    long*   user_input3;

};

struct CXCustomCmdOutputData {
    /* input */
    float*  cmdjtang; // command torque
    int*    cmdtor; // command torque
    int*    collision_detect; // collision result

    long*   user_output1;
    long*   user_output2;
    long*   user_output3;

    float*  user_logging1;
    float*  user_logging2;
    float*  user_logging3;
};

#ifdef __cplusplus
}
#endif


#endif
