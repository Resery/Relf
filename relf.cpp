/*
* @Author: resery
* @Date:   2020-06-10 18:09:29
* @Last Modified by:   resery
* @Last Modified time: 2020-06-11 02:03:28
*/

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <elf.h>
#include <iomanip>

using namespace std;

void help(){
	cout << "There is Resery's elf interpreter." <<endl;
	cout << " Usage: relf <option> file" <<endl;
	cout << " Display information about the contents of ELF format files" <<endl;
	cout << " Options are:" <<endl;
	cout << "  -h --file-header       Display the ELF file header" <<endl;
	cout << "  -l --program-headers   Display the program headers" <<endl;
	cout << "  -S --section-headers   Display the sections' header" <<endl;
	cout << "  -s --syms              Display the symbol table" <<endl;
	cout << "  -r --relocs            Display the relocations (if present)" <<endl;
	cout << "  -H --help              Display the help information" <<endl;
}

void fileheader(const char *pbuff)
{
    cout << "ELF Header: " <<endl;
    cout << "  Magic:    ";
    for(int i = 0;i<EI_NIDENT;++i)   //e_ident[EI_NIDENT]
    {
        cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)pbuff[i] << " ";
        //printf("%02X", pbuff[i]);
        //putchar(' ');
    }
    cout << endl;
    cout << "  Class:    ";
    switch(pbuff[4])
    {
        case 0:
            cout << "                            Invalid class" <<endl;
            break;
        case 1:
            cout << "                            ELF32" <<endl;
            break;
        case 2:
            cout << "                            ELF64" <<endl;
            break;
        default:
            cout << "                            ERROR" <<endl;
            break;
    }
    cout << "  Data:     ";
    switch(pbuff[5])
    {
        case 0:
            cout << "                            Invalid data encoding" <<endl;
            break;
        case 1:
            cout << "                            2's complement, little endian" <<endl;
            break;
        case 2:
            cout << "                            2's complement, big endian" <<endl;
            break;
        default:
            cout << "                            ERROR" <<endl;
            break;
    }
    cout << "  Version:                              1(current)" <<endl;
    cout << "  OS/ABI:                               UNIX - System V" <<endl;
    cout << "  ABI Version:                          0" <<endl;
    pbuff += EI_NIDENT;

    cout << "  Type:     ";
    switch(*(uint16_t*)pbuff)
    {
        case 0:
            cout << "                            无文件类型" <<endl;
            break;
        case 1:
            cout << "                            可重定位文件" <<endl;
            break;
        case 2:
            cout << "                            可执行文件" <<endl;
            break;
        case 3:
            cout << "                            共享目标文件" <<endl;
            break;
        case 4:
            cout << "                            核心转储文件" <<endl;
            break;
        case 65024:
            cout << "                            特定的操作系统" <<endl;
            break;
        case 65279:
            cout << "                            特定的操作系统" <<endl;
            break;
        case 65280:
            cout << "                            处理器指定下限" <<endl;
            break;
        case 65535:
            cout << "                            处理器指定上限" <<endl;
            break;
        default:
            cout << "                            ERROR" <<endl;
            break;
    }

    pbuff += sizeof(uint16_t);
    cout << "  Machine:  ";
    switch(*(uint16_t*)pbuff)
    {
        case EM_NONE:
            cout << "                            No machine" <<endl;
            break;
        case EM_M32:
            cout << "                            AT&T WE 32100" <<endl;
            break;
        case EM_SPARC:
            cout << "                            SPARC" <<endl;
            break;
        case EM_386:
            cout << "                            Intel 80386" <<endl;
            break;
        case EM_68K:
            cout << "                            Motorola 68000" <<endl;
            break;
        case EM_88K:
            cout << "                            Motorola 88000" <<endl;
            break;
        case EM_860:
            cout << "                            Intel 80860" <<endl;
            break;
        case EM_MIPS:
            cout << "                            MIPS I Architecture" <<endl;
            break;
        case EM_S370:
            cout << "                            IBM System/370 Processor" <<endl;
            break;
        case EM_MIPS_RS3_LE:
            cout << "                            MIPS RS3000 Little-endian" <<endl;
            break;
        case EM_PARISC:
            cout << "                            Hewlett-Packard PA-RISC" <<endl;
            break;
        case EM_VPP500:
            cout << "                            Fujitsu VPP500" <<endl;
            break;
        case EM_SPARC32PLUS:
            cout << "                            Enhanced instruction set SPARC" <<endl;
            break;
        case EM_960:
            cout << "                            Intel 80960" <<endl;
            break;
        case EM_PPC:
            cout << "                            PowerPC" <<endl;
            break;
        case EM_PPC64:
            cout << "                            64-bit PowerPC" <<endl;
            break;
        case EM_V800:
            cout << "                            NEC V800" <<endl;
            break;
        case EM_FR20:
            cout << "                            Fujitsu FR20" <<endl;
            break;
        case EM_RH32:
            cout << "                            TRW RH-32" <<endl;
            break;
        case EM_RCE:
            cout << "                            Motorola RCE" <<endl;
            break;
        case EM_ARM:
            cout << "                            Advanced RISC Machines ARM" <<endl;
            break;
        case EM_ALPHA:
            cout << "                            Digital Alpha" <<endl;
            break;
        case EM_SH:
            cout << "                            Hitachi SH" <<endl;
            break;
        case EM_SPARCV9:
            cout << "                            SPARC Version 9" <<endl;
            break;
        case EM_TRICORE:
            cout << "                            Siemens Tricore embedded processor" <<endl;
            break;
        case EM_ARC:
            cout << "                            Argonaut RISC Core, Argonaut Technologies Inc." <<endl;
            break;
        case EM_H8_300:
            cout << "                            Hitachi H8/300" <<endl;
            break;
        case EM_H8_300H:
            cout << "                            Hitachi H8/300H" <<endl;
            break;
        case EM_H8S:
            cout << "                            Hitachi H8/500" <<endl;
            break;
        case EM_IA_64:
            cout << "                            Intel IA-64 processor architecture" <<endl;
            break;
        case EM_MIPS_X:
            cout << "                            Stanford MIPS-X" <<endl;
            break;
        case EM_COLDFIRE:
            cout << "                            Motorola ColdFire" <<endl;
            break;
        case EM_68HC12:
            cout << "                            Motorola M68HC12" <<endl;
            break;
        case EM_MMA:
            cout << "                            Fujitsu MMA Multimedia Accelerator" <<endl;
            break;
        case EM_PCP:
            cout << "                            Siemens PCP" <<endl;
            break;
        case EM_NCPU:
            cout << "                            Sony nCPU embedded RISC processor" <<endl;
            break;
        case EM_NDR1:
            cout << "                            Denso NDR1 microprocesso" <<endl;
            break;
        case EM_STARCORE:
            cout << "                            Motorola Star*Core processor" <<endl;
            break;
        case EM_ME16:
            cout << "                            STMicroelectronics ST100 processor" <<endl;
            break;
        case EM_ST100:
            cout << "                            Intel IA-64 processor architecture" <<endl;
            break;
        case EM_TINYJ:
            cout << "                            Advanced Logic Corp. TinyJ embedded processor family" <<endl;
            break;
        case EM_X86_64:
            cout << "                            AMD X86-64 arrchitecture" <<endl;
            break;
        case EM_PDSP:
            cout << "                            Sony DSP Processor" <<endl;
            break;
        case EM_FX66:
        	cout << "                            Siemens FX66 microcontroller" <<endl;
            break;
        case EM_ST9PLUS:
        	cout << "                            STMicroelectronics ST9+ 8/16 bit microcontroller" <<endl;
            break;
        case EM_ST7:
        	cout << "                            STMicroelectronics ST7 8-bit microcontroller" <<endl;
            break;
        case EM_68HC16:
        	cout << "                            Motorola MC68HC16 Microcontroller " <<endl;
            break;
        case EM_68HC11:
        	cout << "                            Motorola MC68HC11 Microcontroller " <<endl;
            break;
        case EM_68HC08:
        	cout << "                            Motorola MC68HC08 Microcontroller " <<endl;
            break;
        case EM_68HC05:
        	cout << "                            Motorola MC68HC05 Microcontroller " <<endl;
            break;
        case EM_SVX:
        	cout << "                            Silicon Graphics SVx" <<endl;
            break;
        case EM_ST19:
        	cout << "                            Digital VAX" <<endl;
            break;
        case EM_CRIS:
        	cout << "                            Axis Communications 32-bit embedded processor" <<endl;
            break;
        case EM_JAVELIN:
        	cout << "                            Infineon Technologies 32-bit embedded processor" <<endl;
            break;
        case EM_FIREPATH:
        	cout << "                            Element 14 64-bit DSP Processor" <<endl;
            break;
        case EM_ZSP:
        	cout << "                            LSI Logic 16-bit DSP Processor" <<endl;
            break;
        case EM_MMIX:
        	cout << "                            Donald Knuth's educational 64-bit processor" <<endl;
            break;
        case EM_HUANY:
        	cout << "                            Harvard University machine-independent object files" <<endl;
            break;
        case EM_PRISM:
        	cout << "                            SiTera Prism" <<endl;
            break;
        case EM_AVR:
        	cout << "                            Atmel AVR 8-bit microcontroller" <<endl;
            break;
        case EM_FR30:
        	cout << "                            Fujitsu FR30" <<endl;
            break;
        case EM_D10V:
        	cout << "                            Mitsubishi D10V" <<endl;
            break;
        case EM_D30V:
        	cout << "                            Mitsubishi D30V" <<endl;
            break;
        case EM_V850:
        	cout << "                            NEC v850" <<endl;
            break;
        case EM_M32R:
        	cout << "                            Mitsubishi M32R" <<endl;
            break;
        case EM_MN10300:
        	cout << "                            Matsushita MN10300" <<endl;
            break;
        case EM_MN10200:
        	cout << "                            Matsushita MN10200" <<endl;
            break;
        case EM_PJ:
        	cout << "                            picoJava" <<endl;
            break;
        case EM_OPENRISC:
        	cout << "                            OpenRISC 32-bit embedded processor" <<endl;
            break;
        case EM_ARC_A5:
        	cout << "                            ARC Cores Tangent-A5" <<endl;
            break;
        case EM_XTENSA:
        	cout << "                            Tensilica Xtensa Architecture" <<endl;
            break;
        default:
            cout << "                            ERROR" <<endl;
            break;
    }
    pbuff += sizeof(uint16_t);
    cout << "  version:                              0X1" <<endl;
    pbuff += sizeof(uint32_t);
    cout << "  Entry point address:                  0x";
    cout << *(uint64_t*)pbuff <<endl;
    pbuff += sizeof(uint64_t);
    cout << "  Start of program headers:             ";
    cout << std::dec << *(uint64_t*)pbuff << "(bytes into file)" <<endl;
    pbuff += sizeof(uint64_t);
    cout << "  Start of section headers:             ";
    cout << std::dec << *(uint64_t*)pbuff << "(bytes into file)" <<endl;
    pbuff += sizeof(uint64_t);
    cout << "  Flags:                                0x0" <<endl;
    pbuff += sizeof(Elf32_Word);
	cout << "  Size of this header:                  ";
    cout << std::dec << *(Elf32_Half*)pbuff << "(bytes into file)" <<endl;
    pbuff += sizeof(Elf32_Half);
    cout << "  Size of program headers:              ";
    cout << std::dec << *(Elf32_Half*)pbuff << "(bytes into file)" <<endl;
    pbuff += sizeof(Elf32_Half);
    cout << "  Number of program headers:            ";
    cout << std::dec << *(Elf32_Half*)pbuff << "(bytes into file)" <<endl;
    pbuff += sizeof(Elf32_Half);
    cout << "  Size of section headers:              ";
    cout << std::dec << *(Elf32_Half*)pbuff << "(bytes into file)" <<endl;
    pbuff += sizeof(Elf32_Half);
    cout << "  Number of section headers:            ";
    cout << std::dec << *(Elf32_Half*)pbuff << "(bytes into file)" <<endl;
    pbuff += sizeof(Elf32_Half);
    cout << "  Section header string table index:    ";
    cout << std::dec << *(Elf32_Half*)pbuff << "(bytes into file)" <<endl;
}

