# Linux configuration
This repository contains my personal configuration of Linux used with i3 windows manager.

It contains:
* .bashrc simple settings
* vim configuration with plugins for c, python and vhdl
* i3 configuration with i3blocks

## Prerequisites
Vim plugins doesn't need any other program except for vim itself.
For i3 windows manager some application and fonts need to be installed.
You can follow the guide for basic i3 configuration settings here https://youtu.be/8-S0cWnLBKg and here ([setupi3]).  
Everything I did, except few modification, are well explained there.
Install all the software and font in that guide.

## Bashrc
It contains my shell layout, set vim as default editor, plus contains some alias of some application that I use.
This is how the terminal looks like:

<img src="pictures/terminal.png" alt="Terminal" style="float: left; margin-right: 10px;" />  

## Vim
Copy `.vimrc` and `.vim` folder inside your home directory, then extract the zip file `.vim/plugged/plugin.zip` inside that folder.  
Other plugins can be installed writing inside `.vimrc`:

```bash
$ Plug *git-repository-name*
```
and then digit inside vim:

```bash
:PlugInstall
```
or putting the plugin folder directly inside `.vim/plugged/`.  
The installation process is explained in details inside [plug.vim].

In general it contains:
* Color themes for coding
* NerdTree that allows to see and move around the directory tree
* C plugins for syntax check, compilation errors, c automatic code insertion
* Python plugins for documentation, syntax check
* VHDL plugin with automatic template
* Vim shell and others

You can check the documentation of every plugin inside vim with:

```bash
:help *plugin-name*
```

## i3wm
The configurations can be found inside `.config` and `i3blocks` folders.
The `.config` folder content is situated inside your `.config` folder in your home directory. The `i3blocks` is situated in `/usr/share/`.

Please follow this guide ([setupi3]) for the complete configuration.  
During the configuration in that guide I encountered some problems regarding the screen brightness keyboard buttons and the volume in the i3 bar.
* for the brightness check here ([brightness unresponsive])
* the volume bar has been solved changing the [volume] script.

Some of the scripts inside [i3blocks] folder has been modified in order to be more aesthetic and in order to add functionalities. They use [FontAwesome] for icons images.
In particular the battery script has been modified to show the battery level also as an image that updates depending the battery level.  
The general look of the bar is this:

<img src="pictures/i3bar.png" alt="i3Bar" style="float: left; margin-right: 10px;" />

### Keyboard backlight
Since normal programs available online for keyboard backlight didn't work, I decided to write my own program [.runkeyboardlight.c]. The code depends on the computer in which is used. In general the two key factors to take into account are:
- the path of the keyboard backlight device file
- the range of possible configuration of the backlight

If you locate your device file, you can change the `fpath` variable in the code with the right path. In general it would be something like `/sys/class/leds/asus::kbd_backlight/brightness`. Try to act directly changing the content of the file driver, for example with a one, in order to see if the backlight works, it requires root privileges. Then you have to change the range of values for the brightness. In my laptop is 4 but in some it can be 2 or 3. Change line `44` in the code putting instead of 4 the right number.

Then you have to compile and give to the executable the root ownership and the setuid for the user. To do that open a terminal in the file folder and digit:

```bash
$ gcc -o .runkeyboardlight .runkeyboardlight.c
$ sudo chown root .runkeyboardlight
$ sudo chmod u+s .runkeyboardlight
```
Now to increase or decrease the light type in a terminal:
```bash
$ .runkeyboardlight inc
$ .runkeyboardlight dec
```

Then you can bind the program on the keyboard. Take a look inside [config] to see how it is done.


[plug.vim]: .vim/autoload/plug.vim
[setupi3]: https://github.com/bookercodes/setupi3
[brightness unresponsive]: https://www.reddit.com/r/i3wm/comments/8aorse/solution_volumebrightness_keys_unresponsive/
[volume]: i3blocks/volume
[i3blocks]: i3blocks/
[FontAwesome]: https://fontawesome.com/
[.runkeyboardlight.c]: .config/i3/.runkeyboardlight.c
[config]: .config/i3/config
