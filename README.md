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

	
 
 int sensorPin;
 int buttonPin;
	
 int laserPin=1;
 int laserPin_reg;
 
 int buzzerPin=0;
 int buzzerPin_reg;

 int alarmState = 0;
 int mask1 = 0xFFFFFFFB;
 int mask2 = 0xFFFFFFF7;
   
    while (1) 
    {
        switch (alarmState) 
        {
            case 0:
                
                    laserPin = 1;
                    laserPin_reg=laserPin*4;
                    
                    asm volatile(
                    	"and x30,x30, %1\n\t"
			"or x30, x30, %0\n\t"
			: 
			:"r"(laserPin_reg),"r"(mask1)//right end
			:"x30"
			);
               
                    asm volatile(
			"andi %0, x30, 0x01\n\t"
			:"=r"(sensorPin)
			:
			:
			);
                    if (sensorPin==0) 
                    {
                        alarmState = 1;
                        buzzerPin=1;
                        buzzerPin_reg=buzzerPin*8;
                       asm volatile(
                       	"and x30,x30,%1\n\t"
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg),"r"(mask2)
                    	:"x30"
                    	);
                    }
                     else
                    {
                    buzzerPin=0;
                        buzzerPin_reg=buzzerPin*8;
                       asm volatile(
                       	"and x30,x30,%1\n\t"
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg),"r"(mask2)
                    	:"x30"
                    	);
                    	
                    }
                            
                
                break;
            
            case 1:
            	
            	

               asm volatile(
			"andi %0, x30, 0x02\n\t"
			: "=r" (buttonPin)
			:
			:
			);
                if (buttonPin) 
                {
                    alarmState = 0;
                    buzzerPin=0;
                    buzzerPin_reg = buzzerPin*8;
                    
                    asm volatile(
                    	"and x30,x30,%1\n\t"
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg),"r"(mask2)
                    	:"x30"
                    	);
                    
                    
                }
                
                 else //buttonpin = 0 in the start
                {
                	
                    alarmState = 1;
                    buzzerPin=1;
                    buzzerPin_reg = buzzerPin*8;
                    
                    asm volatile(
                    	"and x30,x30,%1\n\t"
                    	"or x30,x30,%0\n\t"
                    	:
                    	:"r"(buzzerPin_reg),"r"(mask2)
                    	:"x30"
                    	);
                    	
                    	
                    	
                }
                break;
        }
    }
}
```


# Spike Results

```
x30[3:0] --> GPIO pins 
x30[0] --> sensor pin (detects the object[0 or1])
x30[1] --> button pin (turns the buzzer on or off)
x30[2] --> laser pin (always on)
x30[3] --> buzzer pin (goes on when sensorpin = 0 / goes off when sensorpin = 1)
```



```
input x30[1:0] -->01  output x30[3:2] --> 01 -->masked output -->1000
input x30[1:0] -->00  output x30[3:2] --> 11 -->masked output -->1100
input x30[1:0] -->10  output x30[3:2] --> 11 -->masked output -->1100
```

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out test2.c 
spike pk out
```

Here the alarmstate is initially set to zero and the laser is always turned on.Now the sensor is set to zero(sensorPin=0) which denotes some object is detected.Now the alarmstate is set to 1and the buzzer is turned on.Then it checks for the buttonPin.here the buttonPin is 1 which makes the buzzer go off and the alarmstate is set to zero(alarmstate=0).

![spike1](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/57848571-2f8f-4985-a2ae-e0767a664eef)


Now the sensor is set to one (sensorPin=1) no object is detected the buzzer remains off.Here it does not check for the button pin.

![spike2](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/e13a09d4-6f6b-4328-b32a-a711cabe468d)






# Assembly Code


code conversion:

