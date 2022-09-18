#include "MDR32F9Qx_lib.h"
#include "MDR32Fx.h" 
#include <MDR32F9Qx_uart.h>
#include <MDR32F9Qx_port.h>

#define mask_RST_CLK_CPU_CLOCK_CPU_C1_HSI_ON       ((unsigned long)0x00000000)
#define mask_RST_CLK_CPU_CLOCK_CPU_C1_HSI_2_ON     ((unsigned long)0x00000001)
#define mask_RST_CLK_CPU_CLOCK_CPU_C1_HSE_ON       ((unsigned long)0x00000002)
#define mask_RST_CLK_CPU_CLOCK_CPU_C1_HSE_2_ON     ((unsigned long)0x00000003)
	
#define mask_RST_CLK_CPU_CLOCK_CPU_C1_SEL       ((unsigned long)0x00000003)
#define mask_RST_CLK_CPU_CLOCK_CPU_C2_SEL       ((unsigned long)0x00000004)
#define mask_RST_CLK_CPU_CLOCK_CPU_C3_SEL       ((unsigned long)0x000000F0)
#define mask_RST_CLK_CPU_CLOCK_HCLK_SEL         ((unsigned long)0x00000300)

//#define mask_RST_CLK_CPU_CLOCK_HCLK_SEL_HSI_ON       ((unsigned long)0x00000000)
#define mask_RST_CLK_CPU_CLOCK_HCLK_SEL_CPU_C3_ON    ((unsigned long)0x00000100)
//#define mask_RST_CLK_CPU_CLOCK_HCLK_SEL_LSE_ON       ((unsigned long)0x00000200)
//#define mask_RST_CLK_CPU_CLOCK_HCLK_SEL_LSI_ON       ((unsigned long)0x00000300)


void CLK_init () {
////---CLK-----------------------------------------------------------------------------------------------------
  MDR_RST_CLK->HS_CONTROL = RST_CLK_HS_CONTROL_HSE_ON; // ���. HSE ����������
	
  while ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY) == 0x00); // ���� ���� HSE ������ � ������� �����
	
  MDR_RST_CLK->PLL_CONTROL = ((RST_CLK_PLL_CONTROL_PLL_CPU_ON )
                    	| (7 << RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos));  // ���. PLL | ����. ��������� = 7  
	
  while ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY) == 0x00); // ���� ����� PLL ������ � ���. �����
		
  MDR_RST_CLK->CPU_CLOCK  = (mask_RST_CLK_CPU_CLOCK_CPU_C1_HSE_ON   // �������� ��� CPU_C1 HSE
														|  mask_RST_CLK_CPU_CLOCK_CPU_C2_SEL         // �������� ��� CPU_C2 PLLCPUo
														|  (0 << RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos)		// �������� ��� CPU_C3   CPU_C2 
														|  mask_RST_CLK_CPU_CLOCK_HCLK_SEL_CPU_C3_ON	// �������� ���  HCLK  CPU_C3 
															);
 
	MDR_RST_CLK->PER_CLOCK |= (1 << 4);//���������� ������������ ������������ ������


}

