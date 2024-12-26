
# Pioneer DJ CDJ-1000MK1 SPI

This repository documents the SPI communication between the Main Assembly and the Display Assembly of the Pioneer DJ CDJ-1000MK1.

The communication between the CDJ main assy and the dislay assy is over SPI running at 1Mhz, MODE3, LSB First
There is no CS line between the master and the salve, but rather a Busy signal from the slave to the master - it's Active Low - and you need to wait until it goes high to send data.

Data signals can be found here:
[spi_signals](/resources/cdj_1000_component_map-spi_pins.png)

Each data sequence contains 12 frames.
Each frame contains 12 bytes, where the 1st byte of each frame indicates the frame number in the sequence, and the last byte is a CRC (Byte0+Byte1+...Byte9+Byte10%256)

For each frame sent to the display assy, a 12 byte response is ent back
The response back is a single 12 byte frame and is repeated for every message sent to the display control unit - regarless of index.

Timing is crucial. At least 50nS between each is required - I've found 200nS to be the stable number
And at least 2300uS between each frame.

[spi_signals](/resources/cdj1000_mk1_logic_analyzer.png)


## Main Assy to Display Assy

### Data Table
|Frame|Byte 0|Byte 1|Byte 2| Byte 3|Byte 4|Byte 5|Byte 6|Byte 7|Byte 8|Byte 9|Byte 10|Byte 11|
|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| 1 |  0x1| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | CRC |
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





### Itemized Communication
| Item | Frame |  Byte| Bit | Bit Mask |
|--|--|--|--|--|--|
| PLAY  |  |  |  | 0x00 | 
| CUE  |  |  |  | 0x00 | 
| Loop IN  |  |  |  | 0x00 | 
| Loop OUT  |  |  |  | 0x00 | 
| Loop Exit  |  |  |  | 0x00 | 
| Tempo Range  |  |  |  | 0x00 | 
| Tempo Lock  |  |  |  | 0x00 | 
| Tempo Reset  |  |  |  | 0x00 | 
| Play Direction  |  |  |  | 0x00 | 
| Eject  |  |  |  | 0x00 | 
| CUE A  |  |  |  | 0x00 | 
| CUE B  |  |  |  | 0x00 | 
| CUE C  |  |  |  | 0x00 | 
| CUE Rec  |  |  |  | 0x00 | 
| Lock  |  |  |  | 0x00 | 
| Lock  |  |  |  | 0x00 | 
| Lock  |  |  |  | 0x00 | 


Item

Frame

Byte

Bit

## Display Assy to Main Assy

### Data Table
For every frame that is sent from the main assy, a response is sent back indicating the state of each button and potentiomenters.
The Jog wheen data and the Tempo pitch control data are not sent here, as they are wired directly to the main assy

|Frame|Byte 0|Byte 1|Byte 2| Byte 3|Byte 4|Byte 5|Byte 6|Byte 7|Byte 8|Byte 9|Byte 10|Byte 11|Byte 12|
|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
| 1 | ??| ?? | ?? | ?? | ?? | ?? | ?? | ?? | ?? | TOUCH/BREAK | RELEAE/START | ?? | CRC |


### Itemized Communication

| Item | Frame |  Byte| Bit | Bit Mask |
|--|--|--|--|--|--|
| PLAY  |  |  |  | 0x00 | 
| CUE  |  |  |  | 0x00 | 
| Loop IN  |  |  |  | 0x00 | 
| Loop OUT  |  |  |  | 0x00 | 
| Loop Exit  |  |  |  | 0x00 | 
| Tempo Range  |  |  |  | 0x00 | 
| Tempo Lock  |  |  |  | 0x00 | 
| Tempo Reset  |  |  |  | 0x00 | 
| Play Direction  |  |  |  | 0x00 | 
| Eject  |  |  |  | 0x00 | 
| CUE A  |  |  |  | 0x00 | 
| CUE B  |  |  |  | 0x00 | 
| CUE C  |  |  |  | 0x00 | 
| CUE Rec  |  |  |  | 0x00 | 
| Lock  |  |  |  | 0x00 | 
| Lock  |  |  |  | 0x00 | 
| Lock  |  |  |  | 0x00 | 