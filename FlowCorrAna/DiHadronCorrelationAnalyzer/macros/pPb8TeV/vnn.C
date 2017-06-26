#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
//#include "/net/hisrv0001/home/davidlw/useful_macros/GetMultiJetCorrFunc.C"

void vnn()
{
  TString filename[100];
  TString filename1[100];
  TString dirname[100];
/*
  filename[0] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N010_run285479_285530_v1.root";
  filename[1] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N1020_run285479_285530_v1.root";
  filename[2] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N2030_run285479_285530_v1.root";
  filename[3] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N3040_run285479_285530_v1.root";
  filename[4] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N4050_run285479_285530_v1.root";
  filename[5] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N5060_run285479_285530_v1.root";
  filename[6] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N6070_run285479_285530_v1.root";
  filename[7] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N7080_run285479_285530_v1.root";
  filename[8] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N80100_run285479_285530_v1.root";
  filename[9] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N100120_run285479_285530_v1.root";
  filename[10] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N120135_run285479_285530_v1.root";
  filename[11] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N135150_run285479_285530_v1.root";
  filename[12] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N150160_run285479_285530_v1.root";
  filename[13] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N160185_run285479_285530_v1.root";
  filename[14] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185210_run285479_285530_v1.root";
  filename[15] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N210230_run285479_285530_v1.root";
  filename[16] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N230250_run285479_285530_v1.root";
  filename[17] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N250270_run285479_285530_v1.root";
  filename[18] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N270300_run285479_285530_v1.root";
  filename[19] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N300330_run285479_285530_v1.root";
  filename[20] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N330360_run285479_285530_v1.root";
  filename[21] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N360400_run285479_285530_v1.root";
  filename[22] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N400500_run285479_285530_v1.root";
*/

  filename[0] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N020MB1_pPb_Golden_dz01_v8.root";
  filename[1] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N0MB1_pPb_Golden_dz01_v8.root";
  filename[2] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N0MB1_pPb_Golden_dz01_v8.root";
  filename[3] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N30MB1_pPb_Golden_dz01_v8.root";
  filename[4] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N30MB1_pPb_Golden_dz01_v8.root";
  filename[5] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N30MB1_pPb_Golden_dz01_v8.root";
  filename[6] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N60MB1_pPb_Golden_dz01_v8.root";
  filename[7] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N60MB1_pPb_Golden_dz01_v8.root";
  filename[8] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N60MB1_pPb_Golden_dz01_v8.root";
  filename[9] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N60MB1_pPb_Golden_dz01_v8.root";
  filename[10] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N120HM0_pPb_Golden_dz01_v8r1.root";
  filename[11] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N120HM0_pPb_Golden_dz01_v8r1.root";
  filename[12] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N120HM0_pPb_Golden_dz01_v8r1.root";
  filename[13] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N120HM0_pPb_Golden_dz01_v8r1.root";
  filename[14] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185HM1_pPb_Golden_dz01_v8r1.root";
  filename[15] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185HM1_pPb_Golden_dz01_v8r1.root";
  filename[16] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185HM1_pPb_Golden_dz01_v8r1.root";
/*
  filename[14] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N120HM0_pPb_Golden_dz01_v8r1.root";
  filename[15] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N120HM0_pPb_Golden_dz01_v8r1.root";
  filename[16] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N120HM0_pPb_Golden_dz01_v8r1.root";
*/
  filename[17] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N250HM7_pPb_Golden_dz01_v8.root";
  filename[18] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N250HM7_pPb_Golden_dz01_v8.root";
  filename[19] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N250HM7_pPb_Golden_dz01_v8.root";
/*
  filename[17] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185HM1_pPb_Golden_dz01_v8r1.root";
  filename[18] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185HM1_pPb_Golden_dz01_v8r1.root";
  filename[19] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N185HM1_pPb_Golden_dz01_v8r1.root";
*/
  filename[20] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N330HM7_All_Golden_dz01_NoHighPU1_v16.root";
  filename[21] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N330HM7_All_Golden_dz01_NoHighPU1_v16.root";
  filename[22] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N370HM7_All_Golden_dz01_NoHighPU1_v16.root";
  filename[23] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N370HM7_All_Golden_dz01_NoHighPU1_v16.root";
  filename[24] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_8TeV/merged/corrana_pPb2016_pt033_N370HM7_All_Golden_dz01_NoHighPU1_v16.root";
/*
  filename1[0] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N0MB5_Golden_dz01_v4.root";
  filename1[1] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N0MB5_Golden_dz01_v4.root";
  filename1[2] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N0MB5_Golden_dz01_v4.root";
  filename1[3] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N30MB5_Golden_dz01_v4.root";
  filename1[4] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N30MB5_Golden_dz01_v4.root";
  filename1[5] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N30MB5_Golden_dz01_v4.root";
  filename1[6] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N60MB5_Golden_dz01_v4.root";
  filename1[7] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N60MB5_Golden_dz01_v4.root";
  filename1[8] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N60MB5_Golden_dz01_v4.root";
  filename1[9] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N60MB5_Golden_dz01_v4.root";
  filename1[10] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N120MB5_Golden_dz01_v4.root";
  filename1[11] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N120MB5_Golden_dz01_v4.root";
  filename1[12] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N120MB5_Golden_dz01_v4.root";
  filename1[13] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N120MB5_Golden_dz01_v4.root";
  filename1[14] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N185MB5_Golden_dz01_v4.root";
  filename1[15] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N185MB5_Golden_dz01_v4.root";
  filename1[16] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N185MB5_Golden_dz01_v4.root";
  filename1[17] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N250MB5_Golden_dz01_v4.root";
  filename1[18] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N250MB5_Golden_dz01_v4.root";
  filename1[19] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N250MB5_Golden_dz01_v4.root";
  filename1[20] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB5_Golden_dz01_v4.root";
  filename1[21] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB5_Golden_dz01_v4.root";
  filename1[22] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB5_Golden_dz01_v4.root";
  filename1[23] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB5_Golden_dz01_v4.root";
  filename1[24] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB5_Golden_dz01_v4.root";
*/

  filename1[0] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N020MB567_All_dz01_v3.root";
//  filename1[0] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N0MB567_Golden_v3.root";
  filename1[1] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N0MB567_Golden_v3.root";
  filename1[2] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N0MB567_Golden_v3.root";
  filename1[3] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N30MB567_Golden_v3.root";
  filename1[4] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N30MB567_Golden_v3.root";
  filename1[5] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N30MB567_Golden_v3.root";
  filename1[6] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N60MB567_Golden_v3.root";
  filename1[7] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N60MB567_Golden_v3.root";
  filename1[8] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N60MB567_Golden_v3.root";
  filename1[9] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N60MB567_Golden_v3.root";
  filename1[10] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N120MB67_Golden_v3.root";
  filename1[11] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N120MB67_Golden_v3.root";
  filename1[12] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N120MB67_Golden_v3.root";
  filename1[13] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N120MB67_Golden_v3.root";
  filename1[14] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N185MB67_Golden_v3.root";
  filename1[15] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N185MB67_Golden_v3.root";
  filename1[16] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N185MB67_Golden_v3.root";
  filename1[17] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N250MB67_Golden_v3.root";
  filename1[18] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N250MB67_Golden_v3.root";
  filename1[19] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N250MB67_Golden_v3.root";
  filename1[20] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB67_Golden_v3.root";
  filename1[21] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB67_Golden_v3.root";
  filename1[22] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB67_Golden_v3.root";
  filename1[23] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB67_Golden_v3.root";
  filename1[24] = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_5TeV/merged/corrana_PbPb2015_pt033_N330MB67_Golden_v3.root";

  dirname[0] = "corr_ana_N020";
  dirname[1] = "corr_ana_N1020";
  dirname[2] = "corr_ana_N2030";
  dirname[3] = "corr_ana_N3040";
  dirname[4] = "corr_ana_N4050";
  dirname[5] = "corr_ana_N5060";
  dirname[6] = "corr_ana_N6070";
  dirname[7] = "corr_ana_N7080";
  dirname[8] = "corr_ana_N80100";
  dirname[9] = "corr_ana_N100120";
  dirname[10] = "corr_ana_N120135";
  dirname[11] = "corr_ana_N135150";
  dirname[12] = "corr_ana_N150160";
  dirname[13] = "corr_ana_N160185";
  dirname[14] = "corr_ana_N185210";
  dirname[15] = "corr_ana_N210230";
  dirname[16] = "corr_ana_N230250";
  dirname[17] = "corr_ana_N250270";
  dirname[18] = "corr_ana_N270300";
  dirname[19] = "corr_ana_N300330";
  dirname[20] = "corr_ana_N330350";
  dirname[21] = "corr_ana_N350370";
  dirname[22] = "corr_ana_N370390";
  dirname[23] = "corr_ana_N390420";
  dirname[24] = "corr_ana_N420500";


  TH1D* hdphi[100];
  TH1D* hdphi_short[100];
  TH1D* hdphi_short_zyam[100];
  TH1D* hmult[100];
  TF1*  fitfunc[100];

  TH1D* hdphi_Pb[100];
  TH1D* hdphi_short_Pb[100];
  TH1D* hdphi_short_zyam_Pb[100];
  TH1D* hmult_Pb[100];
  TF1*  fitfunc_Pb[100];

  int ptmin=0;
  int ptmax=0;
  double detamin=1.9;
  double detamax=4.8; 

  double nmult[100]={0};
  double nmulterr[100]={0};

  double nmult_Pb[100]={0};
  double nmulterr_Pb[100]={0};

  double V0[100]={0};
  double V1[100]={0};
  double V2[100]={0};
  double V3[100]={0};
  double V4[100]={0};
  double V5[100]={0};
  double V6[100]={0};

  double V0err[100]={0};
  double V1err[100]={0};
  double V2err[100]={0};
  double V3err[100]={0};
  double V4err[100]={0};
  double V5err[100]={0};
  double V6err[100]={0};

  double v1[100]={0};
  double v2[100]={0};
  double v3[100]={0};
  double v4[100]={0};
  double v5[100]={0};
  double v6[100]={0};

  double v1err[100]={0};
  double v2err[100]={0};
  double v3err[100]={0};
  double v4err[100]={0};
  double v5err[100]={0};
  double v6err[100]={0};

  double V1sub[100]={0};
  double V2sub[100]={0};
  double V3sub[100]={0};
  double V4sub[100]={0};
  double V5sub[100]={0};
  double V6sub[100]={0};

  double V1suberr[100]={0};
  double V2suberr[100]={0};
  double V3suberr[100]={0};
  double V4suberr[100]={0};
  double V5suberr[100]={0};
  double V6suberr[100]={0};

  double v1sub[100]={0};
  double v2sub[100]={0};
  double v3sub[100]={0};
  double v4sub[100]={0};
  double v5sub[100]={0};
  double v6sub[100]={0};

  double v1suberr[100]={0};
  double v2suberr[100]={0};
  double v3suberr[100]={0};
  double v4suberr[100]={0};
  double v5suberr[100]={0};
  double v6suberr[100]={0};

  double V0_Pb[100]={0};
  double V1_Pb[100]={0};
  double V2_Pb[100]={0};
  double V3_Pb[100]={0};
  double V4_Pb[100]={0};
  double V5_Pb[100]={0};
  double V6_Pb[100]={0};

  double V0err_Pb[100]={0};
  double V1err_Pb[100]={0};
  double V2err_Pb[100]={0};
  double V3err_Pb[100]={0};
  double V4err_Pb[100]={0};
  double V5err_Pb[100]={0};
  double V6err_Pb[100]={0};

  double v1_Pb[100]={0};
  double v2_Pb[100]={0};
  double v3_Pb[100]={0};
  double v4_Pb[100]={0};
  double v5_Pb[100]={0};
  double v6_Pb[100]={0};

  double v1err_Pb[100]={0};
  double v2err_Pb[100]={0};
  double v3err_Pb[100]={0};
  double v4err_Pb[100]={0};
  double v5err_Pb[100]={0};
  double v6err_Pb[100]={0};

  double V1sub_Pb[100]={0};
  double V2sub_Pb[100]={0};
  double V3sub_Pb[100]={0};
  double V4sub_Pb[100]={0};
  double V5sub_Pb[100]={0};
  double V6sub_Pb[100]={0};

  double V1suberr_Pb[100]={0};
  double V2suberr_Pb[100]={0};
  double V3suberr_Pb[100]={0};
  double V4suberr_Pb[100]={0};
  double V5suberr_Pb[100]={0};
  double V6suberr_Pb[100]={0};

  double v1sub_Pb[100]={0};
  double v2sub_Pb[100]={0};
  double v3sub_Pb[100]={0};
  double v4sub_Pb[100]={0};
  double v5sub_Pb[100]={0};
  double v6sub_Pb[100]={0};

  double v1suberr_Pb[100]={0};
  double v2suberr_Pb[100]={0};
  double v3suberr_Pb[100]={0};
  double v4suberr_Pb[100]={0};
  double v5suberr_Pb[100]={0};
  double v6suberr_Pb[100]={0};

  double jetyield[100]={0};
  double jetyielderr[100]={0};
  double jetyield_ratio[100]={0};
  double jetyield_Pb[100]={0};
  double jetyielderr_Pb[100]={0};
  double jetyield_ratio_Pb[100]={0};

  int nref=0;
  for(int i=0;i<25;i++)
  {
//cout<<"i="<<i<<endl;
    hmult[i] = (TH1D*)GetHist(filename[i],dirname[i],"multrawall");
    hdphi[i] = (TH1D*)Get1DCFdPhiv3(filename[i].Data(),dirname[i],ptmin,ptmax,detamin,detamax);
    hdphi_short[i] = (TH1D*)Get1DCFdPhiv3(filename[i].Data(),dirname[i],ptmin,ptmax,-1,1);
    hdphi_short[i]->Add(hdphi[i],-1);
    hdphi_short_zyam[i]=GetJetCorrFunc1D_ZYAM(hdphi_short[i]);
//cout<<"got here"<<endl;
//    hdphi[i] = (TH1D*)Get1DSignaldPhi(filename[i].Data(),dirname[i],ptmin,ptmax,detamin,detamax);
//cout<<"got here 1"<<endl;

    jetyield[i] = hdphi_short_zyam[i]->IntegralAndError(hdphi_short_zyam[i]->FindBin(0),hdphi_short_zyam[i]->FindBin(2.0),jetyielderr[i],"width");
    if(i>=nref) jetyield_ratio[i] = jetyield[i]/jetyield[nref];
//    jetyield_ratio[i] = 1;

    hdphi[i]->SetMarkerStyle(20);
    hdphi_short[i]->SetMarkerStyle(20);
    hdphi_short_zyam[i]->SetMarkerStyle(20);

    fitfunc[i] = new TF1(Form("fitfunc_%d",i),"[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x)+2*[6]*cos(6*x))",0,PI);
    fitfunc[i]->SetLineColor(2);
    hdphi[i]->Fit(Form("fitfunc_%d",i),"RNO");
    hdphi[i]->Fit(Form("fitfunc_%d",i),"RNO");
    hdphi[i]->Fit(Form("fitfunc_%d",i),"RNO");
  
    nmult[i]=hmult[i]->GetMean();
    V0[i]=fitfunc[i]->GetParameter(0);
    V1[i]=fitfunc[i]->GetParameter(1);
    V2[i]=fitfunc[i]->GetParameter(2);
    V3[i]=fitfunc[i]->GetParameter(3);
    V4[i]=fitfunc[i]->GetParameter(4);
    V5[i]=fitfunc[i]->GetParameter(5);
    V6[i]=fitfunc[i]->GetParameter(6);
    V0err[i]=fitfunc[i]->GetParError(0);
    V1err[i]=fitfunc[i]->GetParError(1);
    V2err[i]=fitfunc[i]->GetParError(2);
    V3err[i]=fitfunc[i]->GetParError(3);
    V4err[i]=fitfunc[i]->GetParError(4);
    V5err[i]=fitfunc[i]->GetParError(5);
    V6err[i]=fitfunc[i]->GetParError(6);
    if(V2[i] && fabs(V2[i]/V2err[i])>2) v2[i]=sqrt(V2[i]);
    if(V3[i] && fabs(V3[i]/V3err[i])>2) v3[i]=sqrt(V3[i]);
    if(V4[i] && fabs(V4[i]/V4err[i])>2) v4[i]=sqrt(V4[i]);
    if(V5[i] && fabs(V5[i]/V5err[i])>2) v5[i]=sqrt(V5[i]);
    if(V6[i] && fabs(V6[i]/V6err[i])>2) v6[i]=sqrt(V6[i]);
    if(V2[i] && fabs(V2[i]/V2err[i])>2) v2err[i]=0.5*v2[i]*V2err[i]/V2[i];
    if(V3[i] && fabs(V3[i]/V3err[i])>2) v3err[i]=0.5*v3[i]*V3err[i]/V3[i];
    if(V4[i] && fabs(V4[i]/V4err[i])>2) v4err[i]=0.5*v4[i]*V4err[i]/V4[i];
    if(V5[i] && fabs(V5[i]/V5err[i])>2) v5err[i]=0.5*v5[i]*V5err[i]/V5[i];
    if(V6[i] && fabs(V6[i]/V6err[i])>2) v6err[i]=0.5*v6[i]*V6err[i]/V6[i];

   if(i>=nref)
   {
    V1sub[i] = V1[i]-jetyield_ratio[i]*V1[nref]*V0[nref]/V0[i];
    V2sub[i] = V2[i]-jetyield_ratio[i]*V2[nref]*V0[nref]/V0[i];
    V3sub[i] = V3[i]-jetyield_ratio[i]*V3[nref]*V0[nref]/V0[i];
    V4sub[i] = V4[i]-jetyield_ratio[i]*V4[nref]*V0[nref]/V0[i];
    V5sub[i] = V5[i]-jetyield_ratio[i]*V5[nref]*V0[nref]/V0[i];
    V6sub[i] = V6[i]-jetyield_ratio[i]*V6[nref]*V0[nref]/V0[i];
    V1suberr[i] = sqrt(V1err[i]*V1err[i]+V1err[nref]*V1err[nref]*V0[nref]*V0[nref]/V0[i]/V0[i]);
    V2suberr[i] = sqrt(V2err[i]*V2err[i]+V2err[nref]*V2err[nref]*V0[nref]*V0[nref]/V0[i]/V0[i]);
    V3suberr[i] = sqrt(V3err[i]*V3err[i]+V3err[nref]*V3err[nref]*V0[nref]*V0[nref]/V0[i]/V0[i]);
    V4suberr[i] = sqrt(V4err[i]*V4err[i]+V4err[nref]*V4err[nref]*V0[nref]*V0[nref]/V0[i]/V0[i]);
    V5suberr[i] = sqrt(V5err[i]*V5err[i]+V5err[nref]*V5err[nref]*V0[nref]*V0[nref]/V0[i]/V0[i]);
    V6suberr[i] = sqrt(V6err[i]*V6err[i]+V6err[nref]*V6err[nref]*V0[nref]*V0[nref]/V0[i]/V0[i]);
    if(V2sub[i] && fabs(V2sub[i]/V2suberr[i])>2) v2sub[i]=sqrt(V2sub[i]);
    if(V3sub[i] && fabs(V3sub[i]/V3suberr[i])>2) v3sub[i]=sqrt(V3sub[i]);
    if(V4sub[i] && fabs(V4sub[i]/V4suberr[i])>2) v4sub[i]=sqrt(V4sub[i]);
    if(V5sub[i] && fabs(V5sub[i]/V5suberr[i])>2) v5sub[i]=sqrt(V5sub[i]);
    if(V6sub[i] && fabs(V6sub[i]/V6suberr[i])>2) v6sub[i]=sqrt(V6sub[i]);
    if(V2sub[i] && fabs(V2sub[i]/V2suberr[i])>2) v2suberr[i]=0.5*v2sub[i]*V2suberr[i]/V2sub[i];
    if(V3sub[i] && fabs(V3sub[i]/V3suberr[i])>2) v3suberr[i]=0.5*v3sub[i]*V3suberr[i]/V3sub[i];
    if(V4sub[i] && fabs(V4sub[i]/V4suberr[i])>2) v4suberr[i]=0.5*v4sub[i]*V4suberr[i]/V4sub[i];
    if(V5sub[i] && fabs(V5sub[i]/V5suberr[i])>2) v5suberr[i]=0.5*v5sub[i]*V5suberr[i]/V5sub[i];
    if(V6sub[i] && fabs(V6sub[i]/V6suberr[i])>2) v6suberr[i]=0.5*v6sub[i]*V6suberr[i]/V6sub[i];
   }

    hmult_Pb[i] = (TH1D*)GetHist(filename1[i],dirname[i],"multrawall");
    hdphi_Pb[i] = (TH1D*)Get1DCFdPhiv3(filename1[i].Data(),dirname[i],ptmin,ptmax,detamin,detamax);
    hdphi_short_Pb[i] = (TH1D*)Get1DCFdPhiv3(filename1[i].Data(),dirname[i],ptmin,ptmax,-1,1);
    hdphi_short_Pb[i]->Add(hdphi_Pb[i],-1);
    hdphi_short_zyam_Pb[i]=GetJetCorrFunc1D_ZYAM(hdphi_short_Pb[i]);

    jetyield_Pb[i] = hdphi_short_zyam_Pb[i]->IntegralAndError(hdphi_short_zyam_Pb[i]->FindBin(0),hdphi_short_zyam_Pb[i]->FindBin(2.0),jetyielderr_Pb[i],"width");
    if(i>=nref) jetyield_ratio_Pb[i] = jetyield_Pb[i]/jetyield_Pb[nref];
//    jetyield_ratio_Pb[i] = 1;


//    hdphi_Pb[i] = (TH1D*)Get1DSignaldPhi(filename1[i].Data(),dirname[i],ptmin,ptmax,detamin,detamax);
    hdphi_Pb[i]->SetMarkerStyle(20);
    hdphi_short_Pb[i]->SetMarkerStyle(20);
    hdphi_short_zyam_Pb[i]->SetMarkerStyle(20);

    fitfunc_Pb[i] = new TF1(Form("fitfunc1_%d",i),"[0]*(1+2*[1]*cos(x)+2*[2]*cos(2*x)+2*[3]*cos(3*x)+2*[4]*cos(4*x)+2*[5]*cos(5*x)+2*[6]*cos(6*x))",0,PI);
    fitfunc_Pb[i]->SetLineColor(2);
    hdphi_Pb[i]->Fit(Form("fitfunc1_%d",i),"RNO");
    hdphi_Pb[i]->Fit(Form("fitfunc1_%d",i),"RNO");
    hdphi_Pb[i]->Fit(Form("fitfunc1_%d",i),"RNO");

    nmult_Pb[i]=hmult_Pb[i]->GetMean();
    V0_Pb[i]=fitfunc_Pb[i]->GetParameter(0);
    V1_Pb[i]=fitfunc_Pb[i]->GetParameter(1);
    V2_Pb[i]=fitfunc_Pb[i]->GetParameter(2);
    V3_Pb[i]=fitfunc_Pb[i]->GetParameter(3);
    V4_Pb[i]=fitfunc_Pb[i]->GetParameter(4);
    V5_Pb[i]=fitfunc_Pb[i]->GetParameter(5);
    V6_Pb[i]=fitfunc_Pb[i]->GetParameter(6);
    V0err_Pb[i]=fitfunc_Pb[i]->GetParError(0);
    V1err_Pb[i]=fitfunc_Pb[i]->GetParError(1);
    V2err_Pb[i]=fitfunc_Pb[i]->GetParError(2);
    V3err_Pb[i]=fitfunc_Pb[i]->GetParError(3);
    V4err_Pb[i]=fitfunc_Pb[i]->GetParError(4);
    V5err_Pb[i]=fitfunc_Pb[i]->GetParError(5);
    V6err_Pb[i]=fitfunc_Pb[i]->GetParError(6);
    if(V2_Pb[i] && fabs(V2_Pb[i]/V2err_Pb[i])>2) v2_Pb[i]=sqrt(V2_Pb[i]);
    if(V3_Pb[i] && fabs(V3_Pb[i]/V3err_Pb[i])>2) v3_Pb[i]=sqrt(V3_Pb[i]);
    if(V4_Pb[i] && fabs(V4_Pb[i]/V4err_Pb[i])>2) v4_Pb[i]=sqrt(V4_Pb[i]);
    if(V5_Pb[i] && fabs(V5_Pb[i]/V5err_Pb[i])>2) v5_Pb[i]=sqrt(V5_Pb[i]);
    if(V6_Pb[i] && fabs(V6_Pb[i]/V6err_Pb[i])>2) v6_Pb[i]=sqrt(V6_Pb[i]);
    if(V2_Pb[i] && fabs(V2_Pb[i]/V2err_Pb[i])>2) v2err_Pb[i]=0.5*v2_Pb[i]*V2err_Pb[i]/V2_Pb[i];
    if(V3_Pb[i] && fabs(V3_Pb[i]/V3err_Pb[i])>2) v3err_Pb[i]=0.5*v3_Pb[i]*V3err_Pb[i]/V3_Pb[i];
    if(V4_Pb[i] && fabs(V4_Pb[i]/V4err_Pb[i])>2) v4err_Pb[i]=0.5*v4_Pb[i]*V4err_Pb[i]/V4_Pb[i];
    if(V5_Pb[i] && fabs(V5_Pb[i]/V5err_Pb[i])>2) v5err_Pb[i]=0.5*v5_Pb[i]*V5err_Pb[i]/V5_Pb[i];
    if(V6_Pb[i] && fabs(V6_Pb[i]/V6err_Pb[i])>2) v6err_Pb[i]=0.5*v6_Pb[i]*V6err_Pb[i]/V6_Pb[i];

   if(i>=nref)
   {
    V1sub_Pb[i] = V1_Pb[i]-jetyield_ratio_Pb[i]*V1_Pb[nref]*V0_Pb[nref]/V0_Pb[i];
    V2sub_Pb[i] = V2_Pb[i]-jetyield_ratio_Pb[i]*V2_Pb[nref]*V0_Pb[nref]/V0_Pb[i];
    V3sub_Pb[i] = V3_Pb[i]-jetyield_ratio_Pb[i]*V3_Pb[nref]*V0_Pb[nref]/V0_Pb[i];
    V4sub_Pb[i] = V4_Pb[i]-jetyield_ratio_Pb[i]*V4_Pb[nref]*V0_Pb[nref]/V0_Pb[i];
    V5sub_Pb[i] = V5_Pb[i]-jetyield_ratio_Pb[i]*V5_Pb[nref]*V0_Pb[nref]/V0_Pb[i];
    V6sub_Pb[i] = V6_Pb[i]-jetyield_ratio_Pb[i]*V6_Pb[nref]*V0_Pb[nref]/V0_Pb[i];
    V1suberr_Pb[i] = sqrt(V1err_Pb[i]*V1err_Pb[i]+V1err_Pb[nref]*V1err_Pb[nref]*V0_Pb[nref]*V0_Pb[nref]/V0_Pb[i]/V0_Pb[i]);
    V2suberr_Pb[i] = sqrt(V2err_Pb[i]*V2err_Pb[i]+V2err_Pb[nref]*V2err_Pb[nref]*V0_Pb[nref]*V0_Pb[nref]/V0_Pb[i]/V0_Pb[i]);
    V3suberr_Pb[i] = sqrt(V3err_Pb[i]*V3err_Pb[i]+V3err_Pb[nref]*V3err_Pb[nref]*V0_Pb[nref]*V0_Pb[nref]/V0_Pb[i]/V0_Pb[i]);
    V4suberr_Pb[i] = sqrt(V4err_Pb[i]*V4err_Pb[i]+V4err_Pb[nref]*V4err_Pb[nref]*V0_Pb[nref]*V0_Pb[nref]/V0_Pb[i]/V0_Pb[i]);
    V5suberr_Pb[i] = sqrt(V5err_Pb[i]*V5err_Pb[i]+V5err_Pb[nref]*V5err_Pb[nref]*V0_Pb[nref]*V0_Pb[nref]/V0_Pb[i]/V0_Pb[i]);
    V6suberr_Pb[i] = sqrt(V6err_Pb[i]*V6err_Pb[i]+V6err_Pb[nref]*V6err_Pb[nref]*V0_Pb[nref]*V0_Pb[nref]/V0_Pb[i]/V0_Pb[i]);
    if(V2sub_Pb[i] && fabs(V2sub_Pb[i]/V2suberr_Pb[i])>2) v2sub_Pb[i]=sqrt(V2sub_Pb[i]);
    if(V3sub_Pb[i] && fabs(V3sub_Pb[i]/V3suberr_Pb[i])>2) v3sub_Pb[i]=sqrt(V3sub_Pb[i]);
    if(V4sub_Pb[i] && fabs(V4sub_Pb[i]/V4suberr_Pb[i])>2) v4sub_Pb[i]=sqrt(V4sub_Pb[i]);
    if(V5sub_Pb[i] && fabs(V5sub_Pb[i]/V5suberr_Pb[i])>2) v5sub_Pb[i]=sqrt(V5sub_Pb[i]);
    if(V6sub_Pb[i] && fabs(V6sub_Pb[i]/V6suberr_Pb[i])>2) v6sub_Pb[i]=sqrt(V6sub_Pb[i]);
    if(V2sub_Pb[i] && fabs(V2sub_Pb[i]/V2suberr_Pb[i])>2) v2suberr_Pb[i]=0.5*v2sub_Pb[i]*V2suberr_Pb[i]/V2sub_Pb[i];
    if(V3sub_Pb[i] && fabs(V3sub_Pb[i]/V3suberr_Pb[i])>2) v3suberr_Pb[i]=0.5*v3sub_Pb[i]*V3suberr_Pb[i]/V3sub_Pb[i];
    if(V4sub_Pb[i] && fabs(V4sub_Pb[i]/V4suberr_Pb[i])>2) v4suberr_Pb[i]=0.5*v4sub_Pb[i]*V4suberr_Pb[i]/V4sub_Pb[i];
    if(V5sub_Pb[i] && fabs(V5sub_Pb[i]/V5suberr_Pb[i])>2) v5suberr_Pb[i]=0.5*v5sub_Pb[i]*V5suberr_Pb[i]/V5sub_Pb[i];
    if(V6sub_Pb[i] && fabs(V6sub_Pb[i]/V6suberr_Pb[i])>2) v6suberr_Pb[i]=0.5*v6sub_Pb[i]*V6suberr_Pb[i]/V6sub_Pb[i];
   }
  }

  TCanvas* c = new TCanvas("c","c",1200,1200);
  c->Divide(4,4);
  for(int i=10;i<25;i++)
  {
    c->cd(i-9);
    hdphi_short[i]->Draw("PE");
  }  

  TCanvas* cclow = new TCanvas("cclow","cclow",1200,1200);
  cclow->Divide(4,4);
  for(int i=0;i<10;i++)
  {
    cclow->cd(i+1);
    hdphi_short_zyam[i]->SetAxisRange(-PI/2+0.1,3*PI/2-0.1);
    hdphi_short_zyam[i]->Draw("PE");
  }
  TCanvas* cc = new TCanvas("cc","cc",1200,1200);
  cc->Divide(4,4);
  for(int i=10;i<25;i++)
  {
    cc->cd(i-9);
    hdphi_short_zyam[i]->SetAxisRange(-PI/2+0.1,3*PI/2-0.1);
    hdphi_short_zyam[i]->Draw("PE");
  }

  TCanvas* cclow_Pb = new TCanvas("cclow_Pb","cclow_Pb",1200,1200);
  cclow_Pb->Divide(4,4);
  for(int i=0;i<10;i++)
  {
    cclow_Pb->cd(i+1);
    hdphi_short_zyam_Pb[i]->SetAxisRange(-PI/2+0.1,3*PI/2-0.1);
    hdphi_short_zyam_Pb[i]->Draw("PE");
  }
  TCanvas* cc_Pb = new TCanvas("cc_Pb","cc_Pb",1200,1200);
  cc_Pb->Divide(4,4);
  for(int i=10;i<25;i++)
  {
    cc_Pb->cd(i-9);
    hdphi_short_zyam_Pb[i]->SetAxisRange(-PI/2+0.1,3*PI/2-0.1);
    hdphi_short_zyam_Pb[i]->Draw("PE");
  }

  int n=25;
  TGraphErrors* gr_V1 = new TGraphErrors(n,nmult,V1,nmulterr,V1err); 
  TGraphErrors* gr_V2 = new TGraphErrors(n,nmult,V2,nmulterr,V2err);
  TGraphErrors* gr_V3 = new TGraphErrors(n,nmult,V3,nmulterr,V3err);
  TGraphErrors* gr_V4 = new TGraphErrors(n,nmult,V4,nmulterr,V4err);
  TGraphErrors* gr_V5 = new TGraphErrors(n,nmult,V5,nmulterr,V5err);
  TGraphErrors* gr_V6 = new TGraphErrors(n,nmult,V6,nmulterr,V6err);

  TGraphErrors* gr_v2 = new TGraphErrors(n,nmult,v2,nmulterr,v2err);
  TGraphErrors* gr_v3 = new TGraphErrors(n,nmult,v3,nmulterr,v3err);
  TGraphErrors* gr_v4 = new TGraphErrors(n,nmult,v4,nmulterr,v4err);
  TGraphErrors* gr_v5 = new TGraphErrors(n,nmult,v5,nmulterr,v5err);
  TGraphErrors* gr_v6 = new TGraphErrors(n,nmult,v6,nmulterr,v6err);

  TGraphErrors* gr_PbPb_V1 = new TGraphErrors(n,nmult_Pb,V1_Pb,nmulterr_Pb,V1err_Pb);
  TGraphErrors* gr_PbPb_V2 = new TGraphErrors(n,nmult_Pb,V2_Pb,nmulterr_Pb,V2err_Pb);
  TGraphErrors* gr_PbPb_V3 = new TGraphErrors(n,nmult_Pb,V3_Pb,nmulterr_Pb,V3err_Pb);
  TGraphErrors* gr_PbPb_V4 = new TGraphErrors(n,nmult_Pb,V4_Pb,nmulterr_Pb,V4err_Pb);
  TGraphErrors* gr_PbPb_V5 = new TGraphErrors(n,nmult_Pb,V5_Pb,nmulterr_Pb,V5err_Pb);
  TGraphErrors* gr_PbPb_V6 = new TGraphErrors(n,nmult_Pb,V6_Pb,nmulterr_Pb,V6err_Pb);

  TGraphErrors* gr_PbPb_v2 = new TGraphErrors(n,nmult_Pb,v2_Pb,nmulterr_Pb,v2err_Pb);
  TGraphErrors* gr_PbPb_v3 = new TGraphErrors(n,nmult_Pb,v3_Pb,nmulterr_Pb,v3err_Pb);
  TGraphErrors* gr_PbPb_v4 = new TGraphErrors(n,nmult_Pb,v4_Pb,nmulterr_Pb,v4err_Pb);
  TGraphErrors* gr_PbPb_v5 = new TGraphErrors(n,nmult_Pb,v5_Pb,nmulterr_Pb,v5err_Pb);
  TGraphErrors* gr_PbPb_v6 = new TGraphErrors(n,nmult_Pb,v6_Pb,nmulterr_Pb,v6err_Pb);

  TGraphErrors* gr_V1sub = new TGraphErrors(n,nmult,V1sub,nmulterr,V1suberr);
  TGraphErrors* gr_V2sub = new TGraphErrors(n,nmult,V2sub,nmulterr,V2suberr);
  TGraphErrors* gr_V3sub = new TGraphErrors(n,nmult,V3sub,nmulterr,V3suberr);
  TGraphErrors* gr_V4sub = new TGraphErrors(n,nmult,V4sub,nmulterr,V4suberr);
  TGraphErrors* gr_V5sub = new TGraphErrors(n,nmult,V5sub,nmulterr,V5suberr);
  TGraphErrors* gr_V6sub = new TGraphErrors(n,nmult,V6sub,nmulterr,V6suberr);

  TGraphErrors* gr_v2sub = new TGraphErrors(n,nmult,v2sub,nmulterr,v2suberr);
  TGraphErrors* gr_v3sub = new TGraphErrors(n,nmult,v3sub,nmulterr,v3suberr);
  TGraphErrors* gr_v4sub = new TGraphErrors(n,nmult,v4sub,nmulterr,v4suberr);
  TGraphErrors* gr_v5sub = new TGraphErrors(n,nmult,v5sub,nmulterr,v5suberr);
  TGraphErrors* gr_v6sub = new TGraphErrors(n,nmult,v6sub,nmulterr,v6suberr);

  TGraphErrors* gr_PbPb_V1sub = new TGraphErrors(n,nmult_Pb,V1sub_Pb,nmulterr_Pb,V1suberr_Pb);
  TGraphErrors* gr_PbPb_V2sub = new TGraphErrors(n,nmult_Pb,V2sub_Pb,nmulterr_Pb,V2suberr_Pb);
  TGraphErrors* gr_PbPb_V3sub = new TGraphErrors(n,nmult_Pb,V3sub_Pb,nmulterr_Pb,V3suberr_Pb);
  TGraphErrors* gr_PbPb_V4sub = new TGraphErrors(n,nmult_Pb,V4sub_Pb,nmulterr_Pb,V4suberr_Pb);
  TGraphErrors* gr_PbPb_V5sub = new TGraphErrors(n,nmult_Pb,V5sub_Pb,nmulterr_Pb,V5suberr_Pb);
  TGraphErrors* gr_PbPb_V6sub = new TGraphErrors(n,nmult_Pb,V6sub_Pb,nmulterr_Pb,V6suberr_Pb);

  TGraphErrors* gr_PbPb_v2sub = new TGraphErrors(n,nmult_Pb,v2sub_Pb,nmulterr_Pb,v2suberr_Pb);
  TGraphErrors* gr_PbPb_v3sub = new TGraphErrors(n,nmult_Pb,v3sub_Pb,nmulterr_Pb,v3suberr_Pb);
  TGraphErrors* gr_PbPb_v4sub = new TGraphErrors(n,nmult_Pb,v4sub_Pb,nmulterr_Pb,v4suberr_Pb);
  TGraphErrors* gr_PbPb_v5sub = new TGraphErrors(n,nmult_Pb,v5sub_Pb,nmulterr_Pb,v5suberr_Pb);
  TGraphErrors* gr_PbPb_v6sub = new TGraphErrors(n,nmult_Pb,v6sub_Pb,nmulterr_Pb,v6suberr_Pb);

  TGraph* gr_jetyield_ratio = new TGraph(n,nmult,jetyield_ratio);
  TGraph* gr_PbPb_jetyield_ratio = new TGraph(n,nmult_Pb,jetyield_ratio_Pb);

  TCanvas* c_gr = new TCanvas("c_gr","c_gr",500,500);
  gr_jetyield_ratio->SetMarkerStyle(20);
  gr_PbPb_jetyield_ratio->SetMarkerStyle(24);
  gr_PbPb_jetyield_ratio->Draw("AP");
  gr_jetyield_ratio->Draw("PESAME");

  gr_V1->SetMarkerSize(1.8);
  gr_V2->SetMarkerSize(1.8);
  gr_V3->SetMarkerSize(2.0);
  gr_V4->SetMarkerSize(1.8);
  gr_V5->SetMarkerSize(2.4);
  gr_V6->SetMarkerSize(2.);

  gr_v2->SetMarkerSize(1.5);
  gr_v3->SetMarkerSize(1.5);
  gr_v4->SetMarkerSize(1.5);
  gr_v5->SetMarkerSize(1.5);
  gr_v6->SetMarkerSize(1.5);

  gr_v2sub->SetMarkerSize(1.5);
  gr_v3sub->SetMarkerSize(1.5);
  gr_v4sub->SetMarkerSize(1.5);
  gr_v5sub->SetMarkerSize(1.5);
  gr_v6sub->SetMarkerSize(1.5);

  gr_V1->SetMarkerStyle(24);
  gr_V2->SetMarkerStyle(20);
  gr_V3->SetMarkerStyle(22);
  gr_V4->SetMarkerStyle(21);
  gr_V5->SetMarkerStyle(29);
  gr_V6->SetMarkerStyle(28);

  gr_v2->SetMarkerStyle(27);
  gr_v3->SetMarkerStyle(27);
  gr_v4->SetMarkerStyle(27);
  gr_v5->SetMarkerStyle(27);
  gr_v6->SetMarkerStyle(27);

  gr_v2sub->SetMarkerStyle(20);
  gr_v3sub->SetMarkerStyle(20);
  gr_v4sub->SetMarkerStyle(20);
  gr_v5sub->SetMarkerStyle(20);
  gr_v6sub->SetMarkerStyle(20);

  gr_V1->SetMarkerColor(1);
  gr_V2->SetMarkerColor(2);
  gr_V3->SetMarkerColor(kGreen+2);
  gr_V4->SetMarkerColor(4);
  gr_V5->SetMarkerColor(6);
  gr_V6->SetMarkerColor(1);

  gr_v2->SetMarkerColor(2);
  gr_v3->SetMarkerColor(2);
  gr_v4->SetMarkerColor(2);
  gr_v5->SetMarkerColor(2);
  gr_v6->SetMarkerColor(2);

  gr_v2sub->SetMarkerColor(2);
  gr_v3sub->SetMarkerColor(2);
  gr_v4sub->SetMarkerColor(2);
  gr_v5sub->SetMarkerColor(2);
  gr_v6sub->SetMarkerColor(2);

  gr_PbPb_V1->SetMarkerSize(1.8);
  gr_PbPb_V2->SetMarkerSize(1.8);
  gr_PbPb_V3->SetMarkerSize(2.0);
  gr_PbPb_V4->SetMarkerSize(1.8);
  gr_PbPb_V5->SetMarkerSize(2.4);
  gr_PbPb_V6->SetMarkerSize(2.);

  gr_PbPb_v2->SetMarkerSize(1.5);
  gr_PbPb_v3->SetMarkerSize(1.5);
  gr_PbPb_v4->SetMarkerSize(1.5);
  gr_PbPb_v5->SetMarkerSize(1.5);
  gr_PbPb_v6->SetMarkerSize(1.5);

  gr_PbPb_v2sub->SetMarkerSize(1.5);
  gr_PbPb_v3sub->SetMarkerSize(1.5);
  gr_PbPb_v4sub->SetMarkerSize(1.5);
  gr_PbPb_v5sub->SetMarkerSize(1.5);
  gr_PbPb_v6sub->SetMarkerSize(1.5);

  gr_PbPb_V1->SetMarkerStyle(24);
  gr_PbPb_V2->SetMarkerStyle(24);
  gr_PbPb_V3->SetMarkerStyle(26);
  gr_PbPb_V4->SetMarkerStyle(25);
  gr_PbPb_V5->SetMarkerStyle(30);
  gr_PbPb_V6->SetMarkerStyle(28);

  gr_PbPb_v2->SetMarkerStyle(26);
  gr_PbPb_v3->SetMarkerStyle(26);
  gr_PbPb_v4->SetMarkerStyle(26);
  gr_PbPb_v5->SetMarkerStyle(26);
  gr_PbPb_v6->SetMarkerStyle(26);

  gr_PbPb_v2sub->SetMarkerStyle(25);
  gr_PbPb_v3sub->SetMarkerStyle(25);
  gr_PbPb_v4sub->SetMarkerStyle(25);
  gr_PbPb_v5sub->SetMarkerStyle(25);
  gr_PbPb_v6sub->SetMarkerStyle(25);

  gr_PbPb_V1->SetMarkerColor(4);
  gr_PbPb_V2->SetMarkerColor(4);
  gr_PbPb_V3->SetMarkerColor(4);
  gr_PbPb_V4->SetMarkerColor(4);
  gr_PbPb_V5->SetMarkerColor(4);
  gr_PbPb_V6->SetMarkerColor(4);

  gr_PbPb_v2->SetMarkerColor(4);
  gr_PbPb_v3->SetMarkerColor(4);
  gr_PbPb_v4->SetMarkerColor(4);
  gr_PbPb_v5->SetMarkerColor(4);
  gr_PbPb_v6->SetMarkerColor(4);

  gr_PbPb_v2sub->SetMarkerColor(4);
  gr_PbPb_v3sub->SetMarkerColor(4);
  gr_PbPb_v4sub->SetMarkerColor(4);
  gr_PbPb_v5sub->SetMarkerColor(4);
  gr_PbPb_v6sub->SetMarkerColor(4);

  TFile* fout = new TFile("pPbPbp8TeV_v2v3v4_vsN_dz01_NoHighPU1.root","recreate");
  gr_v2->Write("hadronv2");
  gr_v3->Write("hadronv3");
  gr_v4->Write("hadronv4");
  gr_v2sub->Write("hadronv2sub");
  gr_v3sub->Write("hadronv3sub");
  gr_v4sub->Write("hadronv4sub");
  gr_V2->Write("hadronV2");
  gr_V3->Write("hadronV3");
  gr_V4->Write("hadronV4");
  gr_V2sub->Write("hadronV2sub");
  gr_V3sub->Write("hadronV3sub");
  gr_V4sub->Write("hadronV4sub");
  fout->Close();

/*
  TFile* fout1 = new TFile("PbPb5TeV_v2v3v4_vsN_N020sub.root","recreate");
  gr_PbPb_v2->Write("hadronv2");
  gr_PbPb_v3->Write("hadronv3");
  gr_PbPb_v4->Write("hadronv4");
  gr_PbPb_v2sub->Write("hadronv2sub");
  gr_PbPb_v3sub->Write("hadronv3sub");
  gr_PbPb_v4sub->Write("hadronv4sub");
  gr_PbPb_V2->Write("hadronV2");
  gr_PbPb_V3->Write("hadronV3");
  gr_PbPb_V4->Write("hadronV4");
  gr_PbPb_V2sub->Write("hadronV2sub");
  gr_PbPb_V3sub->Write("hadronV3sub");
  gr_PbPb_V4sub->Write("hadronV4sub");
  fout1->Close();
*/
  TH2D* htmp = new TH2D("htmp",";N_{trk}^{offline};V_{n}(2, |#Delta#eta|>2)",1000,0,500,1000,-0.01,0.01);
  TH2D* htmp1 = new TH2D("htmp1",";N_{trk}^{offline};v_{n}(2, |#Delta#eta|>2)",1000,0,500,1000,0.001,0.112);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->GetXaxis()->SetTitleOffset(1.2); 
  htmp->GetYaxis()->SetTitleOffset(1.2);
  htmp->GetXaxis()->SetTitleSize(0.05);
  htmp->GetYaxis()->SetTitleSize(0.05);
  htmp1->GetXaxis()->CenterTitle();
  htmp1->GetYaxis()->CenterTitle();
  htmp1->GetXaxis()->SetTitleOffset(1.2);
  htmp1->GetYaxis()->SetTitleOffset(1.2);
  htmp1->GetXaxis()->SetTitleSize(0.05);
  htmp1->GetYaxis()->SetTitleSize(0.05);

  TCanvas* c1 = new TCanvas("c1","c1",800,600);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.1);
  htmp->Draw();
