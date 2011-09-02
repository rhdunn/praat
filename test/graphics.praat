# graphics.praat
# Paul Boersma, September 22, 2007

Erase all
Times
14
Select inner viewport... 0.1 0.4 0.1 8.9
Axes... 0 1 0 1
for i from 0 to 800
	grey = i/800
	Paint rectangle... 'grey' 0 1 i/801 (i+1)/801
endfor
Draw inner box
Select inner viewport... 0.6 1 0.1 1.9
Black
Draw line... 0 0 0 1
Text... 0 Left 1.0 Top top-aligned
Text... 0 Left 0.8 Half This text here is
Text... 0 Left 0.6 Half left-aligned text
Text... 0 Left 0.4 Half \aend\0v \dh\ics \swz w\ef\l~.
Text... 0 Left 0.2 Half many----hyphens
Text... 0 Left 0.0 Bottom bottom-aligned
Select inner viewport... 2.8 3.2 0.1 1.9
Dotted line
Draw line... 0.5 0 0.5 1
Solid line
Text... 0.5 Centre 1.0 Top top-aligned
Text... 0.5 Centre 0.8 Half This text here is
Text... 0.5 Centre 0.6 Half centred text
Text... 0.5 Centre 0.4 Half \aend\0v \dh\ics \swz w\ef\l~.
Text... 0.5 Centre 0.2 Half many----hyphens
Text... 0.5 Centre 0.0 Bottom bottom-aligned
Select inner viewport... 5 5.4 0.1 1.9
Draw line... 1 0 1 1
Text... 1 Right 1.0 Top top-aligned
Text... 1 Right 0.8 Half This text here is
Text... 1 Right 0.6 Half right-aligned text
Text... 1 Right 0.4 Half \aend\0v \dh\ics \swz w\ef\l~.
Text... 1 Right 0.2 Half many----hyphens
Text... 1 Right 0.0 Bottom bottom-aligned
Select outer viewport... 0 6 0 9