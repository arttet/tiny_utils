#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import platform

from conans import tools, ConanFile, CMake


class UtilsConan(ConanFile):
    name = "tiny-utils"
    version = "1.0.0"
    description = "Modern C++ Idioms"
    homepage = "https://github.com/arttet/tiny_utils"
    license = "MIT"
    author = "Artyom Tetyukhin"
    settings = "os", "arch", "compiler", "build_type"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],

        "header_only": [True, False],

        "clang_tidy": "ANY",
        "cppcheck": "ANY",
        "cpplint": "ANY",
        "iwyu": "ANY",

        "with_doc": [True, False],
        "with_tests": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,

        "header_only": True,

        "clang_tidy": "",
        "cppcheck": "",
        "cpplint": "",
        "iwyu": "",

        "with_doc": False,
        "with_tests": False,
    }

    generators = "cmake"
    build_policy = "missing"
    exports_sources = "include*"

    def requirements(self):
        if self.options.header_only:
            return

        self.requires("gtest/1.10.0")

    def config_options(self):
        if self.options.header_only:
            return

        self.options["gtest"].shared = self.options.shared
        self.options["gtest"].build_gmock = False

        if self.settings.build_type == "Debug":
            self.options["gtest"].debug_postfix = ''

        if self.settings.os == "Windows":
            del self.options.fPIC

    def cmake_configure(self):
        cmake = CMake(self)

        cmake.definitions["WITH_DOC"] = self.options.with_doc

        if self.options.header_only:
            return cmake

        if self.options.clang_tidy:
            cmake.definitions["CMAKE_CXX_CLANG_TIDY"] = self.options.clang_tidy

        if self.options.cppcheck:
            cmake.definitions["CMAKE_CXX_CPPCHECK"] = self.options.cppcheck

        if self.options.cpplint:
            cmake.definitions["CMAKE_CXX_CPPLINT"] = self.options.cpplint

        if self.options.iwyu:
            cmake.definitions["CMAKE_CXX_INCLUDE_WHAT_YOU_USE"] = self.options.iwyu

        cmake.definitions["WITH_TESTS"] = self.options.with_tests

        return cmake

    def build(self):
        cmake = self.cmake_configure()

        cmake.configure()
        cmake.build()
