#include <stdio.h>

//=================================================================================
//��������������ֲ 
typedef unsigned char u8; 
typedef unsigned int u16; 

u8 PenStatus = 0;  //�ʵ�״̬��0--̧��1--���� 
FILE *fp;


//��ʱ������Ϊȷ���뵥Ƭ��һ�£������һ���պ���
void delay_ms(u16 time)
{
	return;
}
//��ȡ�������룬����ʱ�õ��Լ��̴��濪������� 
char key()
{
	char str = 0;
	
	str = getch();
	return str; 
}
//�ı�ʵ�״̬ 
void SetTim4Pwm(u8 chn,u16 angle)	//̧���
{
	if(angle > 120)  //̧��
		PenStatus = 0; 
	else PenStatus = 1;  
}

//X������������������滻Ϊ�������ݱ������ڹ۲� 
void MotorXDriver(u16 plus,u8 dir,u16 time)
{
	u16 i;

	fprintf(fp,"x,%d,%d,%d\n", plus,dir,PenStatus);
}
//Y������������������滻Ϊ�������ݱ������ڹ۲� 
void MotorYDriver(u16 plus,u8 dir,u16 time)
{
	u16 i;

	fprintf(fp,"y,%d,%d,%d\n", plus,dir,PenStatus);
}
//=================================================================================
//�������ݷ���ɹ�����ֲ�������� 
//�ƶ�����
void Move(u16 x0,u16 y0,u16 x1,u16 y1)
{
	//̧���
	SetTim4Pwm(1,180);

	//��X�����ƶ�
	if(x1>=x0)
		MotorXDriver(x1-x0,0,100);
	else MotorXDriver(x0-x1,1,100);
	
	//��Y�����ƶ�
	if(y1>=y0)
		MotorYDriver(y1-y0,0,100);
	else MotorYDriver(y0-y1,1,100);
}

//��ֱ�ߺ���
void DrawLine(u16 x0,u16 y0,u16 x1,u16 y1)
{
	//����ֲ�����
	u16 xplus = 0;  //X��ÿ��Ҫ�ߵĲ���
	u16 xdir = 0;	 //X��ÿ��Ҫ�ߵķ���	
	u16 yplus = 0;  //Y��ÿ��Ҫ�ߵĲ���
	u16 ydir = 0;    //Y��ÿ��Ҫ�ߵķ���
	u16 x = 0 ,y = 0; 
	
	SetTim4Pwm(1,90);	 //���±�
	delay_ms(50);
	
	x = x0;
	y = y0;
		
	while(1)
	{
		//ֱ�߲���������xplus,xdir,yplus,ydir��4������
		if(x < x1)
		{
			xplus = 1;
			xdir = 0;
			x ++;
		}
		else if(x > x1)
		{
			xplus = 1;
			xdir = 1;
			x --;
		}
		else xplus = 0;
		
		if(y < y1)
		{
			yplus = 1;
			ydir = 0;
			y ++;
		}
		else if(y > y1)
		{
			yplus = 1;
			ydir = 1;
			y --;
		}
		else yplus = 0;
		
		//�������break����ѭ��		
		if(x == x1 && y == y1)
		{
			break;
		}
		//���õ����������
		MotorXDriver(xplus,xdir,100);
		MotorYDriver(yplus,ydir,100);
	}
	
	//̧���
	SetTim4Pwm(1,180);	
	delay_ms(50);
}

//��Բ������
void DrawCircle(u16 x0,u16 y0,u16 x1,u16 y1,u16 r)
{
	//����ֲ�����
	u16 xplus;  //X��ÿ��Ҫ�ߵĲ���
	u16 xdir;	 //X��ÿ��Ҫ�ߵķ���	
	u16 yplus;  //Y��ÿ��Ҫ�ߵĲ���
	u16 ydir;    //Y��ÿ��Ҫ�ߵķ���
	
	SetTim4Pwm(1,90);	//���±�
	delay_ms(50);

	while(1)
	{
		//Բ������������xplus,xdir,yplus,ydir��4������

		//�������break����ѭ��		

		//���õ����������
		MotorXDriver(xplus,xdir,100);
		MotorYDriver(yplus,ydir,100);
	}

	SetTim4Pwm(1,180);	//̧���
	delay_ms(50);
}



int main(void)
{	
	u16 x =0 ,y = 0;   //�����ʼ����
	u16 i;
	u8 key_num;
	
	//����Ҫ�ߵ�·��
	u16 point[4][6]={
	{1,0,0,100,0,0},
	{1,100,0,100,100,0},
	{1,100,100,0,100,0},
	{1,0,100,0,0,0},
	
	};
	//���鶨�壺
	//�±�0: 1��ֱ�ߣ�2��Բ��
	//�±�1: x0����
	//�±�2: y0����
	//�±�3: x1����
	//�±�4: y1����
	//�±�5: �뾶
 
	
	printf("��0��������\n"); //����ר�ã�������ֲ����Ƭ�� 

	SetTim4Pwm(1,180);	//̧���
	
	while (1)	  
	{	
		key_num = key();  //��ȡ����

		if(key_num == '0')  //��������0
		{
			fp=fopen("result.txt","w");  //����ר�ã�������ֲ����Ƭ�� 
			
			//��ͼ
			for(i=0;i<4;i++)
			{
				printf("���ڴ����%d��·��\n",i);  //����ר�ã�������ֲ����Ƭ�� 
				
				//�ƶ������
				Move(x,y,point[i][1],point[i][2]);

				//��ʼ����
				if(point[i][0] == 1)  //1����ֱ��
				{
					DrawLine(point[i][1],point[i][2],point[i][3],point[i][4]);	
				}
				else if(point[i][0] == 2)  //2����Բ��
				{
					DrawCircle(point[i][1],point[i][2],point[i][3],point[i][4],point[i][5]);	
				}
				//���µ�ǰ����
				x = point[i][3];
				y = point[i][4];
			}
			
			fclose(fp); //����ר�ã�������ֲ����Ƭ�� 
			printf("�������\n"); //����ר�ã�������ֲ����Ƭ�� 
		}
	}
	
    return 0;
}