//  gr_PbPb_V1->Draw("PESAME");
//  gr_PbPb_V2->Draw("PESAME");
//  gr_PbPb_V3->Draw("PESAME");
  gr_PbPb_V4->Draw("PESAME");
  gr_PbPb_V4sub->SetMarkerStyle(20);
  gr_PbPb_V4sub->Draw("PESAME");
//  gr_PbPb_V5->Draw("PESAME");
//  gr_PbPb_V6->Draw("PESAME");

  TCanvas* c2 = new TCanvas("c2","c2",800,600);
  c2->SetLeftMargin(0.15);
  c2->SetBottomMargin(0.15);
  htmp1->Draw();
  gr_v2->Draw("PESAME");
  gr_v3->Draw("PESAME");
  gr_v4->Draw("PESAME");
  gr_v5->Draw("PESAME");
//  gr_v6->Draw("PESAME");
  
  TLegend* ll = new TLegend(0.17,0.73,0.32,0.88);
  ll->SetNColumns(2);
  ll->SetBorderSize(0);
  ll->SetFillStyle(0);
  ll->AddEntry(gr_v2,"v_{2}","P");
  ll->AddEntry(gr_v5,"v_{5}","P");
  ll->AddEntry(gr_v3,"v_{3}","P");
//  ll->AddEntry(gr_v6,"v_{6}","P");
  ll->AddEntry(gr_v4,"v_{4}","P");
  ll->Draw("P");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->DrawLatex(0.15,0.92,"CMS pPb #sqrt{s_{NN}} = 8.16 TeV, L_{int} = 64 nb^{-1}");
  latex->DrawLatex(0.67,0.85,"0.3 < p_{T} < 3 GeV/c");

