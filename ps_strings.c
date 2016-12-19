const char *CIRCPAD = "/CIRCPAD {\n"
			"\t\t4 dict begin\n"
			"\t\t/FILL exch def\n"
			"\t\tpop\n"
			"\t\t/RADIUS exch 2 div def\n"
			"\t\t/Y exch def\n"
			"\t\t/X exch def\n"
			"\t\tFILL setgray\n" 
			"\t\tX Y RADIUS 0 360 arc\n" 
			"\t\tclosepath fill\n"
			"\t\tend } bind def\n";

const char *RECTPAD = "/RECTPAD {\n"
			"\t\t8 dict begin\n"
			"\t\t/FILL exch def\n"
			"\t\tdup dup\n"
			"\t\t/YSTART exch 2 div neg def\n"
			"\t\t/DOWN exch neg def\n"
			"\t\t/UP exch def\n"
			"\t\tdup dup\n"
			"\t\t/XSTART exch 2 div neg def\n"
			"\t\t/LEFT exch neg def\n"
			"\t\t/RIGHT exch def\n"
			"\t\t/YREF exch def\n"
			"\t\t/XREF exch def\n"
			"\t\tXREF YREF moveto\n"
			"\t\tXSTART YSTART rmoveto\n"
			"\t\t0 UP rlineto\n"
			"\t\tRIGHT 0 rlineto\n"
			"\t\t0 DOWN rlineto\n"
			"\t\tclosepath\n"
			"\t\tfill\n"
			"\t\tend } bind def\n";

const char *OCTPAD = "/OCTPAD {\n"   
			"\t\t7 dict begin\n"
			"\t\t/FILL exch def\n"
			"\t\tpop\n"
			"\t\tdup dup dup\n"
			"\t\t/POSHLF exch 2 div def\n"
			"\t\t/NEGHLF exch 2 div neg def\n"
			"\t\t/POSQTR exch 4 div def\n"
			"\t\t/NEGQTR exch 4 div neg def\n"
			"\t\t/YREF exch def\n"
			"\t\t/XREF exch def\n"
			"\t\tFILL setgray\n"
			"\t\tXREF YREF moveto\n"
			"\t\tNEGQTR NEGHLF rmoveto\n"
			"\t\tNEGQTR POSQTR rlineto\n"
			"\t\t0 POSHLF rlineto\n"
			"\t\tPOSQTR POSQTR rlineto\n"
			"\t\tPOSHLF 0 rlineto\n"
			"\t\tPOSQTR NEGQTR rlineto\n"
			"\t\t0 NEGHLF rlineto\n"
			"\t\tNEGQTR NEGQTR rlineto\n"
			"\t\tclosepath\n"
			"\t\tfill\n"
			"\t\tend } bind def\n";
			
const char *XRNDRECT = "/XRNDRECT {\n"
			"\t\t10 dict begin\n"
			"\t\t/FILL exch def\n"
			"\t\t/YSIZE exch def\n"
			"\t\t/XSIZE exch def\n"
			"\t\t/YREF exch def\n"
			"\t\t/XREF exch def\n"
			"\t\tXSIZE YSIZE sub\n"
			"\t\t/HLENGTH exch def\n"
			"\t\tHLENGTH 2 div\n"
			"\t\t/OFFSET exch def\n"
			"\t\tXREF OFFSET sub\n"
			"\t\t/XSTART exch def\n"
			"\t\tXREF OFFSET add\n"
			"\t\t/XEND exch def\n"
			"\t\tYSIZE 2 div\n"
			"\t\t/RADIUS exch def\n"
			"\t\tFILL setgray\n"
			"\t\tXEND YREF RADIUS 270 90 arc\n"
			"\t\tXSTART YREF RADIUS 90 270 arc\n"
			"\t\tclosepath fill\n"
			"\t\tend } bind def\n";

const char *YRNDRECT = "/YRNDRECT {\n"
			"\t\t10 dict begin\n"
			"\t\t/FILL exch def\n"
			"\t\t/YSIZE exch def\n"
			"\t\t/XSIZE exch def\n"
			"\t\t/YREF exch def\n"
			"\t\t/XREF exch def\n"
			"\t\tYSIZE XSIZE sub\n"
			"\t\t/HLENGTH exch def\n"
			"\t\tHLENGTH 2 div\n"
			"\t\t/OFFSET exch def\n"
			"\t\tYREF OFFSET sub\n"
			"\t\t/YSTART exch def\n"
			"\t\tYREF OFFSET add\n"
			"\t\t/YEND exch def\n"
			"\t\tXSIZE 2 div\n"
			"\t\t/RADIUS exch def\n"
			"\t\tFILL setgray\n"
			"\t\tXREF YSTART RADIUS 180 0 arc\n"
			"\t\tXREF YEND RADIUS 0 180 arc\n"
			"\t\tclosepath fill\n"
			"\t\tend } bind def\n";
			
const char *XHAIR = "/XHAIR {\n"
			"\t\tend } bind def\n";
			
const char *MOIRO = "/MOIRO {\n"
			"\t\tend } bind def\n";
			
const char *TRACK = "/TRACK {setlinewidth setgray moveto lineto stroke} bind def\n";

const char *DGD = "/DGD {\n"
			"\t\t4 dict begin\n"
			"\t\t/FILL exch def\n"
			"\t\t/RADIUS exch 2 div def\n"
			"\t\t/Y exch def\n"
			"\t\t/X exch def\n"
			"\t\tFILL setgray\n" 
			"\t\tX Y RADIUS 0 360 arc\n" 
			"\t\tclosepath fill\n"
			"\t\tend } bind def\n";
			
const char *FILL = "/FILL {\n"		
			"\t\t5 dict begin\n"
			"\t\t/FILL exch def\n"
			"\t\t/Y2 exch def\n"
			"\t\t/X2 exch def\n"
			"\t\t/Y1 exch def\n"
			"\t\t/X1 exch def\n"
			"\t\tX1 Y1 moveto\n"
			"\t\tX1 Y2 lineto\n"
			"\t\tX2 Y2 lineto\n"
			"\t\tX2 Y1 lineto\n"
			"\t\tclosepath\n"
			"\t\tfill\n"
			"\t\tend } bind def\n";			
			
const char *HEADER ="%!PS-Adobe-";
const char *CREATOR = "%%Creator: PCBREAD v0.0.1";