void sectionheader(const char *pbuff)
{
    int nNumSec = *(Elf64_Half*)(pbuff + 60);
    Elf64_Ehdr* pfilehead = (Elf64_Ehdr*)pbuff;
    Elf64_Half eshstrndx = pfilehead->e_shstrndx;
    Elf64_Shdr* psecheader = (Elf64_Shdr*)(pbuff + pfilehead->e_shoff);
    Elf64_Shdr* pshstr = (Elf64_Shdr*)(psecheader + eshstrndx);
    char* pshstrbuff = (char *)(pbuff + pshstr->sh_offset);
    cout << "There are " << nNumSec << "section headers, starting at offset " <<  *(Elf64_Off*)(pbuff + 40) << ":" <<endl;
    cout << "Section Header:" <<endl;
    cout << "  [Nr] Name              Type              Address           Offset           Size              EntSize          Flags  Link  Info  Align"<<endl;
    for(int i = 0;i<nNumSec;++i)
    {
		if(i==0){
			cout << dec << "  [" <<  i << "]                    ";
		}
		else if(i<10){
			cout << dec << "  [" <<  i << "]  ";
			cout.setf(ios::left);
			cout.fill(' ');
			cout.width(18);
			cout << (char *)(psecheader[i].sh_name + pshstrbuff);
			cout.unsetf(ios::left);
		}
		else{
			cout << dec << "  [" <<  i << "] ";
			cout.setf(ios::left);
			cout.fill(' ');
			cout.width(18);
			cout << (char *)(psecheader[i].sh_name + pshstrbuff);
			cout.unsetf(ios::left);
		}
        switch(psecheader[i].sh_type)
        {
            case SHT_NULL:
            	cout.setf(ios::left);cout.width(18);cout << "NULL"; break;
            case SHT_PROGBITS:
                cout.setf(ios::left);cout.width(18);cout << "PROGBITS";break;
            case SHT_SYMTAB:
                cout.setf(ios::left);cout.width(18);cout << "SYMTAB";break;
            case SHT_STRTAB:
                cout.setf(ios::left);cout.width(18);cout << "STRTAB";break;
            case SHT_RELA:
            	cout.setf(ios::left);cout.width(18);cout << "RELA";break;
            case SHT_HASH:
                cout.setf(ios::left);cout.width(18);cout << "GNU_HASH";break;
            case SHT_DYNAMIC:
                cout.setf(ios::left);cout.width(18);cout << "DYNAMIC";break;
            case SHT_NOTE:
                cout.setf(ios::left);cout.width(18);cout << "NOTE";break;
            case SHT_NOBITS:
                cout.setf(ios::left);cout.width(18);cout << "NOBITS";break;
            case SHT_REL:
                cout.setf(ios::left);cout.width(18);cout << "REL";break;
            case SHT_SHLIB:
                cout.setf(ios::left);cout.width(18);cout << "SHLIB";break;
            case SHT_DYNSYM:
                cout.setf(ios::left);cout.width(18);cout << "DYNSYM";break;
            case SHT_INIT_ARRAY:
                cout.setf(ios::left);cout.width(18);cout << "INIT_ARRY";break;
            case SHT_FINI_ARRAY:
                cout.setf(ios::left);cout.width(18);cout << "FINI_ARRY";break;
            case SHT_PREINIT_ARRAY:
                cout.setf(ios::left);cout.width(18);cout << "PREINIT_ARRAY";break;
            case SHT_GNU_HASH:
                cout.setf(ios::left);cout.width(18);cout << "GNU_HASH";break;               
            case SHT_GNU_ATTRIBUTES:
                cout.setf(ios::left);cout.width(18);cout << "GNU_ATTRIBUTES";break;
            case SHT_GNU_LIBLIST:
                cout.setf(ios::left);cout.width(18);cout << "GNU_LIBLIST";break;
            case SHT_GNU_verdef:
                cout.setf(ios::left);cout.width(18);cout << "GNU_verdef";break;
            case SHT_GNU_verneed:
                cout.setf(ios::left);cout.width(18);cout << "GNU_verneed";break;
            case SHT_GNU_versym:
                cout.setf(ios::left);cout.width(18);cout << "GNU_versym";break;
            default:
                cout.setf(ios::left);cout.width(18);cout << "NONE";break;
        }
        cout.unsetf(ios::left);
		cout << std::hex << std::setw(16) << std::setfill('0') << (unsigned int)psecheader[i].sh_addr;
		cout << "  ";
		cout << std::hex << std::setw(8) << std::setfill('0') << (unsigned int)psecheader[i].sh_offset;
        cout << "         ";
        cout <<std::hex << std::setw(16) << std::setfill('0') << psecheader[i].sh_size;
        cout << "  ";
        cout << std::hex << std::setw(16) << std::setfill('0') << psecheader[i].sh_entsize;
        unsigned int ai_link = 5;
        unsigned int ai_info = 24;
        unsigned long int ai_align=8;
        unsigned int ms_link = 0;
        unsigned int ms_info = 0;
        unsigned long int ms_align=1;
        cout.setf(ios::left);
            switch (psecheader[i].sh_flags) {
                case 0:
                    cout << setw(10) << std::setfill(' ') << " ";
                    cout << dec << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << dec << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << dec << psecheader[i].sh_addralign <<endl;
                    break;
                   
                case SHF_WRITE:
                    cout << setw(10) << std::setfill(' ') << " W";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case SHF_ALLOC:
                    cout << setw(10) << std::setfill(' ') << " A";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case SHF_EXECINSTR:
                    cout << setw(10) << std::setfill(' ') << " X";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case 3:
                    cout << setw(10) << std::setfill(' ') << " WA";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case 5://WX
                    cout << setw(10) << std::setfill(' ') << " WX";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case 6://AX
                    cout << setw(10) << std::setfill(' ') << " AX";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case 7://WAX
                    cout << setw(10) << std::setfill(' ') << " WAX";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case SHF_MASKPROC://MS
                	cout << setw(10) << std::setfill(' ') << " MS";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case 66:
                	cout << setw(10) << std::setfill(' ') << " AI";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case 48:
                	cout << setw(10) << std::setfill(' ') << " MS";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                    break;
                case SHF_MERGE:
                	cout << setw(10) << std::setfill(' ') << " M";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                case SHF_STRINGS:
                	cout << setw(10) << std::setfill(' ') << " S";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                case SHF_INFO_LINK:
                	cout << setw(10) << std::setfill(' ') << " I";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                case SHF_LINK_ORDER:
                	cout << setw(10) << std::setfill(' ') << " L";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                case SHF_OS_NONCONFORMING:
                	cout << setw(10) << std::setfill(' ') << " O";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                case SHF_GROUP:
                	cout << setw(10) << std::setfill(' ') << " G";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                case SHF_TLS:
                	cout << setw(10) << std::setfill(' ') << " T";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                case SHF_EXCLUDE:
                	cout << setw(10) << std::setfill(' ') << " E";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                case SHF_COMPRESSED:
                	cout << setw(10) << std::setfill(' ') << " C";
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_link;
                    cout << setw(6) << std::setfill(' ') << psecheader[i].sh_info;
                    cout << psecheader[i].sh_addralign <<endl;
                default:
                    cout << " None" <<endl;
                    break;
            }

    }
    cout << "Key to Flags:" <<endl;
    cout << "  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)" <<endl;
    cout << "  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)" <<endl;
    cout << "  O (extra OS processing required) o (OS specific), p (processor specific)" <<endl;
}

