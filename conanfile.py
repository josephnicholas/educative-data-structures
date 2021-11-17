from conans import ConanFile


class EducativeDataStructures(ConanFile):
    name = "EducativeDataStructures"
    version = "0.0.1"
    requires = (
        "catch2/2.13.7",
    )
    generators = "cmake", "gcc", "txt", "cmake_find_package"
