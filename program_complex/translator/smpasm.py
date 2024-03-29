import re
import sys
from bitstring import BitArray

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
        "VADDB"   :   "11011",
        "VADDH"   :   "11100"
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
        "BL"    :   "1",   
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

def instrType(instr):
    #begin
    Nwords = len(instr)
    #we cut conditional
    itype = instr[0].upper()
    itype_alu = instr[0].upper()
    # find condition 
    conditional = itype[0:2]
    cond = icond.get(conditional.upper())
    if (cond != None):
        itype_alu = itype_alu[2:]
        itype = itype[2:]
    
    if (itype_alu[len(itype_alu) - 1] == 'S'):
        itype_alu = itype_alu[0:len(itype_alu) - 1]
    
    if(aluTable.get(itype_alu) != None):
        return "ALU"
    elif(mulTable.get(itype) != None):
        return "MUL"
    elif(memTypeTable.get(itype) != None):
        return "MEM"
    elif(ctOpcodeTable.get(itype) != None):
        return "CT"
    elif(sysTypeTable.get(itype) != None):
        return "SYS"
    else:
        return None
    #end


def ALUinstrType(instr, priv):
    #begin
    #parts of ALU instraction
    Nwords = len(instr)
    #we cut conditional
    itype = instr[0].upper()
    # find condition 
    conditional = itype[0:2]
    cond = icond.get(conditional.upper())
    if (cond != None):
        #begin  
        itype = itype[2:]
        print("conditional = ", conditional)
        print("code condition = ", cond)
        #end
    else:
        cond = "11111"
    # find signed condition 
    if (itype[len(itype) - 1] == 'S'):
        #begin
        S = "1"
        itype = itype[0:len(itype) - 1]
        #end
    else:
        S = "0"
    #we get only type

    func = aluTable.get(itype)
    if (func == None): #ALU?
        return None
    print("Instraction type is: ", itype)
    opcode = "0001" # ALU opcode is 0001b

    
    #regs or imm?
    #last or prelast word in instarction can consist of imm32/16 value
    if (instr[Nwords - 1][0].upper() != "R"): #not regs?
        #begin
        imm32 = format(int(instr[Nwords - 1], base = 16), "b").zfill(32)
        I = "1"
        #end
    else:
        I = "0"

    if Nwords == 6:
        #begin
        Rd = format(int(instr[1][1:], base = 10), "b").zfill(6)
        Rn = format(int(instr[2][1:], base = 10), "b").zfill(6)
        Rm = format(int(instr[3][1:], base = 10), "b").zfill(6)
        Rm2= format(int(instr[4][1:], base = 10), "b").zfill(6)
        imm = imm32[12:32]
        binInstr = priv + cond + opcode + I + S + func + "0" + Rn + Rd + Rm + Rm2 + imm
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
    print('\n')
    return output
    #end

def MULinstrType(instr, priv):
    #begin
    #parts of instraction
    Nwords = len(instr)

    #we cut conditional
    itype = instr[0]
    conditional = itype[0:2]
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
    print('\n')
    return output
    #end

def MEMinstrType(instr, priv):
    #begin
    #parts of instraction
    Nwords = len(instr)
    itype = instr[0]
    itype = itype.upper()
    #we cut conditional
    conditional = itype[0:2]
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]#if cond it is existing
    else:
        cond = "11111"#if nocond instraction
    #get opcode
    opcode = memOpcodeTable.get(itype)
    
    if opcode == None:
        return None
    print("MEM opcode", opcode)
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
    slbit = memTypeTable.get(itype)
    TO = memOperSizeTable.get(itype)

    binInstr = priv + cond + opcode + slbit + TO + scale + Rn + Rd + offset
    #debugging code
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
    print('\n')
    return output
    #end

def CTinstrType(instr, priv):
    #begin
    imm48 = ""
    #parts of instraction
    Nwords = len(instr)
    itype = instr[0]
    itype = itype.upper()
    #we cut conditional
    conditional = itype[0:2]
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
    R = None
    #last or prelast word in instarction can consist of imm32/16 value
    if Nwords == 2:
        #begin
        if I == "0":
            #begin
            if(instr[1][0] != 'R'):
                print("translation error: incorrect register:", instr[1])
                return None
            R = format(int(instr[1][1:], base = 10), "b").zfill(6)
            xfill = "00000"
            binInstr = priv + cond + opcode + func + xfill + R
            #end
        elif I == "1":
            #begin
            offset = int(instr[1], base = 10)
            if offset < 0:
                #begin
                #offset = -offset
                offset = offset + 2**64
                imm48 = format(offset, "b")
                imm48 = imm48[16:64]
                len48 = 48 - len(imm48)
                imm48 = str('1')*len48 + imm48
                #end
            else:
                imm48 = format(offset, "b").zfill(48)
            binInstr = priv + cond + opcode + func + imm48
            #end
        #end
    elif Nwords == 1:
        binInstr = priv + cond + opcode + func
    elif Nwords > 2:
        return None
    #debagging code
    print("CT priv = ", priv)
    print("CT R = ", R)
    print("CT imm48 = ", imm48)
    print("CT cond = ", cond)
    #concatenate binary instraction
    temp = '{:<064}'
    output = temp.format(binInstr) 
    print("binary instraction is: ", output)
    print('\n')
    return output
    #end

