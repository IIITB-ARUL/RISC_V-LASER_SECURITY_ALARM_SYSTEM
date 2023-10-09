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


int laserPin;
int laserPin_reg;
int sensorPin=0;
int sensorPin_reg;
int buttonPin=1;
int buttonPin_reg;
int buzzerPin=0;
int buzzerPin_reg;




 
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
			:"r"(laserPin_reg)
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

00010094 <main>:
   10094:	ff010113          	add	sp,sp,-16
   10098:	00812623          	sw	s0,12(sp)
   1009c:	01010413          	add	s0,sp,16
   100a0:	8241a783          	lw	a5,-2012(gp) # 1117c <alarmState>
   100a4:	00078863          	beqz	a5,100b4 <main+0x20>
   100a8:	00100713          	li	a4,1
   100ac:	06e78263          	beq	a5,a4,10110 <main+0x7c>
   100b0:	ff1ff06f          	j	100a0 <main+0xc>
   100b4:	000117b7          	lui	a5,0x11
   100b8:	00100713          	li	a4,1
   100bc:	14e7ae23          	sw	a4,348(a5) # 1115c <laserPin>
   100c0:	000117b7          	lui	a5,0x11
   100c4:	15c7a783          	lw	a5,348(a5) # 1115c <laserPin>
   100c8:	00279713          	sll	a4,a5,0x2
   100cc:	80e1a423          	sw	a4,-2040(gp) # 11160 <laserPin_reg>
   100d0:	8081a783          	lw	a5,-2040(gp) # 11160 <laserPin_reg>
   100d4:	00ff6f33          	or	t5,t5,a5
   100d8:	001f7713          	and	a4,t5,1
   100dc:	80e1a623          	sw	a4,-2036(gp) # 11164 <sensorPin>
   100e0:	80c1a783          	lw	a5,-2036(gp) # 11164 <sensorPin>
   100e4:	06079263          	bnez	a5,10148 <main+0xb4>
   100e8:	00100713          	li	a4,1
   100ec:	82e1a223          	sw	a4,-2012(gp) # 1117c <alarmState>
   100f0:	00100713          	li	a4,1
   100f4:	80e1ac23          	sw	a4,-2024(gp) # 11170 <buzzerPin>
   100f8:	8181a783          	lw	a5,-2024(gp) # 11170 <buzzerPin>
   100fc:	00379713          	sll	a4,a5,0x3
   10100:	80e1ae23          	sw	a4,-2020(gp) # 11174 <buzzerPin_reg>
   10104:	81c1a783          	lw	a5,-2020(gp) # 11174 <buzzerPin_reg>
   10108:	00ff6f33          	or	t5,t5,a5
   1010c:	03c0006f          	j	10148 <main+0xb4>
   10110:	002f7713          	and	a4,t5,2
   10114:	000117b7          	lui	a5,0x11
   10118:	14e7ac23          	sw	a4,344(a5) # 11158 <buttonPin>
   1011c:	000117b7          	lui	a5,0x11
   10120:	1587a783          	lw	a5,344(a5) # 11158 <buttonPin>
   10124:	02079663          	bnez	a5,10150 <main+0xbc>
   10128:	8201a223          	sw	zero,-2012(gp) # 1117c <alarmState>
   1012c:	8001ac23          	sw	zero,-2024(gp) # 11170 <buzzerPin>
   10130:	8181a783          	lw	a5,-2024(gp) # 11170 <buzzerPin>
   10134:	00379713          	sll	a4,a5,0x3
   10138:	80e1ae23          	sw	a4,-2020(gp) # 11174 <buzzerPin_reg>
   1013c:	81c1a783          	lw	a5,-2020(gp) # 11174 <buzzerPin_reg>
   10140:	00ff6f33          	or	t5,t5,a5
   10144:	00c0006f          	j	10150 <main+0xbc>
   10148:	00000013          	nop
   1014c:	f55ff06f          	j	100a0 <main+0xc>
   10150:	00000013          	nop
   10154:	f4dff06f          	j	100a0 <main+0xc>

```


# Unique Instructions

```
Number of different instructions: 13
List of unique instructions:
and
nop
beq
lui
j
or
lw
sw
beqz
sll
add
bnez
li
```



## Acknowledgements
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Skywater Foundry
- Chatgpt
- Emil Jayanth Lal,Colleague,IIIT B
- Shant Rakshit,Colleague,IIIT B
- Mayank Kabra,imtech

 ## Reference 


- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://github.com/SakethGajawada/RISCV-GNU
