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
        "STR"   :   "0011",
        "LDR"   :   "0011",
        "STRW"  :   "0011",
        "LDRW"  :   "0011",
        "STRHW" :   "0011",
        "LDRHW" :   "0011",
        "STRB"  :   "0011",
        "LDRB"  :   "0011"
    }

ctOpcodeTable = {
        "BL"    :   "0100",   
        "BOI"   :   "0100",
        "BOR"   :   "0100",
        "BI"    :   "0100",
        "BR"    :   "0100",
        "RET"   :   "0100",
        "XRET"  :   "0100"
}
ctTypeTable = {
        "BL"    :   "0000",   
        "BOI"   :   "0001",
        "BOR"   :   "1001",
        "BI"    :   "0010",
        "BR"    :   "1010",
        "RET"   :   "0011",
        "XRET"  :   "0100"
}
ctImmTable = {
        "BL"    :   "0",   
        "BOI"   :   "1",
        "BOR"   :   "0",
        "BI"    :   "1",
        "BR"    :   "0",
        "RET"   :   "0",
        "XRET"  :   "0"
}
sysOpcodeTable = {
        "INSY"  :   "0101",
        "IN"    :   "0101",
        "OUTSY" :   "0101",
        "OUT"   :   "0101",
        "SFL"   :   "0101",
        "LFL"   :   "0101",
        "SMF"   :   "0101",
        "SINT"  :   "0101",
        "BINT"  :   "0101",
        "UINT"  :   "0101",
        "CINT"  :   "0101",
        "INT"   :   "0101"
}
sysTypeTable = {
        "INSY"  :   "0000",
        "IN"    :   "0001",
        "OUTSY" :   "0010",
        "OUT"   :   "0011",
        "SFL"   :   "0100",
        "LFL"   :   "0101",
        "SMF"   :   "0110",
        "SINT"  :   "0111",
        "BINT"  :   "1000",
        "UINT"  :   "1001",
        "CINT"  :   "1010",
        "INT"   :   "1011"
}
sysImmTable = {
        "INSY"  :   "1",
        "IN"    :   "1",
        "OUTSY" :   "1",
        "OUT"   :   "1",
        "SFL"   :   "0",
        "LFL"   :   "0",
        "SMF"   :   "0",
        "SINT"  :   "1",
        "BINT"  :   "0",
        "UINT"  :   "0",
        "CINT"  :   "0",
        "INT"   :   "1"
}
def ALUinstrType(instr):
    #begin
    
    #parts of ALU instraction
    Nwords = len(instr)
    #we cut conditional
    itype = instr[0]
    conditional = itype[0:1];
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]
    else:
        cond = "11111"

    itype = itype.upper()
    #we get only type
    func = aluTable.get(itype)
    if func == None:
        return None

    #last or prelast word in instarction can consist of imm32/16 value
    if (instr[Nwords - 1][0].upper() != "R"):
        #begin
        imm32 = format(int(instr[Nwords - 1], base = 16), "b").zfill(32)
        I = "1"
        #end
    else:
        I = "0"
    
    if (itype[-1] == 'S'):
        S = "1"
    else:
        S = "0"


    #Attantion!!!! Hardcode
    priv = "11"
    opcode = "0001"

    if Nwords == 6:
        #begin
        Rd = format(int(instr[1][1:], base = 10), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 10), "b").zfill(6)
        Rd = format(int(instr[3][1:], base = 10), "b").zfill(6)
        Rn = format(int(instr[4][1:], base = 10), "b").zfill(6)
        binInstr = priv + cond + opcode + I + S + func + "0" + Rn + Rd + Rm + Rm2
        #end
    elif Nwords == 4:
        #begin
        Rd = format(int(instr[1][1:], base = 10), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 10), "b").zfill(6)
        Rm2 = ""
        if I == "0":
            #begin
            Rm = format(int(instr[3][1:], base = 10), "b").zfill(6)
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
    #parts of instraction
    Nwords = len(instr)

    #we cut conditional
    itype = instr[0]
    conditional = itype[0:1];
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]#if cond it is existing
    else:
        cond = "11111"#if nocond instraction
    itype = itype.upper()
    #get opcode
    opcode = mulOpcodeTable.get(itype)
    if opcode == None:
        return None
    
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
    print("mul imm = ", imm32)
    
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
    print("B11 = ", B12)
    if I == "1":
        #begin
        Rd = format(int(instr[1][1:], base = 10), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 10), "b").zfill(6)
        Ra = "111111"
        Rm = ""
        binInstr = priv + cond + opcode + A + B12 + Ra + Rn + Rd + imm32
        #end
    elif I == "0":
        #begin
        Rd = format(int(instr[1][1:], base = 10), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 10), "b").zfill(6)
        Rm = format(int(instr[3][1:], base = 10), "b").zfill(6)
        Ra = format(int(instr[4][1:], base = 10), "b").zfill(6)
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
    #parts of instraction
    Nwords = len(instr)
    itype = instr[0]
    itype = itype.upper()
    #we cut conditional
    conditional = itype[0:1];
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]#if cond it is existing
    else:
        cond = "11111"#if nocond instraction
    #get opcode
    opcode = memOpcodeTable.get(itype)
    print("MEM opcode", opcode)
    if opcode == None:
        return None
    #last or prelast word in instarction can consist of imm32/16 value
    if Nwords == 5:
        #begin
        offset = format(int(instr[Nwords - 1], base = 10), "b").zfill(32)
        scale = format(int(instr[Nwords - 2], base = 10), "b").zfill(5)
        Rd = format(int(instr[1][1:], base = 10), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 10), "b").zfill(6)
        #end
    else:
        return None


    #we get only type
    TO = memTypeTable.get(itype)

    #Attantion!!!! Hardcode
    priv = "11"

    binInstr = priv + cond + opcode + TO + scale + Rn + Rd + offset
    #debagging code
    print("MEM priv = ", priv)
    print("MEM Rd = ", Rd)
    print("MEM Rn = ", Rn)
    print("MEM cond = ", cond)
    print("MEM offset = ", offset)
    print("MEM scale = ", scale)
    #concatenate binary instraction
    temp = '{:<064}'
    output = temp.format(binInstr) 
    print("binary instraction is: ", output)
    return output
    #end

