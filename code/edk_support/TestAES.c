#include "xparameters.h"
#include "stdio.h"
#include "xbasic_types.h"
#include "xio.h"

// from xparameters
// #define XPAR_AES_DDR_0_BASEADDR .....


// Test cases
#define PLAIN_1_HI   0x00112233
#define PLAIN_1_MH   0x44556677
#define PLAIN_1_ML   0x8899AABB
#define PLAIN_1_LO   0xCCDDEEFF
#define IVIN_1_HI    0x00000000
#define IVIN_1_MH    0x00000000
#define IVIN_1_ML    0x00000000
#define IVIN_1_LO    0x00000000
#define KEYIN_2_HI   0x2b7e1516
#define KEYIN_2_MH   0x28aed2a6
#define KEYIN_2_ML   0xabf71588
#define KEYIN_2_LO   0x09cf4f3c
#define KEYIN_1_HI   0x00010203
#define KEYIN_1_MH   0x04050607
#define KEYIN_1_ML   0x08090a0b
#define KEYIN_1_LO   0x0c0d0e0f
#define CRYPT_1_HI   0x3925841d
#define CRYPT_1_MH   0x02dc09fb
#define CRYPT_1_ML   0xdc118597
#define CRYPT_1_LO   0x196a0b32

// mettre à jour le expected
#define EXPECT_1_HI 0x69c4e0d8
#define EXPECT_1_MH 0x6a7b0430
#define EXPECT_1_ML 0xd8cdb780
#define EXPECT_1_LO 0x70b4c55a

//  signal slv_reg0                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- commands
//  signal slv_reg1                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- din LSW
//  signal slv_reg2                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- din 1
//  signal slv_reg3                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- din 2
//  signal slv_reg4                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- din MSW
//  signal slv_reg5                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- key LSW
//  signal slv_reg6                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- key 1
//  signal slv_reg7                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- key 2
//  signal slv_reg8                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- key MSW
//  signal slv_reg9                       : std_logic_vector(0 to C_SLV_DWIDTH-1); -- dout LSW
//  signal slv_reg10                      : std_logic_vector(0 to C_SLV_DWIDTH-1); -- dout 1
//  signal slv_reg11                      : std_logic_vector(0 to C_SLV_DWIDTH-1); -- dout 2
//  signal slv_reg12                      : std_logic_vector(0 to C_SLV_DWIDTH-1); -- dout MSW
//  signal slv_reg13                      : std_logic_vector(0 to C_SLV_DWIDTH-1); -- out state


void WriteSlaveReg( Xuint32 reg_idx, Xuint32 data )
{
	XIo_Out32( (void*) XPAR_AES_DDR_0_BASEADDR+0x4*reg_idx, data );
}



void ReadSlaveReg( Xuint32 reg_idx, Xuint32 * data )
{
	*data = XIo_In32( (void*) XPAR_AES_DDR_0_BASEADDR+0x4*reg_idx );
}

int main()
{
	// Attention: tous les registres sont inversés
	// prendre le symétrique

	WriteSlaveReg( 0, 0 );

	WriteSlaveReg( 1, PLAIN_1_LO );
	WriteSlaveReg( 2, PLAIN_1_ML );
	WriteSlaveReg( 3, PLAIN_1_MH ); 
	WriteSlaveReg( 4, PLAIN_1_HI ); 
	WriteSlaveReg( 5, KEYIN_1_LO );
	WriteSlaveReg( 6, KEYIN_1_ML );
	WriteSlaveReg( 7, KEYIN_1_MH );
	WriteSlaveReg( 8, KEYIN_1_HI ); 

	// On fait une encryption
	WriteSlaveReg( 0, 0x20000000 );

	// Front montant pour charger la clé
	WriteSlaveReg( 0, 0 );
	WriteSlaveReg( 0, 0x40000000 );
	WriteSlaveReg( 0, 0 );

	// Front montant pour lancer le processus
	WriteSlaveReg( 0, 0 );
	WriteSlaveReg( 0, 0x80000000 | 0x10000000);
	
	//printf("coucou !\n");

	// On attend la donnée de sortie


	// Configuration du bit 3 du reg. 0 pour programmer une faute
	// voir fichier user_logic.vhd

}



