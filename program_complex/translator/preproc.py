###########################################
# Preprocessor for SMP Assembler language #
###########################################

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

ctOpcodeTable = {
        "BL"    :   "0100",   
        "BOI"   :   "0100",
        "BOR"   :   "0100",
        "BI"    :   "0100",
        "BR"    :   "0100"
}
def split_str(instr):
    instrTemp = instr.replace(',', ' ')
    instrTemp = instrTemp.replace('[', '')
    instrTemp = instrTemp.replace(']', '')
    instrTemp = instrTemp.replace('\n', '')
    instrTemp = re.sub('\s+',' ',instrTemp)
    words = instrTemp.split(' ')
    return words

def replace_CT(instr, num_lable):
    words = split_str(instr)
    words[1] = str(num_lable)
    return words[0] + ' ' +  words[1] + '\n'

def get_lable(word):
    return word[0:-1]

def this_CT(word):
    itype = word.upper()
    conditional = itype[0:2]
    cond = icond.get(conditional.upper())
    if cond != None:
        itype = itype[2:]
    opcode = ctOpcodeTable.get(itype)
    return opcode != None

def get_val_CTinstr(words):
    if(this_CT(words[0])):
        return words[1]
    else:
        return None

def this_not_Num(word):
    return 1

def this_Lable(word):
    return (word[-1] == ':')

def lable_proc(instrs):
    lables_ct = {'':''}
    lable_cntr = 0
    for counter, x in enumerate(instrs):
        #begin
        lable = split_str(x)[0]
        if(this_Lable(lable)):
            lables_ct[get_lable(lable)] = counter - lable_cntr
            lable_cntr = lable_cntr + 1
        #end    
    return lables_ct


def decode_CT(instr, lables_ct):
    #begin
    words = split_str(instr)
    num_lable = 0
    if(this_CT(words[0])):
        #begin
        lable = get_val_CTinstr(words)
        if(lable == None):
            return instr
        
        if(this_not_Num(lable)):
            #begin
            if(lable in lables_ct):
                #begin
                num_lable = lables_ct[lable]
                print('replace:', '[',instr[0:-1], ']', ' to ','[' ,replace_CT(instr, num_lable)[0:-1], ']')
                return replace_CT(instr, num_lable)
                #end
            else:
                return instr
            #end    
        else:
            return instr
        #end    
    #end    
    else:
        return instr


def main(argv):
    #begin
    sFileName = 'sourse_preproc_test.smpasm'
    dFileName = 'sourse_preproc_out.smpasm'
    sFile  = open(sFileName, 'r')
    dFile  = open(dFileName, 'w')
    if ((dFile.mode != 'w') | (sFile.mode != 'r')):
        #begin
        #file error
        print("File error\n")
        return 1
        #end
    instrs = sFile.readlines()
    lables_ct = {'':''}
    lables_ct = lable_proc(instrs)
    print(lables_ct)
    for x in  instrs:
        #begin
        dex = decode_CT(x, lables_ct)
        if(dex != None):
            dFile.writelines(dex)
        #end    
    return 0
    #end    


#entry point
if(main(sys.argv) == 0):
    print("successfull")
else:
    print("Error in main function")