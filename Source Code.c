#include<pic.h>

__CONFIG( HS & WDTDIS & BOREN & LVPDIS );

static bit RELAY1@((unsigned )&PORTC*8+0);
static bit RELAY2@((unsigned )&PORTC*8+1);

static bit BUZZER@((unsigned )&PORTC*8+2);



static bit SW1@((unsigned )&PORTB*8+0);

static bit IR1SENSOR1@((unsigned )&PORTB*8+5);
static bit IR1SENSOR2@((unsigned )&PORTB*8+6);

static bit rs@((unsigned )&PORTD*8+1);
static bit rw@((unsigned )&PORTD*8+2);
static bit en@((unsigned )&PORTD*8+3);

unsigned int count, adc_value,VAL2=0,VAL333=0;
bank2 unsigned char  val5, F_VAL,F_VAL1=0,gsm_count,RFID_count;
unsigned char SMS_N1=0,SMS_N2=0,SMS_N3=0;
unsigned char RFID1[20];
unsigned int val1,val2,val3,val4;
bank2 unsigned char da[10];
bank2 unsigned char da1[10];
unsigned char a,s1,i,j,b,c,d,e,f,g,h,i,j,k,l,m,n,o,VAL1,VAL6,val7=0;
unsigned char VAL3,VAL1,ser=0x37,ser1,st=0x01,data_cap=0x00,VAL33=0,val11=0; 
unsigned char VALA=0,VALB=0,H1,H2,H3,T1,T2,T3,M1,M2,M3,MM1,MM2,M11,M22,M33;
unsigned char st_1=0x01,data_cap_1=0x00; 
bank2 unsigned char gsm_data[55];


void delay(unsigned int y)//delay prg
{
while(y--);
}


void lcd_command(unsigned char com)
{
unsigned char temp;

PORTD=com&0xf0;
rs=0;
rw=0;
en=1;
delay(10);
en=0;
temp=com<<4;
PORTD=temp&0xf0;
rs=0;
rw=0;
en=1;
delay(10);
en=0;
}


void lcd_init()
{
lcd_command(0x02);
lcd_command(0x2c);
lcd_command(0x06);
lcd_command(0x0c);
lcd_command(0x01);
lcd_command(0x80);
}

void lcd_data(unsigned char data)
{
unsigned char val1;
PORTD=data&0xf0;
en=1;
rs=1;
rw=0;
delay(10);
en=0;
val1=data<<4;
PORTD=val1&0xf0;
en=1;
rs=1;
rw=0;
delay(10);
en=0;
}
void lcd_display(const unsigned char*word,unsigned int n)
{
unsigned char l;
for(l=0;l<n;l++)
{
lcd_data(word[l]);
}
}


//**************************************************************************
//  SERIAL INTRRUPT
//**************************************************************************
void interrupt rcx(void)
{

if(RCIF==1)
{
//relay=1;
RCIF=0;
ser=RCREG;
//***************************************************
//RFID
//***************************************************

if((ser=='0')&&(st_1==0x01))
{
data_cap_1=0x01;
st_1=0x00;
}
if((data_cap_1==0x01)&&(RFID_count<30))
{
RFID1[RFID_count]=ser;
RFID_count++;
}




//**************************************************************************


}
}


//**************************************************************************
//  gsm init
//**************************************************************************
void gsm_init()
{
    TXSTA=0x24;
	RCSTA=0x90;
	SPBRG=25;
    BRGH=1;
GIE=1;
PEIE=1;
RCIE=1;

}
//**************************************************************************
//  gsm command
//**************************************************************************
void gsm_command(const unsigned char *da,unsigned int y)
{
unsigned int s;
for(s=0;s<=y;s++)
{
while(!TXIF)
	{
	}
OERR=0;
TXREG=da[s];
}
}
void txs(unsigned char val)
{
while(!TXIF)
	{
	}
OERR=0;
TXREG=val;
}


//**************************************************************************
//IOT
//********************************

void IOT_SEND()
{

TXREG='T';
	delay(100);

TXREG=(H1);
delay(600);

TXREG=(H2);
delay(600);

TXREG=(H3);
delay(600);


TXREG='H';
	delay(100);

TXREG=(T1);
delay(600);

TXREG=(T2);
delay(600);

TXREG=(T3);
delay(600);

TXREG='C';
	delay(100);

TXREG=(MM1);
delay(600);

TXREG=(MM2);
delay(600);

TXREG='A';	delay(100);
TXREG=(M1);
delay(600);

TXREG=(M2);
delay(600);

TXREG=(M3);
delay(600);


TXREG='B';	delay(100);
TXREG=(M11);
delay(600);

TXREG=(M22);
delay(600);

TXREG=(M33);
delay(600);
}


void adcconvert1()
{
b=VAL1%10;
c=VAL1/10;

e=c%10;
f=c/10;
g=f%10;
h=f/10;


lcd_data(g+0x30);
H1=(g+0x30);
delay(100);

lcd_data(e+0x30);
delay(100);
H2=(e+0x30);

lcd_data(b+0x30);
delay(100);
H3=(b+0x30);

}

