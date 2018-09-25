// *********************************************************************************************
// PIC32MZ Family 12.5msps Interleaved ADC sample code example
//
// SUMMARY:
//    TARGET CPU: PIC32MZxxEFxx >= 100 pin
//    OSC INPUT TYPE = 24 MHz Clock oscillator (EC Mode)
//    SYSCLK=200 MHz
//    PBCLK = 100 MHz
//    ADC TAD = SYSCLK / 4 = 50 MHz = 20ns
//    ADC SAMC=3 TAD
//    Interleaved ADC SAMPLE RATE = 12.5msps(max)
//    INTERLEAVED ADCS
//      ADC 0: 12bit mode, ADCTRG1<TRGSRC0> Output Compare 1
//      ADC 1: 12bit mode, ADCTRG1<TRGSRC1> Output Compare 3
//      ADC 2: 12bit mode, ADCTRG1<TRGSRC2> Output Compare 5
//      ADC 3: 12bit mode, ADCTRG1<TRGSRC3> Timer3
//    
//    interleaved ADC0/1/2/3 with AN0/AN1/AN2/AN3 inputs respectively
//    (12.5 msps combined throughput rate)
//
// USER NOTE:
// Although the number of interleaved ADC's the user wishes to use is selectable, it is required
// "FOR THIS CODE ONLY" that those ADCx modules be sequential starting from AN0 to the last sequential
// ANx to be used for interleaving. In different code than below, any combination of interleaved ADC are allowed
//
//   NOTE: (FYI only)
//     A user could configure the PIC32MZ to have multiple sets of 
//     interleaved ADC's to measure multiple different analog input streams like:
//           -----------------------------  EXAMPLE  1  CONFIGURATION  -----------------------------
//       1) AN0-AN1 pair with triggers OC5 and TMR3 @ 6.25msps(max)
//       2) AN2-AN3 pair with triggers OC1 and TMR5 @ 6.25msps(max)
//           -----------------------------  EXAMPLE  2  CONFIGURATION  -----------------------------
//       3) ADC0-ADC2 (3) ADCs with triggers OC1, OC3 and TMR5 @ 8.333333 msps(max) combined
//       4) ADC3-ADC4 (2) ADCs with triggers OC5 and TMR3 @ 6.25msps(max)
//           -----------------------------  EXAMPLE  3  CONFIGURATION  -----------------------------
//       5) ADC0-ADC3 (4) ADCs with triggers OC1, OC3, OC5 and TMR3 @ 12.5msps(max) combined
// *********************************************************************************************
//
// *********************************************************************************************
// USER NOTE:
// Although the number of interleaved ADC's the user wishes to use is selectable in this code 
// example, it is required "FOR THIS CODE ONLY" that those ADCx modules be sequential starting
// from AN0 to the last sequential ANx to be used for interleaving. 
// In a user?s own original code however they can define any combination
// of ADC's they prefer.
//
// ****************************************************************************
//        F I L E   I N C L U D E S
// ****************************************************************************
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/attribs.h>

//----------------------------------------------------------
//                         BF1SEQ0
//----------------------------------------------------------
#pragma config TSEQ =       0x0000
#pragma config CSEQ =       0xFFFF

// *************************************************************************************************
//                                  U S E R     D E F I N E S
// Note: User must configure as required
// *************************************************************************************************
#define TAD_TRIGGER_SOURCE_SPACING 2.5 // TAD trigger spacing value from ADC Table 13 or 15 accordingly  w/12bit & 4 interleaved ADCs
#define INTERLEAVED_ADC_COUNT      4        // Number of interleaved ADC (Cannot be <2 or >4). Changing this value will
                                                                                   // automatically scale the number of interleaved ADC and triggers utilized in this code.
#define ADC_DMA_BUFF_SIZE      1024  //ADC DMA buffer size