void outputsyminfo(const Elf64_Sym *psym, const char *pbuffstr, int ncount)
{
    cout << "   ";
    cout.setf(ios::left);
    cout << setw(6) << std::setfill(' ') << "Num:";
    cout << setw(18) << std::setfill(' ') << "Value:";
    cout << setw(6) << std::setfill(' ') << "Size:";
    cout << setw(8) << std::setfill(' ') << "Type:";
    cout << setw(7) << std::setfill(' ') << "Bind:";
    cout << setw(9) << std::setfill(' ') << "Vis:";
    cout << setw(5) << std::setfill(' ') << "Ndx:";
    cout << "Name:" <<endl;
    //printf("%s  %s    %s   %s      %s  %s\r\n",
    //       "Size", "Type", "Bind", "Vis", "Ndx", "Name");
    for(int i = 0;i<ncount;++i)
    {
        cout << "    ";
        cout.unsetf(ios::left);
        cout << setw(2) << std::setfill(' ') << i;
        cout.setf(ios::left);
        cout << setw(3) << std::setfill(' ') << ":";
		cout.unsetf(ios::left);
        cout << std::hex << std::setw(16) << std::setfill('0') << (unsigned int)psym[i].st_value;
		cout << "  ";
		cout.setf(ios::left);
		cout << setw(6) << std::setfill(' ') << psym[i].st_size;
        char typelow = ELF32_ST_TYPE(psym[i].st_info);
        char bindhig = ELF32_ST_BIND(psym[i].st_info);
        switch(typelow)
        {
            case STT_NOTYPE:
                cout << setw(8) << std::setfill(' ') << "NOTYPE";
                break;
            case STT_OBJECT:
                cout << setw(8) << std::setfill(' ') << "OBJECT";
                break;
            case STT_FUNC:
                cout << setw(8) << std::setfill(' ') << "FUNC";
                break;
            case STT_SECTION:
                cout << setw(8) << std::setfill(' ') << "SECTION";
                break;
            case STT_FILE:
                cout << setw(8) << std::setfill(' ') << "FILE";
                break;
            default:
                cout << setw(8) << std::setfill(' ') << "NONE";
                break;
        }
        switch(bindhig)
        {
            case STB_LOCAL:
                cout << setw(7) << std::setfill(' ') << "LOCAL";
                break;
            case STB_GLOBAL:
                cout << setw(7) << std::setfill(' ') << "GLOBAL";
                break;
            case STB_WEAK:
                cout << setw(7) << std::setfill(' ') << "WEAK";
                break;
            default:
                break;
        }
        cout << std::dec <<setw(7) << std::setfill(' ') << (unsigned int)psym[i].st_other;
        cout.unsetf(ios::left);
        switch(psym[i].st_shndx)
        {
            case SHN_UNDEF:
                cout << setw(5) << setfill(' ') << "UND";
                cout << " ";
                cout << psym[i].st_name + pbuffstr <<endl;
                break;
                //printf("%s  %s\r\n", "UND", psym[i].st_name + pbuffstr);break;
            case SHN_ABS:
                cout << setw(5) << setfill(' ') << "ABS";
                cout << " ";
                cout << psym[i].st_name + pbuffstr <<endl;
                break;
            case SHN_COMMON:
                cout << setw(5) << setfill(' ') << "COM";
                cout << " ";
                cout << psym[i].st_name + pbuffstr <<endl;
                break;
            default:
                cout << setw(5) << setfill(' ') << psym[i].st_shndx;
                cout << " ";
                cout << psym[i].st_name + pbuffstr <<endl;
                break;
        }
    }
}

