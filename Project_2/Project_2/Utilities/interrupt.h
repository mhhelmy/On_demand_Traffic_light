/*
 * interrupts.h
 *
 * Created: 07/11/2022 22:15:46
 *  Author: Mohamed Khalil
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

#define EXT_INT_0 __vector_1
#define EXT_INT_1 __vector_2
#define EXT_INT_2 __vector_3

# define sei()  __asm__ __volatile__ ("sei" ::: "memory")
# define cli()  __asm__ __volatile__ ("cli" ::: "memory")

#  define ISR(vector) \
void vector (void) __attribute__ ((signal,used)); \
void vector (void)



#endif /* INTERRUPTS_H_ */