def SYSinstrType(instr, priv):
    #begin
    #parts of instraction
    Nwords = len(instr)
    itype = instr[0]
    itype = itype.upper()
    #we cut conditional
    conditional = itype[0:1]
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
            binInstr = priv + cond + opcode + func + xfill + Rm + "000000" + I
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
    #debagging code
    print("SYS priv = ", priv)
    print("SYS cond = ", cond)
    print("SYS opcode = ", opcode)
    print("SYS func code = ", func)
    #concatenate binary instraction
    temp = '{:<064}'
    output = temp.format(binInstr) 
    print("binary instraction is: ", output)
    print('\n')
    return output
    #end

def decode(instr, priv):
    #begin
    instrTemp = instr.replace(',', ' ')
    instrTemp = instrTemp.replace('[', '')
    instrTemp = instrTemp.replace(']', '')
    instrTemp = instrTemp.replace('\n', '')
    instrTemp = re.sub('\s+',' ',instrTemp)
    words = instrTemp.split(' ')
    print("Instraction is parsed:", words)
    #split instraction on words
    itype = instrType(words)
    if(itype == None):
        return None
    elif(itype == "ALU"):
        binaryOut = ALUinstrType(words, priv) #Is this an ALU instraction?
    elif(itype == "MUL"):
        binaryOut = MULinstrType(words, priv) #Is this an MLU instraction?
    elif(itype == "MEM"):
        binaryOut = MEMinstrType(words, priv) #Is this an Memory instraction?
    elif(itype == "CT"):
        binaryOut = CTinstrType(words, priv) #Is this an Control Take instaraction
    elif(itype == "SYS"):
        binaryOut = SYSinstrType(words, priv) #Is tis an System instaraction
    return binaryOut
    #end

#main function
def main(argv):
    #begin
    sFileName = ''
    dFileName = ''
    binFileName = ''
    if (len(sys.argv) == 3):
        #begin
        sFileName = sys.argv[1]
        dFileName = sys.argv[2]
        binFileName = sys.argv[2] + '.bin'
        #end    
    elif(len(sys.argv) == 2):
        #begin
        sFileName = sys.argv[1]
        dFileName = sys.argv[1] + '.bindata'
        binFileName = sys.argv[1] + '.bin'
        #end
    elif(len(sys.argv) == 1):
        #begin
        sFileName = 'sourse.smpasm'
        dFileName = 'out.bindata'
        binFileName = 'out' + '.bin'
        #end
    sFile  = open(sFileName, 'r')
    dFile  = open(dFileName, 'w')
    binFile = open(binFileName, 'wb')
    if ((dFile.mode != 'w') | (sFile.mode != 'r') | (binFile.mode != 'wb')):
        #begin
        #file error
        print("File error\n")
        return 1
        #end
    priv = "11" #default value
    instrs = sFile.readlines()
    for x in  instrs:
        #begin
        words = x.split(' ')
        if(words[0] == "priv"):
            #begin
            if (words[1].replace('\n', '') == "0"): priv = "00"
            if (words[1].replace('\n', '') == "1"): priv = "01"
            if (words[1].replace('\n', '') == '2'): priv = "10"
            if (words[1].replace('\n', '') == "3"): priv = "11"
            #end
        else:
            #begin
            print("instraction",'[', x[0:-1] ,']',"is translating...\n")
            if(x != '\n'):
                #begin
                dex = decode(x, priv)
                if(dex != None):
                    #begin 
                    dFile.writelines(dex + "\n")
                    a = int(BitArray(bin=dex).bin,2)
                    bytes16 = a.to_bytes(16, byteorder='little', signed=False)
                    binFile.write(bytes16[0:8])
                    #end
                else: 
                    print("Unknown instraction: ", x)
                    break
                #end
            #end
        #end    
    
    dFile.close()
    sFile.close()
    return 0
    #end



#entry point
if(main(sys.argv) == 0):
    print("successfull")
else:
    print("Error in main function")