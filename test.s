.name "Takeover"
.comment "Yup, it's pretty hostile"

start:								#attack sequence
		ld %57672193, r2			#03700201 == st, r2, 2...
	st r8, -511					#write lfork in case of infiltrator
		ld %0, r15				#carry = 1
loop:
	sti r1, %:live, %1
