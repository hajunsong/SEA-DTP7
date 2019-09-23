#ifndef CNERROR_H
#define CNERROR_H


/*
 *  CN_ERR  : Network Error Codes
 */
#define CN_ERR_NONE                  0   /* success */
#define CN_ERR_RETURN_ERROR         -1  /* retrun -1 */
#define CN_ERR_INVALID_COMMAND      -2
#define CN_ERR_NOT_IMPLEMENTED      -3
#define CN_ERR_NOT_FOUND            -4   /* reqeust data object(pgm, variale...) is not found */
#define CN_ERR_FAILED_REQUEST       -5
#define CN_ERR_NOT_ALLOWED_USER     -6   /* login faied */
#define CN_ERR_ACCESS_RIGHT         -7   /* not locked client */
#define CN_ERR_INVALID_ARG          -8   /* invalid arg */
#define CN_ERR_NOT_FOUND_NAME       -9
#define CN_ERR_WRONG_DATA           -10   /* inupt data wrong */
#define CN_ERR_FAILED_TRANSFORM     -11  /*  */
#define CN_ERR_NOT_EXIST            -12  /* name, data not found */
#define CN_ERR_FAILED_MAKING        -13  /*  */
#define CN_ERR_FAILED_READING       -14  /*  */
#define CN_ERR_FAILED_WRITING       -15  /*  */
#define CN_ERR_FAILED_RUNNING       -16  /* The macro Program can't run */
#define CN_ERR_NOT_EXIST_ID         -17  /* The macro program doesn't exist */
#define CN_ERR_FAILED_SAVING        -18  /* They could not save */
#define CN_ERR_FAILED_LOADING       -19  /* They could not load */
#define CN_ERR_FAILED_MOVING        -20  /* motors could't move */
#define CN_ERR_FAILED_EDITING       -21  /* macros could't edit */
#define CN_ERR_FAILED_ABORTING      -22  /* The macro Program can't abort */
#define CN_ERR_FAILED_HOLDING       -23  /* The macro Program can't hold */
#define CN_ERR_FAILED_SETTING       -24  /*  */
#define CN_ERR_FAILED_GETTING       -25  /*  */
#define CN_ERR_FAILED_DELETING      -26  /*  */
#define CN_ERR_FAILED_CLEANING      -27  /*  */
#define CN_ERR_FAILED_IMPORTING     -28  /*  */
#define CN_ERR_FAILED_EXPORTING     -29  /*  */
#define CN_ERR_FAILED_COPY          -30  /*  */
#define CN_ERR_EXCEEDED_DATA        -31   /*  */
#define CN_ERR_FAILED_HOMING        -32   /*  */
#define CN_ERR_FAILED_RESETTING     -33  /*  */
#define CN_ERR_NOT_EXIST_VAR        -34  /* The variable doesn't exist */
#define CN_ERR_NOT_ONLINE_STATUS    -35
#define CN_ERR_NOT_OP_STATUS        -36
#define CN_ERR_NOT_EXIST_LICENSE    -37  /* 라이센스가 없을 때 */
#define CN_ERR_DISCONNECTED_NETWORK -38  /* 통신이 연결되지 않았거나 끊어졌을 때 */
#define CN_ERR_NOT_EXIST_TYPE       -39  /* not found type */
#define CN_ERR_NOT_READY_STATUS     -40  /* not ready status */
#define CN_ERR_FAILED_ANALYZING     -41  /*  */
#define CN_ERR_NOT_EXIST_TASK       -42  /* The variable doesn't exist */
#define CN_ERR_FAILED_SOMETHING     -43  /* 여러 작업 중 한 가지를 실패함. */

#endif // CNERROR_H