void UART2_init(){
  MDR_RST_CLK->PER_CLOCK |= (1 << 7)               // ���������� ������������ UART2
								 		     | (1 << 29);              // ���������� ������������ ����� F	
//---UART----------------------------------------------------------------------------------------------------
  MDR_RST_CLK->UART_CLOCK = (0                                 // ��������� �������� ��� UART1 = undefined
 											 & (~RST_CLK_UART_CLOCK_UART2_BRG_Msk)   //�������� ������� 
                       | RST_CLK_UART_CLOCK_UART2_CLK_EN);     // ���������� �������� ������� UART2
	//921600 bit/s
	MDR_UART2->IBRD       = 4;				//����� ����� �������� ��������
	MDR_UART2->FBRD       = 10;				//������� ����� �������� ��������
	
//	//19200 bit/s
//	MDR_UART2->IBRD       = 13;				//����� ����� �������� ��������
//	MDR_UART2->FBRD       = 3;				//������� ����� �������� ��������

//	//115200 bit/s
//	MDR_UART2->IBRD       = 4;				//����� ����� �������� ��������
//	MDR_UART2->FBRD       =22;				//������� ����� �������� ��������
	
//	//921600 bit/s
//	MDR_UART2->IBRD       = 0;				//����� ����� �������� ��������
//	MDR_UART2->FBRD       =35;				//������� ����� �������� ��������
	
	
  MDR_UART2->LCR_H      = (0
	                    & (~UART_LCR_H_BRK)
											& (~UART_LCR_H_PEN)  //��� �������� �� ��������
	                    & (~UART_LCR_H_STP2) //�������� ���� (0 - ����� 1 ���� ���; 1 - 2 ���� ����)
	                    & (~UART_LCR_H_FEN)  //����� FIFO (0 - ��������; 1 - �������)
	                    | (3 << UART_LCR_H_WLEN_Pos) //���-�� ������ ��� � �����
	                    & (~UART_LCR_H_SPS)
                    	);

  MDR_UART2->CR         = (
	                    UART_CR_UARTEN //���������� ������ ����������������
											& (~UART_CR_SIREN) //
											& (~UART_CR_SIRLP)
											& (~UART_CR_LBE)
											| UART_CR_TXE         //�������� ���������
											| UART_CR_RXE         //����� ��������
	                      );

  MDR_UART2->IMSC      = (0
	                     & (~UART_IMSC_RIMIM) 
											 & (~UART_IMSC_CTSMIM)
											 & (~UART_IMSC_DCDMIM)
											 & (~UART_IMSC_DSRMIM)
											 | UART_IMSC_RXIM
											 & (~UART_IMSC_TXIM)
											 & (~UART_IMSC_RTIM)
											 & (~UART_IMSC_FEIM)
											 & (~UART_IMSC_PEIM)
											 & (~UART_IMSC_BEIM)
											 & (~UART_IMSC_OEIM)
	                     );

//----------------------------------------------
	 
	 MDR_PORTF->OE = 0xFFFF;
	 MDR_PORTF->FUNC = 0xFFFFFFFF;
	 MDR_PORTF->ANALOG = 0x0000FFFF;
	 MDR_PORTF->PD = 0x0000;
   MDR_PORTF->PWR =  0xFFFFFFFF;
   MDR_PORTF->GFEN = 0x00000000;
	 MDR_PORTF->RXTX = 0xFFFFFFFF; 

	 NVIC_SetPriority(UART2_IRQn, 0);	
	 NVIC_EnableIRQ(UART2_IRQn);
}

void PortA_Unit(){
	MDR_RST_CLK->PER_CLOCK |= (1 << 21);   //���������� ������������ 
//----PORTA--------------------------------------------- 
	 MDR_PORTA->OE = 0x0000;
	 MDR_PORTA->FUNC = 0x00000000;
	 MDR_PORTA->ANALOG = 0x0000FFFF;
	 MDR_PORTA->PULL = PORT_PULL_DOWN_Msk;
	 MDR_PORTA->PD = PORT_PD_SHM_Msk;// 0x0000;
   MDR_PORTA->PWR =  0xFFFFFFFF;
   MDR_PORTA->GFEN = 0x00000000;
}

void PortC_Unit(){
	MDR_RST_CLK->PER_CLOCK |= (1 << 23);   //���������� ������������ 
//----PORTC--------------------------------------------- 
	 MDR_PORTC->OE = 0x00FF;
	 MDR_PORTC->FUNC = 0x00000000;
	 MDR_PORTC->ANALOG = 0x0000FFFF;
	 MDR_PORTC->PULL = PORT_PULL_DOWN_Msk;
	 MDR_PORTC->PD = PORT_PD_SHM_Msk;// 0x0000;
   MDR_PORTC->PWR =  0xFFFFFFFF;
   MDR_PORTC->GFEN = 0x00000000;
}

void PortD_Unit(){
	MDR_RST_CLK->PER_CLOCK |= (1 << 24);   //���������� ������������ 
//----PORTD--------------------------------------------- 
	 MDR_PORTD->OE = 0xFFFF;
	 MDR_PORTD->FUNC = 0x00000000;
	 MDR_PORTD->ANALOG = 0x0000FFFF;
	 MDR_PORTD->PULL = PORT_PULL_DOWN_Msk;
	 MDR_PORTD->PD = PORT_PD_SHM_Msk;// 0x0000;
   MDR_PORTD->PWR =  0xFFFFFFFF;
   MDR_PORTD->GFEN = 0x00000000;
}

