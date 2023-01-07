#include <stdio.h>

//=================================================================================
//以下内容无需移植 
typedef unsigned char u8; 
typedef unsigned int u16; 

u8 PenStatus = 0;  //笔的状态，0--抬起，1--放下 
FILE *fp;


//延时函数，为确保与单片机一致，这里放一个空函数
void delay_ms(u16 time)
{
	return;
}
//读取键盘输入，仿真时用电脑键盘代替开发板键盘 
char key()
{
	char str = 0;
	
	str = getch();
	return str; 
}
//改变笔的状态 
void SetTim4Pwm(u8 chn,u16 angle)	//抬起笔
{
	if(angle > 120)  //抬笔
		PenStatus = 0; 
	else PenStatus = 1;  
}

//X电机驱动函数，这里替换为生成数据保存用于观察 
void MotorXDriver(u16 plus,u8 dir,u16 time)
{
	u16 i;

	fprintf(fp,"x,%d,%d,%d\n", plus,dir,PenStatus);
}
//Y电机驱动函数，这里替换为生成数据保存用于观察 
void MotorYDriver(u16 plus,u8 dir,u16 time)
{
	u16 i;

	fprintf(fp,"y,%d,%d,%d\n", plus,dir,PenStatus);
}
//=================================================================================
//以下内容仿真成功后移植到开发板 
//移动函数
void Move(u16 x0,u16 y0,u16 x1,u16 y1)
{
	//抬起笔
	SetTim4Pwm(1,180);

	//先X方向移动
	if(x1>=x0)
		MotorXDriver(x1-x0,0,100);
	else MotorXDriver(x0-x1,1,100);
	
	//再Y方向移动
	if(y1>=y0)
		MotorYDriver(y1-y0,0,100);
	else MotorYDriver(y0-y1,1,100);
}

//画直线函数
void DrawLine(u16 x0,u16 y0,u16 x1,u16 y1)
{
	//定义局部变量
	u16 xplus = 0;  //X轴每次要走的步数
	u16 xdir = 0;	 //X轴每次要走的方向	
	u16 yplus = 0;  //Y轴每次要走的步数
	u16 ydir = 0;    //Y轴每次要走的方向
	u16 x = 0 ,y = 0; 
	
	SetTim4Pwm(1,90);	 //放下笔
	delay_ms(50);
	
	x = x0;
	y = y0;
		
	while(1)
	{
		//直线差补处理，计算出xplus,xdir,yplus,ydir这4个参数
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
		
		//差补结束后break跳出循环		
		if(x == x1 && y == y1)
		{
			break;
		}
		//调用电机驱动程序
		MotorXDriver(xplus,xdir,100);
		MotorYDriver(yplus,ydir,100);
	}
	
	//抬起笔
	SetTim4Pwm(1,180);	
	delay_ms(50);
}

//画圆弧函数
void DrawCircle(u16 x0,u16 y0,u16 x1,u16 y1,u16 r)
{
	//定义局部变量
	u16 xplus;  //X轴每次要走的步数
	u16 xdir;	 //X轴每次要走的方向	
	u16 yplus;  //Y轴每次要走的步数
	u16 ydir;    //Y轴每次要走的方向
	
	SetTim4Pwm(1,90);	//放下笔
	delay_ms(50);

	while(1)
	{
		//圆弧差补处理，计算出xplus,xdir,yplus,ydir这4个参数

		//差补结束后break跳出循环		

		//调用电机驱动程序
		MotorXDriver(xplus,xdir,100);
		MotorYDriver(yplus,ydir,100);
	}

	SetTim4Pwm(1,180);	//抬起笔
	delay_ms(50);
}



int main(void)
{	
	u16 x =0 ,y = 0;   //定义初始坐标
	u16 i;
	u8 key_num;
	
	//定义要走的路径
	u16 point[4][6]={
	{1,0,0,100,0,0},
	{1,100,0,100,100,0},
	{1,100,100,0,100,0},
	{1,0,100,0,0,0},
	
	};
	//数组定义：
	//下标0: 1—直线，2—圆弧
	//下标1: x0坐标
	//下标2: y0坐标
	//下标3: x1坐标
	//下标4: y1坐标
	//下标5: 半径
 
	
	printf("按0启动程序\n"); //仿真专用，无需移植到单片机 

	SetTim4Pwm(1,180);	//抬起笔
	
	while (1)	  
	{	
		key_num = key();  //读取按键

		if(key_num == '0')  //按下数字0
		{
			fp=fopen("result.txt","w");  //仿真专用，无需移植到单片机 
			
			//绘图
			for(i=0;i<4;i++)
			{
				printf("正在处理第%d条路径\n",i);  //仿真专用，无需移植到单片机 
				
				//移动到起点
				Move(x,y,point[i][1],point[i][2]);

				//开始绘制
				if(point[i][0] == 1)  //1代表画直线
				{
					DrawLine(point[i][1],point[i][2],point[i][3],point[i][4]);	
				}
				else if(point[i][0] == 2)  //2代表画圆弧
				{
					DrawCircle(point[i][1],point[i][2],point[i][3],point[i][4],point[i][5]);	
				}
				//更新当前坐标
				x = point[i][3];
				y = point[i][4];
			}
			
			fclose(fp); //仿真专用，无需移植到单片机 
			printf("处理完成\n"); //仿真专用，无需移植到单片机 
		}
	}
	
    return 0;
}

