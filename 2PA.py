import re
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

POOLTAB = []
SymCnt = 0
LitCnt = 0
PoolCnt = 0
TokCnt = 0
LC = 0

fp1 = open("2PA_IC.txt", "rt")
fp2 = open('OP_2PA.txt', "w")

symlist[0].symbol = "A"
symlist[0].addr = 210
symlist[1].symbol = "B"
symlist[1].addr = 215
symlist[2].symbol = "C"
symlist[2].addr = 216

litlist[0].lit = "1"
litlist[0].addr = 205
litlist[1].lit = "2"
litlist[1].addr = 206
litlist[2].lit = "3"
litlist[2].addr = 217

POOLTAB.append(0)
POOLTAB.append(2)


def generate_datastructures():
	Symcnt = int(input("Enter total no of Symbols : "))
	for i in range(0, Symcnt):
		symlist[i].symbol = input("Enter Symbol: ")
		symlist[i].addr = input("Enter Address: ")
		print()
	print()
	LitCnt = int(input("Enter total no of Literals : "))
	for i in range(0, LitCnt):
		litlist[i].lit = input("Enter Lit.: ")
		litlist[i].addr = input("Enter Address: ")
		print()
	print()

	PoolCnt = int(input("Enter total no of Pools : "))
	for i in range(0, Poolcnt):
		POOLTAB[i] = input("Enter Lit. Referene: ")
		print()
	

def pass_two():
	ind = 0
	global LC
	global symlist
	global litlist
	for data in fp1:
		x = re.findall('\(([^)]+)', data)
		Tok = ",".join(x)
		Tok = Tok.split(",")
		
		if len(Tok) == 5:
			if Tok[3]=='S':
				fp2.write("{0}) {1:0=2d} {2} {3:0=3d}\n".format(LC, int(Tok[1]), int(Tok[2]), symlist[int(Tok[4])].addr))
			elif Tok[3] == "L":
				fp2.write("{0}) {1:0=2d} {2} {3:0=3d}\n".format(LC, int(Tok[1]), int(Tok[2]), litlist[int(Tok[4])].addr))

		if len(Tok) == 4:
			print(Tok)
			if Tok[0]=="AD":
				if Tok[1] == "00" or Tok[1] == "02":
					print(Tok)
					LC = int(Tok[3]) -1
			elif Tok[0] == "IS":
				fp2.write("{0}) {1:0=2d} 0 {2:0=3d}\n".format(LC, int(Tok[1]), int(symlist[int(Tok[3])].addr))) 

			elif Tok[0] =="DL":
				if Tok[1] == "01":
					for i in range(0, int(Tok[3])):
						LC += 1
						fp2.write("{0}) \n".format(LC))
				elif Tok[1] == "00":
					fp2.write("{0}) 00 0 {1:0=3d}\n".format(LC, int(Tok[3])))

		if len(Tok) == 2:
			if Tok[0]=="AD":
				if Tok[1] == "01" or Tok[1] == "04": 
					for i in range(POOLTAB[ind], POOLTAB[ind+1]):
						fp2.write("{0}) 00 0 {1:0=3d}\n".format(LC, int(litlist[i].lit)))
		LC += 1

if __name__=="__main__":
	# generate_datastructures()
	pass_two()
	fp1.close()
	fp2.close()
