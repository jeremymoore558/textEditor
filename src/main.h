#ifndef MAIN_H
#define MAIN_H

// Uses linux escape sequence to clear terminal screen.
// Is used in various modes.
void clear_screen();

// In command mode, need to switch back to cooked terminal for 
// propper use of scanf to emulate vim-style : commands. 
// As such, made control over raw-vs-cooked mode public.
void disableRawMode();

// See above.
void enableRawMode();

#endif