```
riscv64-unknown-elf -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o out alar1.c
riscv64-unknown-elf-objdump -d -r out > asm.txt
```

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fc010113          	addi	sp,sp,-64
   10058:	02812e23          	sw	s0,60(sp)
   1005c:	04010413          	addi	s0,sp,64
   10060:	00100793          	li	a5,1
   10064:	fef42423          	sw	a5,-24(s0)
   10068:	fe042223          	sw	zero,-28(s0)
   1006c:	fe042623          	sw	zero,-20(s0)
   10070:	ffb00793          	li	a5,-5
   10074:	fef42023          	sw	a5,-32(s0)
   10078:	ff700793          	li	a5,-9
   1007c:	fcf42e23          	sw	a5,-36(s0)
   10080:	fec42783          	lw	a5,-20(s0)
   10084:	00078a63          	beqz	a5,10098 <main+0x44>
   10088:	fec42703          	lw	a4,-20(s0)
   1008c:	00100793          	li	a5,1
   10090:	08f70863          	beq	a4,a5,10120 <main+0xcc>
   10094:	fedff06f          	j	10080 <main+0x2c>
   10098:	00100793          	li	a5,1
   1009c:	fef42423          	sw	a5,-24(s0)
   100a0:	fe842783          	lw	a5,-24(s0)
   100a4:	00279793          	slli	a5,a5,0x2
   100a8:	fcf42c23          	sw	a5,-40(s0)
   100ac:	fd842783          	lw	a5,-40(s0)
   100b0:	fe042703          	lw	a4,-32(s0)
   100b4:	00ef7f33          	and	t5,t5,a4
   100b8:	00ff6f33          	or	t5,t5,a5
   100bc:	001f7793          	andi	a5,t5,1
   100c0:	fcf42a23          	sw	a5,-44(s0)
   100c4:	fd442783          	lw	a5,-44(s0)
   100c8:	02079a63          	bnez	a5,100fc <main+0xa8>
   100cc:	00100793          	li	a5,1
   100d0:	fef42623          	sw	a5,-20(s0)
   100d4:	00100793          	li	a5,1
   100d8:	fef42223          	sw	a5,-28(s0)
   100dc:	fe442783          	lw	a5,-28(s0)
   100e0:	00379793          	slli	a5,a5,0x3
   100e4:	fcf42823          	sw	a5,-48(s0)
   100e8:	fd042783          	lw	a5,-48(s0)
   100ec:	fdc42703          	lw	a4,-36(s0)
   100f0:	00ef7f33          	and	t5,t5,a4
   100f4:	00ff6f33          	or	t5,t5,a5
   100f8:	0900006f          	j	10188 <main+0x134>
   100fc:	fe042223          	sw	zero,-28(s0)
   10100:	fe442783          	lw	a5,-28(s0)
   10104:	00379793          	slli	a5,a5,0x3
   10108:	fcf42823          	sw	a5,-48(s0)
   1010c:	fd042783          	lw	a5,-48(s0)
   10110:	fdc42703          	lw	a4,-36(s0)
   10114:	00ef7f33          	and	t5,t5,a4
   10118:	00ff6f33          	or	t5,t5,a5
   1011c:	06c0006f          	j	10188 <main+0x134>
   10120:	002f7793          	andi	a5,t5,2
   10124:	fcf42623          	sw	a5,-52(s0)
   10128:	fcc42783          	lw	a5,-52(s0)
   1012c:	02078663          	beqz	a5,10158 <main+0x104>
   10130:	fe042623          	sw	zero,-20(s0)
   10134:	fe042223          	sw	zero,-28(s0)
   10138:	fe442783          	lw	a5,-28(s0)
   1013c:	00379793          	slli	a5,a5,0x3
   10140:	fcf42823          	sw	a5,-48(s0)
   10144:	fd042783          	lw	a5,-48(s0)
   10148:	fdc42703          	lw	a4,-36(s0)
   1014c:	00ef7f33          	and	t5,t5,a4
   10150:	00ff6f33          	or	t5,t5,a5
   10154:	0300006f          	j	10184 <main+0x130>
   10158:	00100793          	li	a5,1
   1015c:	fef42623          	sw	a5,-20(s0)
   10160:	00100793          	li	a5,1
   10164:	fef42223          	sw	a5,-28(s0)
   10168:	fe442783          	lw	a5,-28(s0)
   1016c:	00379793          	slli	a5,a5,0x3
   10170:	fcf42823          	sw	a5,-48(s0)
   10174:	fd042783          	lw	a5,-48(s0)
   10178:	fdc42703          	lw	a4,-36(s0)
   1017c:	00ef7f33          	and	t5,t5,a4
   10180:	00ff6f33          	or	t5,t5,a5
   10184:	00000013          	nop
   10188:	ef9ff06f          	j	10080 <main+0x2c>
```



# Unique Instructions

```
Number of different instructions: 13
List of unique instructions:
lw
slli
j
andi
beqz
nop
and
sw
or
addi
beq
bnez
li



```




# Functional Verification on using GTKWave Simulation
Here we  will verify all the outputs with waveform for all the possible input combinations.
```
x30[0] --> sensor pin 
x30[1] --> button pin 
x30[2] --> laser pin 
x30[3] --> buzzer pin
```

In the below image you can see the input_wires[1:0]={buttonPin,sensorPin} and output_wires[1:0]={buzzerPin,laserPin(always high)}.

In the first case the ```input_wires-->00``` As explained earlier buzzer goes on when sensorPin is low, ```output_wires-->11``` .Now only buzzer goes off when button pin goes high.You can clearly see that ```input_wires-->01``` Eventhough sensorPin is high buzzer is still on.

![Fvcase1](https://github.com/IIITB-ARUL/RISC_V-SECURITY_ALARM_SYSTEM/assets/140998631/241695b8-688d-4db0-ade5-e566c8c0166b)


Now in the next case ```input_wires-->10``` .Here the sensorPin is low first and then buttonPin is high. So the buzzer goes on first and once the buttonPin is high it goes off.We can infer from the waveform the output keeps changing ```output_wires-->11-->01-->11--01-->.....```




## Acknowledgements
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Chatgpt
- Emil Jayanth Lal,Colleague,IIIT B
- Shant Rakshit,Colleague,IIIT B
- Mayank Kabra,imtech

 ## Reference 
- https://github.com/SakethGajawada/RISCV-GNU