//
// *************************************************************************************************
// EQUATION #1: (Assumptions: INTERLEAVED_ADC_COUNT=4)
//    (Fastest Triggering possible)
//    TAD_TRIGGER_SOURCE_SPACING(min)  = 
//        = ((SAMC(min) + (((#bits Resolution+1) + ADJ) * TAD)) / INTERLEAVED_ADC_COUNT)
//        = (3+12+1) + ADJ) * TAD)) / 4 ADCs)
//        = (16 + ADJ) * TAD)) / 4 ADCs
//        = (16 + 0) * TAD)) / 4 ADCs
//        = 4.0 TAD (minimum trigger spacing possible)
//
// NOTE: "ADJ" term = A user selected whole number adjustment factor between 0-4 
//                    that must yield a Minimum TAD Trigger interval that equates to an exact 
//                    multiple of a ½ TAD. This represents the minimum TAD_TRIGGER_SOURCE_SPACING
//                    and therefore the fastest throughput possible. Additional TAD_TRIGGER_SOURCE_SPACING
//                    and hence ADC Throughput Rates are possible in ½ TAD trigger spacing increments.
//                    (See examples 1-3 below)
//
//  NOTE: Once the minimum, TAD trigger spacing possible is determined, the user can configure for any 
//        additional sampling frequency required if needed in 0.5 TAD trigger spacing increments.
//
//        Example 1: (INTERLEAVED_ADC_COUNT=4)
//          TAD_TRIGGER_SOURCE_SPACING(min) = 4
//          interleaved ADC Throughput rate = TAD clock freq / TAD_TRIGGER_SOURCE_SPACING
//                                          = 50Mhz / 4.0(min)
//                                          = 12.5msps
//
//        Example 2: (INTERLEAVED_ADC_COUNT=4)
//          TAD_TRIGGER_SOURCE_SPACING = 4.5
//          interleaved ADC Throughput rate = TAD clock freq / TAD_TRIGGER_SOURCE_SPACING
//                                          = 50Mhz / 4.5
//                                          = 11.111111msps
//
//        Example 3: (INTERLEAVED_ADC_COUNT=4)
//          TAD_TRIGGER_SOURCE_SPACING = 5.0
//          interleaved ADC Throughput rate = TAD clock freq / TAD_TRIGGER_SOURCE_SPACING
//                                          = 50Mhz / 5.0
//                                          = 10msps
//
// *************************************************************************************************
//
// *************************************************************************************************
//                               P R O G R A M    D E F I N E S 
//                                       (User Do Not Change)
// Note: 
//       TAD_TRIGGER_SOURCE_SPACING is multiplied by (2) because
//       OCx and TMR3 trigger source time base is 2x faster than an ADC TAD clock.
//       2 TMR3 clocks = 1 ADC TAD Clock
// **************************************************************************************************
// ------------------------------------------------------------------------------------------------------------------
// NOTE: Remember that the peripheral trigger clock frequency is 2x TAD clock frequency.
//       This is why the 2x. The -1 is because the Si peripheral triggers are always 
//       on (match+1), so to compensate for correct timing subtract 1. 
//

#define ADC_TRIG        (TAD_TRIGGER_SOURCE_SPACING * 2)	 //
#define OC1_ADC_TRIG    (ADC_TRIG - 1)      			 //
#define OC3_ADC_TRIG    ((2 * ADC_TRIG) - 1)			 //
#define OC5_ADC_TRIG    ((3 * ADC_TRIG) - 1) 			 //
#define T3_ADC_TRIG     ((INTERLEAVED_ADC_COUNT * ADC_TRIG) - 1) //

#define ADC0_IRQ	59	//PIC32MZxxEFxx ADC0 Data_0 IRQ number
#define ADC1_IRQ	60	//PIC32MZxxEFxx ADC1 Data_1 IRQ number
#define ADC2_IRQ	61	//PIC32MZxxEFxx ADC2 Data_2 IRQ number
#define ADC3_IRQ	62	//PIC32MZxxEFxx ADC3 Data_3 IRQ number

#define VirtAddr_TO_PhysAddr(v) ((unsigned long)(v) & 0x1FFFFFFF)

// *************************************************************************************************
//        F U N C T I O N     P R O T O T Y P E S
// *************************************************************************************************
void init_ADC(void);
void init_DMA(void);
void init_TMR3(void);

