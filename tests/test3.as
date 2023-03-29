		addi 1,0,54
        addi 2,0,100
        sub 3,2,1
        nand 3,1,3
start	add	1,1,2
        lw 4,0,neg1
        add 5,1,4
        lui 1,0
		beq	0,1,done
        slti 3,4,6
        ori 1,2,4
		j	start
done	halt
five	.fill 	5
neg1	.fill 	-1
stAddr	.fill 	start