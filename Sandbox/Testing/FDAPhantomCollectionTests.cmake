
SET(COLLECTION_PATH ${TEST_FDA_DATA_ROOT} )

MACRO(TEST_FDA_PHANTOM_DATASET MASTER_DATASET_ID DATASET_ID ROI_X ROI_Y ROI_Z ROI_DX ROI_DY ROI_DZ EXPECTED_VOLUME)

SET(COLLECTION_PATH ${TEST_FDA_DATA_ROOT} )
SET(DATASET_ROI ${TEMP}/${DATASET_ID}_ROI.mha)

EXTRACT_REGION_OF_INTEREST(${MASTER_DATASET_ID} ${DATASET_ID} ${ROI_X} ${ROI_Y} ${ROI_Z} ${ROI_DX} ${ROI_DY} ${ROI_DZ} )
GENERATE_FEATURES( ${DATASET_ID} )
SCREEN_SHOT_FEATURES(  ${DATASET_ID} 001 )
COMPUTE_SEGMENTATIONS( ${DATASET_ID} 001 ${EXPECTED_VOLUME})

ENDMACRO(TEST_FDA_PHANTOM_DATASET)


CONVERT_DICOM_TO_META( ${COLLECTION_PATH} FDA_A "Yamamoto-018/25ma1/3632/6591" )
CONVERT_DICOM_TO_META( ${COLLECTION_PATH} FDA_B "Yamamoto-018/25ma1/3632/6593" )
CONVERT_DICOM_TO_META( ${COLLECTION_PATH} FDA_C "Yamamoto-019/100ma1/3650/7001" )
CONVERT_DICOM_TO_META( ${COLLECTION_PATH} FDA_D "Yamamoto-019/100ma1/3650/7003" )
CONVERT_DICOM_TO_META( ${COLLECTION_PATH} FDA_E "Yamamoto-020/yamamot/3688/7471" )

# "raida/mag4/phantom_studies/Yamamoto-018/25ma1/3632/6591"
# Contains 3 nodules of 5 mm, 10mm, 8mm on the right side of the image (left 
# side of the patient) at 100 HU. The dataset has an interslice spacing of .4mm
# Exposure 25mA

TEST_FDA_PHANTOM_DATASET(FDA_A FDA_A_01 
  370 250 320 
   60  50  70
  452.83
  )

TEST_FDA_PHANTOM_DATASET(FDA_A FDA_A_02 
  330 260 500 
   50  40  70
  226.01
  )

TEST_FDA_PHANTOM_DATASET(FDA_A FDA_A_03 
  320 310 120 
   30  40  70
  56.38
  )

# "raida/mag4/phantom_studies/Yamamoto-018/25ma1/3632/6593"
# Contains 3 nodules of 5 mm, 10mm, 8mm on the right side of the image (left 
# side of the patient) at 100 HU. The dataset has an interslice spacing of 1.5mm
# Exposure 25mA

TEST_FDA_PHANTOM_DATASET(FDA_B FDA_B_01
  317 315 31
  39 32 23
  56.38 # 5mm 
  )

TEST_FDA_PHANTOM_DATASET(FDA_B FDA_B_02
  371 248 77
  55 54 33
  452.83 # 10 mm
  )

TEST_FDA_PHANTOM_DATASET(FDA_B FDA_B_03
  333 260 127
  37 40 30
  226.01 # 8 mm
  )

# "raida/mag4/phantom_studies/Yamamoto-019/100ma1/3650/7001/"
# Contains 3 nodules of 5 mm, 10mm, 8mm on the right side of the image (left 
# side of the patient) at 100 HU. The dataset has an interslice spacing of .4mm
# Exposure 100mA

TEST_FDA_PHANTOM_DATASET(FDA_C FDA_C_01
  308 314 111
  35 34 73
  56.38 # 5mm 
  )

TEST_FDA_PHANTOM_DATASET(FDA_C FDA_C_02
  371 261 309
  32 36 74
  452.83 # 10 mm
  )

TEST_FDA_PHANTOM_DATASET(FDA_C FDA_C_03
  332 266 502
  32 34 75
  226.01 # 8 mm
  )

# "raida/mag4/phantom_studies/Yamamoto-019/100ma1/3650/7003/"
# Contains 3 nodules of 5 mm, 10mm, 8mm on the right side of the image (left 
# side of the patient) at 100 HU. The dataset has an interslice spacing of 1.5mm
# Exposure 100mA

TEST_FDA_PHANTOM_DATASET(FDA_D FDA_D_01
  310 319 32
  29 25 18
  56.38 # 5mm 
  )

TEST_FDA_PHANTOM_DATASET(FDA_D FDA_D_02
  372 264 81
  33 28 23
  452.83 # 10 mm
  )

TEST_FDA_PHANTOM_DATASET(FDA_D FDA_D_03
  332 266 133
  32 31 22
  226.01 # 8 mm
  )

# "raida/mag4/phantom_studies/Yamamoto-020/yamamot/3688/7471"
# Contains 3 nodules of 5 mm, 10mm, 8mm on the right side of the image (left 
# side of the patient) at 100 HU. The dataset has an interslice spacing of .4mm
# Exposure 200mA

TEST_FDA_PHANTOM_DATASET(FDA_E FDA_E_01
  334 316 131
  18 19 54
  56.38 # 5mm 
  )

TEST_FDA_PHANTOM_DATASET(FDA_E FDA_E_02
  388 255 316
  34 27 78
  452.83 # 10 mm
  )

TEST_FDA_PHANTOM_DATASET(FDA_E FDA_E_03
  347 260 517
  31 31 73
  226.01 # 8 mm
  )