// *************************************************************************************************
//        G L O B A L   V A R I A B L E S
// *************************************************************************************************
uint32_t __attribute__((coherent)) adc_bufA[INTERLEAVED_ADC_COUNT * ADC_DMA_BUFF_SIZE];
uint32_t __attribute__((coherent)) adc_bufB[INTERLEAVED_ADC_COUNT * ADC_DMA_BUFF_SIZE];
uint32_t adc_buf_index = 0;
bool adc_dma_buf_full_flg = 0;

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $                            M A I N       R O U T I N E                                                                         $
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
int main(void)
{
    // ******************************************************************************
    // CPU Performance Optimization:
    // ******************************************************************************
    register unsigned long tmp_cache;                 //KSEG0 cache enable
    asm("mfc0 %0,$16,0" :  "=r"(tmp_cache));
    tmp_cache = (tmp_cache & ~7) | 3;
    asm("mtc0 %0,$16,0" :: "r" (tmp_cache));
    
    PRECONbits.PFMWS=2;       //Flash wait states = 2 CPU clock cycles @ 200Mhz        
    PRECONbits.PREFEN = 2;    //Enable predictive prefetch for CPU instructions and CPU data
    PRISSbits.PRI7SS = 7;	//DMA Interrupt with priority level of 7 uses Shadow Set 7
    PRISSbits.PRI6SS = 6;	//Interrupt with priority level of 6 uses Shadow Set 6
    PRISSbits.PRI5SS = 5;	//Interrupt with priority level of 5 uses Shadow Set 5
    PRISSbits.PRI4SS = 4;	//Interrupt with priority level of 4 uses Shadow Set 4
    PRISSbits.PRI3SS = 3;	//Interrupt with priority level of 3 uses Shadow Set 3
    PRISSbits.PRI2SS = 2;	//Interrupt with priority level of 2 uses Shadow Set 2

    INTCONbits.MVEC = 1;	//Enable multi-vector interrupts
    __builtin_mtc0(12,0,(__builtin_mfc0(12,0) | 0x0001)); // Global Interrupt Enable 
        
    // ******************************************************************************
    // * Disable all ANx pins that are enabled by default on reset
    // ******************************************************************************
    /*ANSELA = 0xFFFF;		//Disable all analog ANx input pins
    ANSELBCLR = 0xFFFF;		//Disable all analog ANx input pins
    ANSELCCLR = 0xFFFF;		//Disable all analog ANx input pins
    ANSELDCLR = 0xFFFF;		//Disable all analog ANx input pins
    ANSELECLR = 0xFFFF;		//Disable all analog ANx input pins
    ANSELFCLR = 0xFFFF;		//Disable all analog ANx input pins
    ANSELGCLR = 0xFFFF;		//Disable all analog ANx input pins
    ANSELHCLR = 0xFFFF;		//Disable all analog ANx input pins
    ANSELJCLR = 0xFFFF;		//Disable all analog ANx input pins */

    // ******************************************************************************
    // Initialize and enable ADC(s) followed by ADC trigger sources 2nd
    // ******************************************************************************
    init_ADC();                //Initialize and enable interleaved ADCs first before PWM ADC triggers are enabled

    while(1)
    { 
        if(adc_dma_buf_full_flg)	//If current DMA buffer is full
        {
            adc_dma_buf_full_flg = 0;	//Clr DMA buff full flag

            //***********************************************************************
            // In main(), "adc_buf_index" represents the current active buffer being
            // filled as the companion buffer is already full.
            //***********************************************************************
            if(adc_buf_index == 0)	//if "adc_bufA" active then "adc_bufB" full
            {
                  //-----------------------------------------------------------------------------------------------------------------------
               	// User must process here previously filled ADC DMA Buffer B ptr starting at "adc_bufB"
                  //-----------------------------------------------------------------------------------------------------------------------
            }
            else			//if "adc_bufB" active then "adc_bufA" full
            {
                  //-----------------------------------------------------------------------------------------------------------------------
                	 // User must process here previously filled ADC DMA Buffer A ptr starting at "adc_bufA"
                  //-----------------------------------------------------------------------------------------------------------------------
            }
        }
        //*******************************************************
        //* USERS OTHER MAIN CODE GOES HERE
        //*******************************************************
    }        
} 


// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $        F U N C T I O N   S U B - R O U T I N E S                $
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    
 
// *********************************************************************************
// * init_ADC(void)
// *  I N T E R L E A V E D   A D C   I N I T I L I Z A T I O N   R O U T I N E
// *   Used analog inputs if:
// *      INTERLEAVED_ADC_COUNT  = 2   (Analog inputs, AN0 and AN1 only)
// *      INTERLEAVED_ADC_COUNT  = 3   (Analog inputs, AN0, AN1 and AN2 only)
// *      INTERLEAVED_ADC_COUNT  = 4   (Analog inputs, AN0, AN1, AN2 and AN3 only)
// *********************************************************************************
// *********************************************************************************
//  These steps are already done in this code example, this is just a reminder 
//   to the user for any new original code development.
//
// CAUTION:(Required)  
// 1) The user SHOULD always set the minimum sampling time of each Class_1 ADC 
//      equal to 3TAD as defined by ADCxTIME<SAMC>. 
// 2) The user should insure that the selected trigger source time base clock rate is 
//      exactly 2x faster than the ADC clock TAD rate. This will provide the highest 
//      timing resolution along with the most sampling rate options as defined in 
//      Table 13 or 15 accordingly in this app note. 
// 3) The user selected trigger sources have to be able to be mapped to a single 
//      synchronized time base.
//      For example:
//        a) TMR3 & OCx (x=1,3,5 PIC32MZxxxx)
//        b) TMR3 & OCx (x=1-4 PIC32MKxxGPxx)
//        c) PTMRx & TRIGx ( x=1-12 PIC32MKxxMCxx PWM)
//        d) PTMRx & STRIGx ( x=1-12 PIC32MKxxMCxx PWM)
// 4) In a same group of interleaved ADC?s a user ?MUST NOT? use two separate timer trigger sources.
//     Example: ADC0, ADC1 and ADC2 are being used in an interleaved group. 
//       Trigger sources can be any combination of valid ADC OCx edge triggered sources synchronized to a SINGLE TMRx.
//       It would not be allowed to use in the same group of interleaved ADCs OCx, TMR3 & TMR5 for example. 
//       Separate TMRx in different interleaved ADC groups is OK. 
// 5  If using the DMA for the ADC the user ?MUST? use SYSCLK as the ADC 
//     source clock, (i.e. ADCCON3<ADCSEL>).
// 6) User must configure ADC for 512 TAD warm-up time 
//     (ADCANCONbits.WKUPCLKCNT = 0x9) "BEFORE" enabling ADC.
// 7) Users SW  must wait for ADC BANGAP and ADC warm-up time "AFTER" 
//      enabling ADC and before activating the ADC trigger sources.
// 8) ADC must always be initialized 1st ?BEFORE? activating the ADC trigger sources
//
// NOTE: Failure to follow these recommendations will result in inaccurate ADC
//             data acquisition and poor performance.
//******************************************************************************
void init_ADC(void)
{
    ADC0CFG = DEVADC0;        //Load ADC0 Calibration values
    ADC1CFG = DEVADC1;        //Load ADC1 Calibration values
    ADC2CFG = DEVADC2;        //Load ADC2 Calibration values
    ADC3CFG = DEVADC3;        //Load ADC3 Calibration values
    ADC4CFG = DEVADC4;        //Load ADC4 Calibration values
    ADC7CFG = DEVADC7;        //Load ADC7 Calibration values

    ADCANCONbits.WKUPCLKCNT = 0x9; // ADC Warm up delay = (512 * TADx)
    ADCCON1bits.AICPMPEN = 0;	   //Disable ADC charge pump
    CFGCONbits.IOANCPEN = 0;	   //Disable ADC I/O charge pump

    // ******************************************************************************
    // * If using the DMA the user MUST use SYSCLK as the ADC source clock
    // ******************************************************************************
    ADCCON1bits.FSSCLKEN = 1;	//Fast synchronous SYSCLK to ADC control clock is enabled
    ADCCON3bits.ADCSEL = 1;        	// Select ADC input clock source = SYSCLK 200Mhz
    ADCCON3bits.CONCLKDIV = 1;     	// Analog-to-Digital Control Clock (TQ) Divider = SYSCLK/2

    // ******************************************************************************
    // * ADC0 Module setup:
    // *   TAD = SYSCLK/4, 6bit, SAMC=3TAD, OC1 Trigger
    // ******************************************************************************
    ANSELBSET = 0x1;		//Enable analog AN0 input
    ADC0TIMEbits.ADCDIV = 1;		// ADCx Clock Divisor, Divide by 2, 50Mhz
    ADC0TIMEbits.SAMC = 1;		// 3 TAD (Hardware enforced sample time)
    ADC0TIMEbits.SELRES = 0;	// ADC0 6bit resolution mode
    ADCTRG1bits.TRGSRC0 = 8;	// Set AN0 to trigger from OC1
    ADCANCONbits.ANEN0 = 1;		// Enable ADC0 analog bias/logic
    ADCCON3bits.DIGEN0 = 1;		// Enable ADC0 digital logic
    ADCGIRQEN1bits.AGIEN0 = 1;	//Enb ADC0 AN0 interrupts for DMA

    // ******************************************************************************
    // * ADC1 Module setup:
    // *   TAD = SYSCLK/4, 6bit, SAMC=3TAD
    // *   if(INTERLEAVED_ADC_COUNT == 2) TMR3 trigger else OC3 Trigger
    // ******************************************************************************
    ANSELBSET = 0x2;		//Enable analog AN1 input
    ADC1TIMEbits.ADCDIV = 1;		// ADCx Clock Divisor, Divide by 2, 50Mhz
    ADC1TIMEbits.SAMC = 1;		// 3 TAD
    ADC1TIMEbits.SELRES = 0;	// ADC1 6bit resolution mode

    ADCTRG1bits.TRGSRC1 = 9;	// Set ADC1 to trigger from OC3

    ADCANCONbits.ANEN1 = 1;		// Enable ADC1 analog bias/logic
    ADCCON3bits.DIGEN1 = 1;		// Enable ADC1 digital logic
    ADCGIRQEN1bits.AGIEN1 = 1;	//Enb ADC1 AN1 interrupts for DMA

    // ******************************************************************************
    // * ADC2 Module setup:
    // *    TAD = SYSCLK/4, 6bit, SAMC=3TAD, OC5 Trigger
    // *   if(INTERLEAVED_ADC_COUNT == 3) TMR3 trigger else OC5 Trigger
    // ******************************************************************************
    if(INTERLEAVED_ADC_COUNT  >  2)
    {
        ANSELBSET = 0x4;		//Enable analog AN2 input
        ADC2TIMEbits.ADCDIV = 1;	// ADCx Clock Divisor, Divide by 2, 50Mhz
        ADC2TIMEbits.SAMC = 1;	// 3 TAD
        ADC2TIMEbits.SELRES = 0;	// ADC2 6bit resolution mode

        ADCTRG1bits.TRGSRC2 = 10; // Set ADC2 to trigger from OC5

        ADCANCONbits.ANEN2 = 1;	// Enable ADC2 analog bias/logic
        ADCCON3bits.DIGEN2 = 1;	// Enable ADC2 digital logic      
        ADCGIRQEN1bits.AGIEN2 = 1;	//Enb ADC2 AN2 interrupts for DMA
    }

    // ******************************************************************************
    // * ADC3 Module setup:
    // *   if(INTERLEAVED_ADC_COUNT == 4)
    // *   TAD = SYSCLK/4, 6bit, SAMC=3TAD, TMR3 Trigger
    // ******************************************************************************
    if(INTERLEAVED_ADC_COUNT  >  3) 
    {
        ANSELBSET = 0x8;		//Enable analog AN3 input
        ADC3TIMEbits.ADCDIV = 1;	// ADCx Clock Divisor, Divide by 2, 50Mhz
        ADC3TIMEbits.SAMC = 1;	// 3 TAD
        ADC3TIMEbits.SELRES = 0;	// ADC3 6bit resolution mode
        ADCTRG1bits.TRGSRC3 = 6;	// Set ADC3 to trigger from TMR3
        ADCANCONbits.ANEN3 = 1;	// Enable ADC3 analog bias/logic
        ADCCON3bits.DIGEN3 = 1;	// Enable ADC3 digital logic     
        ADCGIRQEN1bits.AGIEN3 = 1;	//Enb ADC3 AN3 interrupts for DMA
    }

    ADCCON1bits.ON = 1;        		// Turn the ADC on

    // ******************************************************************************
    // * Waiting for ADC warm-up time and ADC bandgap reference to stabilize
    // ******************************************************************************
    while(!ADCCON2bits.BGVRRDY);	// Wait until the reference voltage is ready
    while(!ADCANCONbits.WKRDY0); 	// Wait until ADC0 is ready
    while(!ADCANCONbits.WKRDY1); 	// Wait until ADC1 is ready
    while(!ADCANCONbits.WKRDY2); // Wait until ADC2 is ready
    while(!ADCANCONbits.WKRDY3); // Wait until ADC3 is ready

    ADCDATA0;   // Read ADC data to make sure that data ready bits are clear.
    ADCDATA1;   //
    ADCDATA2;   //
    ADCDATA3;   //
        
    init_DMA();	//Initialize DMA
    init_TMR3();	//Initialize and enable ADC interleaved triggers
}

   
// ***************************************************************
// *    D M A   I N I T I A L I Z A T I O N   R O U T I N E   *
// ***************************************************************
void init_DMA(void)
{
    // **********************************************************
    // * Set the DMA trigger source.  Each interrupt on the indicated 
    // * ADC_DATA_VECTOR begins a DMA transfer.
    // **********************************************************
    DCH0ECONbits.CHSIRQ = ADC3_IRQ; //DMA_TRIGGER_ADC3_DATA3;

    // **********************************************************
    // * Enable DMA Channel Start IRQ.
    // **********************************************************
    DCH0ECONbits.SIRQEN = 1;	//DMA Chan_0 Start IRQ Enable

    // **********************************************************
    // * Set DMA Source Starting Address
    // **********************************************************
    DCH0SSA = (uint32_t) VirtAddr_TO_PhysAddr((const void *)&ADCDATA0);

    // **********************************************************
    // * Set DMA Source Size in bytes
    // **********************************************************
    if(INTERLEAVED_ADC_COUNT == 2) DCH0SSIZ = 8;  // ADC0 + ADC1, 4+4bytes = 8bytes
    if(INTERLEAVED_ADC_COUNT > 2) DCH0SSIZ = 12;  //ADC0 + ADC1 + ADC2 = 12bytes
    if(INTERLEAVED_ADC_COUNT > 3) DCH0SSIZ = 16;  //ADC0 + ADC1 + ADC2 + ADC3 = 16bytes

    // **********************************************************
    // * Set DMA Destination Starting Address
    // **********************************************************
    DCH0DSA = (uint32_t) VirtAddr_TO_PhysAddr((const void *)&adc_bufA[0]);

    // **********************************************************
    // * Set DMA Destination Size
    // **********************************************************
    DCH0DSIZ = (uint16_t) INTERLEAVED_ADC_COUNT*(ADC_DMA_BUFF_SIZE)*sizeof(adc_bufA[0]);

    // **********************************************************
    // * Set Cell Size
    // **********************************************************
    DCH0CSIZ = (uint16_t) sizeof(adc_bufA[0]);

    DCH0INTbits.CHDDIF = 0;	//Clr Chan Dest Done Int Flg
    DCH0INTbits.CHDDIE = 1;	//Enable DMA Destination Interrupt
    
    // **********************************************************
    // * Enable DMA channel 0
    // **********************************************************
    DCH0CONbits.CHEN = 1;	//DMA Chan 0 enable

    // **********************************************************
    // * Enable DMA and DMA interrupts
    // **********************************************************
    IFS4bits.DMA0IF = 0;	//Clr DMA Chan0 int flg
    IPC33bits.DMA0IP = 7;	//Set DMA Chan0 int priority 7
    IPC33bits.DMA0IS = 3;	//Set DMA Chan0 sub priority 3
    IEC4bits.DMA0IE = 1;	//Enable DMA Chan0 interrupt
    
    DMACONbits.ON = 1;	//Enb DMA
}


