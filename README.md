# Wiiero-vita

Port of [Wiiero](http://wiiero.free.fr) for the Playstation Vita 

## This game is multiplayer only, it requires 2 controllers to play, so it will only work on a PS TV or [Vita3K](https://vita3k.org/).

Wiiero is a clone of Liero specially originally developed for Wii.
Liero is a PvP game between two worms armed with heavy weapons of all kinds battling in underground caves.
Wiiero is composed of 3 game modes: Deathmatch, Capture the flag and game of tag.
In the wiiero world, players are able to fight with the original Liero weapons ( there are basically thirty of them) or add the twenty more or less harmful new ones.

## Screenshots

![Wiiero-vita screenshot1](https://i.imgur.com/2zr78QR.png)
![Wiiero-vita screenshot2](https://i.imgur.com/juqEoTp.png)

## Installation
1. Download the .vpk and data files from the [release section](https://github.com/Grzybojad/wiiero-vita/releases).
2. Install the .vpk on your vita.
3. Copy the audio, lang, music and sprites folders to ux0:/data/wiiero (create the wiiero folder there).

## Building

1. To build wiiero-vita you'll need to intsall [VitaSDK](https://github.com/vitasdk/vdpm) first.
2. Run `make` and compress the `param.sfo`, `eboot.bin` and `sce_sys` folder into a .vpk file.
3. Install the .vpk on your vita.
4. Copy the audio, lang, music and sprites folders to ux0:/data/wiiero (create the wiiero folder there).

## Super special thanks
* [Rinnegatamante](https://github.com/Rinnegatamante/) for the huge support with this port, without him I would never be able to get this to work.

## Regular special thanks

* Joosa Riekkinen (Liero Developer)
* Luca Denevolo (Wiiero Developer)
* Every VitaSDK contributor
* [SDL-vita](https://github.com/Rinnegatamante/SDL-Vita) contributors
* [rsn-8887](https://github.com/rsn8887/SDL-Vita) for additional SDL-vita help
* HENkaku Discord community for the development help