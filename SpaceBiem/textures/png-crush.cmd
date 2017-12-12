@ECHO OFF
ECHO ##############################################################
ECHO # Crush all PNG from Images/* and store them in Optimized/*  #
ECHO ##############################################################
ECHO Files to crush:
FOR /F "tokens=*" %%x IN ('DIR *.png /B /S') DO ECHO - %%x

PAUSE

FOR /F "tokens=*" %%x IN ('DIR *.png /B') DO (
	ECHO Crushing: %%x
	pngcrush -brute "%%x" temp.png
	MOVE /Y temp.png "%%x"
)

PAUSE