//  c2->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_pPb_Golden_dz01_v8.gif");
//  c2->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_pPb_Golden_dz01_v8.pdf");

  TCanvas* c22 = new TCanvas("c22","c22",800,600);
  c22->SetLeftMargin(0.15);
  c22->SetBottomMargin(0.15);
  htmp1->Draw();
  gr_PbPb_v2->Draw("PESAME");
  gr_PbPb_v3->Draw("PESAME");
  gr_PbPb_v4->Draw("PESAME");
  gr_PbPb_v5->Draw("PESAME");
//  gr_PbPb_v6->Draw("PESAME");

  TLegend* lll = new TLegend(0.17,0.73,0.32,0.88);
  lll->SetNColumns(2);
  lll->SetBorderSize(0);
  lll->SetFillStyle(0);
  lll->AddEntry(gr_PbPb_v2,"v_{2}","P");
  lll->AddEntry(gr_PbPb_v5,"v_{5}","P");
  lll->AddEntry(gr_PbPb_v3,"v_{3}","P");
//  lll->AddEntry(gr_PbPb_v6,"v_{6}","P");
  lll->AddEntry(gr_PbPb_v4,"v_{4}","P");
  lll->Draw("P");

  TLatex* latex1 = new TLatex();
  latex1->SetNDC();
  latex1->SetTextSize(0.04);
  latex1->DrawLatex(0.15,0.92,"CMS PbPb #sqrt{s_{NN}} = 5.02 TeV");
  latex1->DrawLatex(0.67,0.85,"0.3 < p_{T} < 3 GeV/c");

