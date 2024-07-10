/*
 * calculate.c
 *
 *  Created on: May 13, 2024
 *      Author: THANH AN
 */


#include "calculate.h"

u8 num1_counter=0,  //number1 counter store digits
num2_counter=0,  //number2 counter store digits
operator=0;      //Store operation type

f32 number1[10]={-1}, //Array contain characters of  Number1
	number2[10]={-1}, //Array contain characters of  Number1
	result=0,        //Calculation Result
	num1 = 0,  // first number
	num2 =0 ; //second number

bool num1_flag = true, num2_flag = true, error_flag = false;

int col=0,row=0; //lcd screen

//initilize the program
void Calculator_Init(void)
{
	lcd_init();
	lcd_put_cur(0, 2);
	lcd_send_string("CALCULATOR");
	lcd_put_cur(1, 0);
	lcd_send_string("PRESS C TO START THE PROGRAM!");
	HAL_Delay(200);
	while (keyPressed != 'c') {
		HAL_Delay(200);
	}
	lcd_clear();
	keyPressed = 0;
}

//reset all variables
void Calculator_Reset(void) {
	lcd_clear();
	keyPressed=0;
	num1_flag = true, num2_flag = true, error_flag = false;
	num1_counter=0,num2_counter=0;
	num1=0,num2=0;
	col =0, row =0;
	result=0;
	operator=0;
	for (int i=0;i<10;i++) {
		number1[i]=-1;
		number2[i]=-1;
	}
}
/*
 * Change from characters to number
 */
float Convert(f32 number_array[], u8 counter, bool flag) {
	float num = 0;
	for (u8 i = 0; i < counter; i++) {
		num = num * 10 + number_array[i];
	}
	if (flag == false) num*=-1;
	return num;
}

/*
 * Description :
 * Get the first number and operation of calculation
 */
void First_NUM(void)
{
	int done = 0;
	int subtract_count = 0;
		while(1)
		{
			switch (keyPressed){
			case 'c':
				Calculator_Reset();
				break;
			case '-':
				if (number1[0] == -1) {
					lcd_put_cur(row,col);
					lcd_send_data(keyPressed);
					keyPressed = 0;
					subtract_count++;
					col++;
					if (subtract_count%2==0) num1_flag=true;
					else num1_flag=false;
					break;
				}
			case '+':
				if (number1[0] == -1) {
					lcd_put_cur(row,col);
					lcd_send_data(keyPressed);
					keyPressed = 0;
					col++;
					break;
				}
			case '*':
			case '/':
				operator=keyPressed;
				lcd_put_cur(row,col);
				lcd_send_data(operator);
				keyPressed = 0;
				col++;
				if (keyPressed=='*' && number1[0]==-1 || keyPressed=='/' && number1[0] == -1) {
					error_flag=true;
				}
				done = 1;
				break;
			case '=':
				lcd_put_cur(row, col);
				lcd_send_data(keyPressed);
				float num = Convert(number1, num1_counter, num1_flag);
				lcd_put_cur(1, 0);
				lcd_interger_string(num);
				break;
			case 0:
				break;
			default:
				number1[num1_counter]=keyPressed-'0';
				num1_counter++;
				lcd_put_cur(row, col);
				lcd_send_data(keyPressed);
				keyPressed=0;
				col++;
				break;
			}

			/*
			 * Break loop when user complete entering first number and operation
			 */
			if (done == 1) break;
			HAL_Delay(500);
		}
	num1=Convert(number1, num1_counter, num1_flag);
}
/*
 * Description :
 *  Get two number and operation and do operation and display it on screen
 */
void Second_NUM(void)
{
	int done = 0;
	int subtract_count=0;
		while(1)
		{
			switch (keyPressed){
			case 'c':
				Calculator_Reset();
				break;
			case '/':
			case '*':
				if (number2[0]==-1) {
					lcd_put_cur(row,col);
					lcd_send_data(keyPressed);
					keyPressed = 0;
					col++;
					error_flag=true;
					break;
				}
				HAL_Delay(200);
				break;
			case '+':
				if (number2[0]==-1) {
					lcd_put_cur(row,col);
					lcd_send_data(keyPressed);
					keyPressed = 0;
					col++;
					break;
				}
			case '-':
				if (number2[0]==-1) {
					lcd_put_cur(row,col);
					lcd_send_data(keyPressed);
					keyPressed = 0;
					col++;
					subtract_count++;
					if (subtract_count%2==0) num2_flag=true;
					else num2_flag=false;
					break;
				}
				HAL_Delay(500);
				break;
			case '=':
				lcd_put_cur(row, col);
				lcd_send_data(keyPressed);
				keyPressed=0;
				done = 1;
				break;
			case 0:
				break;
			default:
				number2[num2_counter]=keyPressed-'0';
				num2_counter++;
				lcd_put_cur(row, col);
				lcd_send_data(keyPressed);
				keyPressed=0;
				col++;
				break;
			}

			/*
			 * Break loop when user complete entering first number and operation
			 */
			if (done == 1) break;
			HAL_Delay(200);
		}
		num2=Convert(number2, num2_counter, num2_flag);
}
/*
 * Process calculator
 */

void Calculate(void) {
	switch(operator)
		{
		case '+':
			result=num1+num2;
			break;
		case '-':
			result=num1-num2;
			break;
		case '*':
			result=num1*num2;
			break;
		case '/':
			if (num2==0) {
				error_flag=true;
				break;
			}
			result=num1/num2;
			break;
		}
}

void Calculator_Start(void) {

	/*
	 * Get first number and operation
	 */
	First_NUM();

	/*
	 * Get first number and operation
	 */
	Second_NUM();

	/*
	 * Do operation calculation
	 */
	Calculate();

	if (error_flag == true) {
		lcd_put_cur(1, 0);
		lcd_send_string("ERROR");
		while (keyPressed == 0);
	} else {
		//print the result to screen
		lcd_put_cur(1, 0);
		lcd_interger_string(result);
		//check the key pressed has the new operator
		while (keyPressed != 'c') {
			if (keyPressed == '+' || keyPressed == '-' || keyPressed == '*'|| keyPressed == '/') {
				float temp = result; // store the result to a temp variable
				uint8_t operator_temp = keyPressed; // store operator was pressed to a temp variable
				Calculator_Reset(); // reset all the variables
				num1 = temp;
				operator = operator_temp;
				if (num1 < 0)
					num1_flag = false; //check result value
				//print result as operand 1 to screen
				lcd_put_cur(row, col);
				lcd_interger_string(num1);
				//increase row to continue print operator and new operand 2
				row++;
				lcd_put_cur(row, col);
				lcd_send_data(operator);
				col++;
				Second_NUM();
				Calculate();
				if (error_flag == true) {
						lcd_put_cur(1, 0);
						lcd_send_string("ERROR");
						while (keyPressed == 0);
						break;
				} else {
					lcd_put_cur(1, 0);
					lcd_interger_string(result);
				}

			} else
				HAL_Delay(500);
		}
	}
	//wait for pressing C
	Calculator_Reset();
}