void tableheader(const char *pbuff)
{
    Elf64_Ehdr* pfilehead = (Elf64_Ehdr*)pbuff;
    Elf64_Half eshstrndx = pfilehead->e_shstrndx;
    Elf64_Shdr* psecheader = (Elf64_Shdr*)(pbuff + pfilehead->e_shoff);
    Elf64_Shdr* pshstr = (Elf64_Shdr*)(psecheader + eshstrndx);
    char* pshstrbuff = (char *)(pbuff + pshstr->sh_offset);
    
    for(int i = 0;i<pfilehead->e_shnum;++i)
    {
        if(!strcmp(psecheader[i].sh_name + pshstrbuff, ".dynsym") || !strcmp(psecheader[i].sh_name + pshstrbuff, ".symtab"))
        {
            Elf64_Sym* psym = (Elf64_Sym*)(pbuff + psecheader[i].sh_offset);
            int ncount = psecheader[i].sh_size / psecheader[i].sh_entsize;
            char* pbuffstr = (char*)((psecheader + psecheader[i].sh_link)->sh_offset + pbuff);
            cout << "Symbol table " << "\'" << psecheader[i].sh_name + pshstrbuff;
            cout << "\'" << " contains " << ncount << " entries:" <<endl;
            outputsyminfo(psym, pbuffstr, ncount);
            cout <<endl;
            continue;
        }
    }
}

