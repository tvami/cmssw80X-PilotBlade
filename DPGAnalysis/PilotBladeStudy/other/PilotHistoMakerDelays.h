int delay(uint run, const uint ls) {
  int delay=-9999;
  //2016-04-23
  if (run==271056) {
    if (ls<58)  { delay=37; return delay; }
    if (ls<81)  { delay=12; return delay; }
    if (ls<110) { delay=-25; return delay;} // Get back to this point
    if (ls<223) { delay=49; return delay; }
    if (ls<263) { delay=37; return delay; }
    if (ls<306) { delay=25; return delay; }
  } 
  if (run==271084 || run==271087) { 
    delay=49; return delay; 
  } 
  //2016-04-24
  if (run==271136 || run==271142 || run==271143 || run==271144 || run==271151) {
    delay=49; return delay;
  }
  if (run==271153 || run==271155 || run==271161 || run==271167 || run==271168) {
    delay=49; return delay;
  }
  if (run==271169 || run==271170 || run==271176 || run==271177 || run==271188) {
    delay=49; return delay;
  }
  if (run==271191) {
    if (ls<55)  { delay=62; return delay; }
    if (ls<110) { delay=74; return delay; }
    else 	{ delay=87; return delay; }
  } 
  if (run==271192) {
    if (ls<46)  { delay=87; return delay; } 
    else        { delay=47; return delay; }
  }
  if (run==271193) {
    if (ls<44)  { delay=47; return delay; }
    if (ls<92)  { delay=45; return delay; }
    else        { delay=43; return delay; }
  } 
  if (run==271195) {
    if (ls<47)  { delay=43; return delay; }
    if (ls<95)  { delay=41; return delay; }
    if (ls<134) { delay=39; return delay; }
    if (ls<186) { delay=85; return delay; }
    if (ls<222) { delay=83; return delay; }
    else 	{ delay=79; return delay; }
  }
  if (run==271196) {
    if (ls<37)	{ delay=79; return delay; }
    if (ls<88)  { delay=77; return delay; }
    if (ls<127) { delay=70; return delay; }
    if (ls<168) { delay=68; return delay; }
    if (ls<204) { delay=66; return delay; }
    if (ls<238) { delay=64; return delay; }
    else 	{ delay=60; return delay; }
  }
  if (run==271197) {
    if (ls<5)	{ delay=49; return delay; }
    if (ls<38)	{ delay=60; return delay; }
    else 	{ delay=58; return delay; }
  }
  if (run==271214) {
    if (ls<51)	{ delay=58; return delay; }
    if (ls<94)	{ delay=56; return delay; }
    else 	{ delay=56; return delay; }
  }
  if (run==271215 || run==271216 || run==271221 || run==271224 || run==271230) {
    delay=54; return delay;
  }
  if (run==271234 || run==271244 || run==271245 || run==271248 || run==271250) {
    delay=49; return delay;
  }
  if (run==271253 || run==271254 || run==271269 || run==271280 || run==271291) {
    delay=49; return delay;
  }
  //2016-04-25
  if (run==271304) {
    if (ls<72) { delay=49; return delay; }
    else       { delay=54; return delay; }
  }
  if (run==271306) {
    if (ls<98)  { delay=54; return delay; }
    else 	{ delay=52; return delay; }
  }
  if (run==271307) {
  	//did not manage to be reconfigured, just 52ns.
    		  delay=52; return delay;
  }
  //if (run==271310) {
  //  if (ls<12) { delay=52; return delay; }
  //  else       { delay=49; return delay; }
  //}
  //2016-04-29
  if (run==272008 || run==272010 || run==272011) {
    delay=90; return delay;
  }
  if (run==272012 || run==272013 || run==272014) {
    delay=92; return delay;
  }
  if (run==272021) {
    if (ls<17)  { delay=94; return delay; }
    if (ls<28)  { delay=96; return delay; }
    if (ls<38)  { delay=98; return delay; }
    if (ls<48)  { delay=100; return delay;}
    if (ls<58)  { delay=102; return delay;}
    if (ls<69)  { delay=104; return delay;}
    if (ls<80)  { delay=106; return delay;}
    if (ls<90)  { delay=108; return delay;}
    if (ls<100) { delay=110; return delay;}
    if (ls<110) { delay=112; return delay;}
    else	{ delay=114; return delay;}
  }
  if (run==272022) {
   delay=62; return delay;
  }
  
  // CRAFT from here
  //if (run>272022) {
  // if (run<272000) { // need to check
  //    delay=90; return delay;
  //  }
  //  if (run<272150) {
  //    delay=62; return delay;
  // }
  //}
  // Timing Scan2
  if (run==274000 || run==274002 || run==274004 || run==274007 || run==274008 || run==274036 || run==274044 || run==274046 || run==274047 || run==274048 || run==274049 || run==274050 || run==274052 || run==274057 || run==274062 || run==274064 || run==274076 || run==274077) { 
    delay=62; return delay; }

  if (run==274079 || run==274080 || run==274081 || run==274083 || run==274086 || run==274087 || run==274088 || run==274089 || run==274090 || run==274091 || run==274093 || run==274094 || run==274096) { 
    delay=52; return delay; }

  if (run==274102 || run==274103 || run==274104 || run==274105 || run==274106 || run==274107) { 
    delay=45; return delay; }

  if (run==274108 || run==274113 || run==274114 || run==274115 || run==274122 || run==274123 || run==274132 || run==274133 || run==274134 || run==274135 
|| run==274138 || run==274139 || run==274141 || run==274142 || run==274146 || run==274147 || run==274148 || run==274149 || run==274150 || run==274151 || run==274152 
|| run==274154 || run==274155 || run==274156 || run==274157) { 
    delay=70; return delay; }

  if (run==274159 || run==274192 || run==274195 || run==274196 || run==274246 || run==274247 || run==274248 || run==274256 || run==274263 || run==274264 
|| run==274266 || run==274268 || run==274270 || run==274274 || run==274275 || run==274276 || run==274280 || run==274281 || run==274289 || run==274290 || run==274294 
|| run==274295 || run==274300 || run==274305 || run==274306 || run==274309 || run==274311 || run==274313 || run==274317 || run==274320 || run==274324 || run==274337 
|| run==274344 || run==274345 || run==274346 || run==274347 || run==274349 || run==274356 || run==274363 || run==274366 || run==274367 || run==274368 || run==274369 
|| run==274372 || run==274373 || run==274374 || run==274377 || run==274378 || run==274379 || run==274380 || run==274381 || run==274382 || run==274384 || run==274385) { 
    delay=82; return delay; }

  if (run==274386 || run==274387) { 
    delay=45; return delay; }

  if (run==274391 || run==274392 || run==274393 || run==274394 || run==274396 || run==274398 || run==274401 || run==274402 || run==274414 || run==274415 || run==274417 || run==274418 || run==274419 || run==274420 || run==274421) { 
    delay=50; return delay; }

  if (run==274422) { 
    delay=56; return delay; }

  if (run==274424 || run==274425 || run==274430 || run==274433 || run==274436 || run==274437 || run==274438 || run==274439) { 
    delay=60; return delay; }

  if (run==274440) { 
    delay=60; return delay; }
  if (run==274441 || run==274442) { 
    delay=65; return delay; }
  if (run==274443 || run==274444) { 
    delay=70; return delay; }
  

  if (run==274445 || run==274446 || run==274448 || run==274449 || run==274450 || run==274452 || run==274455 || run==274463 || run==274468 || run==274469 || run==274470 || run==274471 || run==274495 || run==274503 || run==274505 || run==274506 || run==274507 || run==274508 || run==274510 || run==274512 || run==274516 || run==274517 || run==274569 || run==274718 || run==274720 || run==274722 || run==274724 || run==274726 || run==274728 || run==274733 || run==274743 || run==274744 || run==274746 || run==274748 || run==274749 || run==274758 || run==274771 || run==274774 || run==274775 || run==274776 || run==274777 || run==274778 || run==274779 || run==274780 || run==274781 || run==274783 || run==274784 || run==274785 || run==274799 || run==274802 || run==274804 || run==274806 || run==274810 || run==274813 || run==274814 || run==274815 || run==274817 || run==274850 || run==274856 || run==274861 || run==274864 || run==274866 || run==274868 || run==274869 || run==274873 || run==274875 || run==274877 || run==274878 || run==274879 || run==274880 || run==274881 || run==274883 || run==274885 || run==274887 || run==274888 || run==274939 || run==274940 || run==274941 || run==274942 || run==274943 || run==274944 || run==274945 || run==274947 || run==274948 || run==274950 || run==274951 || run==274953 || run==274954) { 
    delay=40; return delay; }

  if (run==279071 || run==279072 || run==279073) { 
    delay=49; return delay; }
// WBC=163. Globaldelay25=24ns

  if (run==279853 || run==279854 || run==279855 || run==279856 || run==279857 || run==279858 || run==279859 || run==279860 || run==279861 || run==279862 || run==279864) { 
    delay=124; return delay; }
// this above is not true.... the truth is: WBC moved 3 BX for BmI module and 4 BX for BmO modules.
  if (run>279864 && run<281602) {delay=62; return delay; }

  if (run==281602) {
    if (ls<22)  { delay=49; return delay; } //alias:Physics_p49ns_p24ns_6
    if (ls<43)  { delay=99; return delay; } //alias:Physics_p99ns_p74ns_6
    if (ls<66)  { delay=24; return delay; } //alias:Physics_p24ns_m1ns_6
    if (ls<87)  { delay=124; return delay; } //alias:Physics_p124ns_p99ns_6
    if (ls<107)  { delay=74; return delay; } //alias:Physics_p74ns_p49ns_6
  }
  //2016 October
  if (run==282093) {
    if (ls<28)  { delay=74; return delay; } //WBC="0", key:2448, LS: 0-28, BmIWBC:166, BmOWBC:167, alias:Physics_p74ns_p49ns_6 
    if (ls<50)  { delay=49; return delay; } //WBC="+1", key:2447, LS:28-50, BmIWBC:167, BmOWBC:168, alias:Physics_p49ns_p24ns_6
    else		{ delay=24; return delay;} //WBC="+2", key:2446, LS:50-, BmIWBC:168, BmOWBC:169, alias:Physics_p24ns_m1ns_6
  }
  if (run==282094) {delay=49; return delay; } //WBC="+1", key:2447, BmIWBC:167, BmOWBC:168 
  if (run==282095) {delay=24; return delay; } //WBC="+2", key:2446, BmIWBC:168, BmOWBC:169, alias:Physics_p24ns_m1ns_6
  if (run==282096) {delay=74; return delay; } //WBC="0", key:2448, BmIWBC:166, BmOWBC:167, alias:Physics_p74ns_p49ns_6
  
  if (run==282649) {delay=74; return delay; } //WBC="0", key:2443, BmIWBC:166, BmOWBC:167, alias:Physics_p74ns_p49ns_6
  if (run==282650) {
    if (ls<22)  { delay=99; return delay; } //WBC="-1", key:2569, BmIWBC:165, BmOWBC:166, LS:  5-22, alias:Physics_p99ns_p74ns_6 
    if (ls<40)  { delay=49; return delay; } //WBC="+1", key:2565, BmIWBC:167, BmOWBC:168, LS: 24-40, alias:Physics_p49ns_p24ns_6
    if (ls<56)  { delay=24; return delay; } //WBC="+2", key:2563, BmIWBC:168, BmOWBC:169, LS: 43-56, alias:Physics_p24ns_m1ns_6
	else		{ delay=124; return delay;} //WBC="-2", key:2571, BmIWBC:164, BmOWBC:165, LS: 58-74, alias:Physics_p124ns_p99ns_6
  }
  if (run==282663) {delay=74; return delay; } //WBC="0", key:????, BmIWBC:166, BmOWBC:167, alias:Physics_p74ns_p49ns_6

  return delay;
}
