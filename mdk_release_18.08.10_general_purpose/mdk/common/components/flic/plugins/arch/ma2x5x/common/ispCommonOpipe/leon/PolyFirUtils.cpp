///
/// @file      PolyFirUtils.c
/// @copyright All code copyright Movidius Ltd 2017, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Application for PolyFirUtils.
///            Platform(s) supported : ma2x5x
///

/**************************************************************************************************
 ~~~ Included types first then APIs from other modules
 **************************************************************************************************/
#include "PolyFirUtils.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "DrvTimer.h"
#include "swcLeonUtils.h"


//#define POLY_PROF 1
/*PROF*/ #if defined(POLY_PROF)
/*PROF*/ uint64_t startTime, endTime, polyTime;
/*PROF*/ #endif


uint32_t PolyFirUtils::sincLut[MAX_SZ] = { //fp32 patterns (dumped from PC)
0x3f800000, 0x3f7fff0f, 0x3f7ffc3d, 0x3f7ff78a, 0x3f7ff0f6, 0x3f7fe880, 0x3f7fde2a, 0x3f7fd1f3, 0x3f7fc3d9, 0x3f7fb3e1, 0x3f7fa208, 0x3f7f8e4e, 0x3f7f78b6, 0x3f7f613d, 0x3f7f47e5, 0x3f7f2cae, 0x3f7f0f99, 0x3f7ef0a6, 0x3f7ecfd5, 0x3f7ead26, 0x3f7e889b, 0x3f7e6233, 0x3f7e39f0, 0x3f7e0fd1, 0x3f7de3d8, 0x3f7db603, 0x3f7d8656, 0x3f7d54d0, 0x3f7d2172, 0x3f7cec3b, 0x3f7cb52e, 0x3f7c7c4b, 0x3f7c4191, 0x3f7c0504, 0x3f7bc6a2, 0x3f7b866e, 0x3f7b4467, 0x3f7b008f, 0x3f7abae7, 0x3f7a736f, 0x3f7a2a28, 0x3f79df13, 0x3f799233, 0x3f794386, 0x3f78f310, 0x3f78a0cf, 0x3f784cc6, 0x3f77f6f6, 0x3f779f61, 0x3f774605, 0x3f76eae6, 0x3f768e04, 0x3f762f60, 0x3f75cefd, 0x3f756cdb, 0x3f7508fa, 0x3f74a35d, 0x3f743c07, 0x3f73d2f6, 0x3f73682c, 0x3f72fbac, 0x3f728d76, 0x3f721d8c, 0x3f71abf1, 0x3f7138a5, 0x3f70c3a7, 0x3f704cfd, 0x3f6fd4a7, 0x3f6f5aa5, 0x3f6edefb, 0x3f6e61a7, 0x3f6de2b0, 0x3f6d6213, 0x3f6cdfd4, 0x3f6c5bf4, 0x3f6bd675, 0x3f6b4f59, 0x3f6ac6a1, 0x3f6a3c4d, 0x3f69b064, 0x3f6922e4, 0x3f6893ce, 0x3f680327, 0x3f6770f0, 0x3f66dd2a, 0x3f6647d6, 0x3f65b0f8, 0x3f651891, 0x3f647ea3, 0x3f63e330, 0x3f63463b, 0x3f62a7c5, 0x3f6207d0, 0x3f61665f, 0x3f60c373, 0x3f601f0e, 0x3f5f7934, 0x3f5ed1e4, 0x3f5e2925, 0x3f5d7ef4, 0x3f5cd356, 0x3f5c264d, 0x3f5b77db, 0x3f5ac802, 0x3f5a16c4, 0x3f596424, 0x3f58b026, 0x3f57fac8, 0x3f574410, 0x3f568c00, 0x3f55d297, 0x3f5517dc, 0x3f545bcf, 0x3f539e73, 0x3f52dfca, 0x3f521fd7, 0x3f515e9c, 0x3f509c1c, 0x3f4fd859, 0x3f4f1355, 0x3f4e4d15, 0x3f4d8598, 0x3f4cbce4, 0x3f4bf2fa, 0x3f4b27db, 0x3f4a5b8c, 0x3f498e0f, 0x3f48bf67,
0x3f47ef95, 0x3f471e9e, 0x3f464c83, 0x3f457947, 0x3f44a4ed, 0x3f43cf78, 0x3f42f8ea, 0x3f422146, 0x3f41488f, 0x3f406ec8, 0x3f3f93f3, 0x3f3eb813, 0x3f3ddb2b, 0x3f3cfd3e, 0x3f3c1e4f, 0x3f3b3e61, 0x3f3a5d75, 0x3f397b90, 0x3f3898b4, 0x3f37b4e4, 0x3f36d023, 0x3f35ea74, 0x3f3503d9, 0x3f341c57, 0x3f3333ee, 0x3f324aa4, 0x3f316079, 0x3f307572, 0x3f2f8992, 0x3f2e9cdb, 0x3f2daf51, 0x3f2cc0f5, 0x3f2bd1cc, 0x3f2ae1d9, 0x3f29f11e, 0x3f28ff9f, 0x3f280d5e, 0x3f271a5e, 0x3f2626a3, 0x3f253230, 0x3f243d08, 0x3f23472d, 0x3f2250a4, 0x3f21596e, 0x3f20618f, 0x3f1f690a, 0x3f1e6fe3, 0x3f1d761c, 0x3f1c7bb9, 0x3f1b80bc, 0x3f1a8529, 0x3f198903, 0x3f188c4d, 0x3f178f09, 0x3f16913d, 0x3f1592ea, 0x3f149413, 0x3f1394bc, 0x3f1294e8, 0x3f11949a, 0x3f1093d6, 0x3f0f929d, 0x3f0e90f4, 0x3f0d8ede, 0x3f0c8c5e, 0x3f0b8977, 0x3f0a862c, 0x3f098281, 0x3f087e78, 0x3f077a15, 0x3f06755c, 0x3f05704e, 0x3f046af0, 0x3f036544, 0x3f025f4e, 0x3f015911, 0x3f005291, 0x3efe979f, 0x3efc89a1, 0x3efa7b2e, 0x3ef86c4e, 0x3ef65d05, 0x3ef44d5b, 0x3ef23d57, 0x3ef02cfc, 0x3eee1c55, 0x3eec0b64, 0x3ee9fa33, 0x3ee7e8c6, 0x3ee5d724, 0x3ee3c554, 0x3ee1b35b, 0x3edfa140, 0x3edd8f0a, 0x3edb7cbf, 0x3ed96a64, 0x3ed75802, 0x3ed5459c, 0x3ed3333b, 0x3ed120e4, 0x3ecf0e9d, 0x3eccfc6d, 0x3ecaea5b, 0x3ec8d86b, 0x3ec6c6a4, 0x3ec4b50e, 0x3ec2a3ae, 0x3ec09289, 0x3ebe81a8, 0x3ebc710e, 0x3eba60c4, 0x3eb850cf, 0x3eb64133, 0x3eb431f9, 0x3eb22327, 0x3eb014c2, 0x3eae06d1, 0x3eabf958, 0x3ea9ec60, 0x3ea7dfed, 0x3ea5d406, 0x3ea3c8b0, 0x3ea1bdf2, 0x3e9fb3d1, 0x3e9daa55, 0x3e9ba182, 0x3e99995e, 0x3e9791ef,
0x3e958b3d, 0x3e93854a, 0x3e91801f, 0x3e8f7bc1, 0x3e8d7835, 0x3e8b7582, 0x3e8973ad, 0x3e8772bc, 0x3e8572b4, 0x3e83739d, 0x3e81757a, 0x3e7ef0a4, 0x3e7af854, 0x3e770211, 0x3e730de4, 0x3e6f1bdb, 0x3e6b2bfe, 0x3e673e5a, 0x3e6352fb, 0x3e5f69e9, 0x3e5b8331, 0x3e579edd, 0x3e53bcf9, 0x3e4fdd8d, 0x3e4c00a6, 0x3e482650, 0x3e444e93, 0x3e407979, 0x3e3ca70f, 0x3e38d75f, 0x3e350a72, 0x3e314053, 0x3e2d790d, 0x3e29b4a9, 0x3e25f331, 0x3e2234b1, 0x3e1e7931, 0x3e1ac0bc, 0x3e170b5c, 0x3e13591b, 0x3e0faa02, 0x3e0bfe1b, 0x3e085571, 0x3e04b00c, 0x3e010df5, 0x3dfade6f, 0x3df3a7b6, 0x3dec77d6, 0x3de54edf, 0x3dde2ce3, 0x3dd711f6, 0x3dcffe28, 0x3dc8f18e, 0x3dc1ec37, 0x3dbaee36, 0x3db3f79e, 0x3dad087f, 0x3da620eb, 0x3d9f40f3, 0x3d9868a8, 0x3d91981b, 0x3d8acf5e, 0x3d840e80, 0x3d7aab25, 0x3d6d494b, 0x3d5ff794, 0x3d52b620, 0x3d45850c, 0x3d38647b, 0x3d2b548c, 0x3d1e555c, 0x3d11670c, 0x3d0489ba, 0x3cef7b06, 0x3cd6050c, 0x3cbcb1c1, 0x3ca3815f, 0x3c8a7420, 0x3c63147c, 0x3c3187e1, 0x3c0042e1, 0x3b9e8bd5, 0x3af48b59, 0xba8ed186, 0xbb83f8fc, 0xbbe3aa25, 0xbc216385, 0xbc50a770, 0xbc7fa06c, 0xbc97270a, 0xbcae5803, 0xbcc562ee, 0xbcdc479e, 0xbcf305e1, 0xbd04cec3, 0xbd100731, 0xbd1b2c23, 0xbd263d81, 0xbd313b38, 0xbd3c252e, 0xbd46fb51, 0xbd51bd8a, 0xbd5c6bc3, 0xbd6705e9, 0xbd718be8, 0xbd7bfdac, 0xbd832d90, 0xbd885219, 0xbd8d6c67, 0xbd927c71, 0xbd97822e, 0xbd9c7d96, 0xbda16e9e, 0xbda6553f, 0xbdab3171, 0xbdb0032a, 0xbdb4ca63, 0xbdb98714, 0xbdbe3936, 0xbdc2e0bf, 0xbdc77da9, 0xbdcc0fee, 0xbdd09787, 0xbdd5146a, 0xbdd98694, 0xbdddedfb, 0xbde24a9c, 0xbde69c6e,
0xbdeae36c, 0xbdef1f91, 0xbdf350d6, 0xbdf77737, 0xbdfb92ae, 0xbdffa335, 0xbe01d464, 0xbe03d1b1, 0xbe05c97f, 0xbe07bbcc, 0xbe09a896, 0xbe0b8fda, 0xbe0d7197, 0xbe0f4dcc, 0xbe112475, 0xbe12f592, 0xbe14c121, 0xbe168720, 0xbe18478d, 0xbe1a0268, 0xbe1bb7af, 0xbe1d6762, 0xbe1f117e, 0xbe20b603, 0xbe2254f0, 0xbe23ee45, 0xbe2581ff, 0xbe271020, 0xbe2898a5, 0xbe2a1b90, 0xbe2b98de, 0xbe2d1092, 0xbe2e82a8, 0xbe2fef22, 0xbe315600, 0xbe32b741, 0xbe3412e6, 0xbe3568ef, 0xbe36b95c, 0xbe38042e, 0xbe394964, 0xbe3a8901, 0xbe3bc303, 0xbe3cf76c, 0xbe3e263d, 0xbe3f4f77, 0xbe407319, 0xbe419127, 0xbe42a9a0, 0xbe43bc86, 0xbe44c9da, 0xbe45d19e, 0xbe46d3d3, 0xbe47d07a, 0xbe48c796, 0xbe49b927, 0xbe4aa530, 0xbe4b8bb3, 0xbe4c6cb0, 0xbe4d482c, 0xbe4e1e27, 0xbe4eeea4, 0xbe4fb9a5, 0xbe507f2c, 0xbe513f3d, 0xbe51f9d8, 0xbe52af01, 0xbe535ebb, 0xbe540908, 0xbe54adec, 0xbe554d69, 0xbe55e782, 0xbe567c39, 0xbe570b92, 0xbe579592, 0xbe581a3a, 0xbe58998e, 0xbe591391, 0xbe598848, 0xbe59f7b6, 0xbe5a61dd, 0xbe5ac6c2, 0xbe5b2669, 0xbe5b80d5, 0xbe5bd60c, 0xbe5c2610, 0xbe5c70e5, 0xbe5cb691, 0xbe5cf717, 0xbe5d327b, 0xbe5d68c1, 0xbe5d99f0, 0xbe5dc609, 0xbe5ded14, 0xbe5e0f13, 0xbe5e2c0c, 0xbe5e4404, 0xbe5e56fe, 0xbe5e6501, 0xbe5e6e12, 0xbe5e7235, 0xbe5e716f, 0xbe5e6bc6, 0xbe5e613f, 0xbe5e51df, 0xbe5e3dac, 0xbe5e24ab, 0xbe5e06e2, 0xbe5de455, 0xbe5dbd0c, 0xbe5d910b, 0xbe5d6058, 0xbe5d2af9, 0xbe5cf0f5, 0xbe5cb250, 0xbe5c6f12, 0xbe5c273f, 0xbe5bdadf, 0xbe5b89f6, 0xbe5b348c, 0xbe5adaa6, 0xbe5a7c4d, 0xbe5a1984, 0xbe59b254, 0xbe5946c2, 0xbe58d6d5, 0xbe586293, 0xbe57ea04,
0xbe576d2e, 0xbe56ec18, 0xbe5666c8, 0xbe55dd47, 0xbe554f99, 0xbe54bdc7, 0xbe5427d8, 0xbe538dd1, 0xbe52efbc, 0xbe524d9f, 0xbe51a780, 0xbe50fd68, 0xbe504f5d, 0xbe4f9d68, 0xbe4ee78e, 0xbe4e2dd9, 0xbe4d704f, 0xbe4caef8, 0xbe4be9db, 0xbe4b2101, 0xbe4a546f, 0xbe498430, 0xbe48b049, 0xbe47d8c3, 0xbe46fda6, 0xbe461efa, 0xbe453cc6, 0xbe445713, 0xbe436de7, 0xbe42814d, 0xbe41914a, 0xbe409de9, 0xbe3fa730, 0xbe3ead27, 0xbe3dafd7, 0xbe3caf49, 0xbe3bab83, 0xbe3aa490, 0xbe399a77, 0xbe388d3f, 0xbe377cf2, 0xbe366999, 0xbe35533b, 0xbe3439e0, 0xbe331d91, 0xbe31fe59, 0xbe30dc3c, 0xbe2fb746, 0xbe2e8f7f, 0xbe2d64ef, 0xbe2c379d, 0xbe2b0795, 0xbe29d4de, 0xbe289f80, 0xbe276785, 0xbe262cf4, 0xbe24efd9, 0xbe23b038, 0xbe226e1e, 0xbe212992, 0xbe1fe29d, 0xbe1e9948, 0xbe1d4d9c, 0xbe1bffa1, 0xbe1aaf61, 0xbe195ce3, 0xbe180833, 0xbe16b158, 0xbe15585a, 0xbe13fd43, 0xbe12a01e, 0xbe1140f0, 0xbe0fdfc5, 0xbe0e7ca5, 0xbe0d1798, 0xbe0bb0a9, 0xbe0a47df, 0xbe08dd45, 0xbe0770e2, 0xbe0602c1, 0xbe0492e9, 0xbe032164, 0xbe01ae3d, 0xbe003979, 0xbdfd8647, 0xbdfa968c, 0xbdf7a3d2, 0xbdf4ae28, 0xbdf1b5a4, 0xbdeeba58, 0xbdebbc54, 0xbde8bbaa, 0xbde5b86f, 0xbde2b2b1, 0xbddfaa84, 0xbddc9ffc, 0xbdd99328, 0xbdd6841c, 0xbdd372e8, 0xbdd05fa1, 0xbdcd4a56, 0xbdca331a, 0xbdc71a00, 0xbdc3ff19, 0xbdc0e276, 0xbdbdc42a, 0xbdbaa447, 0xbdb782e0, 0xbdb46003, 0xbdb13bc5, 0xbdae1637, 0xbdaaef6b, 0xbda7c772, 0xbda49e5e, 0xbda17441, 0xbd9e492c, 0xbd9b1d31, 0xbd97f061, 0xbd94c2cf, 0xbd91948a, 0xbd8e65a6, 0xbd8b3632, 0xbd880642, 0xbd84d5e4, 0xbd81a52d, 0xbd7ce856, 0xbd7685e2, 0xbd70231e,
0xbd69c02f, 0xbd635d35, 0xbd5cfa53, 0xbd5697aa, 0xbd50355b, 0xbd49d389, 0xbd437257, 0xbd3d11e2, 0xbd36b250, 0xbd3053c0, 0xbd29f653, 0xbd239a2a, 0xbd1d3f67, 0xbd16e629, 0xbd108e92, 0xbd0a38c2, 0xbd03e4d9, 0xbcfb25ef, 0xbcee867c, 0xbce1eb98, 0xbcd55583, 0xbcc8c47c, 0xbcbc38c4, 0xbcafb296, 0xbca33234, 0xbc96b7da, 0xbc8a43c7, 0xbc7bac72, 0xbc62ded8, 0xbc4a1f3e, 0xbc316e1a, 0xbc18cbe6, 0xbc00391a, 0xbbcf6c5b, 0xbb9e8730, 0xbb5b873c, 0xbaf48a46, 0xb9ca4f35, 0x3a8ed14f, 0x3b27d0b9, 0x3b83f642, 0x3bb3dd1e, 0x3be39c10, 0x3c09991a, 0x3c214f56, 0x3c38f04c, 0x3c507b8e, 0x3c67f0af, 0x3c7f4f3f, 0x3c8b4b6a, 0x3c96e381, 0x3ca26fae, 0x3cadefbe, 0x3cb9637a, 0x3cc4cab0, 0x3cd0252b, 0x3cdb72b7, 0x3ce6b321, 0x3cf1e638, 0x3cfd0bc8, 0x3d0411d0, 0x3d0996c6, 0x3d0f14b0, 0x3d148b72, 0x3d19faf8, 0x3d1f6328, 0x3d24c3ea, 0x3d2a1d26, 0x3d2f6ec7, 0x3d34b8b4, 0x3d39fad7, 0x3d3f3518, 0x3d446763, 0x3d49919f, 0x3d4eb3b8, 0x3d53cd99, 0x3d58df2a, 0x3d5de856, 0x3d62e90a, 0x3d67e130, 0x3d6cd0b2, 0x3d71b77f, 0x3d769580, 0x3d7b6aa0, 0x3d801b67, 0x3d827cfb, 0x3d84da01, 0x3d873272, 0x3d898643, 0x3d8bd56a, 0x3d8e1fdf, 0x3d906599, 0x3d92a68f, 0x3d94e2b7, 0x3d971a0a, 0x3d994c7e, 0x3d9b7a0c, 0x3d9da2ab, 0x3d9fc651, 0x3da1e4fa, 0x3da3fe99, 0x3da6132a, 0x3da822a4, 0x3daa2d00, 0x3dac3236, 0x3dae323e, 0x3db02d10, 0x3db222a9, 0x3db412fc, 0x3db5fe08, 0x3db7e3c2, 0x3db9c426, 0x3dbb9f2d, 0x3dbd74cf, 0x3dbf4507, 0x3dc10fcf, 0x3dc2d521, 0x3dc494f6, 0x3dc64f49, 0x3dc80415, 0x3dc9b355, 0x3dcb5d01, 0x3dcd0118, 0x3dce9f90, 0x3dd03866, 0x3dd1cb97, 0x3dd3591c, 0x3dd4e0f0,
0x3dd66311, 0x3dd7df79, 0x3dd95624, 0x3ddac70d, 0x3ddc3232, 0x3ddd978e, 0x3ddef71c, 0x3de050db, 0x3de1a4c5, 0x3de2f2d9, 0x3de43b13, 0x3de57d6e, 0x3de6b9ea, 0x3de7f083, 0x3de92135, 0x3dea4bfe, 0x3deb70de, 0x3dec8fcf, 0x3deda8d1, 0x3deebbe1, 0x3defc8fe, 0x3df0d025, 0x3df1d155, 0x3df2cc8d, 0x3df3c1c9, 0x3df4b10b, 0x3df59a50, 0x3df67d97, 0x3df75adf, 0x3df83228, 0x3df90370, 0x3df9ceb8, 0x3dfa93fd, 0x3dfb5342, 0x3dfc0c83, 0x3dfcbfc4, 0x3dfd6d01, 0x3dfe143d, 0x3dfeb578, 0x3dff50b2, 0x3dffe5ea, 0x3e003a92, 0x3e007f2e, 0x3e00c0cc, 0x3e00ff6a, 0x3e013b0b, 0x3e0173ae, 0x3e01a954, 0x3e01dbfe, 0x3e020bad, 0x3e023861, 0x3e02621c, 0x3e0288dd, 0x3e02aca8, 0x3e02cd7c, 0x3e02eb5b, 0x3e030645, 0x3e031e3d, 0x3e033343, 0x3e034559, 0x3e035480, 0x3e0360ba, 0x3e036a08, 0x3e03706d, 0x3e0373e8, 0x3e03747d, 0x3e03722d, 0x3e036cfa, 0x3e0364e6, 0x3e0359f3, 0x3e034c22, 0x3e033b75, 0x3e0327f0, 0x3e031193, 0x3e02f862, 0x3e02dc5e, 0x3e02bd8a, 0x3e029be8, 0x3e02777b, 0x3e025044, 0x3e022647, 0x3e01f986, 0x3e01ca04, 0x3e0197c3, 0x3e0162c6, 0x3e012b11, 0x3e00f0a4, 0x3e00b384, 0x3e0073b4, 0x3e003136, 0x3dffd81c, 0x3dff487b, 0x3dfeb393, 0x3dfe1968, 0x3dfd7a00, 0x3dfcd565, 0x3dfc2b98, 0x3dfb7ca5, 0x3dfac890, 0x3dfa0f60, 0x3df9511c, 0x3df88dcd, 0x3df7c577, 0x3df6f823, 0x3df625d8, 0x3df54e9f, 0x3df4727c, 0x3df3917a, 0x3df2ab9f, 0x3df1c0f2, 0x3df0d17d, 0x3defdd46, 0x3deee455, 0x3dede6b3, 0x3dece469, 0x3debdd7e, 0x3dead1f9, 0x3de9c1e4, 0x3de8ad49, 0x3de7942c, 0x3de6769b, 0x3de5549a, 0x3de42e34, 0x3de30373, 0x3de1d45d, 0x3de0a0fd, 0x3ddf695b, 0x3dde2d80,
0x3ddced76, 0x3ddba947, 0x3dda60fb, 0x3dd9149b, 0x3dd7c430, 0x3dd66fc6, 0x3dd51764, 0x3dd3bb15, 0x3dd25ae3, 0x3dd0f6d6, 0x3dcf8efa, 0x3dce2357, 0x3dccb3f7, 0x3dcb40e6, 0x3dc9ca2b, 0x3dc84fd2, 0x3dc6d1e6, 0x3dc5506f, 0x3dc3cb78, 0x3dc2430b, 0x3dc0b734, 0x3dbf27fc, 0x3dbd956d, 0x3dbbff92, 0x3dba6676, 0x3db8ca23, 0x3db72aa4, 0x3db58804, 0x3db3e24c, 0x3db23988, 0x3db08dc4, 0x3daedf08, 0x3dad2d60, 0x3dab78d9, 0x3da9c17a, 0x3da80752, 0x3da64a6a, 0x3da48acc, 0x3da2c885, 0x3da1039f, 0x3d9f3c26, 0x3d9d7224, 0x3d9ba5a6, 0x3d99d6b5, 0x3d98055d, 0x3d9631ab, 0x3d945ba8, 0x3d928361, 0x3d90a8e0, 0x3d8ecc31, 0x3d8ced5f, 0x3d8b0c77, 0x3d892982, 0x3d87448d, 0x3d855da3, 0x3d8374d0, 0x3d818a1f, 0x3d7f3b3a, 0x3d7b5ea6, 0x3d777e9c, 0x3d739b33, 0x3d6fb482, 0x3d6bca9e, 0x3d67dda2, 0x3d63eda4, 0x3d5ffaba, 0x3d5c04fd, 0x3d580c82, 0x3d541162, 0x3d5013b4, 0x3d4c138f, 0x3d48110a, 0x3d440c3d, 0x3d40053e, 0x3d3bfc26, 0x3d37f10c, 0x3d33e406, 0x3d2fd52b, 0x3d2bc495, 0x3d27b259, 0x3d239e8f, 0x3d1f894e, 0x3d1b72ad, 0x3d175ac4, 0x3d1341a9, 0x3d0f2774, 0x3d0b0c3b, 0x3d06f017, 0x3d02d31e, 0x3cfd6ad0, 0x3cf52e14, 0x3cecf038, 0x3ce4b16c, 0x3cdc71db, 0x3cd431b5, 0x3ccbf125, 0x3cc3b05b, 0x3cbb6f84, 0x3cb32ecc, 0x3caaee63, 0x3ca2ae73, 0x3c9a6f2c, 0x3c9230b9, 0x3c89f349, 0x3c81b708, 0x3c72f843, 0x3c628585, 0x3c521632, 0x3c41aaa0, 0x3c314328, 0x3c20e022, 0x3c1081e7, 0x3c0028cf, 0x3bdfaa5f, 0x3bbf0ec1, 0x3b9e7f72, 0x3b7bfa40, 0x3b3b10ea, 0x3af4887c, 0x3a665644, 0xb8df390b, 0xba8ed0f4, 0xbb07b531, 0xbb47de9d, 0xbb83f1b7, 0xbba3e12a, 0xbbc3bd03, 0xbbe3849a,
};


