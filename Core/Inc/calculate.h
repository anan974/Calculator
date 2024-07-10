/*
 * calculate.h
 *
 *  Created on: May 13, 2024
 *      Author: THANH AN
 */

#ifndef INC_CALCULATE_H_
#define INC_CALCULATE_H_

#include "main.h"
#include "i2c-lcd.h"
/*=================================================================================*/
/*  File        : CALCULATOR Program.c                                             */
/*  Description : This Program file includes CALCULATOR program                    */
/*  Author      : Tarek Ahmed Abd El Wahab. Embedded SW Engineer                   */
/*  Date        : 19/10/2023                                                       */
/*  Linkedin    : https://www.linkedin.com/in/tarek-el-shafei-647698205/           */
/*  Git account : https://github.com/Tarek1482000?tab=repositories                 */
/*  mail        : tarekahmed0128@gmil.com                                          */
/*=================================================================================*/

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

typedef float f32;
typedef  uint8_t u8;
extern u8 keyPressed;


void Calculator_Init(void);
void Calculator_Start(void);
#endif /* INC_CALCULATE_H_ */
