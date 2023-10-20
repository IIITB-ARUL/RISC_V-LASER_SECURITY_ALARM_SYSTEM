# RISC_V-SECURITY_ALARM_SYSTEM


In this project, we are going to design Laser Light Security System Using RISCV with Alarm with the application of Laser Diode Module KY-008. The project idea revolves around creating a security system. Whenever any object will obstruct the LASER ray the buzzer alarm will start ringing.

This project can be implemented anywhere, not only buildings or premises but many precious things like jewelry, diamonds, precious antique items in the museum, etc many other things are also secured using such an invisible LASER beam. Many people secure their home, office, shops, warehouses, etc with the LASER beam security system.


# Circuit Diagram
![alarmsystem](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/ce64a096-e601-49e6-afb8-408ac385ec39)

# Block Diagram

![Slide2](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/d22ac893-b6ab-48b0-aba6-9a505f05f88d)


# Working Principle

The project basically works on the principle of interruption. If by any means the LASER light is interrupted the alarm will start unless it is reset with push-button. The laser is a concentrated light source that puts out a straight beam of light of a single color

The LDR is sensitive to light and puts out a voltage when the laser light hits it. When the laser beam is interrupted and can’t reach LDR, its voltage output changes, and eventually the alarm will ring


# C Code 

```
int main() 
{

	
 int laserPin;
 int laserPin_reg;
 int sensorPin=0;
 int buttonPin=1;
 int buzzerPin=0;
 int buzzerPin_reg;
 int alarmState = 0;

   
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
out:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	fd010113          	add	sp,sp,-48
   10078:	02812623          	sw	s0,44(sp)
   1007c:	03010413          	add	s0,sp,48
   10080:	fe042423          	sw	zero,-24(s0)
   10084:	00100793          	li	a5,1
   10088:	fef42223          	sw	a5,-28(s0)
   1008c:	fe042023          	sw	zero,-32(s0)
   10090:	fe042623          	sw	zero,-20(s0)
   10094:	fec42783          	lw	a5,-20(s0)
   10098:	00078a63          	beqz	a5,100ac <main+0x38>
   1009c:	fec42703          	lw	a4,-20(s0)
   100a0:	00100793          	li	a5,1
   100a4:	04f70e63          	beq	a4,a5,10100 <main+0x8c>
   100a8:	fedff06f          	j	10094 <main+0x20>
   100ac:	00100793          	li	a5,1
   100b0:	fcf42c23          	sw	a5,-40(s0)
   100b4:	fd842783          	lw	a5,-40(s0)
   100b8:	00279793          	sll	a5,a5,0x2
   100bc:	fcf42a23          	sw	a5,-44(s0)
   100c0:	fd442783          	lw	a5,-44(s0)
   100c4:	00ff6f33          	or	t5,t5,a5
   100c8:	001f7793          	and	a5,t5,1
   100cc:	fef42423          	sw	a5,-24(s0)
   100d0:	fe842783          	lw	a5,-24(s0)
   100d4:	04079e63          	bnez	a5,10130 <main+0xbc>
   100d8:	00100793          	li	a5,1
   100dc:	fef42623          	sw	a5,-20(s0)
   100e0:	00100793          	li	a5,1
   100e4:	fef42023          	sw	a5,-32(s0)
   100e8:	fe042783          	lw	a5,-32(s0)
   100ec:	00379793          	sll	a5,a5,0x3
   100f0:	fcf42e23          	sw	a5,-36(s0)
   100f4:	fdc42783          	lw	a5,-36(s0)
   100f8:	00ff6f33          	or	t5,t5,a5
   100fc:	0340006f          	j	10130 <main+0xbc>
   10100:	002f7793          	and	a5,t5,2
   10104:	fef42223          	sw	a5,-28(s0)
   10108:	fe442783          	lw	a5,-28(s0)
   1010c:	02079663          	bnez	a5,10138 <main+0xc4>
   10110:	fe042623          	sw	zero,-20(s0)
   10114:	fe042023          	sw	zero,-32(s0)
   10118:	fe042783          	lw	a5,-32(s0)
   1011c:	00379793          	sll	a5,a5,0x3
   10120:	fcf42e23          	sw	a5,-36(s0)
   10124:	fdc42783          	lw	a5,-36(s0)
   10128:	00ff6f33          	or	t5,t5,a5
   1012c:	00c0006f          	j	10138 <main+0xc4>
   10130:	00000013          	nop
   10134:	f61ff06f          	j	10094 <main+0x20>
   10138:	00000013          	nop
   1013c:	f59ff06f          	j	10094 <main+0x20>
```


# Unique Instructions

```
Number of different instructions: 12
List of unique instructions:
beq
or
nop
li
j
and
sll
add
bnez
lw
sw
beqz


```



## Acknowledgements
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Chatgpt
- Emil Jayanth Lal,Colleague,IIIT B
- Shant Rakshit,Colleague,IIIT B
- Mayank Kabra,imtech

 ## Reference 
- https://github.com/SakethGajawada/RISCV-GNU
