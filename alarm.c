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

