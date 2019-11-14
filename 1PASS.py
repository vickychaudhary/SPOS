MAX = 20 # Max Symbol Table Entry

symlist = []
litlist = []

class SYMTAB:
	pass

class LITTAB:
	pass

for i in range(0, MAX):
	symlist.append(SYMTAB())
for i in range(0, MAX):
	litlist.append(LITTAB())

POOLTAB = [0]
SymCnt = 0
LitCnt = 0
PoolCnt = 0
TokCnt = 0
LC = 0

MOTAB = ["STOP", 
		"ADD",
		"SUB",
		"MULT",
		"MOVER",
		"MOVEM",
		"COMP",
		"BC",
		"DIV",
		"READ",
		"PRINT"]

REGTAB = ["AREG",
		"BREG",
		"CREG",
		"DREG"]

CONDTAB = ["LT", "LE", "EQ", "GT", "GE", "ANY"]
ADTAB = ["START", "END", "ORIGIN", "EQU", "LTORG"]

def SearchReg(key):
	try:
		return REGTAB.index(key)
	except:
		return -1

def SearchCond(key):
	try:
		return CONDTAB.index(key)
	except:
		return -1

def SearchOp(key):
	try:
		return MOTAB.index(key)
	except:
		return -1

def SearchDirective(key):
	try:
		return ADTAB.index(key)
	except:
		return -1

def SearchSymbol(key):
	try:
		for i in range(0, SymCnt):
			if symlist[i].symbol == key:
				return i
	except:
		return -1

def SearchLit(key):
	try:
		for i in range(POOLTAB[PoolCnt], LitCnt):
			if litlist[i].lit == key:
				return i
	except:
		return -1

fp1 = open("input.asm", "rt")
fp2 = open('IntCode.txt', "w")

def HandleOp(Tok0, Tok1, Tok2):
	global SymCnt
	global LitCnt
	i = SearchOp(Tok0)

	if(i >= 1 and i <= 8):

		if Tok2[0] == '=': # Literal
			j = SearchLit(str(Tok2[2]))
			if j == -1 or j is None:
				temp = "(L, %.2i)" % LitCnt
				litlist[LitCnt].lit = Tok2[2]
				LitCnt += 1
			else:
				temp = "(L, %.2i)" % j

		else: # Symbol
			j = SearchSymbol(Tok2)
			if j == -1 or j is None:
				temp = "(S, %.2i)" % SymCnt
				symlist[SymCnt].symbol = Tok2
				SymCnt += 1
			else:
				temp = "(S, %.2i)" % j
		
		if i == 7:
			j = SearchCond(Tok1)
		else:
			j = SearchReg(Tok1)
		fp2.write("(IS, {0:0=2d}) ({1}) {2}\n".format(i, j,temp))

if __name__=="__main__":
	if not fp1.read(1):
		exit()

	for data in fp1:
		Tok = data.split()
		if len(Tok) == 1: # START, END, LTORG, STOP
			i = SearchOp(Tok[0]) # STOP
			if i == 0:
				fp2.write("(IS, %.2i)\n" % i)

			i = SearchDirective(Tok[0]) # START
			if i == 0:
				fp2.write("(AD, %.2i)\n" % i)
				LC -= 1

			if i == 1 or i == 4: # END, LTORG
				fp2.write("(AD, %.2i)\n" % i)

				k = POOLTAB[PoolCnt]
				for x in range(k, LitCnt):
					litlist[x].addr = LC
					LC += 1
				PoolCnt += 1
				POOLTAB.append(LitCnt)
				LC -= 1

		elif len(Tok) == 2: # START, ORIGIN, READ, PRINT
			i = SearchDirective(Tok[0])
			if i == 0 or i == 2:
				LC = int(Tok[1]) - 1
				fp2.write("(AD, {0:0=2d}) (C, {1:1=2d})\n".format(i, LC+1))
			
			i = SearchOp(Tok[0])
			if i == 9 or i == 10:
				j = SearchSymbol(Tok[1])
				if j == -1 or j is None:
					fp2.write("(IS, %.2i)(S, %.2i)\n" % i, SymCnt)
					symlist[SymCnt].symbol = Tok[1]
					SymCnt += 1
				else:
					fp2.write("(IS, %.2i)(S, %.2i)\n" % i, j)	

		elif len(Tok) == 3: # ADD - DIV, DL, EQU
			# ADD - DIV
			HandleOp(Tok[0], Tok[1], Tok[2])

			# DL
			if Tok[1] == "DC" or Tok[1] == "DS": # DC and DS
				i = SearchSymbol(Tok[0])
				if i == -1:
					symlist[SymCnt].symbol = Tok[0]
					symlist[SymCnt].addr = LC
					SymCnt += 1
				else:
					symlist[i].addr = LC

				if Tok[1] == "DS":
					LC = LC + int(Tok[2]) -1
					fp2.write("(DL, 01) (C, %.2i)\n" % int(Tok[2]))
				else:
					fp2.write("(DL, 00) (C, %.2i)\n" % int(Tok[2]))

			# EQU
			i = SearchDirective(Tok[1]) # EQU
			if i == 3:
				x = SearchSymbol(Tok[0])
				y = SearchSymbol(Tok[2])
				if x == -1 or x is None:
					symlist[SymCnt].symbol = Tok[2]
					symlist[SymCnt].addr = symlist[y].addr
					SymCnt += 1
				else:
					symlist[x].addr = symlist[y].addr

				fp2.write("(AD, %.2i)\n" %  i)
				LC -= 1

		elif len(Tok) == 4:
			i = SearchSymbol(Tok[0])
			if i == -1 or i is None:
				symlist[SymCnt].symbol = Tok[0]
				symlist[SymCnt].addr = LC
				SymCnt += 1
			else:
				symlist[i].addr = LC
			HandleOp(Tok[1], Tok[2], Tok[3])

		LC += 1
	fp1.close()
	fp2.close()