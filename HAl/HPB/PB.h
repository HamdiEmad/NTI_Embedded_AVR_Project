//PB.h

#ifndef HAL_HPB_PB_H_
#define HAL_HPB_PB_H_

#define PB_PRESSED      0
#define PB_NOT_PRESSED  1

#define PB_1   0
#define PB_2   1
#define PB_3   2
#define PB_4   3
#define PB_5   4

#define PB_NUM 5

void HPB_voidInit   (void) ;
u8   HPB_u8ReadPin  (u8 A_u8pbId) ;

#endif /* HAL_HPB_PB_H_ */
