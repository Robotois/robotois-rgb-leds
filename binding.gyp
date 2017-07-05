{
  "targets": [
    {
      "target_name": "RGBModule",
      "sources": [
            "src/wrapper/RGBModule.cpp",
            "src/wrapper/RGBWrapper.cpp",
            "src/RGBModule.cpp"
        ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
