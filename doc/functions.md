# Graphics

## void printwCentered(const char* str)
Print the string **str** centered in the screen.

Require *ncurses* initialized.

Do not call **refresh()**.


## void printwXCentered(int y, const char* str)
Same as **printwCentered(str)** but with defined value **y** for the vertical axis.


## void printwYCentered(int x, const char* str)
Same as **printwCentered(str)** but with defined value **x** for the horizontal axis.



# Intro

## void splashscreen()
Display an ascii art splashscreen stored in **SPLASHSCREEN_PATH** text file.


## GameMode homeMenu()
Clear screen and return the selection between *Play*,*Continue*,*Debug*.

**GameMode** is an integer (typedef).



# Gameplay

## bool fight(Node** team1, Node** team2, char* log)
Compute a *fight turn*. **team1** is the player team. Action made in the turn is stored in **log**.

A *fight turn* is one attack made by an *attacker* against a *defender*.

The function memorizes the previous *attacker* or init the first one (**team1**). Next *attacker*s are the next members of the **team**, then the members of the other **team**, repeatedly. *Defender*s are chosen randomly.

The function return **TRUE** while there is at least one member in the two **team**s. Then it return **FALSE** and **log** the fight outcome when all the members of a **team** has been defeated.


## double attack(Entity* attacker, Entity* defender)
Compute and inflige damage points.

Return infliged damages.


## Entity getEntityComputedStats(Entity entity)
Compute the stats of an **entity** including its **weapon** and **armor**.

The returned **entity** has its base stats augmented by the value of **weapon**'s and **armor**'s stats.