void Sensor_Unit(){
		MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_0; 	 //DQ - 0
		MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_2;   //RST
		MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK - 1
}


int i=0,j=0,k=0;
int count=0;
int control_summ=0;
int flag_c_s=0;
int b_1=0,b_2=0,b_3=0,b_4=0,b_5=0,b_6=0,b_7=0;
int flag_a_i_d=0;
int flag_a_i_d_v2=0;
int flag__read_temp_sensor=0;
int flag__request_temp_sensor=0;

void UART2_IRQHandler(){
	if(k==7 && count==7){k=0; }
	if(k==4 && count==4){k=0; }
	
	if(k==0){
		b_1 = MDR_UART2->DR;
		k++;
		if (b_1==0x59){count=7; }
		if (b_1==0x05){count=4; }
	}
	else{
		if(k==1){
			b_2 = MDR_UART2->DR;
			k++;
		}
		else{
			if((k>1) && (k< 7)){
				if (k==2){
							b_3 = MDR_UART2->DR;
							if ((b_1==0x59) && (b_3==0xAA)) {flag__read_temp_sensor=1;}
							if ((b_1==0x59) && (b_3==0xEE)) {flag__request_temp_sensor=1;}
				}
				if (k==3){
							b_4 = MDR_UART2->DR;
							if (count==4){
									control_summ=b_1+b_2+b_3;
									if (control_summ!=b_4){flag_c_s=1;}
									else{flag_c_s=0;}
									
									flag_a_i_d_v2=1;
									flag_a_i_d=1;
							}
				}
				if (k==4){
							b_5 = MDR_UART2->DR;
				}
				if (k==5){
							b_6 = MDR_UART2->DR;
				}
				if (k==6){
							b_7 = MDR_UART2->DR;
							if (count==7){
									control_summ=b_1+b_2+b_3+b_4+b_5+b_6;
									if (control_summ!=b_7){flag_c_s=1;}
									else{flag_c_s=0;}
							}
				}
				k++;
			}
		}
	}
	
}

void analyze_input_data(){
	int analyze_byte=0;
	int mask=0;
	
	// Esli prishlo 4 baita, u v 3 baite v 1 bite stoit 1
	if(count ==4 ){
		analyze_byte=b_3;
		mask=0x02;
		analyze_byte&=mask;
		
		if (analyze_byte==0x02){	
				MDR_PORTD->RXTX=MDR_PORTD->RXTX|PORT_Pin_10;			
			
				analyze_byte=b_3;	 
				mask=0x04;
				analyze_byte&=mask;
				// Esli v 3 baite vo 2 bite stoit 1			
				 if(analyze_byte==0x04){
						for (i=0;i<400000;i++){}
						MDR_PORTD->RXTX=MDR_PORTD->RXTX|PORT_Pin_11;
						for (i=0;i<1200000;i++){}
						MDR_PORTD->RXTX=PORT_Pin_10;
					  for (i=0;i<400000;i++){}
				 }
				 else{
						for (i=0;i<2150000;i++){}
				 }
				MDR_PORTD->RXTX&=~PORT_Pin_10;
				for (i=0;i<2000000;i++){}
		}
		else{
				MDR_PORTD->RXTX&=~PORT_Pin_11;
			  MDR_PORTD->RXTX&=~PORT_Pin_10;
		}
	}
	// Esli prishlo 4 baita, u v 3 baite v 3 bite stoit 1
	if(count ==4 ){
		analyze_byte=b_3;
		mask=0x08;
		analyze_byte&=mask;
		if (analyze_byte==0x08){				 
				analyze_byte=b_3;	 
				mask=0x10;
				analyze_byte&=mask;
				MDR_PORTD->RXTX=MDR_PORTD->RXTX|PORT_Pin_12;
				// Esli v 3 baite v 4 bite stoit 1			
				 if(analyze_byte==0x10){
						for (i=0;i<400000;i++){}
						MDR_PORTD->RXTX=MDR_PORTD->RXTX|PORT_Pin_13;
						for (i=0;i<1200000;i++){}
						MDR_PORTD->RXTX=PORT_Pin_12;
					  for (i=0;i<400000;i++){}
				 }
				 else{
						for (i=0;i<2150000;i++){}
				 }
				MDR_PORTD->RXTX&=~PORT_Pin_12;
				for (i=0;i<2000000;i++){}
		}
		else{
				MDR_PORTD->RXTX&=~PORT_Pin_12;
			  MDR_PORTD->RXTX&=~PORT_Pin_13;
		}
	}
	
	flag_a_i_d=0;
	
}

