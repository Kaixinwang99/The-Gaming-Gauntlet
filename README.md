# The Gaming Gauntlet
University of Glasgow ENG5220: Real Time Embedded Programming Team Project

<!-- PROJECT SHIELDS -->

<!-- PROJECT LOGO -->
<br />

<p align="center">
  <a href="https://github.com/Kaixinwang99/The-Gaming-Gauntlet/">
    <img src="images/logo.jpeg" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">"The Gaming Gauntlet</h3>
  <p align="center">
    A new generation controller
    <br />
    <a href="https://github.com/Kaixinwang99/The-Gaming-Gauntlet/"><strong>Get to know our gaming gauntlet »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Kaixinwang99/The-Gaming-Gauntlet/">Demo</a>
    ·
    <a href="https://github.com/Kaixinwang99/The-Gaming-Gauntlet/issues">Report Bug</a>
    ·
    <a href="https://github.com/Kaixinwang99/The-Gaming-Gauntlet/issues">Add new feature</a>
  </p>

</p>

## Social Media
 
 [![instagram](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a5/Instagram_icon.png/128px-Instagram_icon.png)](https://www.instagram.com/gaminggountlet/)
 [![twitter](https://cdn.iconscout.com/icon/free/png-128/twitter-203-493159.png)](https://twitter.com/GamingGountlet)
 [![youtube](https://github.com/Kaixinwang99/The-Gaming-Gauntlet/tree/main/images/hd-youtube-logo-png-transparent-background-20.png)](https://www.youtube.com/channel/UCEDrEHumIzCC4Mwqvb8Ef9w)
 
## Table of Contects
- [Introduction](#Introduction)
  - [Compatible-Games-and-keys](#Compatible-Games-and-Keys)
- [Installing](#Installing)  
  - [Configuration-Requirements](#Configuration-Requirements)
  - [Install-steps](#Install-steps)
- [Software-Documentation](#Software-Documentation)
- [Usage](#Usage)  
- [Project-Architecture](#Project-Architecture)
- [Contributing](#Contributing)
- [Version-Control](#Version-Control)
- [License](#License)
- [Acknowledgements](#Acknowledgements)

### Introduction 
The Gaming Gauntlet is the new generation of videogame controllers that aims to show the world a new way for people interact with consoles.

###### Compatible-Games-and-Keys
<b>Super Mario Bros pc - NES</b>
|Controller Key|Glove Commands|
|--------------|--------------|
| Jump | Thumb and index finger together |
| Move Left/Right | Rotate wrist left/right |
| Special Ability | Ring winger and thumb together |


<b>Mario Kart pc - NES</b>
|Controller Key|Glove Commands|
|--------------|--------------|
| Left/Right (A/S) | Move hand in front of the screen |
| Drift | Thumb and index finger together  |
| Object | Thumb and middle finger |
    

### Installing

###### Configuration-Requirements

For setting up the raspberry pi as a gaming controller it is necessary to create and deploy a report descriptor that tells the PC that it is an HID 'a controller', for doing this we used the open-sourced milador raspberry_py joystick for 8 buttons that can be found [here](https://github.com/milador/RaspberryPi-Joystick/tree/master/8_Buttons_Joystick)

###### Install-steps

1. Clone the repo

```sh
git clone https://github.com/Kaixinwang99/The-Gaming-Gauntlet.git
```
### Software-Documentation
https://kaixinwang99.github.io/The-Gaming-Gauntlet/

### Usage
```sh
cd The-Gaming-Gauntlet
mkdir build
cd build
cmake ..
make 
./Gauntlet
```


### Contributing

The project is built by a team from MSc student in University of Glasgow
* [Kaixin Wang](https://github.com/Kaixinwang99) 
* [Abhijith Vajjal Sampathkrishna](https://github.com/ajsampathk) 
* [Natalia Ibagon](https://github.com/nibagon) 
* [Marycarmen Flores Lopez](https://github.com/marycarmen1999) 

Further information is found on our Wiki Page: [Project Authors and Individual Contributions](https://github.com/Kaixinwang99/The-Gaming-Gauntlet/wiki/Project-Authors-and-Individual-Contributions).


### Version-Control

This project is using Git to control the version, you can check the repository to see the avilabe version


### License

GNU General Public License v3.0

### Acknowledgements
We scincerely thank the following faculty of the University of Glasgow for helping and guiding us through this project
* Bernd Porr
* Thomas O'Hara
* Nick Bailey
