# ON-Demand-Traffic-Light-Control-AVR
- [Description](#Description)
- [System Layer architecture](#System-layer-architecture)
- [System Flowchart](#System-Flowchart)
- [IDE](#IDE)
- [Schematic capture](#Schematic-capture)
   - [Main Components](#Main-Component)
- [Demo](#Demo)
   - [Normal traffic light Mode](#Normal-traffic-light-Mode)
   - [Case 1](#Case-1)
   - [Case 2](#Case-2)
      - [During green led](#During-green-led)
      - [During yellow-led](#During-yellow-led)

## Description
This is Traffic light system to control and organize Traffic between  cars and human as traffic light normal flow happen (green then  yellow then red then yellow then green and repeat this flow) until  there are pedestrian want to cross road then will press button and  interrupt car traffic light (depend on case 1 and case 2) and pedestrian traffic light will flow until end then return to car traffic  light flow until any pedestrian press button.

## System Layer architecture 
<p align="center">
<img  src="https://user-images.githubusercontent.com/77234053/188304594-b3e37d23-4283-4700-8fbb-793c091c090c.png">
  </p>

## System Flowchart 
<p align="center">
<img src="https://user-images.githubusercontent.com/77234053/188304878-bf00f245-b752-433a-88f7-e689bd2d3c1e.png">
  </p>
  
## IDE
<p>Micrchip studio, Notepad++ and simulide</p>
<p>I use Microchip studio & Notpad++ for writting code</p>
<p>I use simulide to make simulation for project(easy to use and anyone can download without crack)</p>
<p>You can open project as If you have Microchip studio click on on_demand_traffic_light_control.atsln</p>

## Schematic Capture
<p align="center">
  <img src="https://user-images.githubusercontent.com/77234053/188305809-9b66014c-6ee4-41af-ace5-7d171ac651ba.png">
  </p>
  
### Main Component
- atmega32
- green, red and yellow leds
- resistor
- button
- LCD 16*2

## Demo
### Normal traffic light Mode
<p>Normal mode for car traffic light and this mode work until button pedestrian not pressed</p>
<p align= "center">
   <img src="https://user-images.githubusercontent.com/77234053/188307796-bda55e1d-4c92-490f-9a5a-9b0f1a491dfb.gif">
   </p>
  
### Case 1
<p>This case happen when red led car traffic light is on and at same time pedestrian button pressed and at the end of this case return to noraml mode again</p>
<p align="center">
   <img src="https://user-images.githubusercontent.com/77234053/188309473-7beecace-c07b-4248-b304-9615c6b56e80.gif">
   </p>
   
### case 2

#### During green led
<p>This case happen when green led car traffic light is on at same time pedestrian button presses and at the end of this case return to normal mode again </p>
<p align= "center">
   <img src = "https://user-images.githubusercontent.com/77234053/188309902-0aebddab-62f2-4ecd-a59a-65b7ede5299b.gif">
   </p>

#### During yellow led