short int data_PC;
short int data_PA;
int Port_A_C_byte, out_c_s;

void analyze_input_data_v2(){
	Port_A_C_byte=0;
	if ((b_1==0x05) &&(b_2==0x02) && (flag_c_s==0)){
		data_PC=MDR_PORTC->RXTX;
		data_PA=MDR_PORTA->RXTX;
		
		data_PA=data_PA>>1;		
		data_PA=data_PA<<4;
		data_PC=data_PC & 0x0F;
		Port_A_C_byte=data_PA|data_PC;
		out_c_s=0x05+0x83+Port_A_C_byte;
		
		//wait until Tx not ready	
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));
		MDR_UART2->DR=0x05;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));
		MDR_UART2->DR=0x83;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));
		MDR_UART2->DR=Port_A_C_byte;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));
		MDR_UART2->DR=out_c_s;	
	
		flag_a_i_d_v2=0;
	}
}

int out_b_1=0,out_b_2=0,out_b_3=0,out_b_4=0,out_b_5=0,out_b_6=0,out_b_7=0;
void send_data(){	
	for (i=0;i<250;i++){}
	out_b_1=b_1; out_b_2=b_2; out_b_3=b_3;
	out_b_4=b_4; out_b_5=b_5; out_b_6=b_6; out_b_7=b_7;
		
	if (count==4){
		out_b_2=0x00ff;out_b_3=0x00ff;
		out_b_4=out_b_1+out_b_2+out_b_3;
		//wait until Tx not ready	
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_1;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_2;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_3;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_4;
	}
		if (count==7){
		out_b_3=0x00ff;out_b_4=0x00ff;
		out_b_5=0x00ff;out_b_6=0x00ff;
		out_b_7=out_b_1+out_b_2+out_b_3+out_b_4+out_b_5+out_b_6;
		//wait until Tx not ready	
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_1;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_2;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_3;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_4;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_5;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_6;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_7;
	}
	flag_c_s=0;
}

void request_temperature(){
		MDR_PORTC->OE = MDR_PORTC->OE | (1<<0);
		MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_2;//RST
		MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK - 1
		//EEh=11101110b
		j=0;
		while(j<2){
			MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_0; 	 //DQ - 0
			for (i=0;i<5;i++){}			
			MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_1; //CLK - 0
			for (i=0;i<12;i++){}
				
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK - 1
			for (i=0;i<25;i++){}
			
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_0; //DQ - 1
			for (i=0;i<5;i++){}		
			MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_1; //CLK -0
			for (i=0;i<12;i++){}
				
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK - 1
			for (i=0;i<25;i++){}
				
			MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_1; //CLK -0
			for (i=0;i<12;i++){}
				
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK - 1
			for (i=0;i<25;i++){}
				
			MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_1; //CLK - 0
			for (i=0;i<12;i++){}
				
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK - 1
			for (i=0;i<25;i++){}
			j++;
		}
		for (i=0;i<25;i++){}
	
		//Zavershenie obmena
		MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_0; 	 //DQ - 0
		MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_2;   //RST
		for(i=0;i<37;i++){}
			
		flag__request_temp_sensor=0;
}

short int temperature=0;
short int input_C=0;
void read_temperature(){
	temperature=0;
	MDR_PORTC->OE = MDR_PORTC->OE | (1<<0);
	//Zapros - Read_Temperature - peredacha AAh
	MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_2;//RST
	MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK - 1
	//AAh=10101010b
	j=0;
	for (i=0;i<37;i++){}
	while(j<4){	
			MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_0; //DQ - 0
			for (i=0;i<5;i++){}			
			MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_1; //CLK - 0
			for (i=0;i<12;i++){}
		
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK -1
			for (i=0;i<25;i++){}
			
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_0; //DQ - 1
			for (i=0;i<5;i++){}		
			MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_1; //CLK - 0
			for (i=0;i<12;i++){}
				
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK - 1
			for (i=0;i<25;i++){}
			
			j++;
	}
	//-------------------------
	//pause
	MDR_PORTC->OE&=~(0x01);
	MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_0; 	 //DQ - 0
	
	for (i=0;i<50;i++){}
	
	//---------------------------------
	//Priem - 16 bit temperatury
	j=0;
	while (j<16){
		MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_1; //CLK -0
		input_C=MDR_PORTC->RXTX;
		input_C=input_C & (1<<0);
		if (input_C!=0){temperature=temperature| (1<<j);}
		for (i=0;i<12;i++){}
		
			MDR_PORTC->RXTX=MDR_PORTC->RXTX|PORT_Pin_1; //CLK -1
			for (i=0;i<25;i++){}
			
		j++;
	}
	for (i=0;i<25;i++){}
	
	
	//Ybiraem pol gradysa (posledniy bit)
	temperature=(temperature>>1);
		
	//Zavershenie obmena
	MDR_PORTC->RXTX=MDR_PORTC->RXTX&~PORT_Pin_2;//RST
	
}