void programheader(const char *pbuff)
{
    Elf64_Ehdr* pfilehead = (Elf64_Ehdr*)pbuff;
    Elf64_Phdr* pproheader = (Elf64_Phdr*)(pbuff + pfilehead->e_phoff);
    Elf64_Shdr* psecheader = (Elf64_Shdr*)(pbuff + pfilehead->e_shoff);
    Elf64_Shdr* pshstr = (Elf64_Shdr*)(psecheader + pfilehead->e_shstrndx);
    char* pstrbuff = (char*)(pbuff + pshstr->sh_offset);
    cout <<endl;
    cout << "Elf file type is";
    switch(pfilehead->e_type)
    {
        case 0:
            cout << " No file type" <<endl;
            //printf(" No file type\r\n");
            break;
        case 1:
            cout << " Relocatable file" <<endl;
            //printf(" Relocatable file\r\n");
            break;
        case 2:
            cout << " Executable file" <<endl;
            //printf(" Executable file\r\n");
            break;
        case 3:
            cout << " Shared object file" <<endl;
            //pprintf(" Shared object file\r\n");
            break;
        case 4:
            cout << " Core file" <<endl;
            //pprintf(" Core file\r\n");
            break;
        default:
            cout << " ERROR" <<endl;
            //pprintf(" ERROR\r\n");
            break;
    }
    cout << "Entry point 0x";
    cout << std::hex << (unsigned int)pfilehead->e_entry <<endl;
    //printf("入口点位置 0X%0lX\r\n", pfilehead->e_entry);
    cout << "There are ";
    cout << std::dec << pfilehead->e_phnum;
    cout << " program headers, starting at offset ";
    cout << std::dec << pfilehead->e_phoff <<endl;
    cout << endl;
    cout << "Program Headers:" <<endl;
    cout << "  ";
    cout.setf(ios::left);
    cout << setw(16) << setfill(' ') << "Type";
    cout << setw(18) << setfill(' ') << "Offset";
    cout << setw(18) << setfill(' ') << "VirtAddr";
    cout << setw(18) << setfill(' ') << "PhysAddr";
    cout << setw(18) << setfill(' ') << "FileSiz";
    cout << setw(18) << setfill(' ') << "MemSiz";
    cout << setw(8) << setfill(' ') << "Flags";
    cout << "Align" <<endl;
    for(int i=0;i<pfilehead->e_phnum;++i)
    {
        switch(pproheader[i].p_type)
        {
            case PT_NULL:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "PHDR";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
                break;
            case PT_LOAD:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "LOAD";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
                break;
            case PT_DYNAMIC:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "DYNAMIC";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_INTERP:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "INTERP";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_NOTE:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "NOTE";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_SHLIB:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "SHLIB";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_PHDR:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "PHDR";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_TLS:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "TLS";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_NUM:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "NUM";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_GNU_EH_FRAME:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "GNU_EH_FRAME";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_GNU_RELRO:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "GNU_RELRO";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            	break;
            case PT_GNU_STACK:
                cout << "  ";
                cout.setf(ios::left);
                cout << setw(16) << setfill(' ') << "GNU_STACK";
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_vaddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_paddr << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_filesz << "  ";
                cout << std::hex << setw(16) << setfill('0') << pproheader[i].p_memsz << "  ";
            default:
                break;
        }
        //
        cout.setf(ios::left);
        switch(pproheader[i].p_flags)
        {
            case PF_X:
                cout << setw(8) << setfill(' ') << "  E";
                cout << std::hex << pproheader[i].p_align <<endl;
				break;
            case PF_W:
                cout << setw(8) << setfill(' ') << " W ";
                cout << std::hex << pproheader[i].p_align <<endl;
				break;
            case PF_R:
                cout << setw(8) << setfill(' ') << "R  ";
                cout << std::hex << pproheader[i].p_align <<endl;
				break;
            case PF_X|PF_W:
                cout << setw(8) << setfill(' ') << " WE";
                cout << std::hex << pproheader[i].p_align <<endl;
				break;
            case PF_X|PF_R:
                cout << setw(8) << setfill(' ') << "R E";
                cout << std::hex << pproheader[i].p_align <<endl;
                break;
            case PF_W|PF_R:
                cout << setw(8) << setfill(' ') << "RW";
                cout << std::hex << pproheader[i].p_align <<endl;
				break;
            case PF_X|PF_R|PF_W:
                cout << setw(8) << setfill(' ') << "RWE";
                cout << std::hex << pproheader[i].p_align <<endl;
				break;
            default:
                cout <<endl;
                break;
        }
        if(PT_INTERP == pproheader[i].p_type){
        	cout << "                              [Requesting program interpreter: ";
        	cout << (char*)(pbuff + pproheader[i].p_offset);
        	cout << "]" <<endl;
        }	
    }
    cout << endl;
    cout << " Section to Segment mapping:" <<endl;
    cout << "  Segment Sections..." <<endl;
    for(int i=0;i<pfilehead->e_phnum;++i)
    {
        cout << std::dec << "   " << setw(4) << setfill(' ') << i;	
        for(int n = 0;n<pfilehead->e_shnum;++n)
        {
            Elf64_Off temp = psecheader[n].sh_addr + psecheader[n].sh_size;
            if((psecheader[n].sh_addr>pproheader[i].p_vaddr && psecheader[n].sh_addr<pproheader[i].p_vaddr + pproheader[i].p_memsz)  ||
                    (temp > pproheader[i].p_vaddr && temp<=pproheader[i].p_vaddr + pproheader[i].p_memsz))
            {
                cout << (char*)(psecheader[n].sh_name + pstrbuff);
            }
        }
        cout <<endl;
    }
}