def CTinstrType(instr):
    #begin
    imm48 = ""
    #parts of instraction
    Nwords = len(instr)
    itype = instr[0]
    itype = itype.upper()
    #we cut conditional
    conditional = itype[0:1];
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]#if cond it is existing
    else:
        cond = "11111"#if nocond instraction
    #get opcode
    opcode = ctOpcodeTable.get(itype)
    print("CT opcode = ", opcode)
    if opcode == None:
        return None
    func = ctTypeTable.get(itype)
    print("CT func = ", func)
    if func == None:
        return None
    I = ctImmTable.get(itype)
    print("CT I = ", I)
    if I == None:
        return None

    #Attantion!!!! Hardcode
    priv = "11"

    #last or prelast word in instarction can consist of imm32/16 value
    if Nwords == 2:
        #begin
        if I == "0":
            #begin
            R = format(int(instr[1][1:], base = 10), "b").zfill(6)
            xfill = "00000"
            binInstr = priv + cond + opcode + func + xfill + R
            #end
        elif I == "1":
            #begin
            imm48 = format(int(instr[1], base = 10), "b").zfill(48)
            binInstr = priv + cond + opcode + func + imm48
            #end
        #end
    elif Nwords == 1:
        binInstr = priv + cond + opcode + func
    elif Nwords > 2:
        return None

    #we get only type
    TO = memTypeTable.get(itype)

    #debagging code
    print("CT priv = ", priv)
    print("CT R = ", R)
    print("CT imm48 = ", imm48)
    print("CT cond = ", cond)
    #concatenate binary instraction
    temp = '{:<064}'
    output = temp.format(binInstr) 
    print("binary instraction is: ", output)
    return output
    #end

def SYSinstrType(instr):
    #begin
    imm48 = ""
    #parts of instraction
    Nwords = len(instr)
    itype = instr[0]
    itype = itype.upper()
    #we cut conditional
    conditional = itype[0:1];
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]#if cond it is existing
    else:
        cond = "11111"#if nocond instraction
    #get opcode
    opcode = sysOpcodeTable.get(itype)
    print("CT opcode = ", opcode)
    if opcode == None:
        return None
    func = sysTypeTable.get(itype)
    print("CT func = ", func)
    if func == None:
        return None
    I = sysImmTable.get(itype)
    print("CT I = ", I)
    if I == None:
        return None

    #Attantion!!!! Hardcode
    priv = "11"

    #last or prelast word in instarction can consist of imm32/16 value
    if Nwords == 3:
        #begin
        if I == "0":
            #begin
            Rm = format(int(instr[2][1:], base = 10), "b").zfill(6)
            Rn = format(int(instr[1][1:], base = 10), "b").zfill(6)
            xfill = "0000"
            binInstr = priv + cond + opcode + func + xfill + Rm + Rn + I
            #end
        elif I == "1":
            #begin
            imm = format(int(instr[2], base = 10), "b").zfill(6)
            Rn = format(int(instr[1][1:], base = 10), "b").zfill(6)
            xfill = "0000"
            binInstr = priv + cond + opcode + func + xfill + Rn + xfill + "00" + I + imm
            #end
        #end
    elif Nwords == 2:
        #begin
        if I == "0":
            #begin
            R = format(int(instr[1][1:], base = 10), "b").zfill(6)
            binInstr = priv + cond + opcode + func + xfill + Rm + "000000" + I
            #end 
        elif I == "1":
            #begin
            zFill = "0000000000000000"
            imm = format(int(instr[1], base = 10), "b").zfill(6)
            binInstr = priv + cond + opcode + func + zFill + I + imm
            #end
        #end
    elif Nwords == 1:
        binInstr = priv + cond + opcode + func
    else:
        return None

    #we get only type
    TO = memTypeTable.get(itype)

    #debagging code
    print("SYS priv = ", priv)
    print("SYS cond = ", cond)
    print("SYS opcode = ", opcode)
    print("SYS func code = ", func)
    #concatenate binary instraction
    temp = '{:<064}'
    output = temp.format(binInstr) 
    print("binary instraction is: ", output)
    return output
    #end

def decode(instr):
    #begin
    instrTemp = instr.replace(',', ' ')
    instrTemp = instrTemp.replace('[', '')
    instrTemp = instrTemp.replace(']', '')
    instrTemp = instrTemp.replace('\n', '')
    #instrTemp = instrTemp.replace('  ', ' ')
    instrTemp = re.sub('\s+',' ',instrTemp)
    words = instrTemp.split(' ')
    print(words)
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
                print("CT")
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
    return binaryOut
    #end


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
import re
main()