;----------------------------------------------------------------
; This is a Sol Cycle derived from the UAV
;----------------------------------------------------------------

Solenoid power		101   01   0
Solenoid pump		102   02   0
Solenoid ozone		103   03   0
Solenoid N2			105   05   0
Solenoid aircal		104   04   0
Solenoid sampIN		106   06   0
Solenoid sampOUT	 07  107   0

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
       sampOUT: ______
		 ozone: ______
	    aircal: ______
		    N2: OOOOOO
	   elecCH3: oooooj
       elecCH1: oioooo
       elecCH2: oooioo
        gsvCH3: LLLLLL
       mainCH3: eeeeee
         bfCH3: eeeeee
        gsvCH2: LLLLLL
       mainCH2: eeeeee
         bfCH2: eeeeee
      bfprsCH2: aaaaaa
        gsvCH1: LLLLLL
       mainCH1: eeeeee
         bfCH1: eeeeee
      bfprsCH1: aaaaaa^
}


Routine chrom70s_A {

       GCstate: 12222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:___OO:OOO__:_____:_____:_____:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:____O:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:ccccc:ccccc:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:ccccc:ccccc:ccccc:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:ccccc:ccccc:ccddd:ddddd:dddee:eeeee:eeeee:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aabbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:^

}

Routine chrom70s_B {

       GCstate: 12222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_____:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:ILLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaaab:bbbbb:ccccc:ccccc:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:ccccc:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:abbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:ccccc:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:IIIII:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: aaaab:bbbbb:ccccc:ccccc:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:ddddd:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:ccccc:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aabbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:ccccc:^

}


Routine chrom140s_A {

       GCstate: 21222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:____O:OOOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:
       mainCH1: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
}

Routine chrom140s_B {

       GCstate: 22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:____O:OOOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: ILLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aabbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH1: aabbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:^
}

Routine chrom280s_A {

       GCstate: 21222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:____O:OOOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:
       mainCH1: aaaaa:aabbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

}

Routine chrom280s_B {

       GCstate: 22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:____O:OOOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: IIIII:IIIII:IIIII:IIIII:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH1: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aabbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

}

Routine chrom280s_C {

       GCstate: 22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:____O:OOOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

}

Routine chrom280s_D {

       GCstate: 22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:22222:
        sampIN: _____:_____:_____:_____:_____:_____:_____:____O:OOOOO:OOOOO:OOOOO:OOOOO:OOOO_:_____:
       sampOUT: _____:_____:_____:_____:_____:_____:_OOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOOOO:OOO__:

        gsvCH1: LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:ddddd:
      bfprsCH1: bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH2: IIIII:IIIII:IIIII:IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH2: aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
      bfprsCH2: aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:

        gsvCH3: IIIII:IIIII:IIIII:IIILL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:LLLLL:
       mainCH3: aaaab:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:
         bfCH3: aaaaa:aaaaa:aaaaa:aaabb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:bbbbb:^

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

