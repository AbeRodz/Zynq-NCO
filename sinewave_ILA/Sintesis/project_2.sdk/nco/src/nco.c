/*
 * nco.c
 *
 *  Created on: Nov 30, 2024
 *      Author: Abraham R.
 */

#include "xparameters.h"
#include "xil_io.h"
#include "nco_ip.h"


/*
 * REG 0 ->  frequency word
 * REG 1 -> wave type
 * REG 2 -> wave output
 * REG 3 -> enable
 *
 */

#define NCO_BASE_ADDR XPAR_NCO_IP_0_S00_AXI_BASEADDR
#define REG_FREQUENCY_OFFSET 0x00
#define REG_WAVE_TYPE_OFFSET 0x04
#define REG_WAVE_OUTPUT_OFFSET 0x08
#define REG_ENABLE_OFFSET 0x0C


// NCO configuration and state
typedef struct {
    int32_t base_addr;        // Base address of the NCO
    int32_t frequency;        // Current frequency tuning word
    int32_t wave_type;        // Current wave type
    int32_t enable;           // Enable status (0 or 1)
    int32_t freq_step;        // Step size for frequency adjustment
    int32_t min_freq;         // Minimum frequency tuning word
    int32_t max_freq;         // Maximum frequency tuning word
} NCO_Config;

// Function to initialize NCO settings
void NCO_Init(NCO_Config *nco, int32_t base_addr, int32_t init_freq, int32_t freq_step, int32_t min_freq, int32_t max_freq) {
    nco->base_addr = base_addr;
    nco->frequency = init_freq;
    nco->wave_type = 0x01; // Default to sine wave
    nco->enable = 0x01;   // Enable by default
    nco->freq_step = freq_step;
    nco->min_freq = min_freq;
    nco->max_freq = max_freq;
}

// Function to write frequency tuning word
void NCO_SetFrequency(NCO_Config *nco, int32_t frequency_tuning_word) {
    nco->frequency = frequency_tuning_word;
    NCO_IP_mWriteReg(nco->base_addr, REG_FREQUENCY_OFFSET, nco->frequency);
    xil_printf("Frequency tuning word set to: 0x%08X\r\n", nco->frequency);
}

// Function to set wave type
void NCO_SetWaveType(NCO_Config *nco, int32_t wave_type) {
    nco->wave_type = wave_type;
    NCO_IP_mWriteReg(nco->base_addr, REG_WAVE_TYPE_OFFSET, nco->wave_type);
    xil_printf("Wave type set to: %u\r\n", nco->wave_type);
}

// Function to enable/disable NCO
void NCO_SetEnable(NCO_Config *nco, int32_t enable) {
    nco->enable = enable;
    NCO_IP_mWriteReg(nco->base_addr, REG_ENABLE_OFFSET, nco->enable);
    xil_printf("Enable signal set to: %u\r\n", nco->enable);
}

// Function to dynamically adjust frequency
void NCO_AdjustFrequency(NCO_Config *nco) {
    nco->frequency += nco->freq_step;

    // Clamp the frequency to stay within bounds
    if (nco->frequency > nco->max_freq) {
        nco->frequency = nco->max_freq;
    } else if (nco->frequency < nco->min_freq) {
        nco->frequency = nco->min_freq;
    }

    NCO_SetFrequency(nco, nco->frequency); // Apply the new frequency
}


// Function to read wave output
int16_t NCO_ReadWaveOutput(NCO_Config *nco) {
    int32_t wave_output = NCO_IP_mReadReg(nco->base_addr, REG_WAVE_OUTPUT_OFFSET);
    return wave_output & 0xFFFF; // Return lower 16 bits
}


int main(void) {
	int i;
    xil_printf("-- Inicio de NCO IP Core --\r\n");



    NCO_Config nco;
    NCO_Init(&nco, NCO_BASE_ADDR, 0x00100000, 0x00010000, 0x00010000, 0xFFFFFFFF);

    NCO_SetFrequency(&nco, nco.frequency);
    NCO_SetWaveType(&nco, nco.wave_type);
    NCO_SetEnable(&nco, nco.enable);

    while(1) {

        NCO_AdjustFrequency(&nco);

        // Read and display wave output
        int16_t wave_output = NCO_ReadWaveOutput(&nco);
        xil_printf("Wave output: %d\r\n", wave_output);
        for (i=0; i<9999999;i++);
    }

    NCO_SetEnable(&nco, 0x00);

    xil_printf("-- Fin de NCO IP Core --\r\n");
    return 0;
}