void relocheader(const char *pbuff)
{
    Elf64_Ehdr* pfilehead = (Elf64_Ehdr*)pbuff;
    Elf64_Shdr* psecheader = (Elf64_Shdr*)(pbuff + pfilehead->e_shoff);
    Elf64_Shdr* pshstr = (Elf64_Shdr*)(psecheader + pfilehead->e_shstrndx);
    char* pstrbuff = (char*)(pbuff + pshstr->sh_offset);
    for(int i = 0;i<pfilehead->e_shnum;++i)
    {
        if(!strncmp(psecheader[i].sh_name + pstrbuff, ".rel", 4))
        {
            int ncount = psecheader[i].sh_size / psecheader[i].sh_entsize;
            cout << endl << "Relocation section \'" <<  psecheader[i].sh_name + pstrbuff;
            cout << "\' at offset " << std::hex << (unsigned int)psecheader[i].sh_offset;        
            cout << " contains " << ncount << " entries:" <<endl;
            Elf64_Rela* preltable = (Elf64_Rela*)(pbuff + psecheader[i].sh_offset);
            cout.setf(ios::left);
            cout << setw(18) << setfill(' ') << "Offset" << setw(18) << setfill(' ') << "Info" << setfill(' ') << setw(18) << setfill(' ') <<  "Type" << setfill(' ') <<  setw(18) << "Sym.Value" << setfill(' ') << setw(18) << "Sym.Name + Addend" << endl;
            int symnum = psecheader[i].sh_link;
            int strnum = psecheader[symnum].sh_link;
            char* prelstrbuf = (char*)(psecheader[strnum].sh_offset + pbuff);
            Elf64_Sym* psym = (Elf64_Sym*)(pbuff + psecheader[symnum].sh_offset);
            for(int n = 0;n<ncount;++n)
            {
                cout.unsetf(ios::left);
                cout << std::hex << setw(16) << setfill('0') << preltable[n].r_offset << "  ";
                cout << std::hex << setw(16) << setfill('0') << preltable[n].r_info << "  ";
               	cout.setf(ios::left);
               	switch(ELF64_R_TYPE(preltable[n].r_info))
                {
                    case R_386_NONE:
                        cout << setw(18) << setfill(' ') << "R_386_NONE";
                        break;
                    case R_386_32:
                        cout << setw(18) << setfill(' ') << "R_386_32";
                        break;
                    case R_386_PC32:
                        cout << setw(18) << setfill(' ') << "R_386_PC32";
                        break;
                    case R_386_GOT32:
                        cout << setw(18) << setfill(' ') << "R_386_GOT32";
                        break;
                    case R_386_PLT32:
                        cout << setw(18) << setfill(' ') << "R_386_PLT32";
                        break;
                    case R_386_COPY:
                        cout << setw(18) << setfill(' ') << "R_386_COPY";
                        break;
                    case R_386_GLOB_DAT:
                        cout << setw(18) << setfill(' ') << "R_386_GLOB_DAT";
                        break;
                    case R_386_JMP_SLOT:
                        cout << setw(18) << setfill(' ') << "R_386_JMP_SLOT";
                        break;
                    case R_386_RELATIVE:
                        cout << setw(18) << setfill(' ') << "R_386_RELATIVE";
                        break;
                    case R_386_GOTOFF:
                        cout << setw(18) << setfill(' ') << "R_386_GOTOFF";
                        break;
                    case R_386_GOTPC:
                        cout << setw(18) << setfill(' ') << "R_386_GOTPC";
                        break;
                    default:
                        break;
                }
                cout << std::hex << setw(16) << setfill('0') << (psym + ELF64_R_SYM(preltable[n].r_info))->st_value << "  ";
                cout << (char*)(prelstrbuf + (psym + ELF64_R_SYM(preltable[n].r_info))->st_name) << " + ";
                cout << preltable[n].r_addend <<endl;
            }
        }
    }
}

