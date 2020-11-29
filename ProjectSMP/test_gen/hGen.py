from goto import with_goto

icond = {
    "EQ" :  "00000",
    "NE" :  "00001",
    "CS" :  "00010",
    "HL" :  "00010",
    "CC" :  "00011",
    "LO" :  "00011",
    "MI" :  "00100",
    "PL" :  "00101",
    "VS" :  "00111",
    "VC" :  "01000",
    "HI" :  "01001",
    "LS" :  "01010",
    "GE" :  "01011",
    "LT" :  "01100",
    "GT" :  "01101",
    "LE" :  "01110",
    ""   :  "11111"  
    }

aluTable = {
        "AND"   :   "00000",
        "EOR"   :   "00001",
        "ORR"   :   "00010",
        "TST"   :   "00011",
        "TEQ"   :   "00100",
        "CMP"   :   "00101",
        "CMN"   :   "00110",
        "ADD"   :   "00111",
        "SUB"   :   "01000",
        "ADC"   :   "01001",
        "RSB"   :   "01010",
        "SBC"   :   "01011",
        "MVN"   :   "01100",
        "LSL"   :   "01101",
        "ASR"   :   "01110",
        "RRX"   :   "01111",
        "ROR"   :   "10000",
        "BSWP"  :   "10001",
        "SWR"   :   "10010",
        "UADDPB"   :   "10011",
        "UADDPH"   :   "10100",
        "UADDPW"   :   "10101",
        "SADDPB"   :   "10110",
        "SADDPH"   :   "10111",
        "SADDPW"   :   "11000",
        "VUADDB"   :   "11001",
        "VUADDH"   :   "11010",
        "VSADDB"   :   "11011",
        "VSADDH"   :   "11100"
    }

mulOpcodeTable = {
        "MUL"     :   "0010",
        "MLA"     :   "0010",
        "UMULL"   :   "1010",
        "UMLAL"   :   "1010",
        "SMULL"   :   "1010",
        "SMLAL"   :   "1010"
    }
mulTable = {
        "MUL"     :   "0",
        "MLA"     :   "1",
        "UMULL"   :   "0",
        "UMLAL"   :   "1",
        "SMULL"   :   "0",
        "SMLAL"   :   "1"
    }

mulSignTable = {
        "UMULL"   :   "0",
        "UMLAL"   :   "0",
        "SMULL"   :   "1",
        "SMLAL"   :   "1"
    }

memTypeTable = {
        "STR"   :   "0",
        "LDR"   :   "1",
        "STRW"  :   "0",
        "LDRW"  :   "1",
        "STRHW" :   "0",
        "LDRHW" :   "1",
        "STRB"  :   "0",
        "LDRB"  :   "1"
    }
memOperSizeTable = {
        "STR"   :   "11",
        "LDR"   :   "11",
        "STRW"  :   "10",
        "LDRW"  :   "10",
        "STRHW" :   "01",
        "LDRHW" :   "01",
        "STRB"  :   "00",
        "LDRB"  :   "00"
    }
memOpcodeTable = {
        "MUL"     :   "0011",
        "MLA"     :   "0011",
        "UMULL"   :   "0011",
        "UMLAL"   :   "0011",
        "SMULL"   :   "0011",
        "SMLAL"   :   "0011"
    }
def ALUinstrType(instr):
    #begin
    #parts of ALU instraction
    Nwords = len(instr)
    #last or prelast word in instarction can consist of imm32/16 value
    if (instr[Nwords - 1][0].upper() != "R"):
        #begin
        imm32 = format(int(instr[Nwords - 1], base = 16), "b").zfill(32)
        I = "1"
        #end
    else:
        I = "0"
    itype = instr[0]
    if (itype[-1] == 'S'):
        S = "1"
    else:
        S = "0"

    #we cut conditional
    conditional = itype[0:1];
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]
    else:
        cond = "11111"
    #we get only type
    func = aluTable.get(itype.upper())
    if func == None:
        return None
    #Attantion!!!! Hardcode
    priv = "11"
    opcode = "0001"

    if Nwords == 6:
        #begin
        Rd = format(int(instr[1][1:], base = 16), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 16), "b").zfill(6)
        Rd = format(int(instr[3][1:], base = 16), "b").zfill(6)
        Rn = format(int(instr[4][1:], base = 16), "b").zfill(6)
        binInstr = priv + cond + opcode + I + S + func + "0" + Rn + Rd + Rm + Rm2
        #end
    elif Nwords == 4:
        #begin
        Rd = format(int(instr[1][1:], base = 16), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 16), "b").zfill(6)
        Rm2 = ""
        if I == "0":
            #begin
            Rm = format(int(instr[3][1:], base = 16), "b").zfill(6)
            imm32 = ""
            binInstr = priv + cond + opcode + I + S + func + "0" + Rn + Rd + Rm
            #end
        else:
            #begin
            Rm = ""
            binInstr = priv + cond + opcode + I + S + func + "0" + Rn + Rd + imm32
            #end
        #end
    #debugging code
    print("priv = ", priv)
    print("Rd = ", Rd)
    print("Rn = ", Rn)
    print("Rm = ", Rm)
    print("Rm2 = ", Rm2)
    print("cond = ", cond)
    print("func = ", func)
    print("I = ", I)
    print("S = ", S)
    print("imm32 = ", imm32)
    #concatenate binary instraction
    temp = '{:<064}'
    output = temp.format(binInstr) 
    print("binary instraction is: ", output)
    return output
    #end

