# RISC_V-SECURITY_ALARM_SYSTEM


In this project, we are going to design Laser Light Security System Using RISCV with Alarm with the application of Laser Diode Module KY-008. The project idea revolves around creating a security system. Whenever any object will obstruct the LASER ray the buzzer alarm will start ringing.

This project can be implemented anywhere, not only buildings or premises but many precious things like jewelry, diamonds, precious antique items in the museum, etc many other things are also secured using such an invisible LASER beam. Many people secure their home, office, shops, warehouses, etc with the LASER beam security system.


# Circuit Diagram
![alarmsystem](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/ce64a096-e601-49e6-afb8-408ac385ec39)

# Block Diagram

![Slide1](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/61f43221-77c9-4820-983e-25adcf84f518)


# Working Principle

The project basically works on the principle of interruption. If by any means the LASER light is interrupted the alarm will start unless it is reset with push-button. The laser is a concentrated light source that puts out a straight beam of light of a single color

The LDR is sensitive to light and puts out a voltage when the laser light hits it. When the laser beam is interrupted and can’t reach LDR, its voltage output changes, and eventually the alarm will ring


# C Code 

```


int laserPin;
int laserPin_reg;
int sensorPin=0;
int sensorPin_reg;
int buttonPin=1;
int buttonPin_reg;
int buzzerPin=0;
int buzzerPin_reg;




 // Define alarmState as a bit of P1

int startTime = 0;
int alarmState = 0;


void main() 
{

   
    while (1) 
    {
        switch (alarmState) 
        {
            case 0:
                
                    laserPin = 1;
                    laserPin_reg=laserPin*4;
                    
                    asm volatile(
			"or x30, x30, %0\n\t"
			: 
			:"r"(laserPin_reg)//right end
			:"x30"
			);
               
                    asm volatile(
			"andi %0, x30, 0x01\n\t"
			:"=r"(sensorPin)
			:
			);
                    if (!sensorPin) 
                    {
                        alarmState = 1;
                        buzzerPin=1;
                        buzzerPin_reg=buzzerPin*8;
                       asm volatile(
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg)
                    	:"x30"
                    	);
                    }
                    
                            
                
                break;
            
            case 1:
            	
            	

               asm volatile(
			"andi %0, x30, 0x02\n\t"
			: "=r" (buttonPin)
			:
			:);
                if (!buttonPin) 
                {
                    alarmState = 0;
                    buzzerPin=0;
                    buzzerPin_reg = buzzerPin*8;
                    
                    asm volatile(
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg)
                    	:"x30"
                    	);
                    
                    
                }
                break;
        }
    }
}
```






# Assembly Code