//  c22->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_PbPb2015_Golden_v1.gif");
//  c22->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_PbPb2015_Golden_v1.pdf");


  TCanvas* c3 = new TCanvas("c3","c3",1200,400);
  c3->Divide(3,1);
  c3->cd(1);
  c3->GetPad(1)->SetLeftMargin(0.15);
  c3->GetPad(1)->SetBottomMargin(0.13);
  c3->GetPad(1)->SetRightMargin(0.005);
  c3->GetPad(1)->SetTopMargin(0.02);
  TH2D* htmp11 = new TH2D("htmp11",";N_{trk}^{offline};v_{2}(2, |#Delta#eta|>2)",1000,0,505,1000,0.0001,0.122);
  htmp11->GetXaxis()->SetTitleOffset(1.1);
  htmp11->GetYaxis()->SetTitleOffset(1.4);
  htmp11->GetXaxis()->CenterTitle();
  htmp11->GetYaxis()->CenterTitle();
  htmp11->GetXaxis()->SetTitleSize(0.053);
  htmp11->GetYaxis()->SetTitleSize(0.053);
  htmp11->Draw();
  gr_v2sub->Draw("PESAME");
  gr_PbPb_v2sub->Draw("PESAME");
  gr_v2->Draw("LSAME");
  gr_PbPb_v2->Draw("LSAME");
  c3->cd(2);
  c3->GetPad(2)->SetLeftMargin(0.15);
  c3->GetPad(2)->SetBottomMargin(0.13);
  c3->GetPad(2)->SetRightMargin(0.005);
  c3->GetPad(2)->SetTopMargin(0.02);
  TH2D* htmp22 = new TH2D("htmp22",";N_{trk}^{offline};v_{3}(2, |#Delta#eta|>2)",1000,0,505,1000,0.0001,0.04);
  htmp22->GetXaxis()->SetTitleOffset(1.1);
  htmp22->GetYaxis()->SetTitleOffset(1.4);
  htmp22->GetXaxis()->CenterTitle();
  htmp22->GetYaxis()->CenterTitle();
  htmp22->GetXaxis()->SetTitleSize(0.053);
  htmp22->GetYaxis()->SetTitleSize(0.053);
  htmp22->Draw();