/**************************************************************************************************
 ~~~ Local Functions Implementation
 **************************************************************************************************/
inline float PolyFirUtils::sincWarp(float x) {
    //Pick a SINC implementation
    return sincLookup(x);  //fast version (+/- 1 differences)
    //return (sin(x)/(x)); //slow version (accurate)
    //return (0.8f)         //debug only(some constant)
}
inline float PolyFirUtils::sincLookup(float x)
{
  //sinc is symmetric (same for x and -x)
    uint32_t *uVal = (uint32_t*)&x;
    *uVal &= 0x7FFFFFFF; //clear sign

    int p = (int)(x * (MAX_SZ/MAX_VAL) + 0.5f);
    float *sincLutF32 = (float*)sincLut;
    return sincLutF32[p];
}

//Dave's routine to compute polyFir params
void PolyFirUtils::calcCoeffs(uint8_t *coef, uint32_t n, uint32_t d, uint32_t *ksize)
{
    float   scale = (float)n / (float)d;
    int     ncoefs = 7 * n;     /* 7 taps, N phases */
    int     i, p, oIdx;
    float   f, sinc, window;
    float   fCutoff;
    float   tcoef[7*MAX_PHASES];
    float   sum;
    int     sumi;

    #define ZERO_COEF   64

    memset(coef, ZERO_COEF, sizeof(*coef)*8*MAX_PHASES);

  // When downscaling, we want a lower cutoff frequency, to avoid aliasing
    fCutoff = scale * 3;
    if (fCutoff < 1)   fCutoff = 1;
    if (fCutoff > 3)   fCutoff = 3;

    for (i = 0; i < ncoefs; i++) {
        f = (float)i / (ncoefs-1) * 2 * M_PI - M_PI;
        if (f == 0) {
            tcoef[i] = 1.0;
        } else {
            /* Lanczos-windowed Sinc function */
            sinc   = sincWarp(f*fCutoff);
            window = sincWarp(f);
            tcoef[i] = sinc * window;
        }
    }

  // Normalise the co-efficients for each phase so that they sum to 1.
  // For the hardware, we group the co-efficients into phases.  They're
  // in groups of 7, with each group followed by a padding element.
  // Co-efficients are also mapped to the range [-0.5, 1.49219], which
  // is stored as a uint8_t in the hardware registers, by scaling and
  // adding a bias of 64.
    oIdx = 0;
    for (p = n-1; p >= 0; p--) {
        sum = 0;
        for (i = p; i < ncoefs; i += n) {
            sum += tcoef[i];
        }
        sumi = 0;
        for (i = p; i < ncoefs; i += n) {
            int curCoef = (tcoef[i] / sum) * 128.0f + 64.0f + 0.5f;
            assert(curCoef >=   0); //check it's in [0..255] range
            assert(curCoef <= 255);
            coef[oIdx] = (uint8_t)curCoef;
            sumi += coef[oIdx]-64;

            if ((++oIdx & 7) == 7) {
                /* Co-efficients are 8 element aligned */
                oIdx++;
            }
        }
        if (sumi != 128) {
            /*
             * Due to rounding when converting to integer, co-efficients don't
             * sum to exactly 1.0, so perform adjustment.
             */
            coef[oIdx-5] += (128-sumi);
        }

    }

    *ksize = 7;
    if (coef[0] == ZERO_COEF && coef[6] == ZERO_COEF) *ksize -= 2;
    if (coef[1] == ZERO_COEF && coef[5] == ZERO_COEF) *ksize -= 2;
}

