CC      = gcc
LEX		= flex
YACC	= bison
PROF    = -Wall -O2 -g
NOCRYPT =
C_FLAGS =  $(PROF) $(NOCRYPT)
L_FLAGS =  $(PROF) -lcrypt

O_FILES1 = vm/astridvm.o 

O_FILES2 = asm/vm-riskxvii.tab.o asm/vm-riskxvii.yy.o asm/output.o asm/identifiers.o

default: astridvm

asm/vm-riskxvii.tab.c asm/vm-riskxvii.tab.h: asm/vm-riskxvii.y
	$(YACC) -d -o asm/vm-riskxvii.tab.c asm/astridasm.y
	
asm/astridasm.yy.c: asm/vm-riskxvii.l asm/vm-riskxvii.tab.h
	$(LEX) -o asm/vm-riskxvii.yy.c asm/vm-riskxvii.l

.c.o: asm/*.h vm/*.h
	$(CC) -c $(C_FLAGS) -o $@ $<

astridvm: $(O_FILES1) $(O_FILES2)
	rm -f vm-riskxvii
	rm -f astridasm
	$(CC) $(L_FLAGS) -o vm-riskxvii $(O_FILES1)
	$(CC) $(L_FLAGS) -o vm-riskxvii $(O_FILES2) -lfl

clean:
	rm vm/*.o asm/*.o asm/vm-riskxvii.yy.c asm/vm-riskxvii.tab.c asm/vm-riskxvii.tab.h vm-riskxviiasm vm-riskxviivm