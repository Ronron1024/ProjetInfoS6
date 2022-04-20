# void printwCentered(const char* str)

Print the string **str** centered in the screen.

Require *ncurses* initialized.

Do not call **refresh()**.

# void printwXCentered(int y, const char* str)

Same as **printwCentered(str)** but with defined value **y** for the vertical axis.

# void printwYCentered(int x, const char* str)

Same as **printwCentered(str)** but with defined value **x** for the horizontal axis.