int main(int argc,char * argv[]){
	if(argc!=3 || !strcmp(argv[1],"-H")){
		if(strcmp(argv[1],"-H")){
			cout << "Input Error!" <<endl;
		}
		cout <<endl;
		help();
		return 0;
	}

	int fd = open(argv[2],O_RDONLY,0);
	if(fd==-1){
		cout << "Error: Failed to open the file.No such file named " << argv[2] << endl;
		return 0;
	}

	long int end = lseek(fd, 0, SEEK_END);
    long int begin = lseek(fd, 0, SEEK_SET);
    char* pbuff = (char *)malloc(end);

	if(!pbuff){
		cout << "Error: Failed to allocate memory";
		return 0;
	}

	memset(pbuff, 0, end);
    if(-1 == read(fd, pbuff, end))
    {
        perror("Error: Failed to read the file");
        return 0;
    }

    if(!strcmp(argv[1], "-H")){
    	help();
    	return 0;
    }

	if(!strcmp(argv[1],"-h"))
	{
		fileheader(pbuff);
		return 0;
	}
	if(!strcmp(argv[1],"-S"))
	{
		sectionheader(pbuff);
		return 0;
	}
	if(!strcmp(argv[1],"-s"))
	{
		tableheader(pbuff);
		return 0;
	}
	if(!strcmp(argv[1],"-l"))
	{
		programheader(pbuff);
		return 0;
	}
	if(!strcmp(argv[1], "-r"))
    {
        relocheader(pbuff);
        return 0;
    }
    return 0;
}