//==============================================================================
//Computes H/V coefficients based on "cfg" N/D params
//"cfg" can point to either Luma or Chroma config struct
//Returns kernel size
uint32_t PolyFirUtils::computeCoefs(uint8_t *hCoefs, uint8_t *vCoefs, UpfirdnCfg *cfg)
{
   uint32_t szH, szV;

  //Compute Horizontal coefficients
   calcCoeffs(hCoefs, cfg->hN, cfg->hD, &szH);

  //Compute Vertical coefficients
   if((cfg->hN == cfg->vN) && (cfg->hD == cfg->vD))
   { //If vertical N,D match horizontal numbers, just copy
      memcpy(vCoefs, hCoefs, 8 * cfg->vN);
      szV = szH;
   }else{ //else compute
      calcCoeffs(vCoefs, cfg->vN, cfg->vD, &szV);
   }

   return MAX(szH, szV);
}

//==============================================================================
//Adjusts chroma N,D ratios for 420,422 or 444
void PolyFirUtils::setChromaRatio(YuvScale *s)
{
  //Try simplify the Numerator if possible, else double Denominator
   if((s->outFmt == FMT_420)||(s->outFmt == FMT_422)){
     if((s->polyC.hN & 0x1) == 0) s->polyC.hN = s->polyC.hN>>1;
     else                         s->polyC.hD = s->polyC.hD<<1;
   }

   if(s->outFmt == FMT_420){
      if((s->polyC.vN & 0x1) == 0) s->polyC.vN = s->polyC.vN>>1;
      else                         s->polyC.vD = s->polyC.vD<<1;
   }

   //Note: no adjustments for FMT_444 !

    assert(s->polyC.vN <= 16); //"Maximum valid value is 16"
    assert(s->polyC.vD <= 63); //"Maximum valid value is 63"
}

