macro(FindCoreSystemPackages)
    find_package(Boost REQUIRED COMPONENTS system filesystem thread beast)
    find_package(fmt CONFIG REQUIRED)
    find_package(SQLiteCpp REQUIRED)
    find_package(nlohmann_json CONFIG REQUIRED)
    find_package(OpenSSL REQUIRED)

    # These are core libraries that are used by all targets and should be included as targeted linked libraries
    list(APPEND AP_LIBRARIES
            fmt::fmt
            SQLiteCpp
            nlohmann_json::nlohmann_json
            OpenSSL::SSL
            OpenSSL::Crypto
            ${Boost_LIBRARIES}
    )
endmacro()

macro(add_subdirectory_and_link_libs subdirectory)
    add_subdirectory(${subdirectory})
    target_link_libraries(${subdirectory} PRIVATE ${AP_LIBRARIES})
endmacro()
