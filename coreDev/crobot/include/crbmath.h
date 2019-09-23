#ifndef __DEF_CRBMATH_H__
#define __DEF_CRBMATH_H__	1

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

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif


#include "crbtype.h"


extern int crb_round(float x);

/* trigonometric uitility functions */

/**
 * @brief cx_acos
 * @param x
 * @return
 *      x > 1 = 0,  x < -1 : -pi, otheres : acos(x)
 */
extern  float crb_acos(float x);

/**
 * @brief cx_asin
 * @param x
 * @return
 *      x > 1 = pi/2,  x < - 1 : -pi/2, others : asin(x)
 */
extern float crb_asin(float x);

/*  */
/**
 * @brief calc_cos_angle
 *    angle between a, b of triangle(a, b, l)
 *
 * @param a
 * @param b
 * @param l
 * @return
 *
 */
extern float crb_calc_cos_angle(float a, float b, float l);


/* vector */

extern void crb_vec_set(cxvector* a, float x, float y, float z);
extern void crb_vec_sub(cxvector* a, cxvector* b, cxvector* c);
extern void crb_vec_add(cxvector* a, cxvector* b, cxvector* c);
extern void crb_vec_scl(cxvector* a, float b, cxvector* c);

extern float crb_vec_len(cxvector *a);
extern int crb_vec_normalize(cxvector* a);
extern float veclen(cxvector *a);
extern float vecdot(cxvector* a, cxvector* b);

extern float crb_vec_dot(cxvector* a, cxvector* b);
/**
 * @brief veccross
 *  c = a * b
 * @param a
 * @param b
 * @param[out] c
 */
extern void crb_vec_cross(cxvector* a, cxvector* b, cxvector* c);

/* matrix */
/*  c = a * b */
extern void crb_mat_multiply(cxmatrix* a, cxmatrix* b,cxmatrix* c);
extern void crb_mat_init(cxmatrix* mat);
extern void crb_mat_inverse(cxmatrix* mat, cxmatrix* invmat);



/* helper function for angle selection */

/**
 * @brief crb_check_range
 *      if given ang is not between minang and maxang,
 *       ang is shifted to the next phase adding or subtracting  2*PI
 * @param[in,out] ang
 * @param[in] minang
 * @param[in] maxang
 */
extern void crb_check_range(float* ang, float minang, float maxang);
/**
 * @brief select_angle
 *      select the angle which is minimum difference among given newang, newang + 2*pi, newang - 2*pi
 *
 * @param[in] prevang
 * @param[in] newang
 * @return
 *      reselected angle
 */
extern float crb_select_angle(float prevang, float newang);

/**
 * @brief crb_adjang
 *      if (a - b) is greater than pi then a is shifted to be less than pi
 * @param[in,out] a : input angle
 * @param[in] b : reference angle
 */
extern void crb_adjang(float* a, float* b);

/**
 * @brief select_nearest_angle
 *      the minimum difference angle to oldang is returned among the given newangle list
 *
 *      ex)
 *      float newangs[3] = { ang, ang - 2pi, ang + 2pi }
 *
 *      float ans = select_nearest_angle(oldang, newangs, 3);
 *
 * @param[in] oldang
 * @param[in] newang   candidates for new angle
 * @param[in] n_newang  # of candidates
 * @return
 *      return selected angle
 */
float crb_select_nearest_angle(float oldang, float* newang, int n_newang);




#ifdef __cplusplus
}
#endif


#endif
