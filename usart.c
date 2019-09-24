#include "include.h"

/*/串口打开函数/*/
int usart_open(int fd,char* port)
{		
					
	fd = open(port,O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd==-1)
	{
		perror("open fault!!!");
		return -1;
	}
	/*使其为串口为阻塞状态*/
	if(fcntl(fd, F_SETFL, 0) < 0)
	{
		perror("fcntl is failed!!!");
		return -1;		
	}
	return fd; 
}

/**********************
功能：关闭串口函数
参数：无
返回值：无
***********************/
void usart_close(int fd)
{
	close(fd);
}


/**********************
功能：串口初始化函数
参数：baudrate波特率  flew_ctrl流操作  databits数据位  check校验 stopbits停止位
返回值:成功：1 失败：-1
***********************/
int usart_init(int fd,int baudrate,int flew_ctrl,int databits,int check,int stopbits)
{
	struct termios options; 
	
	if(tcgetattr(fd,&options) != 0)  
	{  
		perror("get terminal faild");      
		return -1;   
	} 
	/*设置波特率*/
	
	tcflush(fd, TCIOFLUSH);

	switch(baudrate)
	
	{
		case 300:
			cfsetispeed(&options, B300);   
			cfsetospeed(&options, B300); 
		break;
				
		case 600:
			cfsetispeed(&options, B600);   
			cfsetospeed(&options, B600); 
		break;
		
		case 4800:
			cfsetispeed(&options, B4800);   
			cfsetospeed(&options, B4800); 
		break;
		
		case 9600:
			cfsetispeed(&options, B9600);   
			cfsetospeed(&options, B9600); 
		break;
		
		case 115200:
			cfsetispeed(&options, B115200);   
			cfsetospeed(&options, B115200); 
		break;
		
		default:
			cfsetispeed(&options, B115200);   
			cfsetospeed(&options, B115200); 	   
		break;
	}
	
	tcflush(fd,TCIOFLUSH);  
	 /*激活配置 (将修改后的termios数据设置到串口中)*/  
    if (tcsetattr(fd,TCSANOW,&options) != 0)    
	{  
		perror("com set error!\n");    
		return -1;   
	} 

	switch(flew_ctrl)
	{	
		/*不使用流控制*/
		case 0 : 
            options.c_cflag &= ~CRTSCTS; 
		break;     
        /*使用硬件流控制*/ 
		case 1 : 
            options.c_cflag |= CRTSCTS;  
		break;  
		/*使用软件流控制*/
		case 2 :  
            options.c_cflag |= IXON | IXOFF | IXANY;  
		break; 
	}
	
	/*设置数据位*/  
    /*屏蔽其他标志位*/ 
    


    options.c_cflag &= ~CSIZE;
      
    switch (databits)  
    {    
		case 5:  
			options.c_cflag |= CS5;  
		break;  
		
		case 6:  
			options.c_cflag |= CS6;  
		break;  
		
		case 7:    
            options.c_cflag |= CS7;  
        break;  
		
		case 8:      
            options.c_cflag |= CS8;  
        break;    
		
		default:     
			options.c_cflag |= CS8;
		break;    
    }
    


     /*设置校验位*/  
    switch (check)  
    {   
    	/*无奇偶校验位*/
		case 'n':  
		case 'N':
              options.c_cflag &= ~PARENB;   
              options.c_iflag &= ~INPCK;      
        break; 
          
        /*设置为奇校验*/ 
		case 'o':    
		case 'O':     
             options.c_cflag |= (PARODD | PARENB);   
             options.c_iflag |= INPCK;               
        break; 
        
    	/*设置为偶校验*/
		case 'e':   
		case 'E':    
             options.c_cflag |= PARENB;         
             options.c_cflag &= ~PARODD;         
             options.c_iflag |= INPCK;        
        break; 
        
        /*设置为空格*/  
		case 's':  
		case 'S':   
             options.c_cflag &= ~PARENB;  
             options.c_cflag &= ~CSTOPB;  
        break; 
          
        default:    
             options.c_cflag &= ~PARENB;   
             options.c_iflag &= ~INPCK;      
        break;   
    } 
    


    /*设置停止位*/   
    switch (stopbits)  
    {    
		case 1:     
           options.c_cflag &= ~CSTOPB; 
        break;
           
		case 2:     
           options.c_cflag |= CSTOPB; 
        break;
          
		default:     
           options.c_cflag &= ~CSTOPB;   
        break;  
    } 


    options.c_cflag |= CLOCAL | CREAD;  
	options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    
    /*修改输出模式，原始数据输出*/ 
    
	options.c_oflag &= ~OPOST;  
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  
	
    /*设置等待时间和最小接收字符*/  
    options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */    
    options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */  
     
    /*如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读*/ 
    tcflush(fd,TCIOFLUSH);  
     
    /*激活配置 (将修改后的termios数据设置到串口中)*/  
    if (tcsetattr(fd,TCSANOW,&options) != 0)    
	{  
		perror("com set error!\n");    
		return -1;   
	}  
    return 1;  
}

/*******************************
功能：串口发送数据函数
参数：fd  发送缓冲区  数据长度
返回值：成功：数据长度   失败：-1
********************************/
int usart_send(int fd, uint8_t *s_buff,int data_len)
{
 
   write(fd,s_buff,data_len);  
    return 0;
}

