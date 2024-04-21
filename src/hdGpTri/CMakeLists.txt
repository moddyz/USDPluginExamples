file(GLOB CPPFILES *.cpp)

usd_plugin(hdGpTri

    CPPFILES
        ${CPPFILES}

    LIBRARIES
        arch
        js
        plug
        tf
        sdf
        vt
        gf
        hd
        hf
        hdGp

    RESOURCE_FILES
        plugInfo.json
)
