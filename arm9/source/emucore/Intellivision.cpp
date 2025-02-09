
#include "Intellivision.h"

/**
 * Initializes all of the basic hardware included in the Intellivision
 * Master Component as well as the Intellivoice peripheral.
 * This method is called only once when the Intellivision is constructed.
 */
Intellivision::Intellivision()
    : Emulator("Intellivision"),
      player1Controller(0, "Hand Controller #1"),
      player2Controller(1, "Hand Controller #2"),
      psg(0x01F0, &player1Controller, &player2Controller),
      RAM8bit(RAM8BIT_SIZE, 0x0100, 8),
      RAM16bit(RAM16BIT_SIZE, 0x0200, 16),
      execROM("Executive ROM", "exec.bin", 0, 2, 0x1000, 0x1000),
      grom("GROM", "grom.bin", 0, 1, 0x0800, 0x3000),
      gram(),
      cpu(&memoryBus, 0x1000, 0x1004),
      stic(&memoryBus, &grom, &gram)
{
    // define the video pixel dimensions
    videoWidth = 160;
    videoHeight = 192;

    //make the pin connections from the CPU to the STIC
    stic.connectPinOut(AY38900_PIN_OUT_SR1, &cpu, CP1610_PIN_IN_INTRM);
    stic.connectPinOut(AY38900_PIN_OUT_SR2, &cpu, CP1610_PIN_IN_BUSRQ);
    cpu.connectPinOut(CP1610_PIN_OUT_BUSAK, &stic, AY38900_PIN_IN_SST);

    //add the player one hand controller
    AddInputConsumer(&player1Controller);

    //add the player two hand controller
    AddInputConsumer(&player2Controller);

    //add the 8-bit RAM
    AddRAM(&RAM8bit);

    //add the 16-bit RAM
    AddRAM(&RAM16bit);

    //add the executive ROM
    AddROM(&execROM);

    //add the GROM
    AddROM(&grom);

    //add the GRAM
    AddRAM(&gram);

    //add the backtab ram
    AddRAM(&stic.backtab);

    //add the CPU
    AddProcessor(&cpu);

    //add the STIC
    AddProcessor(&stic);
    AddVideoProducer(&stic);

    //add the STIC registers
    AddRAM(&stic.registers);

    //add the PSG
    AddProcessor(&psg);
    AddAudioProducer(&psg);

    //add the PSG registers
    AddRAM(&psg.registers);

    //add the Intellivoice
    AddPeripheral(&intellivoice);
}

BOOL Intellivision::SaveState(const CHAR* filename)
{
	return FALSE;
}

BOOL Intellivision::LoadState(const CHAR* filename)
{
	return FALSE;
}