void send_temperature(){
		out_b_1=0x59; out_b_2=0x83; out_b_3=0xAA;
		if ((temperature & (1<<7))==0){out_b_4=0x01;}//Poloshitelnoe 
		else{out_b_4=0x02;}	//Otrichatelnoe
		out_b_5=temperature;

		out_b_6=b_6; 
		out_b_7=out_b_1+out_b_2+out_b_3+out_b_4+out_b_5+out_b_6;
		
		//wait until Tx not ready	
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_1;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_2;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_3;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_4;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_5;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_6;
		while((MDR_UART2->FR&UART_FR_BUSY) == (UART_FR_BUSY));	
		MDR_UART2->DR=out_b_7;
	
		flag__read_temp_sensor=0;
}

double koef =0;
int flag_diod=0;
void buttons_check(){
		short int tmp = 0;
		tmp = MDR_PORTC->RXTX;
		
		//UP
		if (!(tmp & PORT_Pin_11)){
			flag_diod=1;
				if (koef>0){
					koef=koef-0.2;
				}
		}
		//DOWN
		if (!(tmp & PORT_Pin_12)){
			flag_diod=1;
				if (koef<=1){
					koef=koef+0.2;
				}
		}
		//Select
		if (!(tmp & PORT_Pin_10)){
			read_temperature();
			send_temperature();
		}

		for(i=0;i<500000;i++){}		
}

void diods(){
		MDR_PORTD->RXTX=PORT_Pin_10;
		for (i=0;i<(2150*koef) ;i++){buttons_check();}
		MDR_PORTD->RXTX=MDR_PORTD->RXTX|PORT_Pin_11;
		for (i=0;i<(2150*koef) ;i++){buttons_check();}
		MDR_PORTD->RXTX=MDR_PORTD->RXTX|PORT_Pin_12;
		for (i=0;i<(2150*koef) ;i++){buttons_check();}
		MDR_PORTD->RXTX&=~PORT_Pin_12;
		for (i=0;i<(2150*koef) ;i++){buttons_check();}
		MDR_PORTD->RXTX&=~PORT_Pin_11;
		for (i=0;i<(2150*koef) ;i++){buttons_check();}
		MDR_PORTD->RXTX&=~PORT_Pin_10;
		for (i=0;i<(2150*koef) ;i++){buttons_check();}
}

int main(void) {
	CLK_init();
	PortA_Unit();
	PortC_Unit();
	PortD_Unit();
	UART2_init();
	Sensor_Unit();
	count=0;
	
	 while(1){
		 	if(flag_c_s!=0){
				send_data();
			}
			else{
				if ((count!=0) && (flag_a_i_d==1)){
				 analyze_input_data();
				}
				if ((count!=0) && (flag_a_i_d_v2==1)){
					analyze_input_data_v2();
				}

				if(flag__request_temp_sensor!=0){
				 request_temperature();
				}
				if (flag__read_temp_sensor!=0){
				 read_temperature();
				 send_temperature();
				}
			}
			
			buttons_check();
			if(flag_diod!=0){
				diods();
			}
	 }
}
	 
//	while(1){
//		MDR_PORTD->RXTX=PORT_Pin_10;
//		for(i=0;i<2500000;i++){}
//		MDR_PORTD->RXTX=0x0000;
//		for(i=0;i<2500000;i++){}
//		MDR_PORTD->RXTX=PORT_Pin_11;
//		for(i=0;i<2500000;i++){}
//		MDR_PORTD->RXTX=0x0000;
//		for(i=0;i<7500000;i++){}
//	 }