// *********************************************************************************
// * I N T E R L E A V E D   A D C   T R I G G E R    I N I T I A L I Z A T I O N
// *********************************************************************************
void init_TMR3(void)
{
    // *****************************************************************************
    // * AN0-ANx Interleaved Triggers: (x=1-3)
    // * Same analog input connected to all interleaved ANx inputs w/staggered triggers:
    // *****************************************************************************
    PR3 = T3_ADC_TRIG;		//ADC3 TRM3 Trigger throughput rate
    
    // ******************************************************************************
    // * ADC0 Trigger setup:
    // *   TMR3 = OC1 time base, continuous pulse 
    // ******************************************************************************
    CFGCONbits.OCACLK = 0;	//
    OC1CONbits.OCTSEL = 1;	//Timer"y" is clk source for OC1 module
    OC1CONbits.OCM = 5; 	//Init OC1 low; gen continuous output pulses
    OC1R = OC1_ADC_TRIG;	//ADC0 OC1 Trigger throughput rate
    OC1RS = OC1_ADC_TRIG+2;
    OC1CONSET = 0x8000;		// Enable OC1

    // ******************************************************************************
    // * ADCx Trigger setup:
    // *   TMR3 = OC3 time base, continuous pulse 
    // ******************************************************************************
    OC3CONbits.OCTSEL = 1;	//Timer"y" is clk source for OC3 module
    OC3CONbits.OCM = 5; 	//Init OC3 low; gen continuous output pulses
    OC3R = OC3_ADC_TRIG;	//ADC1 OC3 Trigger throughput rate
    OC3RS  = OC3_ADC_TRIG+2;
    OC3CONSET = 0x8000;	// Enable OC3

    // ******************************************************************************
    // * ADCy Trigger setup:
    // *   TMR3 = OC5 time base, continuous pulse 
    // ******************************************************************************
    OC5CONbits.OCTSEL = 1;	//Timer"y" is clk source for OC5 module
    OC5CONbits.OCM = 5; 	//Init OC5 low; gen continuous output pulses
    OC5R = OC5_ADC_TRIG;	//ADC2 OC5 Trigger throughput rate
    OC5RS  = OC5_ADC_TRIG+2;
    OC5CONSET = 0x8000;	// Enable OC5
    T3CONSET = 0x8000;		//Start TMR3

}  //End TMR3 Subroutine


// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $     I N T E R R U P T   S E R V I C E    R O U T I N E S        $
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// *************************************************************************************************
//        D M A   I S R (Interrupt Service Routine)
// *************************************************************************************************
void __attribute__((interrupt(ipl7auto), vector(_DMA0_VECTOR), aligned(16), nomips16)) isr ()
{
    IFS4bits.DMA0IF = 0;	//Clr DMA Chan 0 int flg
    DCH0INTbits.CHDDIF = 0;	//Clr DMA dest done flg

    adc_dma_buf_full_flg = 1;	//Current DMA buffer is full

    if(adc_buf_index == 0)	//if "adc_bufA" full, change DMA dest to "adc_bufB"
    {
        DCH0DSA = (uint32_t) VirtAddr_TO_PhysAddr((const void *)&adc_bufB[0]);
        adc_buf_index = 1; 
    }
    else			//if "adc_bufB" full, change DMA dest to "adc_bufA"
    {
        DCH0DSA = (uint32_t) VirtAddr_TO_PhysAddr((const void *)&adc_bufA[0]);
        adc_buf_index = 0; 
    }
    DCH0CONbits.CHEN = 1;	//DMA Chan 0 enable
}