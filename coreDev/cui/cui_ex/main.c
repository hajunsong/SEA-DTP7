/*
 *  CUSTOMUI
 *	custom ui example project
 *
 */
#include <stdio.h>


////////////////////// custom ui test ///////////////////////////////////////////////////
///
///
///
#ifdef __cplusplus
extern "C" {
#endif

/* get widget pointer */
extern void* createTestWidget();

#ifdef __cplusplus
}
#endif


static void*    s_widget_ptr;

void* cui_get_widget()
{
    if(s_widget_ptr == NULL)
        s_widget_ptr = (void*)createTestWidget();

    return s_widget_ptr;
}