void adcconvert2()
{
j=VAL2%10;
k=VAL2/10;

l=k%10;
m=k/10;
n=m%10;
o=m/10;



lcd_data(n+0x30);
delay(100);
T1=(n+0x30);

lcd_data(l+0x30);
delay(100);
T2=(l+0x30);

lcd_data(j+0x30);
delay(100);
T3=(j+0x30);

}
void adcconvert3()
{
j=VALA%10;
k=VALA/10;

l=k%10;
m=k/10;
n=m%10;
o=m/10;



lcd_data(n+0x30);
delay(100);
M1=(n+0x30);

lcd_data(l+0x30);
delay(100);
M2=(l+0x30);

lcd_data(j+0x30);
delay(100);
M3=(j+0x30);

}
void adcconvert4()
{
j=VALB%10;
k=VALB/10;

l=k%10;
m=k/10;
n=m%10;
o=m/10;



lcd_data(n+0x30);
delay(100);
M11=(n+0x30);

lcd_data(l+0x30);
delay(100);  
M22=(l+0x30);

lcd_data(j+0x30);
delay(100);
M33=(j+0x30);

}
void sensor()
{
lcd_command(0x01);
delay(100);
lcd_command(0x80);

delay(100);
CHS0=0;
CHS1=0;
CHS2=0;

ADON=1;
delay(200);
ADCON0=ADCON0|0X04;
delay(200);
adc_value=ADRESH;
adc_value=adc_value<<8;
adc_value=(adc_value+ADRESL)/0x02;
VAL1=adc_value;
//adc_value=adc_value/0x02;
delay(100);
lcd_command(0x82);
delay(100);
adcconvert1();
delay(10000);

CHS0=1;
CHS1=0;
CHS2=0;
ADON=1;
delay(200);
ADCON0=ADCON0|0X04;
delay(200);
adc_value=ADRESH;
adc_value=adc_value<<8;
adc_value=(adc_value+ADRESL)/0x02;
VAL2=adc_value;
delay(100);
lcd_command(0x87);
delay(100);
adcconvert2();
delay(10000);
}


void main()
{
ADCON1=0X84;
ADCON0=0X00;

TRISD=0X00;
TRISE=0X03;
TRISB=0XFF;
TRISC=0X80;
TRISA=0XFF;

PORTD=0XFF;
PORTD=0X00;
PORTE=0X03;
PORTC=0X81;
PORTB=0XFF;
BUZZER=1;
//RELAY=0;
j=0;
 lcd_init();
delay(100);

delay(100);
lcd_command(0x80);
delay(100);
lcd_display("welcome",7);
gsm_init();
RELAY1=0;
delay(50000);


data_cap_1=0x00;
st_1=0x01;
gsm_count=0;
delay(50000);
//RELAY4=1;
//RELAY3=0;
//delay(50000);
//RELAY4=0;RELAY3=0;
adcconvert4();
adcconvert3();
delay(50000);
while(1)
{


 sensor();IOT_SEND();
//**************************************************************************
//IR COUNT
//**************************************************************************
  val2= count%10;//UNIT DIGIT
  val3= count/10;
  val4=val3%10;    // tens digit
  val5=val3/10;
MM1=(val4+0x30);
MM2=(val2+0x30);
lcd_command(0xC7);
delay(100);
lcd_data(val4+0x30);
delay(100);
lcd_data(val2+0x30);
delay(30000);
if(IR1SENSOR1==0)
{
while(IR1SENSOR1==0);
while(IR1SENSOR2==1);
while(IR1SENSOR2==0);
count=count+1;
delay(50000);delay(50000);delay(50000);
} 

if(IR1SENSOR2==0)
{
while(IR1SENSOR2==0);
while(IR1SENSOR1==1);
while(IR1SENSOR1==0);
if(count>0)
{
count=count-1;
}
delay(50000);delay(50000);delay(50000);
} 

if(count>0)
{
BUZZER=0;delay(50000);BUZZER=1;delay(20000);
}
//**************************************************************************
//RFID
//**************************************************************************
 
if(RFID_count>7)
{
RFID_count=0;
data_cap_1=0x00;
st_1=0x01;

lcd_command(0xc0);
delay(1000);

delay(50000);delay(50000);
//RELAY1=1;
delay(50000);delay(50000);
F_VAL1=0;
lcd_command(0x01);
delay(1000);
lcd_command(0x80);
delay(1000);
for(j=0;j<8;j++)
{
ser=(RFID1[j]);
lcd_data(ser);
delay(1200);
}
delay(50000);delay(50000);delay(50000);
if((RFID1[6]=='7')&&(RFID1[7]=='1'))
{
lcd_command(0x80);
delay(100);
lcd_display("authorized",10);

RELAY1=1;delay(50000);RELAY1=0;delay(50000);delay(50000);delay(50000);
RELAY2=1;delay(50000);RELAY2=0;
delay(50000);delay(50000);
}
if((RFID1[6]=='C')&&(RFID1[7]=='F'))
{

lcd_command(0x80);
delay(100);
lcd_display("unauthorized",12);

delay(50000);delay(50000);
}
if((RFID1[6]=='6')&&(RFID1[7]=='4'))
{

lcd_command(0x01);
delay(100);
lcd_command(0x80);
delay(100);
lcd_display("A+     ",7);
delay(50000);delay(50000);
if(SW1==1)
{
VALA=VALA+1;adcconvert3();
}
else
{
if(VALA>0)
{
VALA=VALA-1;adcconvert3();
}
}
//TXREG='A';	delay(100);
//TXREG=(VALA+0X30);delay(600);


delay(50000);RELAY1=0;
}
if((RFID1[6]=='3')&&(RFID1[7]=='5'))
{

lcd_command(0x01);
delay(100);
lcd_command(0x80);
delay(100);
delay(100);
lcd_display("B+     ",7);
delay(50000);delay(50000);

if(SW1==1)
{
VALB=VALB+1;adcconvert4();
}
else
{
if(VALB>0)
{
VALB=VALB-1;adcconvert4();
}
}

delay(50000);RELAY1=0;

}
}



} 
}
