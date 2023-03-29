		addi 1,2,54
start	add	1,1,2
		beq	0,1,done
        slti 3,4,6
        ori 1,2,4
		j	start
done	halt
five	.fill 	5
neg1	.fill 	-1
stAddr	.fill 	start