def MULinstrType(instr):
    #begin
    #get opcode
    opcode = mulOpcodeTable.get(instr[0])
    if opcode == None:
        return None
    #parts of instraction
    Nwords = len(instr)
    #12 bit on instraction:
    B12 = "0"
    #last or prelast word in instarction can consist of imm32/16 value
    if (instr[Nwords - 1][0].upper() != "R"):
        #begin
        imm32 = format(int(instr[Nwords - 1], base = 16), "b").zfill(32)
        I = "1"
        #end
    else:
        I = "0"

    itype = instr[0]

    #we cut conditional
    conditional = itype[0:1];
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]#if cond it is existing
    else:
        cond = "11111"#if nocond instraction
    #we get only type
    #Attantion!!!! Hardcode
    priv = "11"

    #mul or mul with accumulation
    A = mulTable.get(itype)

    Sign = mulSignTable.get(itype)

    if opcode == "0010":
        B12 = I
    elif opcode == "1010":
        B12 = Sign
    
    if I == "1":
        #begin
        Rd = format(int(instr[1][1:], base = 16), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 16), "b").zfill(6)
        Ra = "111111"
        binInstr = priv + cond + opcode + A + B12 + Ra + Rn + Rd + imm32
        #end
    elif I == "0":
        #begin
        Rd = format(int(instr[1][1:], base = 16), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 16), "b").zfill(6)
        Rm = format(int(instr[3][1:], base = 16), "b").zfill(6)
        Ra = format(int(instr[4][1:], base = 16), "b").zfill(6)
        binInstr = priv + cond + opcode + A + B12 + Ra + Rn + Rd + Rm
        #end
    #debagging code
    print("MUL priv = ", priv)
    print("MUL Rd = ", Rd)
    print("Rn = ", Rn)
    print("Rm = ", Rm)
    print("Ra = ", Ra)
    print("cond = ", cond)
    print("A = ", A)
    print("B12 = ", B12)
    print("imm32 = ", imm32)
    #concatenate binary instraction
    temp = '{:<064}'
    output = temp.format(binInstr) 
    print("binary instraction is: ", output)
    return output
    #end

def MEMinstrType(instr):
    #begin
    #get opcode
    opcode = memOpcodeTable.get(instr[0])
    if opcode == None:
        return None

    #parts of instraction
    Nwords = len(instr)
    #last or prelast word in instarction can consist of imm32/16 value
    if Nwords == 5:
        #begin
        offset = format(int(instr[Nwords - 1], base = 16), "b").zfill(32)
        scale = format(int(instr[Nwords - 2], base = 16), "b").zfill(5)
        Rd = format(int(instr[1][1:], base = 16), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 16), "b").zfill(6)
        #end
    else:
        return None

    itype = instr[0]

    #we cut conditional
    conditional = itype[0:1];
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]#if cond it is existing
    else:
        cond = "11111"#if nocond instraction
    #we get only type
    TO = memTypeTable.get(itype)

    #Attantion!!!! Hardcode
    priv = "11"

    binInstr = priv + cond + opcode + TO + scale + Rn + Rd + offset
    #debagging code
    print("MUL priv = ", priv)
    print("MUL Rd = ", Rd)
    print("Rn = ", Rn)
    print("Rm = ", Rm)
    print("Ra = ", Ra)
    print("cond = ", cond)
    print("A = ", A)
    print("B12 = ", B12)
    print("imm32 = ", imm32)
    #concatenate binary instraction
    temp = '{:<064}'
    output = temp.format(binInstr) 
    print("binary instraction is: ", output)
    return output
    #end

def CTinstrType(instr):
    return None

def SYSinstrType(instr):
    return None

def decode(instr):
    #begin
    instrTemp = instr.replace(',', ' ')
    instrTemp = instrTemp.replace('[', ' ')
    instrTemp = instrTemp.replace(']', ' ')
    instrTemp = instrTemp.replace('\n', '')
    instrTemp = instrTemp.replace('  ', ' ')
    words = instrTemp.split(' ')
    #We split instraction on words
    binaryOut = ALUinstrType(words)
    if binaryOut == None:
        #begin
        binaryOut = MULinstrType(words)
        if binaryOut == None:
            #begin
            binaryOut = MEMinstrType(words)
            if binaryOut == None:
                #begin
                binaryOut = CTinstrType(words)
                if binaryOut == None:
                    #begin
                    binaryOut = SYSinstrType(words)
                    if binaryOut == None:
                        #begin
                        print("OOOOOh, NOOOO")
                        return None
                        #end
                    #end
                #end
            #end
        #end
    print(words)
    return binaryOut
    #end


@with_goto
def main():
    #begin
    sFile  = open("sourse.smpasm", "r")
    dFile  = open("tests.h", "w")

    if ((dFile.mode != 'w') | (sFile.mode != 'r')):
        #begin
        #file error
        print("File error\n")
        return 1
        #end
    instrs = sFile.readlines()
    for x in  instrs:
        #begin
        print("instraction", x ,"is translating\n")
        dFile.writelines(decode(x) + "\n")

        #end    

    dFile.close();
    sFile.close();
    return 0
    #end
#entry point 
main()