		sw	1,0,five
		lw	2,1,2
		sub 1,2,54
start	add	1,1,2
        or 1,2,1
		beq	0,1,done
		j	start
done	halt
five	.fill 	5
neg1	.fill 	-1
stAddr	.fill 	start