//  gr_v3sub->Draw("PESAME");
//  gr_PbPb_v3sub->Draw("PESAME");
  gr_PbPb_v3sub->Draw("PESAME");
  gr_PbPb_v3->Draw("PESAME");
  c3->cd(3);
  c3->GetPad(3)->SetLeftMargin(0.15);
  c3->GetPad(3)->SetBottomMargin(0.13);
  c3->GetPad(3)->SetRightMargin(0.005);
  c3->GetPad(3)->SetTopMargin(0.02);
  TH2D* htmp33 = new TH2D("htmp33",";N_{trk}^{offline};v_{4}(2, |#Delta#eta|>2)",1000,0,505,1000,0.0001,0.02);
  htmp33->GetXaxis()->SetTitleOffset(1.1);
  htmp33->GetYaxis()->SetTitleOffset(1.4);
  htmp33->GetXaxis()->CenterTitle();
  htmp33->GetYaxis()->CenterTitle();
  htmp33->GetXaxis()->SetTitleSize(0.053);
  htmp33->GetYaxis()->SetTitleSize(0.053);
  htmp33->Draw();
//  gr_v4sub->Draw("PESAME");
//  gr_PbPb_v4sub->Draw("PESAME");
  gr_PbPb_v4sub->Draw("PESAME");
  gr_PbPb_v4->Draw("PESAME");

