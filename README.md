
# Pioneer DJ CDJ-1000MK1 SPI

This repository documents the SPI communication between the Main Assembly and the Display Assembly of the Pioneer DJ CDJ-1000MK1.

I do not need the main VDF display or Jog wheel VFD display, and therefore their control parameters are not logged here.

The communication between the CDJ main assy and the dislay assy is over SPI running at 1Mhz, MODE3, LSB First
There is no CS line between the master and the salve, but rather a Busy signal from the slave to the master - it's Active Low - and you need to wait until it goes high to send data.

Data signals can be found here:
![spi signals](/resources/cdj_1000_component_map-spi_pins.png)

Each data sequence contains 12 frames.
Each frame contains 12 bytes, where the 1st byte of each frame indicates the frame number in the sequence, and the last byte is a CRC. 

``CRC = (Byte0+Byte1+...Byte9+Byte10)%256``


For each frame sent to the display assy, a 12 byte response is sent back
The response back is a single 12 byte frame and is repeated for every message sent to the display control unit - regarless of index.

Timing is crucial. At least ``50μs`` between each byte is required - I've found ``200μs`` to be the stable number
And at least ``2300μs`` between each frame, I personally use ``3000μs``

![spi la](/resources/cdj1000_mk1_logic_analyzer.png)


In the /examples folder you will find a test sketch for a Teensy 4.x using the standard SPI library and pins to control/read the display assy and will turn all the LEDs on, as well as print out frames of button statuses.
![cdj leds on](/resources/CDJ1000_mk1_leds_on.jpeg)
**NOTE #1** -  The display assy uses 5 volt logic, and therefore a 5v to 3.3v logic level shifter is required!!
**NOTE #2** - The image above is MK1 PCBs with an MK2 case - I cannot guarentee that this will work on an MK2. And if you're after an MK3 then [look here](https://github.com/djgreeb/CDJ-1000mk3_new_life_project/blob/master/Reverse%20Engineering%20Pioneer%20CDJ-1000%20serial%20protocol.pdf)

</br>
</br>

## Main Assy to Display Assy

### Data Table
| Frame | Byte 0 | Byte 1 | Byte 2 | Byte 3 | Byte 4 | Byte 5 | Byte 6 | Byte 7 | Byte 8 | Byte 9 | Byte 10 | Byte 11 |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| 1 |  0x1 | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 2 |  0x2| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 3 |  0x3| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 4 |  0x4| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 5 |  0x5| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 6 |  0x6| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 7 |  0x7| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 8 |  0x8| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 9 |  0x9| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | LED CTRL |CRC |
| 10 |  0xA| LED CTRL | LED CTRL | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 11 |  0xB| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
| 12 |  0xC| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |





### LED Control
| Item | Frame |  Byte| Bit | Bit Mask |
|---|---|---|---|---|
| Jog mode CDJ LED | 10 | 9 |  | 0x80 |
| Master Tempo LED | 10 | 9 |  | 0x20 | 
| Tempo Reset LED  | 10 | 9 |  | 0x10 | 
| SD CARD LED  | 10 | 9  |  | 0x08 |
| CUE  LED| 10 | 9  |  | 0x04 | 
| PLAY LED| 10 | 9 |  | 0x02 | 
| Direction  LED| 10| 9 |  | 0x01 | 
| Loop OUT LED | 11 | 1 |  | 0x80 | 
| Loop IN  LED| 11 | 1 |  | 0x40 | 
| CUE C LED GREEN | 11 | 1 |  | 0x20 |
| CUE C LED RED | 11 | 1 |  | 0x10 | 
| CUE B LED GREEN | 11 | 1 |  | 0x08 |
| CUE B LED RED | 11 | 1 |  | 0x04 | 
| CUE A LED GREEN | 11 | 1 |  | 0x02 |
| CUE A LED RED | 11 | 1 |  | 0x01 | 
| Jog mode CDJ LED | 11 | 2 |  | 0x01 | 


 
 


</br>
</br>
</br>
</br>


## Display Assy to Main Assy

### Data Table
For every frame that is sent from the main assy, a response is sent back indicating the state of each button and potentiomenters.
The Jog wheen data and the Tempo pitch control data are not sent here, as they are wired directly to the main assy

| Frame | Byte 0 | Byte 1 | Byte 2 | Byte 3 | Byte 4 | Byte 5 | Byte 6 | Byte 7 | Byte 8 | Byte 9 | Byte 10 | Byte 11 |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | ??| ?? | ?? | ?? | ?? | ?? | ?? | ?? | TOUCH/BREAK | RELEAE/START | ?? | CRC |


### Panel outputs

| Item |  Byte| Bit | Bit Mask |
|---|---|---|---|
| PLAY  |  |  | 0x00 | 
| Track  FWD  |  |  | 0x00 | 
| Track  BWD  |  |  | 0x00 | 
| Track Search FWD  |  |  | 0x00 | 
| Track Search BWD  | 2 |  | 0x10 | 
| CUE  | 3 |  | 0x40 | 
| CUE A  | 4 |  | 0x80 | 
| CUE B  | 4 |  | 0x40 | 
| CUE C  | 4 |  | 0x20 | 
| CUE Rec  | 4 |  | 0x10 | 
| Time mode  | 4 |  | 0x08 | 
| CD Text/Wave |  |  | 0x00 | 
| Loop IN  | 5 |  | 0x80 | 
| Loop OUT  | 5 |  | 0x40 |
| Loop Reloop/Exit | 5 |  | 0x20 | 
| Wave Search BWD | 5 |  | 0x10 | 
| Call Search BWD | 5 |  | 0x08 |
| Memory | 5 |  | 0x04 | 
| Delete | 5 |  | 0x02 | 
| Wave Search FWD | 6 |  | 0x02 | 
| Call Search FWD | 6 |  | 0x01 | 
| Tempo Range  | 6 |  | 0x80 | 
| Master Tempo | 6 |  |  | 0x40 | 
| Tempo Reset | 6 |  | 0x20 | 
| Eject  | 6 |  | 0x10 | 
| Jog Mode  | 6 |  | 0x04 |  
| Play Direction  | 7 |  | 0x01 |
| Lock | 7 |  | 0x02 |  
| TOUCH/BREAK  | 8 | -- | 0-254 | 
| RELEASE/START  | 9 | -- | 0-254 | 




