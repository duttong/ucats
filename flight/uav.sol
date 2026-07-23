;----------------------------------------------------------------
; This is a Sol Cycle derived from the UAV
;----------------------------------------------------------------

Solenoid power		101   01   0
Solenoid pump		112   12   0
Solenoid ozone		103   03   0
Solenoid N2			105   05   0
Solenoid aircal		114   14   0
Solenoid sampIN		116   16   0
Solenoid sampOUT	 17  117   0

dtoa GCstate 0x000 { 0:0 1:1 2:2 3:3 s:4 h:5 }
dtoa RunState 0x000 { L:0 R:1 }

; Open and closed definitions
open = 'O'		;inject,	trap heat off
;closed = '_'	;load,		trap heat on 
; NOTE:  The previous line is commented out because the '_' is the default char 

resolution = 1/1

Routine Init {
	  RunState: LLLLLL
       GCstate: 000000
        sampIN: ______
       sampOUT: OOOOOO
		 ozone: ______
	    aircal: ______
		    N2: OOOOOO
       elecCH1: oioooo
       elecCH2: oooioo
	   elecCH3: oooooj
        gsvCH1: LLLLLL
       mainCH1: iiiiii
         bfCH1: iiiiii
      bfprsCH1: iiiiii
        gsvCH2: LLLLLL
       mainCH2: iiiiii
         bfCH2: iiiiii
      bfprsCH2: iiiiii
        gsvCH3: LLLLLL
       mainCH3: iiiiii
         bfCH3: iiiiii^
}


Routine chrom70s_A {

       GCstate: 12222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:
       mainCH1: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:^

}

Routine chrom70s_B {

       GCstate: 12222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: ILLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bcccc:
      bfprsCH1: abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:^

}


Routine chrom140s_A {

       GCstate: 21222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:_____:__OOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:
       sampOUT: _OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIIL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIIII:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
}

Routine chrom140s_B {

       GCstate: 23222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:_____:__OOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:
       sampOUT: _OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbccc:ccccc:ccccc:
      bfprsCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bcccc:ccccc:ccccc:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIIII:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:^
}

Routine chrom280s_A {

       GCstate: 21222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:_____:
       sampOUT: _____:_____:_____:__OOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:
       mainCH1: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
}

Routine chrom280s_B {

       GCstate: 22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:_____:
       sampOUT: _____:_____:_____:__OOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:
       mainCH1: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
}

Routine chrom280s_C {

       GCstate: 22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:_____:
       sampOUT: _____:_____:_____:__OOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: ILLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aabbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
      bfprsCH1: aabbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
}

Routine chrom280s_D {

       GCstate: 22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:_____:
       sampOUT: _____:_____:_____:__OOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
      bfprsCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
   
        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbcc:^
}

; Safe Mode
mode 0 {
	Init      
	select 5
}

; Init mode
mode 1 {
	Init
	select 5
}

; RUN mode
mode 2 {
  	RunState: R
  	select 22
}
mode 22 {
	chrom140s_A
    chrom140s_B
}

; Lab mode 70s chroms
mode 3 {
	chrom70s_A
}

; Lab mode 140s chroms
mode 4 {
	RunState: L
	select 44
}
mode 44 {
	chrom140s_A
	chrom140s_B
}

; Lab mode 280s chroms
mode 6 {   
	chrom280s_A
	chrom280s_B
	chrom280s_C
	chrom280s_D
}

; Do nothing
mode 5 {
	select 5
}

; Cal mode
mode 7 {
	chrom140s_A
    chrom140s_B
}

; Shutdown mode
mode 9 {
	Init
	select 5
}

