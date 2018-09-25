///
/// @file
/// @copyright All code copyright Movidius Ltd 2015, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief   ISPParamsPP.c
///

// 1: Includes
// ----------------------------------------------------------------------------
#include <stdint.h>
#include "Cam214SIPPDebayerHdmi.h"

// 2:  Source Specific #defines and types  (typedef,enum,struct)
// ----------------------------------------------------------------------------
// 3: Global Data (Only if absolutely necessary)
// ----------------------------------------------------------------------------
// Bayer gain map (8.8)
uint16_t ispcLscMesh[ISPC_LSC_GAIN_MAP_W * ISPC_LSC_GAIN_MAP_H] ALIGNED(8) =
{
0x02c9, 0x02c9, 0x02c9, 0x0311, 0x026a, 0x02a5, 0x022f, 0x0263, 0x0206, 0x0236, 0x01e9, 0x0212, 0x01d6, 0x01f9, 0x01bf, 0x01e1, 0x01ae, 0x01cb, 0x01a2, 0x01ba, 0x0193, 0x01aa, 0x0186, 0x019b, 0x0180, 0x0190, 0x0178, 0x0187, 0x0173, 0x0180, 0x016f, 0x017d, 0x0171, 0x017b, 0x0171, 0x017c, 0x0174, 0x0181, 0x0179, 0x0187, 0x0182, 0x0193, 0x0189, 0x01a1, 0x0195, 0x01ab, 0x01a4, 0x01be, 0x01b3, 0x01d5, 0x01c7, 0x01ec, 0x01dc, 0x0206, 0x01ec, 0x0219, 0x0208, 0x023d, 0x022e, 0x026b,
0x02ba, 0x02ba, 0x02ba, 0x02c8, 0x0256, 0x0268, 0x0220, 0x022d, 0x01f5, 0x0207, 0x01d8, 0x01ea, 0x01c8, 0x01d4, 0x01b1, 0x01be, 0x01a0, 0x01ae, 0x0191, 0x019e, 0x0183, 0x0190, 0x0179, 0x0186, 0x0170, 0x017c, 0x0168, 0x0173, 0x0165, 0x0170, 0x0160, 0x016c, 0x0160, 0x016d, 0x0161, 0x016c, 0x0163, 0x0170, 0x0167, 0x0175, 0x016f, 0x017c, 0x0178, 0x0186, 0x0182, 0x0192, 0x0192, 0x01a1, 0x01a0, 0x01af, 0x01b1, 0x01c6, 0x01c5, 0x01da, 0x01d2, 0x01ed, 0x01e9, 0x0207, 0x0211, 0x023a,
0x0288, 0x0288, 0x0288, 0x02d1, 0x0235, 0x0270, 0x0209, 0x023b, 0x01e7, 0x0216, 0x01d0, 0x01f8, 0x01ba, 0x01df, 0x01a8, 0x01c8, 0x0197, 0x01b4, 0x0188, 0x01a1, 0x017c, 0x0191, 0x0171, 0x0184, 0x0167, 0x0178, 0x0161, 0x016f, 0x015d, 0x0169, 0x0159, 0x0165, 0x0158, 0x0164, 0x015a, 0x0166, 0x015d, 0x016a, 0x0162, 0x0172, 0x016a, 0x017b, 0x0173, 0x0186, 0x017e, 0x0195, 0x018c, 0x01a6, 0x019b, 0x01ba, 0x01ae, 0x01d2, 0x01c2, 0x01ea, 0x01d6, 0x0202, 0x01ea, 0x021d, 0x0204, 0x024d,
0x0277, 0x0277, 0x0277, 0x0287, 0x021c, 0x0237, 0x01f2, 0x0208, 0x01d1, 0x01e7, 0x01bb, 0x01d0, 0x01a6, 0x01bb, 0x0194, 0x01a8, 0x0183, 0x0197, 0x0175, 0x0187, 0x0169, 0x017b, 0x015e, 0x0170, 0x0156, 0x0167, 0x0150, 0x0160, 0x014b, 0x015b, 0x0148, 0x0158, 0x0146, 0x0157, 0x0148, 0x0159, 0x014b, 0x015c, 0x014f, 0x0160, 0x0155, 0x0168, 0x015d, 0x0171, 0x0168, 0x017c, 0x0174, 0x018a, 0x0183, 0x019a, 0x0193, 0x01ad, 0x01a6, 0x01c1, 0x01b8, 0x01d6, 0x01ca, 0x01eb, 0x01e8, 0x0218,
0x025e, 0x025e, 0x025e, 0x0298, 0x0219, 0x0250, 0x01f1, 0x0222, 0x01d6, 0x0201, 0x01c0, 0x01e6, 0x01ab, 0x01ce, 0x0198, 0x01b7, 0x0187, 0x01a1, 0x0177, 0x018e, 0x016b, 0x017f, 0x0160, 0x0171, 0x0157, 0x0166, 0x0151, 0x015d, 0x014b, 0x0156, 0x0148, 0x0152, 0x0148, 0x0152, 0x0149, 0x0153, 0x014d, 0x0158, 0x0152, 0x015e, 0x015a, 0x0168, 0x0163, 0x0173, 0x016e, 0x0181, 0x017c, 0x0193, 0x018b, 0x01a7, 0x019e, 0x01be, 0x01b1, 0x01d5, 0x01c7, 0x01f1, 0x01db, 0x020b, 0x01ef, 0x0238,
0x0248, 0x0248, 0x0248, 0x025a, 0x0202, 0x021b, 0x01dc, 0x01f2, 0x01c0, 0x01d6, 0x01ad, 0x01c0, 0x0197, 0x01ab, 0x0186, 0x0197, 0x0176, 0x0187, 0x0167, 0x0178, 0x015b, 0x016b, 0x0151, 0x015f, 0x0148, 0x0157, 0x0142, 0x0150, 0x013d, 0x014a, 0x013a, 0x0147, 0x0139, 0x0147, 0x013b, 0x0148, 0x013d, 0x014b, 0x0142, 0x0151, 0x0148, 0x0158, 0x014f, 0x0161, 0x015a, 0x016c, 0x0166, 0x017b, 0x0174, 0x0189, 0x0185, 0x019c, 0x0198, 0x01b1, 0x01aa, 0x01c7, 0x01bd, 0x01dd, 0x01d1, 0x0202,
0x023e, 0x023e, 0x023e, 0x0274, 0x0204, 0x0236, 0x01e0, 0x020d, 0x01c8, 0x01f0, 0x01b1, 0x01d5, 0x019c, 0x01bb, 0x0189, 0x01a5, 0x0178, 0x0190, 0x0169, 0x017d, 0x015b, 0x016d, 0x0151, 0x015f, 0x0147, 0x0154, 0x0141, 0x014a, 0x013c, 0x0145, 0x0139, 0x0140, 0x0138, 0x013f, 0x013a, 0x0141, 0x013d, 0x0146, 0x0143, 0x014d, 0x014b, 0x0157, 0x0155, 0x0163, 0x0160, 0x0170, 0x016e, 0x0182, 0x017d, 0x0195, 0x018f, 0x01ab, 0x01a3, 0x01c5, 0x01b8, 0x01e0, 0x01cf, 0x01fc, 0x01e1, 0x0222,
0x022e, 0x022e, 0x022e, 0x023b, 0x01ec, 0x0204, 0x01cc, 0x01e1, 0x01b4, 0x01c8, 0x019d, 0x01b1, 0x018a, 0x019c, 0x0178, 0x018a, 0x0168, 0x0178, 0x015a, 0x0168, 0x014e, 0x015b, 0x0143, 0x0150, 0x013c, 0x0147, 0x0135, 0x0140, 0x0130, 0x013b, 0x012d, 0x0138, 0x012c, 0x0137, 0x012d, 0x0139, 0x0130, 0x013c, 0x0135, 0x0142, 0x013b, 0x014a, 0x0143, 0x0153, 0x014d, 0x015f, 0x0159, 0x016c, 0x0167, 0x017c, 0x0177, 0x018f, 0x018a, 0x01a3, 0x019c, 0x01ba, 0x01b0, 0x01d1, 0x01c5, 0x01f6,
0x0226, 0x0226, 0x0226, 0x025d, 0x01f2, 0x0222, 0x01d4, 0x01fe, 0x01bb, 0x01e0, 0x01a5, 0x01c7, 0x0190, 0x01ad, 0x017c, 0x0196, 0x016a, 0x0181, 0x015b, 0x016e, 0x014e, 0x015e, 0x0143, 0x014f, 0x013a, 0x0144, 0x0132, 0x013a, 0x012c, 0x0133, 0x012a, 0x012f, 0x0129, 0x012f, 0x012b, 0x0130, 0x012f, 0x0135, 0x0136, 0x013d, 0x013d, 0x0147, 0x0147, 0x0153, 0x0153, 0x0162, 0x0161, 0x0172, 0x0170, 0x0185, 0x0183, 0x019c, 0x0196, 0x01b5, 0x01ad, 0x01d0, 0x01c4, 0x01ee, 0x01d5, 0x0213,
0x0215, 0x0215, 0x0215, 0x0227, 0x01dc, 0x01f4, 0x01be, 0x01d4, 0x01a7, 0x01bb, 0x0192, 0x01a5, 0x017e, 0x018f, 0x016c, 0x017c, 0x015c, 0x016b, 0x014e, 0x015b, 0x0143, 0x014f, 0x0138, 0x0143, 0x0130, 0x013a, 0x0129, 0x0132, 0x0124, 0x012c, 0x0121, 0x012a, 0x0121, 0x0129, 0x0121, 0x012a, 0x0124, 0x012f, 0x0129, 0x0135, 0x0130, 0x013c, 0x0138, 0x0146, 0x0142, 0x0153, 0x014d, 0x0160, 0x015a, 0x0170, 0x016b, 0x0183, 0x017d, 0x0197, 0x0192, 0x01ae, 0x01a6, 0x01c5, 0x01bc, 0x01e9,
0x0213, 0x0213, 0x0213, 0x0248, 0x01e5, 0x0211, 0x01ca, 0x01f1, 0x01b1, 0x01d4, 0x019a, 0x01b9, 0x0185, 0x019f, 0x0171, 0x0189, 0x015f, 0x0173, 0x0150, 0x0161, 0x0142, 0x0151, 0x0137, 0x0142, 0x012d, 0x0136, 0x0125, 0x012c, 0x0120, 0x0124, 0x011d, 0x0121, 0x011c, 0x0120, 0x011e, 0x0122, 0x0123, 0x0127, 0x0129, 0x012e, 0x0132, 0x0139, 0x013d, 0x0146, 0x0148, 0x0154, 0x0157, 0x0165, 0x0166, 0x0178, 0x0177, 0x018f, 0x018c, 0x01a7, 0x01a1, 0x01c3, 0x01b8, 0x01e0, 0x01d0, 0x020b,
0x0209, 0x0209, 0x0209, 0x0219, 0x01cf, 0x01e6, 0x01b5, 0x01cb, 0x019c, 0x01b1, 0x0187, 0x019a, 0x0173, 0x0185, 0x0161, 0x0171, 0x0152, 0x015f, 0x0144, 0x0151, 0x0138, 0x0143, 0x012e, 0x0138, 0x0126, 0x012d, 0x011f, 0x0125, 0x0119, 0x0120, 0x0117, 0x011d, 0x0116, 0x011c, 0x0116, 0x011e, 0x011a, 0x0122, 0x011f, 0x0128, 0x0125, 0x0131, 0x012f, 0x013b, 0x0139, 0x0147, 0x0144, 0x0155, 0x0151, 0x0165, 0x0161, 0x0178, 0x0174, 0x018c, 0x0187, 0x01a3, 0x019d, 0x01ba, 0x01b3, 0x01e2,
0x0208, 0x0208, 0x0208, 0x023a, 0x01db, 0x0205, 0x01c1, 0x01e7, 0x01a8, 0x01c9, 0x0192, 0x01af, 0x017c, 0x0195, 0x0168, 0x017d, 0x0156, 0x0169, 0x0146, 0x0156, 0x0138, 0x0144, 0x012c, 0x0136, 0x0122, 0x0129, 0x011a, 0x0120, 0x0115, 0x0118, 0x0112, 0x0114, 0x0112, 0x0114, 0x0114, 0x0116, 0x0118, 0x011b, 0x011f, 0x0122, 0x0127, 0x012c, 0x0133, 0x013a, 0x0140, 0x014a, 0x014d, 0x015b, 0x015d, 0x016d, 0x016e, 0x0183, 0x0182, 0x019c, 0x0199, 0x01b9, 0x01b1, 0x01d6, 0x01c5, 0x0200,
0x01fb, 0x01fb, 0x01fb, 0x0209, 0x01c5, 0x01dc, 0x01ae, 0x01c2, 0x0195, 0x01a8, 0x0180, 0x0193, 0x016b, 0x017c, 0x0159, 0x0168, 0x0149, 0x0157, 0x013c, 0x0147, 0x0130, 0x0138, 0x0125, 0x012c, 0x011d, 0x0122, 0x0116, 0x011a, 0x0111, 0x0115, 0x010e, 0x0112, 0x010d, 0x0111, 0x010e, 0x0113, 0x0111, 0x0118, 0x0117, 0x011e, 0x011e, 0x0127, 0x0126, 0x0132, 0x0131, 0x013f, 0x013d, 0x014d, 0x014a, 0x015c, 0x0159, 0x016e, 0x016b, 0x0183, 0x0180, 0x019b, 0x0195, 0x01b3, 0x01ad, 0x01d9,
0x0200, 0x0200, 0x0200, 0x022b, 0x01d4, 0x01fe, 0x01ba, 0x01df, 0x01a2, 0x01c1, 0x018a, 0x01a6, 0x0174, 0x018c, 0x0160, 0x0175, 0x014f, 0x0160, 0x013e, 0x014d, 0x0130, 0x013b, 0x0123, 0x012c, 0x0119, 0x0120, 0x0111, 0x0115, 0x010c, 0x010e, 0x010a, 0x010b, 0x0109, 0x010a, 0x010b, 0x010c, 0x010f, 0x0111, 0x0116, 0x0119, 0x011f, 0x0123, 0x012b, 0x0130, 0x0138, 0x0140, 0x0146, 0x0152, 0x0156, 0x0164, 0x0167, 0x017a, 0x017b, 0x0191, 0x0191, 0x01af, 0x01aa, 0x01cd, 0x01bf, 0x01f7,
0x01f0, 0x01f0, 0x01f0, 0x0202, 0x01be, 0x01d6, 0x01a6, 0x01ba, 0x018f, 0x01a2, 0x0179, 0x018a, 0x0164, 0x0174, 0x0152, 0x0160, 0x0143, 0x014f, 0x0136, 0x013f, 0x0129, 0x0130, 0x011e, 0x0123, 0x0115, 0x0119, 0x010f, 0x0111, 0x010a, 0x010c, 0x0108, 0x0109, 0x0107, 0x0109, 0x0108, 0x010a, 0x010a, 0x010f, 0x0110, 0x0116, 0x0117, 0x011f, 0x0120, 0x012a, 0x012b, 0x0137, 0x0137, 0x0147, 0x0143, 0x0156, 0x0152, 0x0168, 0x0164, 0x017c, 0x0178, 0x0193, 0x018e, 0x01ac, 0x01a8, 0x01d2,
0x01f9, 0x01f9, 0x01f9, 0x0225, 0x01cf, 0x01f8, 0x01b5, 0x01d8, 0x019d, 0x01bb, 0x0185, 0x01a0, 0x016f, 0x0185, 0x015b, 0x016f, 0x0149, 0x0159, 0x0139, 0x0146, 0x012a, 0x0134, 0x011d, 0x0125, 0x0113, 0x0118, 0x010c, 0x010e, 0x0107, 0x0108, 0x0104, 0x0105, 0x0104, 0x0104, 0x0106, 0x0106, 0x010a, 0x010a, 0x0110, 0x0112, 0x011a, 0x011d, 0x0124, 0x012a, 0x0132, 0x013a, 0x0142, 0x014b, 0x0152, 0x015e, 0x0163, 0x0174, 0x0176, 0x018d, 0x018d, 0x01a9, 0x01a5, 0x01c7, 0x01ba, 0x01f3,
0x01eb, 0x01eb, 0x01eb, 0x01fc, 0x01ba, 0x01d1, 0x01a1, 0x01b6, 0x018a, 0x019c, 0x0174, 0x0186, 0x0160, 0x0170, 0x014e, 0x015b, 0x013f, 0x0149, 0x0131, 0x0139, 0x0124, 0x012a, 0x0119, 0x011d, 0x0110, 0x0113, 0x010a, 0x010c, 0x0106, 0x0106, 0x0104, 0x0104, 0x0103, 0x0104, 0x0104, 0x0105, 0x0106, 0x0109, 0x010b, 0x010f, 0x0112, 0x0119, 0x011b, 0x0124, 0x0126, 0x0131, 0x0133, 0x0141, 0x0140, 0x0152, 0x014e, 0x0163, 0x0160, 0x0178, 0x0175, 0x018f, 0x018b, 0x01a7, 0x01a3, 0x01ce,
0x01f3, 0x01f3, 0x01f3, 0x0221, 0x01cd, 0x01f3, 0x01b2, 0x01d5, 0x0199, 0x01b8, 0x0182, 0x019d, 0x016c, 0x0182, 0x0158, 0x016b, 0x0145, 0x0155, 0x0135, 0x0143, 0x0127, 0x0131, 0x011a, 0x0121, 0x0110, 0x0114, 0x0109, 0x010b, 0x0104, 0x0105, 0x0101, 0x0101, 0x0101, 0x0101, 0x0103, 0x0103, 0x0106, 0x0107, 0x010d, 0x010d, 0x0116, 0x0119, 0x0121, 0x0126, 0x012f, 0x0136, 0x013f, 0x0147, 0x014f, 0x015b, 0x0160, 0x0170, 0x0174, 0x0189, 0x018b, 0x01a6, 0x01a3, 0x01c4, 0x01b9, 0x01ee,
0x01ec, 0x01ec, 0x01ec, 0x01f7, 0x01b7, 0x01ce, 0x019f, 0x01b3, 0x0187, 0x019a, 0x0171, 0x0182, 0x015d, 0x016c, 0x014c, 0x0159, 0x013c, 0x0146, 0x012e, 0x0136, 0x0122, 0x0127, 0x0117, 0x011a, 0x010e, 0x0110, 0x0108, 0x0108, 0x0104, 0x0104, 0x0101, 0x0101, 0x0101, 0x0100, 0x0102, 0x0102, 0x0104, 0x0106, 0x0109, 0x010c, 0x0110, 0x0115, 0x0119, 0x0121, 0x0123, 0x012f, 0x0130, 0x013e, 0x013d, 0x014e, 0x014c, 0x0161, 0x015e, 0x0175, 0x0172, 0x018d, 0x0189, 0x01a5, 0x01a2, 0x01cc,
0x01f2, 0x01f2, 0x01f2, 0x0220, 0x01cc, 0x01f3, 0x01b1, 0x01d5, 0x0199, 0x01b7, 0x0180, 0x019b, 0x016a, 0x0181, 0x0156, 0x016a, 0x0144, 0x0155, 0x0133, 0x0141, 0x0125, 0x012f, 0x0118, 0x0120, 0x010e, 0x0113, 0x0108, 0x010a, 0x0103, 0x0104, 0x0100, 0x0100, 0x0100, 0x0100, 0x0101, 0x0101, 0x0105, 0x0105, 0x010b, 0x010c, 0x0114, 0x0116, 0x011f, 0x0124, 0x012d, 0x0134, 0x013d, 0x0146, 0x014d, 0x015a, 0x015f, 0x016f, 0x0173, 0x0188, 0x018a, 0x01a4, 0x01a2, 0x01c3, 0x01b6, 0x01ee,
0x01e6, 0x01e6, 0x01e6, 0x01fa, 0x01b6, 0x01ce, 0x019e, 0x01b1, 0x0187, 0x0199, 0x0170, 0x0181, 0x015c, 0x016a, 0x014a, 0x0157, 0x013b, 0x0145, 0x012d, 0x0134, 0x0120, 0x0126, 0x0115, 0x0118, 0x010d, 0x010f, 0x0107, 0x0108, 0x0103, 0x0103, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0101, 0x0103, 0x0104, 0x0107, 0x010a, 0x010e, 0x0113, 0x0117, 0x011f, 0x0123, 0x012d, 0x012f, 0x013d, 0x013d, 0x014e, 0x014c, 0x015f, 0x015e, 0x0174, 0x0171, 0x018c, 0x0188, 0x01a5, 0x01a2, 0x01cc,
0x01f6, 0x01f6, 0x01f6, 0x0220, 0x01cc, 0x01f4, 0x01b2, 0x01d4, 0x019a, 0x01b8, 0x0182, 0x019e, 0x016c, 0x0183, 0x0157, 0x016b, 0x0145, 0x0156, 0x0134, 0x0142, 0x0126, 0x0131, 0x0119, 0x0121, 0x010f, 0x0115, 0x0108, 0x010c, 0x0104, 0x0106, 0x0101, 0x0102, 0x0101, 0x0101, 0x0102, 0x0103, 0x0106, 0x0107, 0x010c, 0x010e, 0x0115, 0x0118, 0x0121, 0x0125, 0x012f, 0x0136, 0x013e, 0x0148, 0x014f, 0x015c, 0x0160, 0x0171, 0x0174, 0x018b, 0x018b, 0x01a6, 0x01a3, 0x01c5, 0x01bb, 0x01ee,
0x01eb, 0x01eb, 0x01eb, 0x01f9, 0x01b8, 0x01cd, 0x019f, 0x01b2, 0x0187, 0x019a, 0x0172, 0x0183, 0x015d, 0x016c, 0x014c, 0x0158, 0x013c, 0x0146, 0x012e, 0x0135, 0x0121, 0x0126, 0x0116, 0x011a, 0x010d, 0x010f, 0x0108, 0x0108, 0x0103, 0x0103, 0x0101, 0x0101, 0x0100, 0x0100, 0x0101, 0x0102, 0x0104, 0x0105, 0x0109, 0x010b, 0x010f, 0x0114, 0x0118, 0x0120, 0x0124, 0x012e, 0x0131, 0x013d, 0x013e, 0x014f, 0x014d, 0x0161, 0x015f, 0x0176, 0x0173, 0x018d, 0x0188, 0x01a6, 0x01a1, 0x01c9,
0x01f9, 0x01f9, 0x01f9, 0x0226, 0x01d1, 0x01f8, 0x01b6, 0x01db, 0x019d, 0x01bd, 0x0185, 0x01a2, 0x016f, 0x0187, 0x015b, 0x0170, 0x0149, 0x015b, 0x0139, 0x0148, 0x0129, 0x0136, 0x011d, 0x0126, 0x0113, 0x011a, 0x010c, 0x0110, 0x0107, 0x010a, 0x0104, 0x0106, 0x0103, 0x0105, 0x0105, 0x0107, 0x0109, 0x010b, 0x010f, 0x0112, 0x0119, 0x011d, 0x0124, 0x012b, 0x0132, 0x013a, 0x0141, 0x014c, 0x0152, 0x0160, 0x0164, 0x0176, 0x0178, 0x018f, 0x018f, 0x01ab, 0x01a7, 0x01ca, 0x01bb, 0x01f3,
0x01ec, 0x01ec, 0x01ec, 0x0200, 0x01bb, 0x01d1, 0x01a2, 0x01b7, 0x018b, 0x019e, 0x0174, 0x0186, 0x0160, 0x0170, 0x014f, 0x015c, 0x013f, 0x0149, 0x0131, 0x0139, 0x0125, 0x012a, 0x011a, 0x011d, 0x0111, 0x0113, 0x010a, 0x010b, 0x0106, 0x0106, 0x0104, 0x0104, 0x0103, 0x0103, 0x0104, 0x0105, 0x0106, 0x0108, 0x010c, 0x010f, 0x0113, 0x0118, 0x011c, 0x0123, 0x0126, 0x0131, 0x0133, 0x0141, 0x0142, 0x0151, 0x0150, 0x0164, 0x0163, 0x0179, 0x0176, 0x0190, 0x018d, 0x01aa, 0x01a4, 0x01ce,
0x01ff, 0x01ff, 0x01ff, 0x0232, 0x01d5, 0x0200, 0x01bb, 0x01df, 0x01a2, 0x01c4, 0x018b, 0x01a8, 0x0175, 0x018f, 0x0161, 0x0177, 0x014f, 0x0162, 0x013e, 0x014f, 0x012f, 0x013d, 0x0122, 0x012e, 0x0118, 0x0122, 0x0111, 0x0117, 0x010c, 0x0111, 0x0109, 0x010d, 0x0108, 0x010c, 0x010a, 0x010d, 0x010e, 0x0112, 0x0115, 0x0119, 0x011e, 0x0124, 0x012a, 0x0132, 0x0137, 0x0142, 0x0146, 0x0152, 0x0156, 0x0166, 0x0169, 0x017d, 0x017e, 0x0197, 0x0194, 0x01b2, 0x01ad, 0x01d2, 0x01c2, 0x01fc,
0x01f1, 0x01f1, 0x01f1, 0x0205, 0x01c0, 0x01d7, 0x01a7, 0x01bd, 0x0190, 0x01a3, 0x0179, 0x018b, 0x0165, 0x0175, 0x0153, 0x0161, 0x0144, 0x014f, 0x0136, 0x013e, 0x0129, 0x012f, 0x011f, 0x0123, 0x0116, 0x0118, 0x010f, 0x0111, 0x010a, 0x010c, 0x0108, 0x0108, 0x0107, 0x0108, 0x0109, 0x010a, 0x010b, 0x010e, 0x0110, 0x0114, 0x0118, 0x011e, 0x0121, 0x0129, 0x012c, 0x0137, 0x0138, 0x0146, 0x0145, 0x0157, 0x0156, 0x0169, 0x0168, 0x017f, 0x017a, 0x0196, 0x0192, 0x01b0, 0x01ab, 0x01d8,
0x0208, 0x0208, 0x0208, 0x023d, 0x01dd, 0x0208, 0x01c1, 0x01ea, 0x01a9, 0x01cd, 0x0192, 0x01b1, 0x017b, 0x0197, 0x0167, 0x0180, 0x0156, 0x016c, 0x0146, 0x0158, 0x0137, 0x0147, 0x012a, 0x0138, 0x0120, 0x012b, 0x0119, 0x0121, 0x0114, 0x011b, 0x0110, 0x0116, 0x0110, 0x0115, 0x0112, 0x0118, 0x0117, 0x011d, 0x011d, 0x0124, 0x0126, 0x012e, 0x0132, 0x013b, 0x013f, 0x014b, 0x014e, 0x015d, 0x015d, 0x016f, 0x0171, 0x0186, 0x0185, 0x019f, 0x019b, 0x01bc, 0x01b3, 0x01d9, 0x01c9, 0x0206,
0x01fb, 0x01fb, 0x01fb, 0x020e, 0x01c8, 0x01df, 0x01ad, 0x01c3, 0x0195, 0x01aa, 0x0180, 0x0192, 0x016b, 0x017c, 0x015a, 0x0168, 0x014b, 0x0157, 0x013d, 0x0146, 0x0130, 0x0138, 0x0126, 0x012b, 0x011d, 0x0120, 0x0116, 0x0119, 0x0111, 0x0114, 0x010e, 0x0110, 0x010d, 0x010f, 0x010f, 0x0111, 0x0112, 0x0116, 0x0117, 0x011c, 0x011e, 0x0126, 0x0128, 0x0131, 0x0132, 0x013e, 0x013f, 0x014d, 0x014c, 0x015d, 0x015d, 0x0170, 0x016e, 0x0185, 0x0182, 0x019d, 0x0199, 0x01b6, 0x01b5, 0x01e0,
0x0216, 0x0216, 0x0216, 0x024b, 0x01e8, 0x0216, 0x01cc, 0x01f6, 0x01b3, 0x01d8, 0x019b, 0x01bd, 0x0186, 0x01a4, 0x0172, 0x018d, 0x0160, 0x0178, 0x0150, 0x0165, 0x0142, 0x0154, 0x0136, 0x0146, 0x012c, 0x0139, 0x0124, 0x012f, 0x011f, 0x0127, 0x011b, 0x0123, 0x011a, 0x0122, 0x011d, 0x0125, 0x0121, 0x0129, 0x0128, 0x0131, 0x0131, 0x013b, 0x013c, 0x0148, 0x0149, 0x0158, 0x0158, 0x0169, 0x0167, 0x017b, 0x0179, 0x0192, 0x018e, 0x01ab, 0x01a5, 0x01c8, 0x01be, 0x01e6, 0x01d5, 0x020f,
0x0209, 0x0209, 0x0209, 0x021f, 0x01cf, 0x01e9, 0x01b7, 0x01ce, 0x01a0, 0x01b4, 0x018a, 0x019c, 0x0175, 0x0186, 0x0163, 0x0172, 0x0153, 0x0160, 0x0146, 0x0150, 0x013a, 0x0142, 0x012f, 0x0136, 0x0126, 0x012c, 0x011f, 0x0124, 0x011a, 0x011e, 0x0117, 0x011b, 0x0116, 0x011a, 0x0118, 0x011c, 0x011b, 0x0120, 0x0120, 0x0127, 0x0127, 0x0130, 0x0131, 0x013b, 0x013b, 0x0149, 0x0147, 0x0157, 0x0154, 0x0167, 0x0165, 0x017a, 0x0177, 0x018f, 0x018b, 0x01a7, 0x01a2, 0x01c0, 0x01ba, 0x01e7,
0x0229, 0x0229, 0x0229, 0x0260, 0x01f5, 0x0225, 0x01d6, 0x0204, 0x01be, 0x01e7, 0x01a7, 0x01cb, 0x0191, 0x01b2, 0x017d, 0x019a, 0x016b, 0x0185, 0x015d, 0x0174, 0x014e, 0x0163, 0x0142, 0x0154, 0x0139, 0x0148, 0x0131, 0x013e, 0x012c, 0x0137, 0x0128, 0x0133, 0x0128, 0x0132, 0x0129, 0x0134, 0x012e, 0x0139, 0x0134, 0x0140, 0x013d, 0x014c, 0x0148, 0x0158, 0x0155, 0x0166, 0x0161, 0x0176, 0x0172, 0x018a, 0x0185, 0x01a1, 0x0199, 0x01ba, 0x01af, 0x01d5, 0x01c8, 0x01f4, 0x01e0, 0x021f,
0x021b, 0x021b, 0x021b, 0x022c, 0x01de, 0x01f8, 0x01c2, 0x01d8, 0x01a9, 0x01c0, 0x0194, 0x01a8, 0x0180, 0x0192, 0x016e, 0x017e, 0x015e, 0x016c, 0x0150, 0x015d, 0x0143, 0x014f, 0x0139, 0x0143, 0x0131, 0x0139, 0x0129, 0x0131, 0x0125, 0x012b, 0x0122, 0x0128, 0x0121, 0x0127, 0x0122, 0x0129, 0x0126, 0x012d, 0x012b, 0x0134, 0x0132, 0x013d, 0x013a, 0x0147, 0x0144, 0x0153, 0x0150, 0x0161, 0x015f, 0x0172, 0x016f, 0x0186, 0x0182, 0x019b, 0x0196, 0x01b1, 0x01ad, 0x01cb, 0x01c4, 0x01f5,
0x023f, 0x023f, 0x023f, 0x027c, 0x0208, 0x023d, 0x01e4, 0x0214, 0x01cb, 0x01f7, 0x01b4, 0x01dd, 0x019e, 0x01c2, 0x018b, 0x01aa, 0x0179, 0x0196, 0x0169, 0x0183, 0x015b, 0x0173, 0x0151, 0x0166, 0x0147, 0x015a, 0x0140, 0x0150, 0x013b, 0x0149, 0x0137, 0x0144, 0x0137, 0x0145, 0x0139, 0x0146, 0x013d, 0x014b, 0x0143, 0x0152, 0x014c, 0x015c, 0x0156, 0x0168, 0x0162, 0x0175, 0x016f, 0x0186, 0x0180, 0x019b, 0x0193, 0x01b1, 0x01a6, 0x01cc, 0x01bd, 0x01e6, 0x01d6, 0x0205, 0x01eb, 0x0232,
0x0230, 0x0230, 0x0230, 0x0246, 0x01ef, 0x020b, 0x01d0, 0x01e7, 0x01b7, 0x01cd, 0x01a1, 0x01b5, 0x018c, 0x019f, 0x017a, 0x018b, 0x0169, 0x017a, 0x015c, 0x016a, 0x0150, 0x015c, 0x0146, 0x0151, 0x013e, 0x0148, 0x0137, 0x0140, 0x0131, 0x013a, 0x012e, 0x0137, 0x012f, 0x0136, 0x0130, 0x0138, 0x0132, 0x013c, 0x0138, 0x0142, 0x013e, 0x014b, 0x0147, 0x0156, 0x0150, 0x0161, 0x015c, 0x016f, 0x016a, 0x0180, 0x017c, 0x0193, 0x018f, 0x01a9, 0x01a3, 0x01bf, 0x01bb, 0x01da, 0x01d0, 0x0202,
0x025d, 0x025d, 0x025d, 0x029f, 0x021f, 0x0258, 0x01f7, 0x022b, 0x01da, 0x020a, 0x01c3, 0x01ee, 0x01ad, 0x01d4, 0x019b, 0x01be, 0x0189, 0x01a9, 0x0179, 0x0197, 0x016b, 0x0186, 0x0161, 0x0178, 0x0158, 0x016c, 0x0150, 0x0163, 0x014b, 0x015d, 0x0148, 0x0159, 0x0148, 0x0158, 0x014a, 0x015a, 0x014d, 0x015e, 0x0153, 0x0165, 0x015c, 0x016f, 0x0165, 0x017a, 0x0171, 0x0189, 0x0180, 0x019b, 0x0190, 0x01ae, 0x01a3, 0x01c4, 0x01b7, 0x01de, 0x01ce, 0x01fb, 0x01e5, 0x0218, 0x01fd, 0x0248,
0x024a, 0x024a, 0x024a, 0x0263, 0x0204, 0x0223, 0x01e1, 0x01fa, 0x01c5, 0x01dc, 0x01af, 0x01c5, 0x019a, 0x01ae, 0x0188, 0x019b, 0x0178, 0x018a, 0x016a, 0x017a, 0x015d, 0x016d, 0x0153, 0x0161, 0x014b, 0x0158, 0x0144, 0x0151, 0x013f, 0x014c, 0x013d, 0x0148, 0x013c, 0x0148, 0x013d, 0x0149, 0x0141, 0x014d, 0x0145, 0x0152, 0x014c, 0x015b, 0x0154, 0x0165, 0x015e, 0x0171, 0x016a, 0x017f, 0x0179, 0x0190, 0x018a, 0x01a3, 0x019d, 0x01b8, 0x01b2, 0x01d0, 0x01c8, 0x01e8, 0x01e2, 0x0214,
0x028a, 0x028a, 0x028a, 0x02c9, 0x023e, 0x027e, 0x020f, 0x0249, 0x01ef, 0x0223, 0x01d4, 0x0203, 0x01bf, 0x01e9, 0x01ab, 0x01d1, 0x019a, 0x01be, 0x018b, 0x01ab, 0x017e, 0x019b, 0x0172, 0x018e, 0x0169, 0x0182, 0x0162, 0x0178, 0x015d, 0x0172, 0x015b, 0x016f, 0x015a, 0x016d, 0x015c, 0x016f, 0x0160, 0x0174, 0x0165, 0x017a, 0x016c, 0x0183, 0x0176, 0x0190, 0x0182, 0x019f, 0x0192, 0x01b1, 0x01a2, 0x01c5, 0x01b5, 0x01dc, 0x01c8, 0x01f4, 0x01de, 0x020f, 0x01f7, 0x022e, 0x0218, 0x0266,
0x0272, 0x0272, 0x0272, 0x028f, 0x0221, 0x0241, 0x01f7, 0x0213, 0x01d7, 0x01f0, 0x01be, 0x01d6, 0x01a9, 0x01c0, 0x0197, 0x01ac, 0x0186, 0x019a, 0x0178, 0x018b, 0x016d, 0x017e, 0x0161, 0x0172, 0x0158, 0x0169, 0x0152, 0x0162, 0x014f, 0x015d, 0x014c, 0x015a, 0x014b, 0x0159, 0x014c, 0x015b, 0x014f, 0x015e, 0x0153, 0x0164, 0x015a, 0x016c, 0x0162, 0x0175, 0x016d, 0x0182, 0x0179, 0x0191, 0x0189, 0x01a2, 0x0199, 0x01b5, 0x01ac, 0x01c8, 0x01c0, 0x01df, 0x01d8, 0x01fa, 0x01f8, 0x022b,
0x02c6, 0x02c6, 0x02c6, 0x0315, 0x0267, 0x02ac, 0x022e, 0x026e, 0x0208, 0x0241, 0x01e9, 0x021c, 0x01d2, 0x0200, 0x01bf, 0x01ea, 0x01ad, 0x01d3, 0x019e, 0x01c2, 0x0190, 0x01b1, 0x0185, 0x01a4, 0x017d, 0x0199, 0x0175, 0x018f, 0x0170, 0x0189, 0x016e, 0x0186, 0x016d, 0x0184, 0x016f, 0x0186, 0x0172, 0x018a, 0x0179, 0x0191, 0x0180, 0x019b, 0x018b, 0x01a8, 0x0197, 0x01b6, 0x01a5, 0x01c8, 0x01b5, 0x01dc, 0x01c7, 0x01f4, 0x01dc, 0x020d, 0x01f1, 0x0227, 0x0211, 0x024d, 0x0235, 0x028f,
0x02b3, 0x02b3, 0x02b3, 0x02d3, 0x024c, 0x026a, 0x0217, 0x0231, 0x01f1, 0x020a, 0x01d4, 0x01ea, 0x01bd, 0x01d3, 0x01ab, 0x01c0, 0x0199, 0x01ae, 0x018a, 0x019f, 0x017e, 0x0191, 0x0173, 0x0186, 0x016b, 0x017d, 0x0164, 0x0176, 0x0160, 0x0171, 0x015d, 0x016e, 0x015c, 0x016d, 0x015d, 0x016e, 0x0160, 0x0172, 0x0164, 0x0178, 0x016c, 0x0180, 0x0175, 0x018a, 0x0180, 0x0196, 0x018c, 0x01a5, 0x019c, 0x01b5, 0x01ad, 0x01c8, 0x01bf, 0x01dc, 0x01d3, 0x01f3, 0x01f0, 0x0213, 0x0217, 0x024b,
0x0333, 0x0333, 0x0333, 0x035a, 0x029e, 0x02ed, 0x0251, 0x0298, 0x0228, 0x0269, 0x0205, 0x023b, 0x01e6, 0x0219, 0x01d5, 0x0205, 0x01c0, 0x01ec, 0x01b0, 0x01d6, 0x01a5, 0x01c7, 0x0199, 0x01bd, 0x0190, 0x01b0, 0x018a, 0x01a4, 0x0185, 0x01a2, 0x0184, 0x019c, 0x0181, 0x019a, 0x0184, 0x019e, 0x0189, 0x01a1, 0x018e, 0x01ab, 0x0196, 0x01b2, 0x019d, 0x01bf, 0x01ac, 0x01d0, 0x01bb, 0x01e1, 0x01cb, 0x01f7, 0x01dd, 0x020e, 0x01ed, 0x0226, 0x0208, 0x0244, 0x022d, 0x0270, 0x025e, 0x02ba,
0x02fd, 0x02fd, 0x02fd, 0x0330, 0x0283, 0x02a5, 0x023a, 0x0254, 0x0212, 0x022a, 0x01f0, 0x0205, 0x01d6, 0x01e8, 0x01bf, 0x01d3, 0x01ae, 0x01c0, 0x01a1, 0x01b2, 0x0192, 0x01a4, 0x0189, 0x0198, 0x0181, 0x018e, 0x0177, 0x018b, 0x0173, 0x0184, 0x0170, 0x0181, 0x0171, 0x0181, 0x0172, 0x0182, 0x0174, 0x0185, 0x0179, 0x018a, 0x017f, 0x0192, 0x018a, 0x019e, 0x0198, 0x01ab, 0x01a3, 0x01b7, 0x01b3, 0x01ca, 0x01c3, 0x01de, 0x01d5, 0x01f2, 0x01ed, 0x020a, 0x0213, 0x0236, 0x0248, 0x0270,
};


// 4: Static Local Data
// ----------------------------------------------------------------------------
// 5: Static Function Prototypes
// ----------------------------------------------------------------------------
// 6: Functions Implementation
// ----------------------------------------------------------------------------
