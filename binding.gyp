{
  "targets": [
    {
      "target_name": "RGBModule",
      "sources": [ "RGBModule.cpp","RGBWrapper.cpp",
      "src/Modules/RGBLEDs/RGBLEDs.cpp",
      "src/Libraries/PCA9685/PCA9685.cpp",
      "src/Libraries/Timer/AccurateTiming.cpp",
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
