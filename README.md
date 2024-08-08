<div align="center">
    <img src="readme-assets/logo.png" alt="logo" width="250"/>
    <h1>Bincture</h1>
</div>
<h4 align="center">Tiny CLI binary data visualization tool.</h4>
<!--<div align="center">-->
<!--    <img alt="GitHub last commit" src="https://img.shields.io/badge/made_with-love-red">-->
<!--</div>-->

## 🖼 Examples
|Half-Life01.mp3 (24-bit) | ELF binary (8-bit) | shell32.dll.mun (32-bit) | tui.c (24-bit) | secret.docx (16-bit)
|-|-|-|-|-|
|<img src="readme-assets/example1.png" alt="Half-Life01.mp3 visualization" width="200"> | <img src="readme-assets/example2.png" alt="Visualization of the bincture's ELF binary" width="200"> | <img src="readme-assets/example3.png" alt="shell32.dll.mun visualization" width="200"> | <img src="readme-assets/example4.png" alt="tui.c visualization" width="100"> |<img src="readme-assets/example5.png" alt="gl finding out the secret" width="100">

## ❓ Where and why to use it
This application can be used to find hidden bitmaps within binary files and to analyze the file structure. With this tool, you can find code density, ASCII character blocks, and more. I primarily see this tool being used for educational purposes, helping users better understand the structure of binary files.

## ✨ Features
* Visualization can be saved with different bits per pixel value.
* Executable itself is tiny and takes up <100 kb of storage.
* Massive files are visualized in a matter of seconds.

*Fun fact: The logo and icons were made in the Windows 98 style.*

## 💿 Installation
Download the portable application from [release page](https://github.com/Makzzzimus/bincture/releases/) and launch. No installation is required. 
Note: pallette.txt is required to run 8-bit visualizations. It can be found [here](https://github.com/Makzzzimus/bincture/blob/main/pallette.txt)

Sorry, no build for macOS. But you can try to compile from the source.
## 🧱 Building from source
### On Linux 🐧
Make sure GCC and Make are installed before proceeding.

Enter the following command in the terminal while inside the source directory:
```
make
```
Application was dropped to the newly created bin folder in the same directory
### On Windows 🎴
Make sure MinGW-w64 toolchain is installed and added to environmental variables before proceeding.

Enter the following command in the terminal while inside the source directory:
```
mingw32-make
```
Executable was dropped to the newly created bin folder in the same directory

## 📝 License
This project is licensed under the terms of the GNU General Public License v2.0. See the [LICENSE](https://github.com/Makzzzimus/bincture/blob/main/LICENSE.md) file for details

## 📑 Credits
### 🎇 Inspiration
* This application was inspired by some YouTube videos that showcased binary visualizations of different executables using this repo: [Binary Waterfall](https://github.com/nimaid/binary-waterfall/).

### 📚 External libraries used
* This project uses [conio](https://github.com/thradams/conio) library which is licensed under MIT license.

## 🌟Future of the project
From the start of development, this project was planned as a tiny toy to get in touch with the C programming language and low-level development overall. Indeed, **this project isn't meant for professional or day-to-day use**. But still, I would appreciate all feedback and repo stars! As a toy project **it isn't planned to receive any future updates**. Despite this, I have some ideas for new features and overall improvements. Maybe someday, I will return to the project, update it, or completely rewrite it from scratch.