```
alar1.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	ff010113          	add	sp,sp,-16
   4:	00812623          	sw	s0,12(sp)
   8:	01010413          	add	s0,sp,16

0000000c <.L10>:
   c:	000007b7          	lui	a5,0x0
  10:	0007a783          	lw	a5,0(a5) # 0 <main>
  14:	00078863          	beqz	a5,24 <.L2>
  18:	00100713          	li	a4,1
  1c:	10e78c63          	beq	a5,a4,134 <.L3>
  20:	fedff06f          	j	c <.L10>

00000024 <.L2>:
  24:	000007b7          	lui	a5,0x0
  28:	0007a783          	lw	a5,0(a5) # 0 <main>
  2c:	04079063          	bnez	a5,6c <.L5>
  30:	000007b7          	lui	a5,0x0
  34:	00100713          	li	a4,1
  38:	00e7a023          	sw	a4,0(a5) # 0 <main>
  3c:	000007b7          	lui	a5,0x0
  40:	00100713          	li	a4,1
  44:	00e7a023          	sw	a4,0(a5) # 0 <main>
  48:	000007b7          	lui	a5,0x0
  4c:	0007a783          	lw	a5,0(a5) # 0 <main>
  50:	00179713          	sll	a4,a5,0x1
  54:	000007b7          	lui	a5,0x0
  58:	00e7a023          	sw	a4,0(a5) # 0 <main>
  5c:	00ef6f33          	or	t5,t5,a4
  60:	000007b7          	lui	a5,0x0
  64:	00e7a023          	sw	a4,0(a5) # 0 <main>
  68:	12c0006f          	j	194 <.L4>

0000006c <.L5>:
  6c:	000007b7          	lui	a5,0x0
  70:	0007a703          	lw	a4,0(a5) # 0 <main>
  74:	3e700793          	li	a5,999
  78:	00e7ce63          	blt	a5,a4,94 <.L7>
  7c:	000007b7          	lui	a5,0x0
  80:	0007a783          	lw	a5,0(a5) # 0 <main>
  84:	00178713          	add	a4,a5,1
  88:	000007b7          	lui	a5,0x0
  8c:	00e7a023          	sw	a4,0(a5) # 0 <main>
  90:	1040006f          	j	194 <.L4>

00000094 <.L7>:
  94:	000007b7          	lui	a5,0x0
  98:	0007a783          	lw	a5,0(a5) # 0 <main>
  9c:	00479713          	sll	a4,a5,0x4
  a0:	000007b7          	lui	a5,0x0
  a4:	00e7a023          	sw	a4,0(a5) # 0 <main>
  a8:	001f7713          	and	a4,t5,1
  ac:	000007b7          	lui	a5,0x0
  b0:	00e7a023          	sw	a4,0(a5) # 0 <main>
  b4:	000007b7          	lui	a5,0x0
  b8:	0007a703          	lw	a4,0(a5) # 0 <main>
  bc:	000007b7          	lui	a5,0x0
  c0:	0007a783          	lw	a5,0(a5) # 0 <main>
  c4:	02e7de63          	bge	a5,a4,100 <.L8>
  c8:	000007b7          	lui	a5,0x0
  cc:	00100713          	li	a4,1
  d0:	00e7a023          	sw	a4,0(a5) # 0 <main>
  d4:	000007b7          	lui	a5,0x0
  d8:	00100713          	li	a4,1
  dc:	00e7a023          	sw	a4,0(a5) # 0 <main>
  e0:	000007b7          	lui	a5,0x0
  e4:	0007a783          	lw	a5,0(a5) # 0 <main>
  e8:	00279713          	sll	a4,a5,0x2
  ec:	000007b7          	lui	a5,0x0
  f0:	00e7a023          	sw	a4,0(a5) # 0 <main>
  f4:	00ef6f33          	or	t5,t5,a4
  f8:	000007b7          	lui	a5,0x0
  fc:	00e7a023          	sw	a4,0(a5) # 0 <main>

00000100 <.L8>:
 100:	000007b7          	lui	a5,0x0
 104:	0007a023          	sw	zero,0(a5) # 0 <main>
 108:	000007b7          	lui	a5,0x0
 10c:	0007a783          	lw	a5,0(a5) # 0 <main>
 110:	00179713          	sll	a4,a5,0x1
 114:	000007b7          	lui	a5,0x0
 118:	00e7a023          	sw	a4,0(a5) # 0 <main>
 11c:	00ef6f33          	or	t5,t5,a4
 120:	000007b7          	lui	a5,0x0
 124:	00e7a023          	sw	a4,0(a5) # 0 <main>
 128:	000007b7          	lui	a5,0x0
 12c:	0007a023          	sw	zero,0(a5) # 0 <main>
 130:	0640006f          	j	194 <.L4>

00000134 <.L3>:
 134:	000007b7          	lui	a5,0x0
 138:	0007a783          	lw	a5,0(a5) # 0 <main>
 13c:	00379713          	sll	a4,a5,0x3
 140:	000007b7          	lui	a5,0x0
 144:	00e7a023          	sw	a4,0(a5) # 0 <main>
 148:	00ef6f33          	or	t5,t5,a4
 14c:	000007b7          	lui	a5,0x0
 150:	00e7a023          	sw	a4,0(a5) # 0 <main>
 154:	000007b7          	lui	a5,0x0
 158:	0007a783          	lw	a5,0(a5) # 0 <main>
 15c:	02079a63          	bnez	a5,190 <.L11>
 160:	000007b7          	lui	a5,0x0
 164:	0007a023          	sw	zero,0(a5) # 0 <main>
 168:	000007b7          	lui	a5,0x0
 16c:	0007a023          	sw	zero,0(a5) # 0 <main>
 170:	000007b7          	lui	a5,0x0
 174:	0007a783          	lw	a5,0(a5) # 0 <main>
 178:	00279713          	sll	a4,a5,0x2
 17c:	000007b7          	lui	a5,0x0
 180:	00e7a023          	sw	a4,0(a5) # 0 <main>
 184:	00ef6f33          	or	t5,t5,a4
 188:	000007b7          	lui	a5,0x0
 18c:	00e7a023          	sw	a4,0(a5) # 0 <main>

00000190 <.L11>:
 190:	00000013          	nop

00000194 <.L4>:
 194:	e79ff06f          	j	c <.L10>
```


# Unique Instructions


```
Number of different instructions: 15
List of unique instructions:
lw
or
lui
and
add
bge
li
blt
beqz
sw
j
nop
sll
beq
bnez
```