/*
  c3->cd(4);
  c3->GetPad(4)->SetLeftMargin(0.15);
  c3->GetPad(4)->SetBottomMargin(0.15);
  TH2D* htmp44 = new TH2D("htmp44",";N_{trk}^{offline};v_{5}(2, |#Delta#eta|>2)",1000,0,500,1000,0.0001,0.01);
  htmp44->GetXaxis()->SetTitleOffset(1.5);
  htmp44->GetYaxis()->SetTitleOffset(1.5);
  htmp44->Draw();
  gr_v5->Draw("PESAME");
  gr_PbPb_v5->Draw("PESAME");
*/

  double nmult_pPb5[18] = {6.917, 14.37, 24.41, 34.39, 44.36, 54.33, 68.63, 88.39, 108.2, 131.3, 162.1, 196.6, 227.5, 247.2, 267.1, 287, 306.8, 328.6};
  double nmulterr_pPb5[18] = {0};
  double v2_pPb5[18] = {0.05367, 0.05428, 0.05379, 0.05501, 0.05651, 0.05814, 0.06038, 0.0629, 0.06421, 0.06633, 0.06777, 0.06887, 0.06927, 0.0697, 0.06977, 0.06896, 0.06706, 0.06621};
  double v2err_pPb5[18] = {0.001655, 0.0006222, 0.0003994, 0.0002977, 0.0002436, 0.0002135, 0.0001381, 0.0001397, 0.0001624, 4.268e-05, 3.212e-05, 2.831e-05, 4.645e-05, 8.416e-05, 0.0001636, 0.0003366, 0.000741, 0.00147};
  double v3_pPb5[18] = {0, 0, 0, 0, 0, 0.004507, 0.009104, 0.01335, 0.01606, 0.01767, 0.02009, 0.0219, 0.02328, 0.02384, 0.02476, 0.02639, 0.02402, 0.02182};
  double v3err_pPb5[18] = {0, 0, 0, 0, 0, 0.002763, 0.0009177, 0.0006602, 0.000651, 0.0001609, 0.0001087, 8.923e-05, 0.0001385, 0.0002466, 0.0004619, 0.0008825, 0.002072, 0.004465};

  TGraphErrors* gr_pPb5_v2 = new TGraphErrors(18,nmult_pPb5,v2_pPb5,nmulterr_pPb5,v2err_pPb5);
  TGraphErrors* gr_pPb5_v3 = new TGraphErrors(18,nmult_pPb5,v3_pPb5,nmulterr_pPb5,v3err_pPb5);
  gr_pPb5_v2->SetMarkerStyle(24);
  gr_pPb5_v3->SetMarkerStyle(24);
  gr_pPb5_v2->SetMarkerColor(1);
  gr_pPb5_v3->SetMarkerColor(1);
  gr_pPb5_v2->SetMarkerSize(1.5);
  gr_pPb5_v3->SetMarkerSize(1.5);

//  c3->cd(1);
//  gr_pPb5_v2->Draw("PESAME");
//  c3->cd(2);
//  gr_pPb5_v3->Draw("PESAME");
//  c3->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_pPbVsPbPb2015_v1.gif");
//  c3->Print("/net/hisrv0001/home/davidlw/pic/pPb/8TeV/vnn_pPbVsPbPb2015_v1.pdf");
}