/**************************************************************************************************
 ~~~ Exported Functions Implementation
 **************************************************************************************************/

//Once, at plugin creation
void PolyFirUtils::computePolyFirInit()
{
    s = &scale;
   //Assing local object tables
    s->polyY.hCoefs = s->_hCoefsY;
    s->polyY.vCoefs = s->_vCoefsY;
    s->polyC.hCoefs = s->_hCoefsC;
    s->polyC.vCoefs = s->_vCoefsC;
   //Some invalid "last" value
    s->polyY.hN = s->polyY.hD = 0;
}

//Compute all Luma and Chroma polyfir params based on Luma N and D factors
void PolyFirUtils::computePolyfirParams(icIspConfig *ic)
{
   //Recompute params only on Luma N/D changes (track vs old values)
    if( (s->polyY.hN != ic->updnCfg0.hN) || (s->polyY.hD != ic->updnCfg0.hD) ||
        (s->polyY.vN != ic->updnCfg0.vN) || (s->polyY.vD != ic->updnCfg0.vD) )
    {
      /*PROF*/ #if defined(POLY_PROF)
      /*PROF*/ DrvTimerGetSystemTicks64(&startTime);
      /*PROF*/ #endif

      //Luma params:
       s->polyY.hN    = ic->updnCfg0.hN;  s->polyY.hD = ic->updnCfg0.hD;
       s->polyY.vN    = ic->updnCfg0.vN;  s->polyY.vD = ic->updnCfg0.vD;
       s->polyY.kerSz = computeCoefs(s->_hCoefsY, s->_vCoefsY, &s->polyY);

      //Chroma params:
       s->polyC.hN = ic->updnCfg0.hN;  s->polyC.vN = ic->updnCfg0.vN; //default Y params
       s->polyC.hD = ic->updnCfg0.hD;  s->polyC.vD = ic->updnCfg0.vD;
       setChromaRatio(s);
       s->polyC.kerSz = computeCoefs(s->_hCoefsC, s->_vCoefsC, &s->polyC);

       /*PROF*/ #if defined(POLY_PROF)
       /*PROF*/  DrvTimerGetSystemTicks64(&endTime);
       /*PROF*/  polyTime = endTime - startTime;
       /*PROF*/ #endif
    }

  //Must always set polyfir params
    ic->updnCfg0  = s->polyY;
    ic->updnCfg12 = s->polyC;
}
