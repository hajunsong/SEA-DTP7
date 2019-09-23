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
 * Interface definitions for custom robot
 *
 * History :
 *
 */

#include "crbtype.h"

#ifdef __cplusplus
extern "C" {
#endif



/******************************************************************/
/* for virtual joint assigment */
/******************************************************************/


/*  return :
 *       0 : OK
 *       1 : NOTOK
 */

/* physical joint angle to logical joint angle (Z,T,R, D) */
/**
 * @brief cx_ptol
 * @param[in] pv : actual motor angle
 * @param[out] lv : logical joint angle
 */
extern void cx_ptol(float* pv, float* lv);

/**
 * @brief cx_ltop
 * @param[in] lv
 * @param[out] pv
 */
extern void cx_ltop(float* lv, float* pv);


/******************************************************************/
/* for basic forward/inverse kinematics */
/******************************************************************/


/* uc : array of tran struct matrix : n, o, a, p, l*/
/* CXTMat array */

/**
 * @brief cx_jatouc
 *      foward kinematics :  joint angle to trans matrix
 * @param[in] jtang
 * @param[out] trans  :
 *      pointer to cxmatrix : use casting
 * @param hint
 * @return
 */
extern int cx_jatouc(float* jtang, float* trans, void* hint);


/**
 * @brief cx_uctoja
 *      inverse kinematics : trans matrix to joint angle
 * @param[in] trans : cxmatrix pointer
 * @param[in] oldang : previous angle
 * @param[out] newang : calculated angle
 * @param[in,out] hint
 *     config input
 *      if config cannot set, input config is changed
 * @return
 */
extern int cx_uctoja(float* trans, float* oldang, float* newang, void* hint);

/* calc config using joint angle*/

/**
 * @brief cx_config
 * @param[in] ja
 * @param[out] conf
 * @return
 */
extern int cx_config(float* ja, unsigned char* conf);


/**
 * @brief cx_check_interfere
 * @param ja
 * @return
 *      interenced axis bit return;
 *      BIT00 : axis1 ....
 *      ex) return 6  means (BIT01 + BIT02) = axis2 and axis 3
 */
extern int cx_check_interfere(float* ja);


/******************************************************************/
/* for hybrid linear move */
/******************************************************************/

/**
 * @brief cx_hytoja
 *
 *      using tr and newang[3][4][5], calculate newang[1][2][3] refering the oldang and hit
 *
 * @param[in] tr
 * @param[in] oldang
 *      previous angle
 *
 * @param[in, out] newang
 *      for 6 axis :   newang[3][4][5] is calculated
 *
 * @param[in] environment data
 *      use casting like
 *          CxCustomEnv* pEnv = (CxCustomEnv*)env
 *
 * @return
 */
extern int cx_hytoja(float* tr, float* oldang, float* newang, void* env);


/******************************************************************/
/* for multi-tcp */
/******************************************************************/
extern int cx_sethint(char* name, float value);
extern int cx_gethint(char* name, float *value);

/** MULTI TCP ROBOT */
extern int cx_gettcpsize();

/**
 * @brief cx_jatomtr
 *  joint value (angle or distance) to coordinate value
 * @param[in] ja   : pointer to joint angle
 * @param[out] mtr  : pointer to cxmmatrix
 * @param[in] hint
 * @return
 */
extern int  cx_jatomtr(float* ja, float* mtr, void* hint);
/**
 *  coordinate value to joint value
 */
/**
 * @brief cx_mtrtoja
 * @param[in] mtr  :  *cxmatrix
 * @param[in] oldja  :  flaot[]
 * @param[out] newja   : float []
 * @param[in] mconf   :  CxConstraint*
 * @return
 */
extern int  cx_mtrtoja(float* mtr, float* oldja, float* newja, void* mconf);
/**
 * @brief cx_configmtr
 * @param[in] ja : joint angle
 * @param[out] mconf : CxConstraint*
 * @return
 */
extern int  cx_configmtr(float* ja, void* mconf);


/******************************************************************/
/* for custom parameters */
/******************************************************************/


/**
 * @brief cx_setparam
 *   parameter name must be started with CPARAM_
 * @param name
 * @param value
 * @param nvalue
 * @return
 */
extern int cx_setparam(char* name, float* value, int nvalue);

extern int cx_getparam(char* name, float* value, int nvalue);
extern int cx_getparamcount();
extern char* cx_getparamname(int index);



/******************************************************************/
/* for profile generation */
/******************************************************************/

/**
 * @brief cx_profile_create
 * @param[out] pobj
 *     created custom profile object
 *     object structure must be created client side
 * @return
 *      0 : OK
 *      others : error
 */
extern int cx_profile_create(void** pobj);
/**
 *  input : pobj
 *          amax, dmax : accel data : unit/cycle^2
 *          vmax : max speed data : unit/cycle
 *          dist : distance data : unit
 *          vfactor : override speed factor ( 0.01 ~  1. (100%)
 */
/**
 * @brief cx_profile_generate
 *      pobj is created by cx_profile_create
 *      custom profile is calculated and set result to CxCustomProfileData pio
 *      this is used when planning steps
 * @param[in] pobj
 * @param[in,out] pio CxCustomProfileData
 * @return
 */
extern int cx_profile_generate(void* pobj, CXCustomProfileData* pio);

/**
 * @brief cx_profile_calc_s
 *      pobj is created by cx_profile_create
 *      s parameter for trajectory generation is calculated using custom profile
 *
 * @param[in] pobj
 *      pobj is created by cx_profile_create
 * @param[in] cycle  : current time cycle
 * @param[out] s   : result s-parameter for interpolation
 *          for cycle  0 : s = 1, cycle = end : s = 0
 * @return
 *      0 : not decel states,
 *      DECEL_SEGMENT : decel
 *      END_SEGMENT : all cycles are consumed. the robot is in end position
 */
extern int cx_profile_calc_s(void* pobj, int cycle, float* s);

/**
 * @brief cx_profile_calc_v
 *      calc target speed for given cycle
 * @param pobj
 * @param cycle
 * @param vout
 * @return
 */
extern int cx_profile_calc_v(void* pobj, int cycle, float* vout);


/**
 * @brief cx_profile_calc_a
 *      accel/decel is calculated
 * @param[in] pobj
 * @param[in] sang
 * @param[in] eang
 * @param[out] amax
 * @param[out] dmax
 * @return
 */
extern int cx_profile_calc_a(void* pobj, float* sang, float* eang, float* amax, float* dmax);






#ifdef __cplusplus
}
#endif


#endif
