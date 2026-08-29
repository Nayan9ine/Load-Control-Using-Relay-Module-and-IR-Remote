# Load-Control-Using-Relay-Module-and-IR-Remote
Created a load control system in which load connected to relay module is turned ON or OFF on entering a password with IR based remote.Built on arduin UNO R3 clone using CH340 chip.
<br>
<img width="1116" height="628" alt="image" src="https://github.com/user-attachments/assets/c37c8031-149f-4ed6-9f4a-a2ae66c77b9f" />
<br>
Used IRremote library by Shhirrif.The library can detect numerous protocols used for communication by IR.Standard rgb light control Remote was used that uses NEC protocol.IR receiver was salvaged off from old dish tv setup box . Has 3 pins with signal,gnd,power starting from left to right respectively. The library helped identify signal protocol and command code for each button pressed. 
<br>
<img width="1137" height="639" alt="image" src="https://github.com/user-attachments/assets/e85a53d6-4822-4038-9c3f-eef992fe7c7d" />
<br>
2 passwords declared in code one to turn relay on and other to turn off. Delay() of any value was causing timing issue hence leading to frozen response of lcd or ir. Baud rate of 115200 was utilized. Code only uploads when set back to 9600 for some reason and then turned back to 115200(I think it has something to do with CH340 chip). Millis() was used to debounce the buttons. LCD with I2C used to show the status of relay and password entered. Backlight pins connected with 220ohm resistor and also LCD was supplied with separate 5v to reduce current draw. 

