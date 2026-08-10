#include "idt.h"

/*
static IDT* idt_desc = (IDT*)0x00000000;
idtr_descriptor.limit = (sizeof(IDT) * TOTAL_INTERRUPTS) - 1;
idtr_descriptor.base = 0x00000000;
*/

static IDT idt_desc[256];
static idtr idtr_descriptor;
static bool capslock = false;

extern void no_interrupt();
extern void isr_keyboard();
extern void idt_load(idtr* ptr);

uint8_t tolower(uint8_t ch) 
{
    if ((ch >= 65) && (ch <= 90))
    {
        ch = ch + 32; 
    }

    return ch;
}

void idt_init()
{
    //for idt_desc[i] = 0
    //memset(idt_desc, 0, sizeof(idt_desc));


    //butun tablo sifirlaniyor
    uint64_t* idt_ptr = (uint64_t *)idt_desc;

    for (size_t i = 0; i < 256; i++) 
    {
        idt_ptr[i] = 0;
    }
    

    //tablonun bulundugu nokta (*struct, sizeof(struct))
    idtr_descriptor.limit = sizeof(idt_desc) - 1;
    idtr_descriptor.base = (uint32_t)idt_desc;
        
    //butun kesmeler bos fonksiyona baglaniyor
    for (size_t i = 0; i < TOTAL_INTERRUPTS; i++)
    {
        idt_set(i, no_interrupt);
    }

    //pic adresi kaydiriliyor
    pic_remap();
    
    //idt_set(0, isr_divide_zero);    

    //idt_set(0x20, isr_timer);
    idt_set(0x21, isr_keyboard);

    
    idt_load(&idtr_descriptor);
}

void no_interrupt_handler()
{
    //printf("AAA!\n");
    outb(PIC_MASTER, EOI);
}
/*
_______________________________________
|  1 bit               |   7 bit      |
.______________________|______________.
| key released/pressed |  key id      |
|______________________|______________|

0 = key pressed 
1 = key released
*/
void idt_keyboard_handler()
{
    uint8_t scancode = inb(PORT_KEYBOARD_DATA);

    //7 bitlik id kismini al
    uint8_t key = scancode & 0x7F;
            
    //bu tus tablo icinde tanimlimi
    if(scancode_names[key] != NULL)
    {
        //tus basildi ise
        if(scancode & 0x80) 
        {            
            if(key == IDT_KEY_CAPSLOCK)   
            {
                capslock = !capslock;
            }
            else
            {
                uint8_t input = (uint8_t)*scancode_names[key];

                if(capslock == false)
                {
                    printf("%c", tolower(input));
                }
                else
                {
                    printf("%c", input);
                }
            }                                 
        }
    }
        
    outb(PIC_MASTER, EOI);
}

void idt_set(int intrerrupt_no, void* address)
{
    IDT* desc = &idt_desc[intrerrupt_no];

    desc->offset_lower = (uint32_t)address & 0xffff;
    desc->selector = 0x08;
    desc->zero = 0;
    //kesme kapisi (interrupt gate) => 0x8e
    //tuzak kapisi (trap gate) => 0x8f
    desc->types_attr = 0x8e; 

    desc->offset_upper = (uint32_t)address >> 16;
}

/*
https://wiki.osdev.org/Exceptions
https://wiki.osdev.org/Interrupt_Vector_Table

Master 8259
-----------
IVTOffset  INT     IRQ 	 Description
.____________________________________________________.
|0x0020	   0x08	    0	  PIT                        |
|0x0024	   0x09	    1	  Keyboard                   |
|0x0028	   0x0A	    2	  8259A slave controller     |
|0x002C	   0x0B	    3	  COM2 / COM4                |
|0x0030	   0x0C	    4	  COM1 / COM3                |
|0x0034	   0x0D	    5	  LPT2                       |
|0x0038	   0x0E	    6	  Floppy controller          |
|0x003C	   0x0F	    7	  LPT1                       |
.____________________________________________________.

Slave 8259
----------
IVTOffset	INT 	IRQ 	Description
.____________________________________________________.
|0x01c0	    0x70	 8	      RTC                    |
|0x01C4	    0x71	 9	      Unassigned             |
|0x01C8	    0x72	 10	      Unassigned             |
|0x01CC	    0x73	 11	      Unassigned             |
|0x01D0	    0x74	 12	      Mouse controller       |
|0x01D4	    0x75	 13	      Math coprocessor       |
|0x01D8	    0x76	 14	      Hard disk controller 1 |
|0x01DC	    0x77	 15	      Hard disk controller 2 |
.____________________________________________________.
      
https://www.geeksforgeeks.org/computer-organization-architecture/command-words-of-8259-pic/
https://helppc.netcore2k.net/hardware/8259


*/
void pic_remap()
{
    outb(PIC_MASTER, INIT_COMMAND_WORD);
    outb(PIC_SLAVE, INIT_COMMAND_WORD);

    outb(PIC_MASTER_DATA, 0x20); // master irq + 0x20
    outb(PIC_SLAVE_DATA, 0x28);  // slave irq + 0x28

    /*    
	Initialization Command Word 3 at Port 21h and A1h

	│7│6│5│4│3│2│1│0│  ICW3 for Master Device
	 │ │ │ │ │ │ │ └──── 1=interrupt request 0 has slave, 0=no slave
	 │ │ │ │ │ │ └───── 1=interrupt request 1 has slave, 0=no slave
	 │ │ │ │ │ └────── 1=interrupt request 2 has slave, 0=no slave <========== 0x04
	 │ │ │ │ └─────── 1=interrupt request 3 has slave, 0=no slave 
	 │ │ │ └──────── 1=interrupt request 4 has slave, 0=no slave
	 │ │ └───────── 1=interrupt request 5 has slave, 0=no slave
	 │ └────────── 1=interrupt request 6 has slave, 0=no slave
	 └─────────── 1=interrupt request 7 has slave, 0=no slave
    */
    outb(PIC_MASTER_DATA, ICW3_MASTER); //Efendi PIC'i kole ile bagliyoruz (master.irq2 = slave)

    /*
    │7│6│5│4│3│2│1│0│  ICW3 for Slave Device
	 │ │ │ │ │ └─┴─┴──── master interrupt request slave is attached to
	 └─┴─┴─┴─┴───────── must be zero
    */
    outb(PIC_SLAVE_DATA, ICW3_SLAVE);  //Kole PIC'i kirbac ile IRQ2 pinine bagliyoruz (slave.irq2 = master)

    outb(PIC_MASTER_DATA, ICW4);
    outb(PIC_SLAVE_DATA, ICW4);

    outb(PIC_MASTER_DATA, PIC_UNMASK_ALL);
    outb(PIC_SLAVE_DATA, PIC_UNMASK_ALL);
}