/*
 * error_handler.h
 *
 * Created: 11/11/2022 21:07:36
 * Author: Mohamed Khalil
 */ 


#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

/************************************************************************/
/* Types                                      */
/************************************************************************/

/* enum defines the different types of errors returning from the functions of the project */
typedef enum _ERROR_ID
{
  ERROR_ID_NO_ERROR = 0,
  
  ERROR_ID_INVALID_INPUT_ARGUMENT,
  
  ERROR_ID_OUT_OF_MEMORY,
  
  ERROR_ID_INSUFFECIENT_RESOURCES,
  
  ERROR_ID_HW_ERROR
  
} T_ERROR_ID_E;

#endif /* ERROR_HANDLER_H_ */
